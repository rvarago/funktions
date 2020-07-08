# funktions

A small C++17 set of utilities for functional composition.

# Utilities

* [`fn_wrapper`](#fn_wrapper)

## <A name="fn_wrapper"/>`fn_wrapper`

A wrapper around a generic function-like type to make DSLs created via operator-overloading less intrusive,
which when invoked with a pack of arguments forwards them to the wrapped callable.

[fnwrapper.h](include/funktions/fnwrapper.h)

