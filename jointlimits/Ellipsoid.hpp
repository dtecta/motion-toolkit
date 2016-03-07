#ifndef IK_ELLIPSOID_HPP
#define IK_ELLIPSOID_HPP

#include "Types.hpp"

namespace ik
{
    /**
     * This class represent an ellipsoid that is used for clamping 3D points. Points that lie outside the ellipoide are clamped to the point on the boundary closest to their location.
     */

    class Ellipsoid
    {
    public:
        /**
         * Ellipsoid is unit sphere by default. A radius of 1 denotes a rotation of 180 degrees in quaternion space. 180 degrees is the maximum angle you may use as a swing limit.
         */
        explicit Ellipsoid(Scalar a = 1, Scalar b = 1, Scalar c = 1)
        {
            setBounds(a, b, c);
        }

        
        /**
         * Sets the dimensions of the ellipsoid. 
         * These values represent sin(theta / 2), where theta is the maximum swing angle. The values are required to lie in the range (0, 1].

         * @param a            radius on X axis
         * @param b            radius on Y axis
         * @param c            radius on Z axis
         */
        void setBounds(Scalar a, Scalar b, Scalar c)
        {
            ASSERT(0 < a && a <= 1);
            ASSERT(0 < b && b <= 1);
            ASSERT(0 < c && c <= 1);

            mA = a;
            mB = b;
            mC = c;
        }
          
        /**
         * Clamps a 3D point against the ellipsoid. The returned (x, y, z) is the point inside or on the boundary of the ellipsoid closest to the input point.
         * @param x           x coordinate
         * @param y           y coordinate
         * @param z           z coordinate
         * @param k           maximum number of Newton-Raphson iterations 
         */
        void clamp(Scalar& x, Scalar& y, Scalar& z, int k = 50) const;

            
        /**
         * Returns a scalar that denotes the location wrt the ellipsoid. 
         * @param x           x coordinate
         * @param y           y coordinate
         * @param z           z coordinate
         * @return            negative value denotes a point inside the ellipsoid. Zero denotes a point on the boundary. Positive value denotes outside the ellipsoid.
         */
        Scalar eval(Scalar x, Scalar y, Scalar z) const 
        {
            return mt::square(x / mA) + mt::square(y / mB) + mt::square(z / mC) - 1;
        }
        
    private:
        /**
         * Generating function for the Newton-Raphson iteration. This is a function template since the t argument may be a Scalar or Dual number. 
         * @param t           real or dual parameter that "offsets" the point closer to the ellipse
         * @param x           x coordinate
         * @param y           y coordinate
         * @param z           z coordinate
         * @return            real or dual parameter for the new position.
         */
        template <typename ScalarParam>
        ScalarParam genFunc(ScalarParam t, Scalar x, Scalar y, Scalar z) const
        {
            return mt::square(x * mA / (mA * mA + t)) + mt::square(y * mB / (mB * mB + t)) + mt::square(z * mC / (mC * mC + t)) - Scalar(1);
        }

        static Scalar sTolerance; /// Maximum allowed error in the generating function's return value

        Scalar mA; /// horizontal radius (half width)
        Scalar mB; /// vertical radius (half height)
        Scalar mC; /// vertical radius (half height)
    };   
}

#endif
