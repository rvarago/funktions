#ifndef RVARAGO_FUNKTIONS_PREDICATES_H
#define RVARAGO_FUNKTIONS_PREDICATES_H

#include "funktions/fnwrapper.h"

#include <utility>

namespace rvarago::funktions {

/**
 * Wraps the equality operation, such that eq(x)(y) is equivalent to y == x.
 * @tparam T type of the argument to be checked for equality.
 * @param value argument to be checked for equality.
 * @return a predicate wrapped in an fn_wrapper that upon evaluation checks the equality of its arguments.
 */
template <typename T>
constexpr auto eq(T &&value) {
    return fn_wrapper{[v = std::forward<T>(value)](auto &&other) { return std::forward<decltype(other)>(other) == v; }};
}

/**
 * Wraps the inequality operation, such that ne(x)(y) is equivalent to y != x.
 * @tparam T type of the argument to be checked for inequality.
 * @param value argument to be checked for inequality.
 * @return a predicate wrapped in an fn_wrapper that upon evaluation checks the inequality of its arguments.
 */
template <typename T>
constexpr auto ne(T &&value) {
    return fn_wrapper{[v = std::forward<T>(value)](auto &&other) { return std::forward<decltype(other)>(other) != v; }};
}

/**
 * Wraps the less-than operation, such that lt(x)(y) is equivalent to y < x.
 * @tparam T type of the argument to be checked for comparison.
 * @param value argument to be checked for comparison.
 * @return a predicate wrapped in an fn_wrapper that upon evaluation checks if the second argument is less-than the
 * first.
 */
template <typename T>
constexpr auto lt(T &&value) {
    return fn_wrapper{[v = std::forward<T>(value)](auto &&other) { return std::forward<decltype(other)>(other) < v; }};
}

/**
 * Wraps the greater-than operation, such that gt(x)(y) is equivalent to y > x.
 * @tparam T type of the argument to be checked for comparison.
 * @param value argument to be checked for comparison.
 * @return a predicate wrapped in an fn_wrapper that upon evaluation checks if the second argument is greater-than the
 * first.
 */
template <typename T>
constexpr auto gt(T &&value) {
    return fn_wrapper{[v = std::forward<T>(value)](auto &&other) { return std::forward<decltype(other)>(other) > v; }};
}

/**
 * Wraps the y == true operation in a curried-form, such that is_true()(y) is equivalent to y == true.
 * @return a predicate wrapped in an fn_wrapper that upon evaluation checks if the argument is equals to true.
 */
constexpr auto is_true() {
    return fn_wrapper{[](auto &&other) { return static_cast<bool>(std::forward<decltype(other)>(other)); }};
}

/**
 * Wraps the y == false operation in a curried-form, such that is_false()(y) is equivalent to y == false.
 * @return a predicate wrapped in an fn_wrapper that upon evaluation checks if the argument is equals to false.
 */
constexpr auto is_false() {
    return fn_wrapper{[](auto &&other) { return !static_cast<bool>(std::forward<decltype(other)>(other)); }};
}

}

#endif
