#include <funktions/predicates.h>

#include <catch2/catch.hpp>

#include <string>
#include <type_traits>

using namespace rvarago::funktions;

TEST_CASE("eq(x)(y) is equivalent to y == x", "[predicates]") {
    auto const x = GENERATE(take(100, random(-100, 100)));
    auto const y = GENERATE(take(100, random(-100, 100)));

    auto const expected = y == x;
    auto const got = eq(x)(y);

    CHECK(expected == got);
}

TEST_CASE("ne(x)(y) is equivalent to y != x", "[predicates]") {
    auto const x = GENERATE(take(100, random(-100, 100)));
    auto const y = GENERATE(take(100, random(-100, 100)));

    auto const expected = y != x;
    auto const got = ne(x)(y);

    CHECK(expected == got);
}

TEST_CASE("gt(x)(y) is equivalent to y > x", "[predicates]") {
    auto const x = GENERATE(take(100, random(-100, 100)));
    auto const y = GENERATE(take(100, random(-100, 100)));

    auto const expected = y > x;
    auto const got = gt(x)(y);

    CHECK(expected == got);
}