#ifndef RVARAGO_FUNKTIONS_PREDICATES_H
#define RVARAGO_FUNKTIONS_PREDICATES_H

#include "funktions/fnwrapper.h"

#include <utility>

namespace rvarago::funktions::preds {

/**
 * Wraps the equality operation, such that eq(x)(y) is equivalent to x == y.
 * @tparam T type of the argument to be checked for equality.
 * @param value argument to be checked for equality.
 * @return a predicate wrapped in an fn_wrapper that upon evaluation checks the equality of its arguments.
 */
template <typename T>
constexpr auto eq(T &&value) {
    return fn_wrapper{[v = std::forward<T>(value)](auto &&other) {
        return std::forward<T>(v) == std::forward<decltype(other)>(other);
    }};
}

/**
 * Wraps the inequality operation, such that ne(x)(y) is equivalent to x != y.
 * @tparam T type of the argument to be checked for inequality.
 * @param value argument to be checked for inequality.
 * @return a predicate wrapped in an fn_wrapper that upon evaluation checks the inequality of its arguments.
 */
template <typename T>
constexpr auto ne(T &&value) {
    return fn_wrapper{[v = std::forward<T>(value)](auto &&other) {
        return !eq(std::forward<T>(v))(std::forward<decltype(other)>(other));
    }};
}

}

#endif
