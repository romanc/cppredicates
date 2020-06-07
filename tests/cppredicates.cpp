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

    Ray2D r(Point2D{16.8, 16.8}, Point2D{18.0, 18.0});
    const real eps = std::pow(2, -40);
    for (int i = 0; i < 32; ++i) {
        for (int j = 0; j < 32; ++j) {
            const real o = predicates.orientation(
                Point2D(0.95 + i * eps, 0.95 + j * eps), r);
            if (i == j) {
                REQUIRE(o == 0.0);
            } else {
                if (i > j) {
                    REQUIRE(o < 0);
                } else {
                    REQUIRE(o > 0);
                }
            }
        }
    }
}

TEST_CASE("CPPredicates benchmark orientation left", "[cppredicates]") {
    CPPredicates predicates;

    Point2D pa{0, 0};
    Point2D pb{2, 0};
    Point2D pc{1, 1};
    Ray2D bc(pb, pc);

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

TEST_CASE("CPPredicates benchmark orientation left (harder)",
          "[cppredicates]") {
    CPPredicates predicates;

    Point2D pa{3.84, 3.84};
    Point2D pb{3.92, 3.92};
    Point2D pf{0.98, 0.980000000000001};
    Ray2D bf(pb, pf);

    BENCHMARK("orientation left (harder)") {
        return predicates.orientation(pa, bf);
    };
}

TEST_CASE("CPPredicates benchmark orientation right (harder)",
          "[cppredicates]") {
    CPPredicates predicates;

    Point2D pa{3.84, 3.84};
    Point2D pb{3.92, 3.92};
    Point2D pg{0.98, 0.979999999999999};
    Ray2D bg(pb, pg);

    BENCHMARK("orientation right (harder)") {
        return predicates.orientation(pa, bg);
    };
}

TEST_CASE("CPPredicates benchmark whole square", "[cppredicates]") {
    CPPredicates predicates;

    Ray2D r(Point2D{16.8, 16.8}, Point2D{18.0, 18.0});
    const real eps = std::pow(2, -40);

    BENCHMARK("orientation whole square") {
        real sum = 0;
        for (int i = 0; i < 32; ++i) {
            for (int j = 0; j < 32; ++j) {
                sum += predicates.orientation(
                    Point2D(0.95 + i * eps, 0.95 + j * eps), r);
            }
        }
        return sum;
    };
}
