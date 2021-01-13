#pragma once

// stl
#include <functional>

// style
#include <style/Guidelines.hpp>

// Simple signal slot system with one slot per signal
// without collecting return values.
//
// Any copy of signal resets it, because you can get an error
// accessing 'this' pointer of maybe deleted object passing various
// lambda functions as a slot and other bad stuff can happen

#undef emit

template <typename SlotFunction>
class Signal {
public:
    Signal();
    Signal(const Signal& that);
    Signal& operator=(Signal& that);
    ~Signal() = default;

public:
    void connect(const std::function<SlotFunction>& slot);
    template <typename... Args>
    void emit(Args... args);

private:
    std::function<SlotFunction> mEmit;
};

// implementation

template <typename SlotFunction>
Signal<SlotFunction>::Signal()
    : mEmit(nullptr)
{
    //
}

template <typename SlotFunction>
Signal<SlotFunction>::Signal(const Signal& that)
    : mEmit(nullptr)
{

    UNUSED(that);
    CAUTION("Variable 'mEmit' intentionally set to 'nullptr'");
}

template <typename SlotFunction>
Signal<SlotFunction>& Signal<SlotFunction>::operator=(Signal<SlotFunction>& that)
{

    UNUSED(that);
    CAUTION("Variable 'mEmit' intentionally set to 'nullptr'");

    mEmit = nullptr;

    return *this;
}

template <typename SlotFunction>
void Signal<SlotFunction>::connect(const std::function<SlotFunction>& slot)
{
    mEmit = slot;
}

template <typename SlotFunction>
template <typename... Args>
void Signal<SlotFunction>::emit(Args... args)
{

    if (mEmit != nullptr) {
        mEmit(args...);
    }
}
