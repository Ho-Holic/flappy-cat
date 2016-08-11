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
  Class(const Class &) = delete;\
  Class &operator=(const Class &) = delete;

/**
 * @def forever - endless loop in more readable format
 *
 * Avoid common warnings and static analyzer false positives.
 *
 * Implemented as `for(;;)` instead of `while(true)` or `while(1)` because
 * some compilers can warn about `condition is always true` and some
 * static analyzers would have a lot of false positive on this issue
 * along with real ones like typo `while(i = 1)` when programmer
 * intended to write `while(i == 1)`.
 */
#define forever() for(;;)

/**
 * @def CAUTION - document critical sections of code
 */
#define CAUTION(message) (void)(message); do {} while(0)

/**
 * @def REQUIRE - assert with fancy name =)
 */
#define REQUIRE(tag, condition, ...) Log::assert(condition, #condition, tag, __VA_ARGS__)


#endif //FLAPPY_CAT_GUIDELINES_H
