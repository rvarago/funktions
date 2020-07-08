#include <funktions/fnwrapper.h>

#include <catch2/catch.hpp>

using namespace rvarago::funktions;

TEST_CASE("fn_wrapper wraps a generic callable that can be later called") {
    auto model = [](auto const x, auto const y) { return std::to_string(2 * x + y); };

    auto model_wrapped = fn(model);

    auto const x = GENERATE(take(100, random(-100, 100)));
    auto const y = GENERATE(take(100, random(-100, 100)));

    CHECK(model_wrapped(x, y) == model(x, y));
}