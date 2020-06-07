#include "predicates.h"

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

using Point = std::array<double, 2>;

TEST_CASE("Original benchmarks", "[predicates]") {
    exactinit();

    Point pa = {0, 0};
    Point pb = {2, 0};
    Point pc = {1, 1};
    Point pd = {1, -1};
    Point pe = {1, 0};

    double left = orient2d(pa.data(), pb.data(), pc.data());
    double right = orient2d(pa.data(), pb.data(), pd.data());
    double middle = orient2d(pa.data(), pb.data(), pe.data());

    CHECK(left > 0);
    CHECK(right < 0);
    CHECK(middle == 0);
}

TEST_CASE("Original benchmark orient2d left", "[predicates]") {
    exactinit();

    Point pa = {0, 0};
    Point pb = {2, 0};
    Point pc = {1, 1};

    BENCHMARK("orient2d left") {
        return orient2d(pa.data(), pb.data(), pc.data());
    };

    BENCHMARK("orient2d fast (left)") {
        return orient2dfast(pa.data(), pb.data(), pc.data());
    };
}

TEST_CASE("Original benchmark orient2d right", "[predicates]") {
    exactinit();

    Point pa = {0, 0};
    Point pb = {2, 0};
    Point pd = {1, -1};

    BENCHMARK("orient2d right") {
        return orient2d(pa.data(), pb.data(), pd.data());
    };

    BENCHMARK("orient2d fast (right)") {
        return orient2dfast(pa.data(), pb.data(), pd.data());
    };
}

TEST_CASE("Original benchmark orient2d colinear", "[predicates]") {
    exactinit();

    Point pa = {0, 0};
    Point pb = {2, 0};
    Point pe = {1, 0};

    BENCHMARK("orient2d colinear") {
        return orient2d(pa.data(), pb.data(), pe.data());
    };

    BENCHMARK("orient2d fast (colinear)") {
        return orient2dfast(pa.data(), pb.data(), pe.data());
    };
}

TEST_CASE("Original benchmark orient2d left (harder)", "[predicates]") {
    exactinit();

    Point pa{3.84, 3.84};
    Point pb{3.92, 3.92};
    Point pf{0.98, 0.980000000000001};

    BENCHMARK("orient2d left (harder)") {
        return orient2d(pa.data(), pb.data(), pf.data());
    };
}

TEST_CASE("Original benchmark orient2d right (harder)", "[predicates]") {
    exactinit();

    Point pa{3.84, 3.84};
    Point pb{3.92, 3.92};
    Point pg{0.98, 0.979999999999999};

    BENCHMARK("orient2d right (harder)") {
        return orient2d(pa.data(), pb.data(), pg.data());
    };
}
