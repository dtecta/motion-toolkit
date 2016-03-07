#include "SwingTwistJointLimits.hpp"



#define TWIST_BEFORE_SWING 0

namespace ik
{   
    SwingTwistJointLimits::SwingTwistJointLimits(Scalar minRx, Scalar maxRx, Scalar maxRy, Scalar maxRz)
    {
        setLocalJointLimits(minRx, maxRx, maxRy, maxRz);
    }


    void SwingTwistJointLimits::setLocalJointLimits(Scalar minRx, Scalar maxRx, Scalar maxRy, Scalar maxRz)
    {
        ASSERT(-ScalarTraits::pi() <= minRx && minRx <= maxRx && maxRx <= ScalarTraits::pi());
        ASSERT(0 < maxRy && maxRy <= ScalarTraits::pi());
        ASSERT(0 < maxRz && maxRz <= ScalarTraits::pi());

        mTwistLimit = Interval(mt::sin(minRx * Scalar(0.5)), mt::sin(maxRx * Scalar(0.5)));
        mSwingCone.setBounds(mt::sin(maxRy * Scalar(0.5)), mt::sin(maxRz * Scalar(0.5)));
    }


    
    void SwingTwistJointLimits::bound(DualQuaternion& relPose) const
    {
        Quaternion q = rotation(relPose);
        Vector3 p = translation(relPose);

        // Make sure the scalar part is positive. Since quaternions have a double covering, q and -q represent the same orientation.
        if (mt::isnegative(q.w))
        {
            q = -q; // Negate the quaternion. Still represents the same orientation.
        }

        // Here swing and twist are dependent. The twist can be applied before or after the swing. After (parent ->swing -> twist -> child) makes the most sense
        Scalar rx, ry, rz;
        Scalar s = q.x * q.x + q.w * q.w;
        if (mt::iszero(s))
        { 
            // swing by 180 degrees is a singularity. We assume twist is zero.
            rx = 0;
            ry = q.y;
            rz = q.z;
        }
        else
        {
            Scalar r = mt::rsqrt(s);

            rx = q.x * r;
    
#if TWIST_BEFORE_SWING
            ry = (q.w * q.y + q.x * q.z) * r;
            rz = (q.w * q.z - q.x * q.y) * r;
#else  
            ry = (q.w * q.y - q.x * q.z) * r;
            rz = (q.w * q.z + q.x * q.y) * r;
#endif

        }

        rx = clamp(rx, mTwistLimit);

        mSwingCone.clamp(ry, rz);

        Quaternion qTwist(rx, 0, 0, mt::sqrt(mt::max<Scalar>(0, 1 - rx * rx)));
        Quaternion qSwing(0, ry, rz, mt::sqrt(mt::max<Scalar>(0, 1 - ry * ry - rz * rz)));
     
     
#if TWIST_BEFORE_SWING
        q = mul(qTwist, qSwing);
#else
        q = mul(qSwing, qTwist);
#endif

        relPose = rigid(q, p);
    }

}