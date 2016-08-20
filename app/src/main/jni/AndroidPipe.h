#ifndef FLAPPY_CAT_ANDROIDPIPE_H
#define FLAPPY_CAT_ANDROIDPIPE_H

// self
#include "Guidelines.h"

// posix
#include <unistd.h>

class AndroidPipe {
private:
  DISABLE_COPY(AndroidPipe)

public:
  AndroidPipe();
  ~AndroidPipe();

public:
  int readEnd() const;
  int writeEnd() const;

  /**
   * readEnum - Read bytes enough to fill `EnumType`
   *
   * If read fails `defaultValue` is returned
   */
  template <typename EnumType, EnumType defaultValue>
  EnumType readEnum();

  template <typename EnumType>
  ssize_t writeEnum(EnumType buf);



private:
  int mReadEnd;
  int mWriteEnd;
};

// implementation

template <typename EnumType, EnumType defaultValue>
EnumType AndroidPipe::readEnum() {

  REQUIRE(TAG, sizeof(EnumType) <= sizeof(ssize_t),
          "Must fit to `ssize_t`");

  EnumType data;
  ssize_t bytesRead = ::read(mReadEnd, &data, sizeof(data));
  return bytesRead == sizeof(data) ? data
                                   : defaultValue;
}

template <typename EnumType>
ssize_t AndroidPipe::writeEnum(EnumType buf) {
  ssize_t bytesWritten = ::write(mWriteEnd, &buf, sizeof(buf));
  return bytesWritten;
}


#endif //FLAPPY_CAT_ANDROIDPIPE_H
