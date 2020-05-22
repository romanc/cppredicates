#ifndef CPPREDICATES_RAY_2D_T_H
#define CPPREDICATES_RAY_2D_T_H

#include <cppredicates/Point2D_T.hpp>

namespace cppredicates
{
//! Represents a ray in two dimensions
template <class T>
class Ray2D_T {
   public:
    //! Default constructor
    Ray2D_T() = default;

    /** Construct a ray starting at \c origin_, going through \c through_
     *
     *  @param origin_  Start of this ray
     *  @param through_ This ray goes through this point
     */
    explicit Ray2D_T(const Point2D_T<T>& origin_, const Point2D_T<T>& through_)
        : origin(origin_), through(through_) {}

    /** Default move constructor
     *
     *  @param r  Other ray to move from
     */
    Ray2D_T(Ray2D_T<T>&& r) = default;
    /** Default move assignment
     *
     *  @param r Other ray to move from
     *  @return  Move constructed ray
     */
    Ray2D_T<T>& operator=(Ray2D_T<T>&& r) = default;

   private:
    Point2D_T<T> origin;
    Point2D_T<T> through;
};

// Template implementation
#include "Ray2D_T.tpp"

}  // namespace cppredicates

#endif
