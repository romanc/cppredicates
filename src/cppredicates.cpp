
#include <cppredicates/Point2D.hpp>
#include <cppredicates/Ray2D.hpp>
#include <cppredicates/cppredicates.hpp>

//#include "detail.hpp"

#include <numeric>

using namespace cppredicates;

std::pair<real, real> init() {
    const real one = real(1.0);
    const real two = real(2.0);
    const real half = real(0.5);

    real epsilon = one;
    real splitter = one;

    real check = one;
    real lastcheck;
    bool every_other = true;

    /* Repeatedly divide `m_epsilon' by two until it is too small to add to */
    /* one without causing roundoff.  (Also check if the sum is equal to    */
    /* the previous sum, for machines that round up instead of using exact  */
    /* rounding. Note that this library will work on such machines anyway.) */
    do {
        lastcheck = check;
        epsilon *= half;
        if (every_other) {
            splitter *= two;
        }
        every_other = !every_other;
        check = one + epsilon;
    } while ((check != one) && (check != lastcheck));
    splitter += one;

    return {epsilon, splitter};
}

const auto tmp = init();
const real CPPredicates::m_epsilon = tmp.first;
const real CPPredicates::m_splitter = tmp.second;

const real CPPredicates::m_resulterrbound =
    (3.0 + 8.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_ccwerrboundA =
    (3.0 + 16.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_ccwerrboundB =
    (2.0 + 12.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_ccwerrboundC =
    (9.0 + 64.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon *
    CPPredicates::m_epsilon;
const real CPPredicates::m_o3derrboundA =
    (7.0 + 56.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_o3derrboundB =
    (3.0 + 28.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_o3derrboundC =
    (26.0 + 288.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon *
    CPPredicates::m_epsilon;
const real CPPredicates::m_iccerrboundA =
    (10.0 + 96.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_iccerrboundB =
    (4.0 + 48.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_iccerrboundC =
    (44.0 + 576.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon *
    CPPredicates::m_epsilon;
const real CPPredicates::m_isperrboundA =
    (16.0 + 224.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_isperrboundB =
    (5.0 + 72.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon;
const real CPPredicates::m_isperrboundC =
    (71.0 + 1408.0 * CPPredicates::m_epsilon) * CPPredicates::m_epsilon *
    CPPredicates::m_epsilon;

namespace detail
{
std::pair<real, real> split(real a) {
    const real c = CPPredicates::m_splitter * a;
    const real abig = c - a;
    const real high = c - abig;
    const real low = a - high;
    return {high, low};
}

std::pair<real, real> two_diff(real a, real b) {
    const real diff = a - b;

    const real bvirt = a - diff;
    const real avirt = diff + bvirt;
    const real bround = bvirt - b;
    const real around = a - avirt;
    return {diff, around + bround};
}

std::pair<real, real> two_sum(real a, real b) {
    const real sum = a + b;

    const real bvirt = sum - a;
    const real avirt = sum - bvirt;
    const real bround = b - bvirt;
    const real around = a - avirt;
    return {sum, around + bround};
}

std::pair<real, real> two_product(real a, real b) {
    const real prod = a * b;

    const auto [ahi, alo] = split(a);
    const auto [bhi, blo] = split(b);
    const real err1 = prod - (ahi * bhi);
    const real err2 = err1 - (alo * bhi);
    const real err3 = err2 - (ahi * blo);
    return {prod, (alo * blo) - err3};
}

std::array<real, 3> two_one_diff(real a1, real a0, real b) {
    const auto [i, x0] = two_diff(a0, b);
    const auto [x2, x1] = two_sum(a1, i);
    return {x2, x1, x0};
}

std::array<real, 4> two_two_diff(real a1, real a0, real b1, real b0) {
    const auto [j, k, x0] = two_one_diff(a1, a0, b0);
    const auto [x3, x2, x1] = two_one_diff(j, k, b1);
    return {x3, x2, x1, x0};
}

}  // namespace detail

CPPredicates::CPPredicates() {}

real CPPredicates::orientation(const Point2D& point, const Ray2D& ray) {
    const Point2D ac = point - ray.through();
    const Point2D bc = ray.origin() - ray.through();

    const real detleft = ac.x() * bc.y();
    const real detright = ac.y() * bc.x();
    const real det = detleft - detright;
    const real zero = real(0.0);
    real detsum;

    if (detleft > zero) {
        if (detright <= zero) {
            return det;  // return detToLeftRightColinear(det);
        } else {
            detsum = detleft + detright;
        }
    } else if (detleft < zero) {
        if (detright >= 0) {
            return det;  // return detToLeftRightColinear(det);
        } else {
            detsum = -detleft - detright;
        }
    } else {
        return det;  // return detToLeftRightColinear(det);
    }

    const real errbound = m_ccwerrboundA * detsum;
    if (det >= errbound || -det >= errbound) {
        return det;  // return detToLeftRightColinear(det);
    }

    return adaptiveOrient2D(point, ray, detsum);
}

real CPPredicates::orientationApprox(const Point2D& point, const Ray2D& ray) {
    const Point2D ac = point - ray.through();
    const Point2D bc = ray.origin() - ray.through();

    const real detleft = ac.x() * bc.y();
    const real detright = ac.y() * bc.x();

    return detleft - detright;
}

real CPPredicates::adaptiveOrient2D(const Point2D& point, const Ray2D& ray,
                                    real detsum) {
    const Point2D ac = point - ray.through();
    const Point2D bc = ray.origin() - ray.through();

    const auto [left, lefttail] = detail::two_product(ac.x(), bc.y());
    const auto [right, righttail] = detail::two_product(ac.y(), bc.x());

    const std::array<real, 4> B =
        detail::two_two_diff(left, lefttail, right, righttail);

    const real det = std::reduce(B.begin(), B.end());
    const real errbound = m_ccwerrboundB * detsum;
    if ((det >= errbound) || (-det >= errbound)) {
        return det;
    }

    return 42;

    // TODO ... continue
}
