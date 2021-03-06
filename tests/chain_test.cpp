#include <funktions/chain.h>

#include <catch2/catch.hpp>

#include <string>

using namespace rvarago::funktions;
using namespace rvarago::funktions::dsl;

TEST_CASE("chain can compose two functions on integers", "[chain]") {
    auto const plus_1 = [](auto const x) { return x + 1; };
    auto const square = [](auto const x) { return x * x; };

    auto const x = GENERATE(take(100, random(-100, 100)));

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

    auto const x = GENERATE(take(100, random(-100, 100)));

    auto const expected = std::to_string((x + 1) * (x + 1));
    auto const got = (fn(plus_1) >> square >> to_string)(x);
    CHECK(expected == got);
}

TEST_CASE("chain can be used for projections", "[chain]") {
    struct connection {
        int id;
    };
    struct device {
        connection conn;
    };

    auto const get_id = [](connection const x) { return x.id; };
    auto const get_connection = [](device const x) { return x.conn; };

    auto const id = GENERATE(take(100, random(-100, 100)));
    auto const dev = device{connection{id}};

    auto const expected = id;
    auto const got = (fn(get_connection) >> get_id)(dev);

    CHECK(expected == got);
}