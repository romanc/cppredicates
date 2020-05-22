#ifndef CPPREDICATES_POINT_3D_T_H
#define CPPREDICATES_POINT_3D_T_H

namespace cppredicates
{
//! Represents a point in three dimensions
template <class T>
class Point3D_T {
   public:
    //! Default constructor
    Point3D_T<T>() : m_x(T(0)), m_y(T(0)), m_z(T(0)) {}

    /*! Constructor from \c x and \c y
     *
     *  @param x x-coordinate
     *  @param y y-coordinate
     *  @param z z-coordinate
     */
    explicit Point3D_T<T>(T x, T y, T z) : m_x(x), m_y(y), m_z(z) {}

    /** Default move constructor
     *
     *  @param p Other point to move from
     */
    Point3D_T(Point3D_T&& p) = default;
    /** Default move assignment
     *
     *  @param p Other point to move from
     *  @return  Move constructed point
     */
    Point3D_T& operator=(Point3D_T&& p) = default;

   private:
    T m_x;
    T m_y;
    T m_z;
};

// Template implementation
#include "Point3D_T.tpp"

}  // namespace cppredicates

#endif
