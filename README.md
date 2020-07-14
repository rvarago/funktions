# funktions

A small C++17 set of utilities for functional composition.

# Utilities

* [`fn_wrapper`](#fn_wrapper)
* [`logical_and`](#logical_and)
* [`logical_or`](#logical_or)
* [`chain`](#chain)
* [`predicates`](#predicates)

## <A name="fn_wrapper"/>`fn_wrapper`

A wrapper around a generic function-like type to make DSLs created via operator-overloading less intrusive,
which when invoked with a pack of arguments forwards them to the wrapped callable.

[fnwrapper.h](include/funktions/fnwrapper.h)

## <A name="logical_and"/>`logical_and`

An overload for the `operator&` that acts on two predicates wrapped in `fn_wrapper`'s to produce a third predicate,
which when invoked with a pack of arguments, forwards them to each predicate and computes the logical-and of their outcomes.

Example:

```Cpp
auto const gt_2 = [](auto const x) { return x > 2; };
auto const lt_6 = [](auto const x) { return x < 6; };

auto const bt_2_6 = fn(gt_2) & fn(lt_6);

auto const y = bt_2_6(x); // y = (x > 2) && (x < 6)
```

[logical.h](include/funktions/logical.h)

## <A name="logical_or"/>`logical_or`

An overload for the `operator|` that acts on two predicates wrapped in `fn_wrapper`'s to produce a third predicate,
which when invoked with a pack of arguments, forwards them to each predicate and computes the logical-or of their outcomes.

Example:

```Cpp
auto const eq_2 = [](auto const x) { return x == 2; };
auto const eq_6 = [](auto const x) { return x == 6; };

auto const eq_2_or_6 = fn(eq_2) | fn(eq_6);

auto const y = eq_2_or_6(x); // y = (x == 2) || (x == 6)
```

[logical.h](include/funktions/logical.h)

## <A name="chain"/>`chain`

An overload for the `operator>>` that acts on two functions wrapped in `fn_wrapper`'s to produce a third function (their composition),
which when invoked with a pack of arguments, forwards them to the first function and then applies its
outcome into the second function.

Example:

```Cpp
auto const plus_1 = [](auto const x) { return x + 1; };
auto const square = [](auto const x) { return x * x; };

auto const plus_1_then_square = fn(plus_1) >> square;

auto const y = plus_1_then_square(x); // y = (x + 1) * (x + 1)
```

[chain.h](include/funktions/chain.h)


## <A name="predicates"/>`predicates`

A set of reusable and curried predicates for common operations that would otherwise likely be written as inline lambdas.

These operations are already wrapped inside `fn_wrapper`'s to profit from logical combinators.

Built-in operations:

* `eq(x)(y) // y == x`
* `ne(x)(y) // y != x`
* `gt(x)(y) // y > x`

[predicates.h](include/funktions/predicates.h)