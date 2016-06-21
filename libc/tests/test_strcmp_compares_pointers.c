#include <string.h>
#include "testmacros.h"

/*
 * If both str1 and str2 are pointers to the same location in memory, strcmp
 * should say they are equal without checking the individual array elements.
 *
 * To check this, we'll give strcmp the same null pointer (which would fail the
 * character check) and see if it returns a success.
 */
int do_test() {
  const char* my_string = NULL;
  ASSERT_EQ(strcmp(my_string, my_string), 0);
  return 0;
}
