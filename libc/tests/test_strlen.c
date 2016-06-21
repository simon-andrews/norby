#include <string.h>
#include "testmacros.h"

int do_test(void) {
	ASSERT_EQ(strlen("hello"), 5); //regular strings
	ASSERT_EQ(strlen(""), 0);      //empty strings
	return 0;
}
