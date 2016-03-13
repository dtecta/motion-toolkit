/*  IK - Sample Code for Rotational Joint Limits in Quaternion Space
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "Ellipse.hpp"

namespace ik
{   
    Scalar Ellipse::sTolerance = ScalarTraits::epsilon() * 10;

    void Ellipse::clamp(Scalar& x, Scalar& y, int k) const
    {
        // (x, y) outside the ellipse?
        if (mt::ispositive(eval(x, y)))
        {
            Scalar t = 0; // It is assumed that (x, y) is close to the boundary of the ellipse, so t0 = 0 is a proper intial value. Since our query point lies
            // outside the ellipsoid the final t cannot be negative. We are solving: (x', y') for which
            // x = x' * (1 + t / (mA * mA)) and y = y' * (1 + t / (mB * mB))  under the constraint that eval(x', y') == 0.
            
            Dual result; // Calling the function using dual numbers. The result holds the function's value as real component and the derivative's value as dual component.
            while (k != 0 && real(result = genFunc(Dual(t, 1), x, y)) > sTolerance)
            {
                t -= real(result) / dual(result); // Newton-Raphson step: t1 = t0 - F(t, x, y) / F'(t, x, y)
                --k;
            }
            
            // Set the point (x, y) to the closest point on the boundary of the ellipse
            x *= mA * mA / (mA * mA + t);
            y *= mB * mB / (mB * mB + t);
        }

    }
        
}
