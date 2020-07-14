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