/*
 * CControlComp.cpp
 *
 *  Created on: Dec 14, 2017
 *      Author: Andreas Diehm, Fabian Stangl
 */

#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include"AComponentBase.h"
#include"Assertion.h"
#include"CBinarySemaphore.h"
#include"CContainer.h"
#include"CMutex.h"
#include"Config.h"
#include"CThread.h"
#include"Global.h"
#include"IRunnable.h"
#include"SContent.h"
#include"SMPU6050Data.h"
#include"SStateVectorData.h"
#include"CControlComp.h"
#include"CCommComp.h"
#include"CBBBHardware.h"
#include<pthread.h>
#include<iostream>
using namespace std;

extern CContainer myContainer;

void CControlComp::init()
{
	mGebewerte.enableMotor();
};

void CControlComp::run()
{

	while(1)
	{


		//Lese Werte aus BBB
		mGebewerte.fetchValues(mAdcWert, mSensor1, mSensor2);

		calibrate();
		filter();
		regler();
	    	//jump();
		motor();

		cout<<"Motormoment: "<<mMotormoment<<endl;
		cout<<"Phi: "<<mPhi_gefiltert<<endl;
		cout<<"Phi_d: "<<mCalSensorGemittelt_mPhi_d<<endl;
		cout<<"Phi_dd: "<<mPhi_dd_Acc<<endl;
		cout<<"Psi_d: "<<mCalPsi_d<<endl<<endl;
		cout<<"Drehzahl:"<<mCalDrehzahl-10000<<endl;
		//Schreibe Werte in Übergabecontainer
		myContainer.writeADCValue(mAdcWert);
		myContainer.writeSensor1Data(mSensor1);
		myContainer.writeSensor2Data(mSensor2);
		myContainer.signalReader();
		usleep(20000);
	}
};


void CControlComp::calibrate()
{
	//Kalibrierung der Sensordaten mit Ausgleichgeraden:

		//Ausgleichsgeraden (Steigung a und Offset b)
		const float a_X1_dd=-0.0005987;
		const float a_Y1_dd=-0.0005911;
		const float a_X2_dd=-0.0006044;
		const float a_Y2_dd=-0.0005991;

		const float b_X1_dd=-0.1142;
		const float b_Y1_dd=-0.1322;
	   	const float b_X2_dd=0.08675;
		const float b_Y2_dd=0.04191;

		//Kalibrierung:
		mCalSensor1.mX__dd=a_X1_dd*(float)mSensor1.mX__dd+b_X1_dd; //[m/s²]
		mCalSensor1.mY__dd=a_Y1_dd*(float)mSensor1.mY__dd+b_Y1_dd; //[m/s²]

		mCalSensor2.mX__dd=a_X2_dd*(float)mSensor2.mX__dd+b_X2_dd; //[m/s²]
		mCalSensor2.mY__dd=a_Y2_dd*(float)mSensor2.mY__dd+b_Y2_dd; //[m/s²]



	//Phi_Accelerometer:

		//Anlegen von Strecken und alpha_acc
		const float rs1=0.14;
		const float rs2=0.061;
		const float alpha_acc=(rs1/rs2);

		//Phi-Berechnung:
		mPhi_Acc=atan2(-(mCalSensor1.mX__dd-alpha_acc*mCalSensor2.mX__dd),mCalSensor1.mY__dd-alpha_acc*mCalSensor2.mY__dd);

		//Phi_dd-Berechnung:
		mPhi_dd_Acc=-(mCalSensor1.mX__dd-mCalSensor2.mX__dd)/(rs1-rs2);


	//Kalibrierung der Motordaten:

		//Umrechnungsfaktor Digital in Drehzahl:
		const float dig2drehzahl=0.2048;

		//Digital zu Drehzahl [1/min]-Umrechung (mit Offset!):
		mCalDrehzahl=(float)mAdcWert/dig2drehzahl;//Mit Offset und [1/min]


		//Offsetangleichung und [1/min] in [rad/s]-Umrechnung:
		const float offsetangleich_n=-10000+92.773438;
		const float drehzahl2psi_d=0.1047197551197;

		mCalPsi_d=(mCalDrehzahl+offsetangleich_n)*drehzahl2psi_d; //[rad/s]


		//Motorspannungsbrechenung (aus Digitalwert):
		const float digi2volt=2275.5;
		const float offsetangleich_volt=-0.89;

		mCalMotorspannung=(float)mAdcWert/digi2volt+offsetangleich_volt;//[V]


	//Kalibrierung des Gyros:

		//Anlegen der Umrechnungsvariablen (aus Datenblatt):
		const float LSB_Gyro=16.4;

		//Berechnung der Kalibrierten Gyro-Werte in [rad/s]:
		mCalSensor1.mPhi__d = (-(1/LSB_Gyro) * (mSensor1.mPhi__d + 0))*(3.14/180); //[rad/s]
		mCalSensor2.mPhi__d = (-(1/LSB_Gyro) * (mSensor2.mPhi__d + 0))*(3.14/180); //[rad/s]

		//Mitteln beider Gyro-Daten:
		mCalSensorGemittelt_mPhi_d=(mCalSensor1.mPhi__d+mCalSensor2.mPhi__d)/2;

};

void CControlComp::filter()
{
	const float alpha=0.98;
	const float T=0.02;

	mPhi_gefiltert=alpha*(mPhi_gefiltert+T*mCalSensorGemittelt_mPhi_d)+(1-alpha)*mPhi_Acc;//[rad]

};

void CControlComp::regler()
{

	const float K[] = {-1.4185F,-0.0954F,-0.0002F}; //{-0.761051959319451F,-0.0694106322056069,-0.000168492222909921};
	float mReglerArray[] = {mPhi_gefiltert,mCalSensorGemittelt_mPhi_d,mCalPsi_d};


	mMotormoment = (-K[0])*mReglerArray[0] + (-K[1])*mReglerArray[1] + (-K[2])*mReglerArray[2];
	
};

void CControlComp::motor()
{
	if((mPhi_Acc<0.2) && (mPhi_Acc>-0.2))
	{
		mGebewerte.setTorque(-mMotormoment);
	}
	else
	{
		mGebewerte.setTorque(0);
	}
};

/*
void CControlComp::jump()
{




	if((mCalDrehzahl-10000>2215) || (mCalDrehzahl-10000<-2215))
	{
		mGebewerte.setTorque(0);
		usleep(5000);
		mGebewerte.closeBrake();
		usleep(20000);
		mJump = 1;
	}
	else
	{
		mGebewerte.setTorque(0.01);

	}


};
*/


