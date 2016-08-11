#ifndef FLAPPY_CAT_ANDROIDPIPE_H
#define FLAPPY_CAT_ANDROIDPIPE_H

// self
#include "Guidelines.h"

class AndroidPipe {
private:
  DISABLE_COPY(AndroidPipe)

public:
  AndroidPipe();
  ~AndroidPipe();

public:
  int readEnd() const;
  int writeEnd() const;

private:
  int mReadEnd;
  int mWriteEnd;
};


#endif //FLAPPY_CAT_ANDROIDPIPE_H
