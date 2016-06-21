//It would probably be better to call these assert_not_uneq and assert_not_eq
#define ASSERT_EQ(a, b) {if(a != b) return 1; }
#define ASSERT_NQ(a, b) {if(a == b) return 1; }

#define ASSERT(expr) { if(!(expr)) return 1; }
