#include <cppredicates/Point2D.hpp>
#include <cppredicates/Ray2D.hpp>
#include <cppredicates/cppredicates.hpp>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>

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

real fast_two_sum_tail(real a, real b, real x) {
    const real bvirt = x - a;
    return b - bvirt;
}

std::pair<real, real> fast_two_sum(real a, real b) {
    const real sum = a + b;
    return {sum, fast_two_sum_tail(a, b, sum)};
}

real two_diff_tail(real a, real b, real diff) {
    const real bvirt = a - diff;
    const real avirt = diff + bvirt;
    const real bround = bvirt - b;
    const real around = a - avirt;
    return around + bround;
}

std::pair<real, real> two_diff(real a, real b) {
    const real diff = a - b;

    return {diff, two_diff_tail(a, b, diff)};
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

class Expansion {
   public:
    Expansion(const real* data, std::size_t size, bool dynamic)
        : m_data(data), m_size(size), m_dynamic(dynamic), m_ownsData(dynamic) {}

    explicit Expansion(const std::vector<real>& v)
        : m_data(v.data()),
          m_size(v.size()),
          m_dynamic(true),
          m_ownsData(false) {}

    explicit Expansion(std::vector<real>&& v)
        : m_data(v.data()),
          m_size(v.size()),
          m_dynamic(true),
          m_ownsData(true) {
        std::vector<real> tmp;
        v = tmp;
        std::cout << "new extension" << std::endl;
    }

    Expansion(const Expansion& other) = delete;
    Expansion& operator=(const Expansion& other) = delete;

    ~Expansion() {
        if (m_dynamic && m_ownsData) {
            std::cout << "deleting data" << std::endl;
            delete[] m_data;
        }
    }

    bool isDynamic() const { return m_dynamic; }
    bool ownsData() const { return m_dynamic && m_ownsData; }

    std::size_t size() const { return m_size; }

    const real* data() const { return m_data; }

    real back() const { return m_data[m_size - 1]; }

    real operator[](std::size_t idx) const {
        assert(idx < m_size);
        return *(m_data + idx);
    }

    friend Expansion operator+(const Expansion&, const Expansion&);

   private:
    const real* m_data;
    std::size_t m_size;
    bool m_dynamic;   // true, if m_data is a dynamically allocated array
    bool m_ownsData;  // true, if we own the dynamic data in m_data
};

// implements fast_expansion_sum_zeroelim
Expansion operator+(const Expansion& e, const Expansion& f) {
    const std::size_t esize = e.size();
    const std::size_t fsize = f.size();
    std::vector<real> h;
    h.reserve(esize + fsize);

    std::size_t eidx = 0;
    std::size_t fidx = 0;
    std::size_t hidx = 0;

    real enow = e[eidx];
    real fnow = f[fidx];
    const bool condition = (fnow > enow) == (fnow > -enow);
    real Q = condition ? enow : fnow;
    if (condition) {
        enow = e[++eidx];
    } else {
        fnow = f[++fidx];
    }

    if ((eidx < esize) && (fidx < fsize)) {
        const bool condition = (fnow > enow) == (fnow > -enow);
        const auto [Qnew, hh] = condition ? detail::fast_two_sum(enow, Q)
                                          : detail::fast_two_sum(fnow, Q);
        if (condition) {
            enow = e[++eidx];
        } else {
            fnow = f[++fidx];
        }
        Q = Qnew;
        if (hh != 0.0) {
            h.emplace_back(hh);
        }

        while ((eidx < esize) && (fidx < fsize)) {
            const bool condition = (fnow > enow) == (fnow > -enow);
            const auto [Qnew, hh] =
                condition ? detail::two_sum(Q, enow) : detail::two_sum(Q, fnow);
            if (condition) {
                enow = e[++eidx];
            } else {
                fnow = f[++fidx];
            }
            Q = Qnew;
            if (hh != 0.0) {
                h.emplace_back(hh);
            }
        }
    }

    while (eidx < esize) {
        const auto [Qnew, hh] = detail::two_sum(Q, enow);
        enow = e[++eidx];
        Q = Qnew;
        if (hh != 0.0) {
            h.emplace_back(hh);
        }
    }
    while (fidx < fsize) {
        const auto [Qnew, hh] = detail::two_sum(Q, fnow);
        fnow = f[++fidx];
        Q = Qnew;
        if (hh != 0.0) {
            h.emplace_back(hh);
        }
    }
    if ((Q != 0.0) || (h.size() == 0)) {
        h.emplace_back(Q);
    }

    return Expansion(std::move(h));
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
    std::cout << "okay, let's get started" << std::endl;

    const Point2D ac = point - ray.through();
    const Point2D bc = ray.origin() - ray.through();

    const auto [left, lefttail] = detail::two_product(ac.x(), bc.y());
    const auto [right, righttail] = detail::two_product(ac.y(), bc.x());

    const std::array<real, 4> B =
        detail::two_two_diff(left, lefttail, right, righttail);

    real det = std::reduce(B.begin(), B.end());
    const real errbound = m_ccwerrboundB * detsum;
    if ((det >= errbound) || (-det >= errbound)) {
        return det;
    }

    std::cout << "I made it here :)" << std::endl;

    const real acxtail =
        detail::two_diff_tail(point.x(), ray.through().x(), ac.x());
    const real acytail =
        detail::two_diff_tail(point.y(), ray.through().y(), ac.y());

    const real bcxtail =
        detail::two_diff_tail(ray.origin().x(), ray.through().x(), bc.x());
    const real bcytail =
        detail::two_diff_tail(ray.origin().y(), ray.through().y(), bc.y());

    if ((acxtail == 0.0) && (acytail == 0.0) && (bcxtail == 0.0) &&
        (bcytail == 0.0)) {
        return det;
    }

    std::cout << "I made it almost to the end :)" << std::endl;

    const real errbound2 =
        m_ccwerrboundC * detsum + m_resulterrbound * std::abs(det);
    det += (ac.x() * bcytail + bc.y() * acxtail) -
           (ac.y() * bcxtail + bc.x() * acytail);
    if ((det >= errbound2) || (-det >= errbound2)) {
        return det;
    }

    std::cout << "I made it all the way to the end :)" << std::endl;

    const auto [s, stail] = detail::two_product(acxtail, bc.y());
    const auto [t, ttail] = detail::two_product(acytail, bc.x());

    const auto [s2, s2tail] = detail::two_product(ac.x(), bcytail);
    const auto [t2, t2tail] = detail::two_product(ac.y(), bcxtail);

    const auto [s3, s3tail] = detail::two_product(acxtail, bcytail);
    const auto [t3, t3tail] = detail::two_product(acytail, bcxtail);

    const auto u = detail::two_two_diff(s, stail, t, ttail);
    const auto u2 = detail::two_two_diff(s2, s2tail, t2, t2tail);
    const auto u3 = detail::two_two_diff(s3, s3tail, t3, t3tail);

    const detail::Expansion Be(B.data(), B.size(), false);
    const detail::Expansion Ue(u.data(), u.size(), false);
    const auto c1 = Be + Ue;

    const detail::Expansion U2e(u2.data(), u2.size(), false);
    const auto c2 = c1 + U2e;

    const detail::Expansion U3e(u3.data(), u3.size(), false);
    const auto d = c2 + U3e;

    return d.back();
}
