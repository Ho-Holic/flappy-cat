#ifndef FLAPPY_CAT_FIXNDK_H
#define FLAPPY_CAT_FIXNDK_H

// stl
#include <string>
#include <sstream>

namespace fix {

  namespace ndk {

    namespace std {

      template <typename T>
      ::std::string to_string(T value)
      {
        ::std::ostringstream os ;
        os << value ;
        return os.str() ;
      }
    }
  }
}

#endif //FLAPPY_CAT_FIXNDK_H
