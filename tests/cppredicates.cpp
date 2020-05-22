#include <cppredicates/cppredicates.hpp>

#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

using namespace cppredicates;

TEST_CASE("CPPredicates simple tests", "[cppredicates]") {
    CPPredicates predicates;

    Point2D pa{0, 0};
    Point2D pb{2, 0};
    Point2D pc{1, 1};
    Point2D pd{1, -1};
    Point2D pe{1, 0};

    Ray2D bc(pb, pc);
    Ray2D bd(pb, pd);
    Ray2D be(pb, pe);

    real ole = predicates.orientation(pa, bc);
    real ore = predicates.orientation(pa, bd);
    real oco = predicates.orientation(pa, be);

    CHECK(ole > 0);
    CHECK(ore < 0);
    CHECK(oco == 0.0);
}

TEST_CASE("CPPredicates benchmark orientation left", "[cppredicates]") {
    CPPredicates predicates;

    Point2D pa{0, 0};
    Point2D pb{2, 0};
    Point2D pc{1, 1};
    Ray2D bc(pb, pc);

    std::array<double, 2> a = {0, 0};
    std::array<double, 2> b = {2, 0};
    std::array<double, 2> c = {1, 1};

    BENCHMARK("orientation left") { return predicates.orientation(pa, bc); };
    BENCHMARK("orientation left (approx)") {
        return predicates.orientationApprox(pa, bc);
    };
}

TEST_CASE("CPPredicates benchmark orientation right", "[cppredicates]") {
    CPPredicates predicates;

    Point2D pa{0, 0};
    Point2D pb{2, 0};
    Point2D pd{1, -1};
    Ray2D bd(pb, pd);

    BENCHMARK("orientation right") { return predicates.orientation(pa, bd); };
    BENCHMARK("orientation right (approx)") {
        return predicates.orientationApprox(pa, bd);
    };
}

TEST_CASE("CPPredicates benchmark orientation colinear", "[cppredicates]") {
    CPPredicates predicates;

    Point2D pa{0, 0};
    Point2D pb{2, 0};
    Point2D pe{1, 0};
    Ray2D be(pb, pe);

    BENCHMARK("orientation colinear") {
        return predicates.orientation(pa, be);
    };

    BENCHMARK("orientation colinear (approx)") {
        return predicates.orientationApprox(pa, be);
    };
}
