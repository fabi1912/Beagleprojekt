/*
 * main.cpp
 *
 *  Created on: Dec 14, 2017
 *      Author: Andreas Diehm
 *
 *
 *
 *
 */

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

#include<pthread.h>
#include<iostream>
using namespace std;

CContainer myContainer;

int main()
{
	CCommComp commklasse;
	CControlComp controlklasse;

	CThread commthread(&commklasse,CThread::PRIORITY_ABOVE_NORM);
	CThread controlthread(&controlklasse,CThread::PRIORITY_ABOVE_NORM);


	commthread.start();
	controlthread.start();

	commthread.join();
	controlthread.join();

	return 0;
}




