#include "EllipticCylinderJointLimits.hpp"

namespace ik
{   
    EllipticCylinderJointLimits::EllipticCylinderJointLimits(Scalar minRx, Scalar maxRx, Scalar maxRy, Scalar maxRz)
    {
        setLocalJointLimits(minRx, maxRx, maxRy, maxRz);
    }


    void EllipticCylinderJointLimits::setLocalJointLimits(Scalar minRx, Scalar maxRx, Scalar maxRy, Scalar maxRz)
    {
        ASSERT(-ScalarTraits::pi() <= minRx && minRx <= maxRx && maxRx <= ScalarTraits::pi());
        ASSERT(0 < maxRy && maxRy <= ScalarTraits::pi());
        ASSERT(0 < maxRz && maxRz <= ScalarTraits::pi());

        mLimit = Interval(mt::sin(minRx * Scalar(0.5)), mt::sin(maxRx * Scalar(0.5)));
        mEllipse.setBounds(mt::sin(maxRy * Scalar(0.5)), mt::sin(maxRz * Scalar(0.5)));
    }


    
    void EllipticCylinderJointLimits::bound(DualQuaternion& relPose) const
    {
        Quaternion q = rotation(relPose);
        Vector3 p = translation(relPose);

        // Make sure the scalar part is positive. Since quaternions have a double covering, q and -q represent the same orientation.
        if (mt::isnegative(q.w))
        {
            q = -q; // Negate the quaternion. Still represents the same orientation.
        }

        // Swing and twist are handled independently in quaternion space. Cheapest and most predictable method.
        q.x = clamp(q.x, mLimit);      

        mEllipse.clamp(q.y, q.z);

        // We clamp the vector part, and recompute the scalar part (w). The scalar part is known up to a sign, but since we made sure that w was positive, and clamping does not switch the sign,
        // we can return a positive scalar part here.
        q.w = mt::sqrt(mt::max<Scalar>(0, 1 - (q.x * q.x + q.y * q.y + q.z * q.z)));

        relPose = rigid(q, p);
    }

}