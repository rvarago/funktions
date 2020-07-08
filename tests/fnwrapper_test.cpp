#include <funktions/fnwrapper.h>

#include <catch2/catch.hpp>

using namespace rvarago::funktions;

namespace {
auto generate_random_ints() {
    return GENERATE(take(100, random(-100, 100)));
}
}

TEST_CASE("fn_wrapper wraps a generic callable that can be later called", "[fn_wrapper]") {
    auto const model = [](auto const x, auto const y) { return std::to_string(2 * x + y); };

    auto const model_wrapped = fn(model);

    auto const x = generate_random_ints();
    auto const y = generate_random_ints();

    CHECK(model_wrapped(x, y) == model(x, y));
}