/*
 * bifrost_api.c
 *
 *  Created on: Aug 28, 2015
 *      Author: gsilverman
 */

#include "bifrost_api.h"
#include "MagniAuth.hpp"

extern "C" {
MagniAuth *authenticate(FILE *fp) {
	MagniAuth *ma = new MagniAuth();
	ma->authenticate(fp);
	return ma;
}
}
