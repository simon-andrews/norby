#include <string.h>
#include "testmacros.h"

int do_test() {
  ASSERT_EQ(strcmp("hello", "hello"), 0);
  return 0;
}
