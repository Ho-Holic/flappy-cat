#ifndef FLAPPY_CAT_SIGNAL_H
#define FLAPPY_CAT_SIGNAL_H

// stl
#include <functional>

// simple signal slot system with one slot per signal
// without collecting return values

template <typename SlotFunction>
class Signal {
public:
  Signal();
public:
  void connect(const std::function<SlotFunction>& slot);
  template <typename... Args>
  void emit(Args... args);
  std::function<SlotFunction> mEmit;
};

// implementation

template <typename SlotFunction>
Signal<SlotFunction>::Signal()
: mEmit(nullptr) {
  //
}

template <typename SlotFunction>
void Signal<SlotFunction>::connect(const std::function<SlotFunction>& slot) {
  mEmit = slot;
}

template <typename SlotFunction>
template <typename... Args>
void Signal<SlotFunction>::emit(Args... args) {

  if (mEmit != nullptr) {
    mEmit(args...);
  }
}


#endif //FLAPPY_CAT_SIGNAL_H
