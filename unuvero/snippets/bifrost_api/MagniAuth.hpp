/*
 * MagniAuth.hpp
 *
 *  Created on: Aug 28, 2015
 *      Author: gsilverman
 */

#ifndef MAGNIAUTH_HPP_
#define MAGNIAUTH_HPP_

#include <stdio.h>
class MagniAuth {
public:
	virtual ~MagniAuth();
	MagniAuth();
	bool authenticate(FILE *);

};

#endif /* MAGNIAUTH_HPP_ */
