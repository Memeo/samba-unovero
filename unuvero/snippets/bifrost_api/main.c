#include <stdio.h>
#include "bifrost_api.h"

int
main
  ()
{
  struct MagniAuth *ma = authenticate(stdout);  
  return 0;
}
