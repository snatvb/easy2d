#include <iostream>

#ifdef NDEBUG
#define ASSERT(condition, message)
#else
#define ASSERT(condition, message)                                            \
  (!(condition)) ? (std::cerr << "Assertion failed: (" << #condition << "), " \
                              << "function " << __FUNCTION__                  \
                              << ", file " << __FILE__                        \
                              << ", line " << __LINE__ << "."                 \
                              << std::endl                                    \
                              << message << std::endl,                        \
                    abort(), 0)                                               \
                 : 1
#endif