/*
 * CControlComp.h
 *
 *  Created on: Dec 14, 2017
 *      Author: Andreas Diehm
 */

#ifndef CCONTROLCOMP_H_
#define CCONTROLCOMP_H_
#include "IRunnable.h"
#include "CBBBHardware.h"
#include "SMPU6050DataFloat.h"

class CControlComp:public IRunnable
{
	public:
		void run();
		void init();
		void calibrate();
		void filter();
		void regler();
		void motor();
		void jump();
	private:
			CBBBHardware mGebewerte;
			UInt16 mAdcWert;
			SMPU6050Data mSensor1;
			SMPU6050Data mSensor2;
			SMPU6050DataFloat mCalSensor1;
			SMPU6050DataFloat mCalSensor2;
			float mCalDrehzahl;
			float mCalMotorspannung;
			float mPhi_Acc;
			float mPhi_dd_Acc;
			float mPhi_gefiltert;
			float mCalPsi_d;
			float mMotormoment;
			float mCalSensorGemittelt_mPhi_d;
			bool mJump;
};



#endif /* CCONTROLCOMP_H_ */
