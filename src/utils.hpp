#ifndef __BLT_UTILS_H__
#define __BLT_UTILS_H__

#include <exception>
#include <string>
#include <iostream>

#define ERROR(MSG) { throw runtime_error(MSG); }
#define ASSERT(X) { if (!(X)) { throw runtime_error(string("Assertion failed (") + string(#X) + string(")")); } }
#define ASSERT_NOT_REACHED { throw runtime_error("Assertion failed (ASSERT_NOT_REACHED)"); }

#define LOG(MSG) { std::cout << (MSG) << std::endl; }

#endif