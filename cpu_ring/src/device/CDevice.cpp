#include "CDevice.h"
#include <iostream>

CDevice::CDevice(const string& name_)
{
	if (!name_.empty())
	{
		name = name_;
		for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
		{
			mX_P[i][j] = 0;
			mY_P[i][j] = 0;
			mX_T[i][j] = 0;
			mY_T[i][j] = 0;
		}
	}
	cout << "You are trying to create empty CDevice object." << endl
		 << "Please check your input files." << endl;
	exit(EXIT_FAILURE);
}

void CDevice::generateTwissM()
{
	double C = mX_P[0][0],  S = mX_P[0][1];
	double C_= mX_P[1][0],  S_= mX_P[1][1];

	mX_T[0][0] = +1 * C *C;   mX_T[0][1] = -2 * C *S;    mX_T[0][2] = +1 * S *S;
	mX_T[1][0] = -1 * C *C_;  mX_T[1][1] = C*S_ + C_*S;  mX_T[1][2] = -1 * S *S_;
	mX_T[2][0] = +1 * C_*C_;  mX_T[2][1] = -2 * C_*S_;   mX_T[2][2] = +1 * S_*S_;

	C = mY_P[0][0], S = mY_P[0][1];
	C_= mY_P[1][0], S_= mY_P[1][1];

	mY_T[0][0] = +1 * C *C;   mY_T[0][1] = -2 * C *S;    mY_T[0][2] = +1 * S *S;
	mY_T[1][0] = -1 * C *C_;  mY_T[1][1] = C*S_ + C_*S;  mY_T[1][2] = -1 * S *S_;
	mY_T[2][0] = +1 * C_*C_;  mY_T[2][1] = -2 * C_*S_;   mY_T[2][2] = +1 * S_*S_;
}