# funktions

A small C++17 set of utilities for functional composition.

```Cpp
enum class status { Idle, Waiting, Busy };

struct device {
    long id;
    long vendor_id;
    status current_status;
};

std::vector<device> const devices = fetch_all_devices();

// Given a device d:
//  d.vendor_id == 2 and d.current_status != status::Busy
auto const query = fn(&device::vendor_id) >> eq(2)
                    & fn(&device::current_status) >> ne(status::Busy);

// 'fn', 'eq', 'ne', '>>', and '&' are some of the utilities provided by
// funktions to build fluent Domain-Specific Languages.

auto const device = std::find_if(devices.begin(), devices.end(), query);
```

# Utilities

* [`fn_wrapper`](#fn_wrapper)
* [`logical_not`](#logical_not)
* [`logical_and`](#logical_and)
* [`logical_or`](#logical_or)
* [`chain`](#chain)
* [`predicates`](#predicates)

[funktions/all.h](include/funktions/all.h)

## <A name="fn_wrapper"/>`fn_wrapper`

A wrapper around a generic function-like type to make DSLs created via operator-overloading less intrusive.

When invoked with a pack of arguments forwards them to the wrapped callable.

[funktions/fnwrapper.h](include/funktions/fnwrapper.h)

## <A name="logical_not"/>`logical_not`

An overload for the `operator!` that acts on a predicate wrapped in `fn_wrapper` to produce another predicate.

When invoked with a pack of arguments, forwards them to the predicate and computes the logical-not of its outcome.

*Example*:

```Cpp
auto const eq_2 = [](auto const x) { return x == 2; };

auto const not_eq_2 = !fn(eq_2);

auto const y = not_eq_2(x); // y = !(x == 2)
```

[funktions/logical.h](include/funktions/logical.h)

## <A name="logical_and"/>`logical_and`

An overload for the `operator&` that acts on two predicates wrapped in `fn_wrapper`s to produce a third predicate.

When invoked with a pack of arguments, forwards them to each predicate and computes the logical-and of their outcomes.

*Example*:

```Cpp
auto const gt_2 = [](auto const x) { return x > 2; };
auto const lt_6 = [](auto const x) { return x < 6; };

auto const bt_2_6 = fn(gt_2) & fn(lt_6);

auto const y = bt_2_6(x); // y = (x > 2) && (x < 6)
```

[funktions/logical.h](include/funktions/logical.h)

## <A name="logical_or"/>`logical_or`

An overload for the `operator|` that acts on two predicates wrapped in `fn_wrapper`s to produce a third predicate.

When invoked with a pack of arguments, forwards them to each predicate and computes the logical-or of their outcomes.

*Example*:

```Cpp
auto const eq_2 = [](auto const x) { return x == 2; };
auto const eq_6 = [](auto const x) { return x == 6; };

auto const eq_2_or_6 = fn(eq_2) | fn(eq_6);

auto const y = eq_2_or_6(x); // y = (x == 2) || (x == 6)
```

[funktions/logical.h](include/funktions/logical.h)

## <A name="chain"/>`chain`

An overload for the `operator>>` that acts on two functions wrapped in `fn_wrapper` to produce a third function (their composition).

When invoked with a pack of arguments, forwards them to the first function and then applies its
outcome into the second function.

*Example*:

```Cpp
auto const plus_1 = [](auto const x) { return x + 1; };
auto const square = [](auto const x) { return x * x; };

auto const plus_1_then_square = fn(plus_1) >> square;

auto const y = plus_1_then_square(x); // y = (x + 1) * (x + 1)
```

[funktions/chain.h](include/funktions/chain.h)


## <A name="predicates"/>`predicates`

A set of reusable and curried predicates for common operations that would otherwise likely be written as inline lambdas.

These operations are already wrapped inside `fn_wrapper`s to profit from logical combinators.

Built-in operations:

* `eq(x)(y)         // y == x`
* `ne(x)(y)         // y != x`
* `lt(x)(y)         // y < x`
* `gt(x)(y)         // y > x`
* `is_true()(y)     // y == true`
* `is_false()(y)    // y == false`

[funktions/predicates.h](include/funktions/predicates.h)

# Examples

[device_validation.cpp](examples/device_validation.cpp)