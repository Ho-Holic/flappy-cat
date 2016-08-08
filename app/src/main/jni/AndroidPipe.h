#ifndef FLAPPY_CAT_ANDROIDPIPE_H
#define FLAPPY_CAT_ANDROIDPIPE_H

// self
#include "macro.h"

class AndroidPipe {
private:
  DISABLE_COPY(AndroidPipe)

public:
  AndroidPipe();
  ~AndroidPipe();

private:
  int mReadEnd;
  int mWriteEnd;
};


#endif //FLAPPY_CAT_ANDROIDPIPE_H
