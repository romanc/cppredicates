#ifndef CPPREDICATES_CPPREDICATES_H
#define CPPREDICATES_CPPREDICATES_H

#include <cppredicates/Circle2D.hpp>
#include <cppredicates/Plane3D.hpp>
#include <cppredicates/Point2D.hpp>
#include <cppredicates/Point3D.hpp>
#include <cppredicates/Ray2D.hpp>
#include <cppredicates/Sphere.hpp>
#include <cstdint>

//! Project namespace
namespace cppredicates
{
//! Describes orientation of points with respect to rays and planes
enum class Orientation : int {
    left = 1,     //!< Point is to the left of the ray
    right = -1,   //!< Point is to the right of the ray
    colinear = 0  //!< Point is coliniear with the ray
    // coplanar = 0x5,  //!< Point is coplanar with the plane
};

//! In-circle and in-sphere test result enum
enum class Orientation2 : int {
    inside = 1,    //!< Point is inside the circle/sphere
    outside = -1,  //!< Point is outside the circle/sphere
    boundary = 0   //!< Point is on the boundary of the circle/sphere
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
    real orientation(const Point2D& point, const Ray2D& ray);

    /** Checks the orienation of a point in 2D with respect to a given ray
     *
     *  @param point 2D-Point to examine
     *  @param ray Ray in 2D
     *
     *  @returns One of \c Orientation::left, \c Orientation::right or \c
     * Orientation::colinear
     */
    real orientationApprox(const Point2D& point, const Ray2D& ray);

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
    Orientation2 inCircle(const Point2D& point, const Circle2D& circle);

    /** Check whether a point in 3D is inside or outside a given sphere
     *
     *  @param point 3D-Point to examine
     *  @param sphere Sphere
     *
     *  @returns One of \c Orientation::inside or \c Orientation::outside
     */
    Orientation2 inSphere(const Point3D& point, const Sphere& sphere);

   private:
    real adaptiveOrient2D(const Point2D& point, const Ray2D& ray, real detsum);

   public:
    static const real m_epsilon;   //!< Machine epsilon
    static const real m_splitter;  //!< ...

   private:
    static const real m_resulterrbound;
    static const real m_ccwerrboundA;
    static const real m_ccwerrboundB;
    static const real m_ccwerrboundC;
    static const real m_o3derrboundA;
    static const real m_o3derrboundB;
    static const real m_o3derrboundC;
    static const real m_iccerrboundA;
    static const real m_iccerrboundB;
    static const real m_iccerrboundC;
    static const real m_isperrboundA;
    static const real m_isperrboundB;
    static const real m_isperrboundC;
};
}  // namespace cppredicates

#endif
