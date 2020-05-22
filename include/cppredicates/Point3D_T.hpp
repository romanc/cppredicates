#ifndef CPPREDICATES_POINT_3D_T_H
#define CPPREDICATES_POINT_3D_T_H

namespace cppredicates
{
//! Represents a point in three dimensions
template <class T>
class Point3D_T {
   public:
    //! Default constructor
    Point3D_T<T>() : x(T(0)), y(T(0)), z(T(0)) {}

    /*! Constructor from \c x_ and \c y_
     *
     *  @param x_ x-coordinate
     *  @param y_ y-coordinate
     *  @param z_ z-coordinate
     */
    explicit Point3D_T<T>(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}

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
    T x;
    T y;
    T z;
};

// Template implementation
#include "Point3D_T.tpp"

}  // namespace cppredicates

#endif
