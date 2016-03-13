/*  IK - Sample Code for Rotational Joint Limits in Quaternion Space
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "EllipsoidJointLimits.hpp"

namespace ik
{   
    EllipsoidJointLimits::EllipsoidJointLimits(Scalar maxRx, Scalar maxRy, Scalar maxRz)
    {
        setLocalJointLimits(maxRx, maxRy, maxRz);
    }


    void EllipsoidJointLimits::setLocalJointLimits(Scalar maxRx, Scalar maxRy, Scalar maxRz)
    {
        ASSERT(0 < maxRx && maxRx <= ScalarTraits::pi());
        ASSERT(0 < maxRy && maxRy <= ScalarTraits::pi());
        ASSERT(0 < maxRz && maxRz <= ScalarTraits::pi());

        mEllipsoid.setBounds(mt::sin(maxRx * Scalar(0.5)), mt::sin(maxRy * Scalar(0.5)), mt::sin(maxRz * Scalar(0.5)));
    }


    
    void EllipsoidJointLimits::bound(DualQuaternion& relPose) const
    {
        Quaternion q = rotation(relPose);
        Vector3 p = translation(relPose);

        // Make sure the scalar part is positive. Since quaternions have a double covering, q and -q represent the same orientation.
        if (mt::isnegative(q.w))
        {
            q = -q; // Negate the quaternion. Still represents the same orientation.
        }

        mEllipsoid.clamp(q.x, q.y, q.z);

        // We clamp the vector part, and recompute the scalar part (w). The scalar part is known up to a sign, but since we made sure that w was positive, and clamping does not switch the sign,
        // we can return a positive scalar part here.
        q.w = mt::sqrt(mt::max<Scalar>(0, 1 - (q.x * q.x + q.y * q.y + q.z * q.z)));

        relPose = rigid(q, p);
    }

}
