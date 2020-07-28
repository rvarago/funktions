#ifndef RVARAGO_FUNKTIONS_LOGICAL_H
#define RVARAGO_FUNKTIONS_LOGICAL_H

#include "funktions/fnwrapper.h"

namespace rvarago::funktions::dsl {

/**
 * Wraps the predicate _p_ (itself wrapped in `fn_wrapper`) to produce another predicate, which
 * when invoked with a pack of arguments, forwards them to the predicate and then computes the logical-not
 * of its outcome.
 * @tparam Predicate type of the predicate.
 * @param p predicate wrapped in a fn_wrapper.
 * @return a new fn_wrapper that wraps the predicate and computes the logical-not of its outcome.
 */
template <typename Predicate>
constexpr auto operator!(fn_wrapper<Predicate> const p) {
    return fn_wrapper{[=](auto const &... args) { return !(p(args...)); }};
}

/**
 * Wraps the predicates _left_ and _right_ themselves wrapped in `fn_wrapper`'s to produce a third predicate, which
 * when invoked with a pack of arguments, forwards them to each predicate and computes the logical-and of their
 * outcomes.
 * @tparam PredicateA type of the right predicate.
 * @tparam PredicateB type of the left predicate.
 * @param right first predicate wrapped in a fn_wrapper.
 * @param left second predicate wrapped in a fn_wrapper.
 * @return a new fn_wrapper that wraps the two predicates and computes the logical-and of their outcomes.
 */
template <typename PredicateA, typename PredicateB>
constexpr auto operator&(fn_wrapper<PredicateA> const left, fn_wrapper<PredicateB> const right) {
    return fn_wrapper{[=](auto const &... args) { return left(args...) && right(args...); }};
}

template <typename PredicateA, typename PredicateB>
constexpr auto operator&(fn_wrapper<PredicateA> const left, PredicateB const right) {
    return left & fn(right);
}

/**
 * Wraps the predicates _left_ and _right_ themselves wrapped in `fn_wrapper`'s to produce a third predicate, which
 * when invoked with a pack of arguments, forwards them to each predicate and computes the logical-or of their
 * outcomes.
 * @tparam PredicateA type of the right predicate.
 * @tparam PredicateB type of the left predicate.
 * @param right first predicate wrapped in a fn_wrapper.
 * @param left second predicate wrapped in a fn_wrapper.
 * @return a new fn_wrapper that wraps the two predicates and computes the logical-or of their outcomes.
 */
template <typename PredicateA, typename PredicateB>
constexpr auto operator|(fn_wrapper<PredicateA> const left, fn_wrapper<PredicateB> const right) {
    return fn_wrapper{[=](auto const &... args) { return left(args...) || right(args...); }};
}

template <typename PredicateA, typename PredicateB>
constexpr auto operator|(fn_wrapper<PredicateA> const left, PredicateB const right) {
    return left | fn(right);
}

}

#endif
