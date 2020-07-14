#include <funktions/logical.h>

#include <catch2/catch.hpp>
#include <map>

using namespace rvarago::funktions;
using namespace rvarago::funktions::dsl;

TEST_CASE("fn_wrappers can be combined by logical-and's", "[logical]") {
    auto const gt_2 = [](auto const x) { return x > 2; };
    auto const lt_6 = [](auto const x) { return x < 6; };

    auto const [input, expected_output] = GENERATE(table<int, bool>({
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

    auto const bt_2_6 = fn(gt_2) & lt_6;
    CHECK(bt_2_6(input) == expected_output);
}

TEST_CASE("fn_wrappers can be combined by logical-or's", "[logical]") {
    auto const eq_1 = [](auto const x) { return x == 1; };
    auto const eq_4 = [](auto const x) { return x == 4; };

    auto const [input, expected_output] = GENERATE(table<int, bool>({
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

    auto const eq_1_or_4 = fn(eq_1) | eq_4;
    CHECK(eq_1_or_4(input) == expected_output);
}

TEST_CASE("fn_wrappers can be combined by logical-and's and logical-or's", "[logical]") {
    auto const gt_2 = [](auto const x) { return x > 2; };
    auto const lt_6 = [](auto const x) { return x < 6; };
    auto const eq_8 = [](auto const x) { return x == 8; };

    auto const [input, expected_output] = GENERATE(table<int, bool>({
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

    auto const bt_2_6_or_eq_8 = fn(gt_2) & lt_6 | eq_8;
    CHECK(bt_2_6_or_eq_8(input) == expected_output);
}