#pragma once

#include <cstddef>

using TypeIndex = size_t;

template <typename UniqueUsageContext, typename T>
TypeIndex unorderedTypeIndex()
{
    static char takeMyAddress;
    return reinterpret_cast<TypeIndex>(&takeMyAddress);
}

template <typename UniqueUsageContext>
struct InstantiationCounter {
    static TypeIndex lastInstantiatedCounterForContext;
    const TypeIndex savedAtTimeCounterForContext = lastInstantiatedCounterForContext++;
};

template <typename UniqueUsageContext>
TypeIndex InstantiationCounter<UniqueUsageContext>::lastInstantiatedCounterForContext = 0;

template <typename UniqueUsageContext, typename T>
TypeIndex orderedTypeIndex()
{
    static InstantiationCounter<UniqueUsageContext> instance;
    return instance.savedAtTimeCounterForContext;
}
