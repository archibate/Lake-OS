#define likely(x) (!__builtin_expect(!(x), 0))
#define unlikely(x) (__builtin_expect(!!(x), 0))
