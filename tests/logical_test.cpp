#include <funktions/logical.h>

#include <catch2/catch.hpp>

using namespace rvarago::funktions;
using namespace rvarago::funktions::dsl;

TEST_CASE("fn_wrapper p1 can have the outcome of its evaluation logically-negated as !p", "[logical]") {
    auto const is_true = [](auto const x) { return x == true; };

    auto const [input, expected] = GENERATE(table<bool, bool>({
        {true, false},
        {false, true},
    }));

    auto const got = !fn(is_true)(input);
    CHECK(expected == got);
}

TEST_CASE("fn_wrappers p1 and p2 can be combined by logical-ands as p1 & p2", "[logical]") {
    auto const gt_2 = [](auto const x) { return x > 2; };
    auto const lt_6 = [](auto const x) { return x < 6; };

    auto const [input, expected] = GENERATE(table<int, bool>({
        {0, false},
        {1, false},
        {2, false},
        {3, true},
        {4, true},
        {5, true},
        {6, false},
        {7, false},
        {8, false},
    }));

    auto const got = (fn(gt_2) & lt_6)(input);
    CHECK(expected == got);
}

TEST_CASE("fn_wrappers p1 and p2 can be combined by logical-or as p1 | p2", "[logical]") {
    auto const eq_1 = [](auto const x) { return x == 1; };
    auto const eq_4 = [](auto const x) { return x == 4; };

    auto const [input, expected] = GENERATE(table<int, bool>({
        {0, false},
        {1, true},
        {2, false},
        {3, false},
        {4, true},
        {5, false},
        {6, false},
        {7, false},
        {8, false},
    }));

    auto const got = (fn(eq_1) | eq_4)(input);
    CHECK(expected == got);
}

TEST_CASE("fn_wrappers can be combined by logical-ands and logical-ors", "[logical]") {
    auto const gt_2 = [](auto const x) { return x > 2; };
    auto const lt_6 = [](auto const x) { return x < 6; };
    auto const eq_8 = [](auto const x) { return x == 8; };

    auto const [input, expected] = GENERATE(table<int, bool>({
        {0, false},
        {1, false},
        {2, false},
        {3, true},
        {4, true},
        {5, true},
        {6, false},
        {7, false},
        {8, true},
    }));

    auto const got = (fn(gt_2) & lt_6 | eq_8)(input);
    CHECK(expected == got);
}