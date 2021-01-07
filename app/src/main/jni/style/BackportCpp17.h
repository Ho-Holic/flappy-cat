#ifndef FLAPPY_CAT_BACKPORTCPP17_H
#define FLAPPY_CAT_BACKPORTCPP17_H

// engine
#include <core/Log.h>
#include "Guidelines.h"

// stl
#include <functional>

// backport of std::clamp from C++17

namespace backport {

  namespace std {

    template<class T, class Compare>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp) {

      return REQUIRE(TAG, !comp(hi, lo), "hi must be greater then lo"),
             comp(v, lo) ? lo : comp(hi, v) ? hi : v;
    }

    template<class T>
    constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
        return backport::std::clamp(v, lo, hi, ::std::less<>());
    }

  }
}

#endif //FLAPPY_CAT_BACKPORTCPP17_H
