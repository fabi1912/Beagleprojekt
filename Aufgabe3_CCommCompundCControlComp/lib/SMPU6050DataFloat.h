/*
 * SMPU6050DataFloat.h
 *
 *  Created on: Jan 4, 2018
 *      Author: vmuser
 */

#ifndef LIB_SMPU6050DATAFLOAT_H_
#define LIB_SMPU6050DATAFLOAT_H_
#include "Global.h"

struct SMPU6050DataFloat
{
public:
	float mX__dd;		//! Sensor  X-Acceleration []
	float mY__dd;		//! Sensor  Y-Acceleration []
	float mPhi__d;		//! Sensor  Z-Angular Velocity []
	float mPadding;
};




#endif /* LIB_SMPU6050DATAFLOAT_H_ */
