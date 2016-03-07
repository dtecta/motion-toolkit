#include "Ellipsoid.hpp"

namespace ik
{   
    Scalar Ellipsoid::sTolerance = ScalarTraits::epsilon() * 10;

    void Ellipsoid::clamp(Scalar& x, Scalar& y, Scalar& z,  int k) const
    {
        // (x, y, z) outside the ellipsoid?
        if (mt::ispositive(eval(x, y, z)))
        {
            Scalar t = 0; // It is assumed that (x, y, z) is close to the boundary of the ellipsoid, so t0 = 0 is a proper intial value. Since our query point lies
            // outside the ellipsoid the final t cannot be negative. We are solving: (x', y', z') for which
            // x = x' * (1 + t / (mA * mA)), y = y' * (1 + t / (mB * mB)), and z = z' * (1 + t / (mC * mC)) under the constraint that eval(x', y', z') == 0.
            
            Dual result; // Calling the function using dual numbers. The result holds the function's value as real component and the derivative's value as dual component.
            while (k != 0 && real(result = genFunc(Dual(t, 1), x, y, z)) > sTolerance)
            {
                t -= real(result) / dual(result); // Newton-Raphson step: t1 = t0 - F(t, x, y) / F'(t, x, y)
                --k;
            }
            
            // Set the point (x, y, z) to the closest point on the boundary of the ellipse
            x *= mA * mA / (mA * mA + t);
            y *= mB * mB / (mB * mB + t);
            z *= mC * mC / (mC * mC + t);

        }

    }
        
}
