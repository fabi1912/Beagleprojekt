/*
 * CCommComp.h
 *
 *  Created on: Dec 14, 2017
 *      Author: Andreas Diehm
 */

#ifndef CCOMMCOMP_H_
#define CCOMMCOMP_H_
#include "CContainer.h"
#include "IRunnable.h"
#include "CServer.h"

extern CContainer myContainer;

class CCommComp:public IRunnable
{
	public:
		void run();
		void init();
	private:
		CServer mServer;

};



#endif /* CCOMMCOMP_H_ */
