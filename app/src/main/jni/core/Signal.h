#ifndef FLAPPY_CAT_SIGNAL_H
#define FLAPPY_CAT_SIGNAL_H

// stl
#include <functional>

// simple signal slot system with one slot per signal
// without collecting return values
// and possible nullptr call

template <typename SlotFunction>
class Signal {
public:
  Signal();
public:
  void connect(const std::function<SlotFunction>& slot);
  std::function<SlotFunction> emit;
};

// implementation

template <typename SlotFunction>
Signal<SlotFunction>::Signal()
: emit(nullptr) {
  //
}

template <typename SlotFunction>
void Signal<SlotFunction>::connect(const std::function<SlotFunction>& slot) {
  emit = slot;
}


#endif //FLAPPY_CAT_SIGNAL_H
