#ifndef CPPREDICATES_CPPREDICATES_H
#define CPPREDICATES_CPPREDICATES_H

//! Project namespace
namespace cppredicates
{
// Forward declarations
class Circle;
class Point2D;
class Point3D;
class Ray;
class Sphere;

//! Describes orientation of points with respect to geometric primitives.
enum class Orientation : int16_t {
    left = 0x0,      //!< Point is to the left of the ray
    right = 0x1,     //!< Point is to the right of the ray
    colinear = 0x4,  //!< Point is coliniear with the ray
    coplanar = 0x5,  //!< Point is coplanar with the plane
    inside = 0x2,    //!< Point is inside the circle/sphere
    outside = 0x3,   //!< Point is outside the circle/sphere
    boundary = 0x6   //!< Point is on the boundary of the circle/sphere
};

//! CPPredicates provides robust geometric orientation primitives in modern C++
class CPPredicates {
   public:
    //! Constructor initializes member variables needed for exact computations
    CPPredicates();

    /** Checks the orienation of a point in 2D with respect to a given ray
     *
     *  @param point 2D-Point to examine
     *  @param ray Ray in 2D
     *
     *  @returns One of \c Orientation::left, \c Orientation::right or \c
     * Orientation::colinear
     */
    Orientation orientation(const Point2D& point, const Ray2D& ray);

    /** Checks the orienation of a point in 3D with respect to a given plane
     *
     *  @param point 3D-Point to examine
     *  @param plane Plane in 3D
     *
     *  @returns One of \c Orientation::left, \c Orientation::right or \c
     * Orientation::coplanar
     */
    Orientation orientation(const Point3D& point, const Plane3D& plane);

    /** Check whether a point in 2D is inside or outside a given circle
     *
     *  @param point 2D-Point to examine
     *  @param circle Circle in 2D
     *
     *  @returns One of \c Orientation::inside or \c Orientation::outside
     */
    Orientation inCircle(const Point2D& point, const Circle2D& circle);

    /** Check whether a point in 3D is inside or outside a given sphere
     *
     *  @param point 3D-Point to examine
     *  @param sphere Sphere
     *
     *  @returns One of \c Orientation::inside or \c Orientation::outside
     */
    Orientation inSphere(const Point3D& point, const Sphere& sphere);

   private:
    real m_epsilon;   //!< Machine epsilon
    real m_splitter;  //!< ...
                      // ...
};
}  // namespace cppredicates

#endif
