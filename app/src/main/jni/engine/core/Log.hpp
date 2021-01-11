#pragma once


// engine
#ifdef FLAPPYCAT_QT

#include "qt/QtLog.hpp"
using Log = QtLog;

#elif FLAPPYCAT_ANDROID

#include <android/AndroidLog.hpp>
using Log = AndroidLog;

#else

using Log = void;

#endif



// TODO: decide on what is better 'REQUIRE' macro or 'require' free function
//template<typename Tag, typename... Args>
//inline void require(Tag tag, bool condition, Args... args) {
//
//  Log::assert(condition, "", tag, args...);
//}


