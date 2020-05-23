#ifndef CPPREDICATES_POINT_3D_T_H
#define CPPREDICATES_POINT_3D_T_H

#include <array>

namespace cppredicates
{
//! Represents a point in three dimensions
template <class T>
class Point3D_T {
   public:
    //! Default constructor
    Point3D_T<T>() : m_xyz({0, 0, 0}) {}

    /*! Constructor from \c x and \c y
     *
     *  @param x x-coordinate
     *  @param y y-coordinate
     *  @param z z-coordinate
     */
    explicit Point3D_T<T>(T x, T y, T z) : m_xyz({x, y, z}) {}

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
    std::array<T, 3> m_xyz;
};

// Template implementation
#include "Point3D_T.tpp"

}  // namespace cppredicates

#endif
