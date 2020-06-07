#ifndef CPPREDICATES_RAY_2D_T_H
#define CPPREDICATES_RAY_2D_T_H

#include <cppredicates/Point2D_T.hpp>

#include <utility>

namespace cppredicates
{
//! Represents a ray in two dimensions
template <class T>
class Ray2D_T {
   public:
    //! Default constructor
    Ray2D_T() = default;

    /** Construct a ray starting at \c origin, going through \c through
     *
     *  @param origin  Start of this ray
     *  @param through This ray goes through this point
     */
    explicit Ray2D_T(Point2D_T<T> origin, Point2D_T<T> through)
        : m_origin(std::move(origin)), m_through(std::move(through)) {}

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

    /** Access \c m_origin
     *
     *  @returns origin of this ray
     */
    const Point2D_T<T>& origin() const { return m_origin; }

    /** Access \c m_through
     *
     *  @returns point defining the direction of this ray
     */
    const Point2D_T<T>& through() const { return m_through; }

   private:
    Point2D_T<T> m_origin;
    Point2D_T<T> m_through;
};

// Template implementation
#include "Ray2D_T.tpp"

}  // namespace cppredicates

#endif
