/*  IK - Sample Code for Rotational Joint Limits in Quaternion Space
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef IK_ELLIPSE_HPP
#define IK_ELLIPSE_HPP

#include "Types.hpp"

namespace ik
{
    /**
     * This class represent an ellipse that used for clamping 2D points. Points that lie outside the ellipse are clamped to the point on the boundary closest to their location.
     */

    class Ellipse
    {
    public:
        /**
         * Ellipse is unit circle by default. A radius of 1 denotes a rotation of 180 degrees in quaternion space. 180 degrees is the maximum angle you may use as a swing limit.
         */
        explicit Ellipse(Scalar a = 1, Scalar b = 1)
        {
            setBounds(a, b);
        }

        
        /**
         * Sets the horizontal and vertical radius of the ellipse. 
         * These values represent sin(theta / 2), where theta is the maximum swing angle. The values are required to lie in the range (0, 1].

         * @param a            horizontal radius (half width)
         * @param b            vertical radius (half height)
         */
        void setBounds(Scalar a, Scalar b)
        {
            ASSERT(0 < a && a <= 1);
            ASSERT(0 < b && b <= 1);

            mA = a;
            mB = b;
        }
          
        /**
         * Clamps a 2D point against the ellipse. The returned (x, y) is the point inside or on the boundary of the ellipse closest to the input point.
         * @param x           horizontal coordinate of point
         * @param y           vertical coordinate of point
         * @param k           maximum number of Newton-Raphson iterations 
         */
        void clamp(Scalar& x, Scalar& y, int k = 50) const;

            
        /**
         * Returns a scalar that denotes the location wrt the ellipse. 
         * @param x           horizontal coordinate of point
         * @param y           vertical coordinate of point
         * @return            negative value denotes a point inside the ellipse. Zero denotes a point on the boundary. Positive value denotes outside the ellipse.
         */
        Scalar eval(Scalar x, Scalar y) const 
        {
            return mt::square(x / mA) + mt::square(y / mB) - 1;
        }
        
    private:
        /**
         * Generating function for the Newton-Raphson iteration. This is a function template since the t argument may be a Scalar or Dual number. 
         * @param t           real or dual parameter that "offsets" the point closer to the ellipse
         * @param x           horizontal coordinate of point
         * @param y           vertical coordinate of point
         * @return            real or dual parameter for the new position.
         */
        template <typename ScalarParam>
        ScalarParam genFunc(ScalarParam t, Scalar x, Scalar y) const
        {
            return mt::square(x * mA / (mA * mA + t)) + mt::square(y * mB / (mB * mB + t)) - Scalar(1);
        }

        static Scalar sTolerance; /// Maximum allowed error in the generating function's return value

        Scalar mA; /// horizontal radius (half width)
        Scalar mB; /// vertical radius (half height)
    };   
}

#endif
