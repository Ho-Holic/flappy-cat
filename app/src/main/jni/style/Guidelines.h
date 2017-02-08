#ifndef FLAPPY_CAT_GUIDELINES_H
#define FLAPPY_CAT_GUIDELINES_H

/**
 * @def UNUSED - document that variable is unused and programmer know this
 */
#define UNUSED(expr) (void)(expr)

/**
 * @def SCOPE - document that you creating new scope with some purpose
 * Useful with RAII techniques
 */
#define SCOPE(description) (void)(description);

/**
 * @def DISABLE_COPY - disable copy construction and assignment operations
 */
#define DISABLE_COPY(Class) \
  Class(const Class&) = delete;\
  Class& operator=(const Class&) = delete;

/**
 * @def loop - endless loop in more readable format
 *
 * Avoid common warnings and static analyzer false positives.
 *
 * Implemented as `for(;;)` instead of `while(true)` or `while(1)` because
 * some compilers can warn about `condition is always true` and some
 * static analyzers would have a lot of false positive on this issue
 * along with real ones like typo `while(i = 1)` when programmer
 * intended to write `while(i == 1)`.
 *
 * ... and inspired by Rust language
 */
#define loop() for(;;)

/**
 * @def CAUTION(message) - document critical sections of code
 * This macro do noting. This is like a comment, but bring extra attention to it's message
 */
#define CAUTION(message)

/**
 * @def REQUIRE - assert with fancy name =)
 */
#define REQUIRE(tag, condition, ...) Log::assert(condition, #condition, tag, __VA_ARGS__)

/**
 * @def UNEXPECTED_SWITCH - Mark switch branch that must be unreachable
 *
 * This is used when some code permutations lead to code that compile but works wrong,
 * like adding new enum value and not handle this in a switch
 */
#define UNEXPECTED_SWITCH                                            \
  default: {                                                         \
    throw std::logic_error("ASSERT: this code must be unreachable"); \
  }

/**
 * @def UNEXPECTED_RETURN - Mark switch branch that must be unreachable
 *
 * This is used for switch constructions when all brunches return from a function
 * but you need to be shure that code does not leave the switch statement
 */
#define UNEXPECTED_RETURN(RETURN_VALUE)                            \
  throw std::logic_error("ASSERT: this code must be unreachable"); \
  return RETURN_VALUE;

#endif //FLAPPY_CAT_GUIDELINES_H
