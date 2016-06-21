#include <string.h>
#include "testmacros.h"

int do_test() {
  ASSERT_NQ(strcmp("hello", "h"), 0);
  return 0;
}
