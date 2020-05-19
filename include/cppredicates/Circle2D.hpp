#ifndef CPPREDICATES_CIRCLE_2D_H
#define CPPREDICATES_CIRCLE_2D_H

#include <cppredicates/Point2D.hpp>

namespace cppredicates
{
//! Represents a circle in two dimensions
template <class T>
class Circle2D_T {
   public:
    //! Default constructor
    Circle2D_T() = default;

    /** Constructor from \c origin and \c radius
     *
     *  @param origin Center of the circle
     *  @param radius Radius of the circle
     */
    explicit Circle2D_T(const Point2D_T<T>& origin, T radius) {
        // TODO convert to 3 points on the circle
    }

    /** Constructor from three coplanar points
     *
     *  @param pA \c Point2D A on the circle
     *  @param pB \c Point2D B on the circle
     *  @param pC \c Point2D C on the circle
     */
    explicit Circle2D_T(const Point2D_T<T>& pA, const Point2D_T<T>& pB,
                        const Point2D_T<T>& pC)
        : pA(pA), pB(pB), pC(pC) {}

    /** Default move constructor
     *
     *  @param other Other circle to move from
     */
    Circle2D_T(Circle2D_T&& other) = default;
    /** Default move assignment
     *
     *  @param other Other circle to move from
     *  @return      Move constructed circle
     */
    Circle2D_T& operator=(Circle2D_T&& other) = default;

   private:
    Point2D_T<T> pA;
    Point2D_T<T> pB;
    Point2D_T<T> pC;
};

// Template implementations
#include "Circle2D.tpp"

//! Explicit template instantiation for type Circle2D
using Circle2D = Circle2D_T<real>;

}  // namespace cppredicates

#endif
