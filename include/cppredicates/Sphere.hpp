#ifndef CPPREDICATES_SPHERE_H
#define CPPREDICATES_SPHERE_H

#include <cppredicates/Point3D.hpp>

namespace cppredicates
{
//! Represents a sphere in three dimensions
template <class T>
class Sphere_T {
   public:
    //! Default constructor
    Sphere_T() = default;

    /** Constructor from \c origin and \c radius
     *
     *  @param origin Center of the sphere
     *  @param radius Radius of the sphere
     */
    explicit Sphere_T(const Point3D_T<T>& origin, T radius) {
        // TODO convert to 4 points in 3D
    }

    /** Constructor from four points
     *
     *  @param pA \c Point3D A on the circle
     *  @param pB \c Point3D B on the circle
     *  @param pC \c Point3D C on the circle
     *  @param pD \c Point3D D on the circle
     */
    explicit Sphere_T(const Point3D_T<T>& pA, const Point3D_T<T>& pB,
                      const Point3D_T<T>& pC, const Point3D_T<T>& pD)
        : pA(pA), pB(pB), pC(pC), pD(pD) {}

    /** Default move constructor
     *
     *  @param other Other sphere to move from
     */
    Sphere_T(Sphere_T&& other) = default;
    /** Default move assignment
     *
     *  @param other Other sphere to move from
     *  @return      Move constructed circle
     */
    Sphere_T& operator=(Sphere_T&& other) = default;

   private:
    Point3D_T<T> pA;
    Point3D_T<T> pB;
    Point3D_T<T> pC;
    Point3D_T<T> pD;
};

// Template implementations
#include "Sphere.tpp"

//! Explicit template instantiation for type Sphere
using Sphere = Sphere_T<real>;

}  // namespace cppredicates

#endif
