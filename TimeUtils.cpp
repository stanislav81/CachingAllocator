/*
 * TimeUtils.cpp
 *
 *  Created on: 12.08.2011
 *      Author: stan
 */

#include "TimeUtils.h"
#include <sys/time.h>
#include <stdio.h>

namespace utils {

	namespace time {

		double GetMilliseconds(void)
		{
			struct timeval _tv;
			if ( gettimeofday(&_tv, NULL) )
				return (double)NULL;
			return (double)_tv.tv_sec * 1000 + (double)_tv.tv_usec/1000;
		}
	};
};
