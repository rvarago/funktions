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

TEST_CASE("lt(x)(y) is equivalent to y < x", "[predicates]") {
    auto const x = GENERATE(take(100, random(-100, 100)));
    auto const y = GENERATE(take(100, random(-100, 100)));

    auto const expected = y < x;
    auto const got = lt(x)(y);

    CHECK(expected == got);
}

TEST_CASE("gt(x)(y) is equivalent to y > x", "[predicates]") {
    auto const x = GENERATE(take(100, random(-100, 100)));
    auto const y = GENERATE(take(100, random(-100, 100)));

    auto const expected = y > x;
    auto const got = gt(x)(y);

    CHECK(expected == got);
}

TEST_CASE("is_true()(y) is equivalent to y == true", "[predicates]") {
    auto const [input, expected] = GENERATE(table<bool, bool>({
        {true, true},
        {false, false},
    }));

    auto const got = is_true()(input);

    CHECK(expected == got);
}