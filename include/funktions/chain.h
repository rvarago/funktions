#ifndef RVARAGO_FUNKTIONS_CHAIN_H
#define RVARAGO_FUNKTIONS_CHAIN_H

#include "funktions/fnwrapper.h"

namespace rvarago::funktions::dsl {

/**
 * Wraps the functions _left_ and _right_ themselves wrapped in `fn_wrapper`'s to produce a third function (their
 * composition), which when invoked with a pack of arguments, forwards them to _left_ and then applies its outcome into
 * _right_.
 * @tparam FunctionA type of the right function.
 * @tparam FunctionB type of the left function.
 * @param right first function wrapped in a fn_wrapper.
 * @param left second function wrapped in a fn_wrapper.
 * @return a new fn_wrapper that wraps the two function and computes their composition.
 */
template <typename FunctionA, typename FunctionB>
constexpr auto operator>>(fn_wrapper<FunctionA> const left, fn_wrapper<FunctionB> const right) {
    return fn_wrapper{[=](auto const &... args) { return right(left(args...)); }};
}

template <typename FunctionA, typename FunctionB>
constexpr auto operator>>(fn_wrapper<FunctionA> const left, FunctionB const right) {
    return left >> fn(right);
}

}

#endif
