#ifndef RVARAGO_FUNKTIONS_FNWRAPPER_H
#define RVARAGO_FUNKTIONS_FNWRAPPER_H

#include <utility>

namespace rvarago::funktions {

/**
 * Simple wrapper for a generic callable that allows coherent operator-overloading.
 * @tparam Function type of the generic callable.
 */
template <typename Function>
class fn_wrapper {
    Function _f;

  public:
    constexpr explicit fn_wrapper(Function f) : _f{f} {
    }

    template <typename... Args>
    constexpr auto operator()(Args &&... args) const noexcept(noexcept(_f(std::forward<Args>(args)...)))
        -> decltype(_f(std::forward<Args>(args)...)) {
        return _f(std::forward<Args>(args)...);
    }

    /**
     * Calls the non-const wrapped callable by forwarding the variadic arguments.
     * @tparam Args type of parameters-pack.
     * @param args pack of arguments to be forwarded to the generic callable.
     * @return the outcome of calling the wrapped callable with the generic pack of arguments.
     */
    template <typename... Args>
    constexpr auto operator()(Args &&... args) noexcept(noexcept(_f(std::forward<Args>(args)...)))
        -> decltype(_f(std::forward<Args>(args)...)) {
        return _f(std::forward<Args>(args)...);
    }
};

/**
 * Shorthand for wrapping a generic callable into an fn_wrapper.
 * @tparam Function type of the generic callable.
 * @param f generic callable to be wrapped.
 * @return a fn_wrapper that wraps f.
 */
template <typename Function>
auto fn(Function &&f) -> fn_wrapper<Function> {
    return fn_wrapper<Function>{std::forward<Function>(f)};
}

}

#endif
