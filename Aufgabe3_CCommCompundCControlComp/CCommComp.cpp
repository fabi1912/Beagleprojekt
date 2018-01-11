/*
 * CCommComp.cpp
 *
 *  Created on: Dec 14, 2017
 *      Author: Andreas Diehm
 */




#include "CCommComp.h"
#include "CContainer.h"
#include <unistd.h>
#include <iostream>
#include "CServer.h"

using namespace std;

extern CContainer myContainer;

void CCommComp::init()
{

mServer.init();
mServer.waitForClient();

};


void CCommComp::run(){

	SContent myData;
	cout<<"ich bin CComComp und funktioniere!"<<endl;
	while(1)
	{
		myContainer.getContent(true, myData);
		mServer.transmitMessage(myData);
	}

};
