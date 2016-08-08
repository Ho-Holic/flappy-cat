// self
#include "AndroidPipe.h"
#include "Log.h"

// stl
#include <cstring>

// posix
#include <unistd.h>

AndroidPipe::AndroidPipe()
: mReadEnd()
, mWriteEnd() {

  enum { ReadEndIndex, WriteEndIndex, ChannelCount };

  int pipefd[ChannelCount];
  int hasErrors = ::pipe(pipefd);

  if (hasErrors) {
    Log::i("Could not create pipe: %s", std::strerror(errno));
  }

  mReadEnd = pipefd[ReadEndIndex];
  mWriteEnd = pipefd[WriteEndIndex];
}

AndroidPipe::~AndroidPipe() {

  ::close(mReadEnd);
  ::close(mWriteEnd);
}
