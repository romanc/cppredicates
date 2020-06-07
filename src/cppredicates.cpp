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
    Expansion() = default;
    virtual ~Expansion() = default;

    virtual std::size_t size() const = 0;
    virtual real operator[](std::size_t idx) const = 0;
    virtual real back() const = 0;
};

class DynamicExpansion : public Expansion {
   public:
    DynamicExpansion() = default;
    ~DynamicExpansion() override = default;

    explicit DynamicExpansion(size_t maxLength) { m_data.reserve(maxLength); }
    explicit DynamicExpansion(const std::vector<real>& vector)
        : m_data(vector) {}
    explicit DynamicExpansion(std::vector<real>&& vector)
        : m_data(move(vector)) {}

    std::size_t size() const override { return m_data.size(); }

    std::vector<real>& vector() { return m_data; }
    const std::vector<real>& vector() const { return m_data; }

    real back() const override { return m_data.back(); }

    real operator[](std::size_t idx) const override {
        assert(idx < m_data.size());
        return m_data[idx];
    }

   private:
    std::vector<real> m_data;
};

class StaticExpansion : public Expansion {
   public:
    StaticExpansion() = default;
    ~StaticExpansion() override = default;

    explicit StaticExpansion(const real* data, std::size_t size)
        : m_data(data), m_size(size) {}

    std::size_t size() const override { return m_size; }

    real back() const override { return m_data[m_size - 1]; }

    real operator[](std::size_t idx) const override {
        if (idx >= m_size) {
            std::cout << "trying to access [" << idx << "] while size is only "
                      << m_size << std::endl;
        }
        assert(idx < m_size);
        return *(m_data + idx);
    }

   private:
    const real* m_data = nullptr;
    const std::size_t m_size = 0;
};

// implements fast_expansion_sum_zeroelim
DynamicExpansion operator+(const Expansion& e, const Expansion& f) {
    // std::cout << "fast_expansion_sum_zeroelim(" << e.size() << ", " <<
    // f.size()
    //           << ")" << std::endl;
    const std::size_t esize = e.size();
    const std::size_t fsize = f.size();

    assert(esize >= 1);
    assert(fsize >= 1);
    DynamicExpansion expH(esize + fsize);
    auto& h = expH.vector();

    std::size_t eidx = 0;
    std::size_t fidx = 0;

    real enow = e[eidx];
    real fnow = f[fidx];
    const bool condition = ((fnow > enow) == (fnow > -enow));
    real Q = condition ? enow : fnow;

    if ((eidx < esize) && (fidx < fsize)) {
        const bool condition = ((fnow > enow) == (fnow > -enow));
        const auto [Qnew, hh] = condition ? detail::fast_two_sum(enow, Q)
                                          : detail::fast_two_sum(fnow, Q);
        if (condition) {
            enow = e[eidx];
            ++eidx;
        } else {
            fnow = f[fidx];
            ++fidx;
        }
        Q = Qnew;
        if (hh != 0.0) {
            h.emplace_back(hh);
        }

        while ((eidx < esize) && (fidx < fsize)) {
            const bool condition = ((fnow > enow) == (fnow > -enow));
            const auto [Qnew, hh] =
                condition ? detail::two_sum(Q, enow) : detail::two_sum(Q, fnow);
            if (condition) {
                enow = e[eidx];
                ++eidx;
            } else {
                fnow = f[fidx];
                ++fidx;
            }
            Q = Qnew;
            if (hh != 0.0) {
                h.emplace_back(hh);
            }
        }
    }

    while (eidx < esize) {
        const auto [Qnew, hh] = detail::two_sum(Q, enow);
        enow = e[eidx];
        ++eidx;
        Q = Qnew;
        if (hh != 0.0) {
            h.emplace_back(hh);
        }
    }
    while (fidx < fsize) {
        const auto [Qnew, hh] = detail::two_sum(Q, fnow);
        fnow = f[fidx];
        ++fidx;
        Q = Qnew;
        if (hh != 0.0) {
            h.emplace_back(hh);
        }
    }
    if ((Q != 0.0) || (h.size() == 0)) {
        h.emplace_back(Q);
    }

    return expH;
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

    real det = std::reduce(B.cbegin(), B.cend());
    const real errbound = m_ccwerrboundB * detsum;
    if ((det >= errbound) || (-det >= errbound)) {
        return det;
    }

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

    const real errbound2 =
        m_ccwerrboundC * detsum + m_resulterrbound * std::abs(det);
    det += (ac.x() * bcytail + bc.y() * acxtail) -
           (ac.y() * bcxtail + bc.x() * acytail);
    if ((det >= errbound2) || (-det >= errbound2)) {
        return det;
    }

    const auto [s, stail] = detail::two_product(acxtail, bc.y());
    const auto [t, ttail] = detail::two_product(acytail, bc.x());
    const auto u = detail::two_two_diff(s, stail, t, ttail);
    const detail::StaticExpansion Be(B.data(), B.size());
    const detail::StaticExpansion Ue(u.data(), u.size());
    const auto C1 = Be + Ue;

    const auto [s2, s2tail] = detail::two_product(ac.x(), bcytail);
    const auto [t2, t2tail] = detail::two_product(ac.y(), bcxtail);
    const auto u2 = detail::two_two_diff(s2, s2tail, t2, t2tail);
    const detail::StaticExpansion U2e(u2.data(), u2.size());
    const auto C2 = C1 + U2e;

    const auto [s3, s3tail] = detail::two_product(acxtail, bcytail);
    const auto [t3, t3tail] = detail::two_product(acytail, bcxtail);
    const auto u3 = detail::two_two_diff(s3, s3tail, t3, t3tail);
    const detail::StaticExpansion U3e(u3.data(), u3.size());
    const auto D = C2 + U3e;

    return D.back();
}
