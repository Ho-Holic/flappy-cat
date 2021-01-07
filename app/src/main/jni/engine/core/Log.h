#ifndef FLAPPY_CAT_LOG_H_H
#define FLAPPY_CAT_LOG_H_H

// engine
#ifdef FLAPPYCAT_QT

#include "QtLog.hpp"
using Log = QtLog;

#else

#include <android/AndroidLog.h>
using Log = AndroidLog;

#endif



// TODO: decide on what is better 'REQUIRE' macro or 'require' free function
//template<typename Tag, typename... Args>
//inline void require(Tag tag, bool condition, Args... args) {
//
//  Log::assert(condition, "", tag, args...);
//}

#endif //FLAPPY_CAT_LOG_H_H
