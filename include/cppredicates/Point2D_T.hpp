#ifndef CPPREDICATES_POINT_2D_T_H
#define CPPREDICATES_POINT_2D_T_H

#include <array>

namespace cppredicates
{
//! Represents a point in two dimensions
template <class T>
class Point2D_T {
   public:
    //! Default constructor
    Point2D_T<T>() : m_x(0), m_y(0) {}

    /** Constructor from \c x and \c y
     *
     *  @param x x-coordinate
     *  @param y y-coordinate
     */
    explicit Point2D_T<T>(T x, T y) : m_x(x), m_y(y) {}

    /** Default move constructor
     *
     *  @param p Other point to move from
     */
    Point2D_T(Point2D_T&& p) = default;
    Point2D_T(const Point2D_T& other) = default;

    /** Default move assignment
     *
     *  @param p Other point to move from
     *  @return  Move constructed point
     */
    Point2D_T& operator=(Point2D_T&& p) = default;
    Point2D_T& operator=(const Point2D_T& other) = default;

    T x() const { return m_x; }
    T y() const { return m_y; }

    friend Point2D_T operator-(const Point2D_T& left, const Point2D_T& right) {
        return Point2D_T(left.m_x - right.m_x, left.m_y - right.m_y);
    }

   private:
    T m_x;
    T m_y;
};

// Template implementation
#include "Point2D_T.tpp"

}  // namespace cppredicates

#endif
