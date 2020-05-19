#ifndef CPPREDICATES_PLANE_3D_H
#define CPPREDICATES_PLANE_3D_H

#include <cppredicates/Point3D.hpp>

namespace cppredicates
{
//! Represents a plane in three dimensions
template <class T>
class Plane3D_T {
   public:
    //! Default constructor
    Plane3D_T<T>() = default;

    /** Constructs a plane from a \c normal
     *
     * @param normal_ Normal vector defining this plane (assumed to point
     * upwards)
     */
    explicit Plane3D_T<T>(const Point3D_T<T>& normal_) {
        // TODO convert to 3 points
    }

    /** Constructor from three coplanar points
     *
     *  @param pA \c Point3D A on the circle
     *  @param pB \c Point3D B on the circle
     *  @param pC \c Point3D C on the circle
     */
    explicit Plane3D_T(const Point3D_T<T>& pA, const Point3D_T<T>& pB,
                       const Point3D_T<T>& pC)
        : pA(pA), pB(pB), pC(pC) {}

    /** Default move constructor
     *
     *  @param other  Other plane to move from
     */
    Plane3D_T(Plane3D_T&& other) = default;
    /** Default move assignment
     *
     *  @param other Other plane to move from
     *  @return      Move constructed plane
     */
    Plane3D_T& operator=(Plane3D_T&& other) = default;

   private:
    Point3D_T<T> pA;
    Point3D_T<T> pB;
    Point3D_T<T> pC;
};

// Template implementation
#include "Plane3D.tpp"

//! Explicit template instantiation for type Plane3D
using Plane3D = Plane3D_T<real>;

}  // namespace cppredicates

#endif
