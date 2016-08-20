#ifndef FLAPPY_CAT_ANDROIDPIPE_H
#define FLAPPY_CAT_ANDROIDPIPE_H

// self
#include "Guidelines.h"

// stl
#include <cstring>

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
   * Read bytes enough to fill `EnumType`
   * If read fails `defaultValue` is returned
   */
  template <typename EnumType, EnumType defaultValue> EnumType readEnum();

  /**
   * Write `value` to pipe
   * Returns `true` if write is successful
   */
  template <typename EnumType> bool writeEnum(EnumType value);

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
bool AndroidPipe::writeEnum(EnumType value) {

  REQUIRE(TAG, sizeof(EnumType) <= sizeof(ssize_t),
          "Must fit to `ssize_t`");

  ssize_t bytesWritten = ::write(mWriteEnd, &value, sizeof(value));

  bool isOk = (bytesWritten == sizeof(value));
  if ( ! isOk) {
    Log::i("Failure writing to pipe: %s\n", std::strerror(errno));
  }

  return isOk;
}


#endif //FLAPPY_CAT_ANDROIDPIPE_H
