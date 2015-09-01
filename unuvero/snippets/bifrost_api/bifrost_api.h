#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
struct MagniAuth;
struct MagniAuth *authenticate(FILE *);

#ifdef __cplusplus
}
#endif

