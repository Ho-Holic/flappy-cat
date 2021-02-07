#pragma once

/**
 * UNUSED - document that variable is unused and programmer know this
 */
#define UNUSED(expr) (void)(expr)

/**
 * CAUTION(message) - document critical sections of code
 * This macro do noting. This is like a comment, but bring extra attention to it's message
 */
#define CAUTION(message)

/**
 * REQUIRE - assert with fancy name =)
 */
#define REQUIRE(tag, condition, ...) Log::assert_condition(condition, #condition, tag, __VA_ARGS__)
