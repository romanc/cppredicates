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

	Point pf = {10, -0.0000000001};
	Point pg = {10, 0.000000001};

	double left = orient2d(pa.data(), pb.data(), pc.data());
	double right = orient2d(pa.data(), pb.data(), pd.data());
	double middle = orient2d(pa.data(), pb.data(), pe.data());

	CHECK(left > 0);
	CHECK(right < 0);
	CHECK(middle == 0);

	BENCHMARK("orient2d left") {
		return orient2d(pa.data(), pb.data(), pc.data());
	};

	BENCHMARK("orient2d fast (left)") {
		return orient2dfast(pa.data(), pb.data(), pc.data());
	};

	BENCHMARK("orient2d right") {
		return orient2d(pa.data(), pb.data(), pd.data());
	};
	
	BENCHMARK("orient2d fast (right)") {
		return orient2dfast(pa.data(), pb.data(), pd.data());
	};

	BENCHMARK("orient2d colinear") {
		return orient2d(pa.data(), pb.data(), pd.data());
	};
	
	BENCHMARK("orient2d fast (colinear)") {
		return orient2dfast(pa.data(), pb.data(), pe.data());
	};

	BENCHMARK("orient2d left (harder)") {
		return orient2d(pa.data(), pb.data(), pf.data());
	};

	BENCHMARK("orient2d right (harder)") {
		return orient2d(pa.data(), pb.data(), pg.data());
	};
}

