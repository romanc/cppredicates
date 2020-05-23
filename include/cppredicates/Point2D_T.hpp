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
    Point2D_T<T>() : m_xy({0, 0}) {}

    /** Constructor from \c x and \c y
     *
     *  @param x x-coordinate
     *  @param y y-coordinate
     */
    explicit Point2D_T<T>(T x, T y) : m_xy({x, y}) {}

    /** Default move constructor
     *
     *  @param p Other point to move from
     */
    Point2D_T(Point2D_T&& p) = default;

    /** Default copy constructor
     *
     *  @param other Other point to copy from
     */
    Point2D_T(const Point2D_T& other) = default;

    /** Default move assignment
     *
     *  @param p Other point to move from
     *  @return  Move constructed point
     */
    Point2D_T& operator=(Point2D_T&& p) = default;

    /** Default copy assignment
     *
     *  @param other Other point to move from
     *  @return  Copy constructed point
     */
    Point2D_T& operator=(const Point2D_T& other) = default;

    /** Access x-coordinate of this point
     *
     *  @returns x-coordinate of this point
     */
    T x() const { return m_xy[0]; }

    /** Access y-coordinate of this point
     *
     * @returns y-coordinate of this point
     */
    T y() const { return m_xy[1]; }

    /** Subtraction operator
     *
     *  @param left operand
     *  @param right operand
     *  @returns \c left - \c right
     */
    friend Point2D_T operator-(const Point2D_T& left, const Point2D_T& right) {
        return Point2D_T(left.m_xy[0] - right.m_xy[0],
                         left.m_xy[1] - right.m_xy[1]);
    }

   private:
    std::array<T, 2> m_xy;
};

// Template implementation
#include "Point2D_T.tpp"

}  // namespace cppredicates

#endif
