#include <funktions/chain.h>

#include <catch2/catch.hpp>

#include <string>

using namespace rvarago::funktions;
using namespace rvarago::funktions::dsl;

namespace {
auto generate_random_ints() {
    return GENERATE(take(100, random(-100, 100)));
}
}

TEST_CASE("chain can compose two functions on integers", "[chain]") {
    auto const plus_1 = [](auto const x) { return x + 1; };
    auto const square = [](auto const x) { return x * x; };

    auto const x = generate_random_ints();

    auto const expected = (x + 1) * (x + 1);
    auto const got = (fn(plus_1) >> square)(x);
    CHECK(expected == got);
}

TEST_CASE("chain can compose several functions where the domain of the first function does not need to match the "
          "co-domain of the last function",
          "[chain]") {
    auto const plus_1 = [](auto const x) { return x + 1; };
    auto const square = [](auto const x) { return x * x; };
    auto const to_string = [](auto const x) { return std::to_string(x); };

    auto const x = generate_random_ints();

    auto const expected = std::to_string((x + 1) * (x + 2));
    auto const got = (fn(plus_1) >> square >> to_string)(x);
    CHECK(expected == got);
}