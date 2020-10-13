#include <funktions/fnwrapper.h>

#include <catch2/catch.hpp>

using namespace rvarago::funktions;

TEST_CASE("fn_wrapper wraps a generic callable that can be later called", "[fn_wrapper]") {
    auto const model = [](auto const x, auto const y) { return std::to_string(2 * x + y); };

    auto const model_wrapped = fn(model);

    auto const x = GENERATE(take(100, random(-100, 100)));
    auto const y = GENERATE(take(100, random(-100, 100)));

    auto const expected = model(x, y);
    auto const got = model_wrapped(x, y);
    CHECK(expected == got);
}

TEST_CASE("fn_wrapper accesses a member variable as if it were calling a function", "[fn_wrapper]") {
    using id_t = long;
    struct device {
        id_t id;
    };

    auto const model = [](auto const dev) { return dev.id; };
    auto const model_wrapped = fn(&device::id);

    auto const dev = device{id_t{GENERATE(take(100, random(-100, 100)))}};

    auto const expected = model(dev);
    auto const got = model_wrapped(dev);
    CHECK(expected == got);
}