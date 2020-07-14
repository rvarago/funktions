#include <funktions/predicates.h>

#include <catch2/catch.hpp>

#include <string>
#include <type_traits>

using namespace rvarago::funktions;

namespace {

template <typename T>
auto generate_randoms() {
    auto static const into = [](auto const x) {
        if constexpr (std::is_same_v<T, std::string>) {
            return std::to_string(x);
        } else {
            return static_cast<T>(x);
        }
    };
    return GENERATE(take(100, map(into, random(-100, 100))));
}

}

TEMPLATE_TEST_CASE("eq(x)(y) is equivalent to y == x", "[predicates]", int, double, std::string) {
    auto const x = generate_randoms<TestType>();
    auto const y = generate_randoms<TestType>();

    auto const expected = y == x;
    auto const got = eq(x)(y);

    CHECK(expected == got);
}

TEMPLATE_TEST_CASE("ne(x)(y) is equivalent to y != x", "[predicates]", int, double, std::string) {
    auto const x = generate_randoms<TestType>();
    auto const y = generate_randoms<TestType>();

    auto const expected = y != x;
    auto const got = ne(x)(y);

    CHECK(expected == got);
}