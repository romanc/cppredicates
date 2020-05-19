#ifndef CPPREDICATES_POINT_2D_H
#define CPPREDICATES_POINT_2D_H

#include <cppredicates/typedefs.hpp>

namespace cppredicates
{
//! Represents a point in two dimensions
template <class T>
class Point2D_T {
   public:
    //! Default constructor
    Point2D_T<T>() : x(T(0)), y(T(0)) {}

    /** Constructor from \c x_ and \c y_
     *
     *  @param x_ x-coordinate
     *  @param y_ y-coordinate
     */
    explicit Point2D_T<T>(T x_, T y_) : x(x_), y(y_) {}

    /** Default move constructor
     *
     *  @param p Other point to move from
     */
    Point2D_T(Point2D_T&& p) = default;
    /** Default move assignment
     *
     *  @param p Other point to move from
     *  @return  Move constructed point
     */
    Point2D_T& operator=(Point2D_T&& p) = default;

   private:
    T x;
    T y;
};

// Template implementation
#include "Point2D.tpp"

//! Explicit template instantiation for type Point2D
using Point2D = Point2D_T<real>;

}  // namespace cppredicates

#endif
