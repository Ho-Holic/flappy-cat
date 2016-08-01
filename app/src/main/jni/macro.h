#ifndef FLAPPYCAT_MACRO_H
#define FLAPPYCAT_MACRO_H

/**
 * @def UNUSED - document that variable is unused and programmer know this
 */
#define UNUSED(x) (void)(x)

/**
 * @def SCOPE - document that you creating new scope with some purpose
 * Useful with RAII techniques
 */
#define SCOPE(x) (void)(x);

/**
 * @def DISABLE_COPY - disable copy construction and assignment operations
 */
#define DISABLE_COPY(Class) \
  Class(const Class &) = delete;\
  Class &operator=(const Class &) = delete;

#endif //FLAPPYCAT_MACRO_H
