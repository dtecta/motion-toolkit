#include "EulerAnglesJointLimits.hpp"
#include <moto/Trigonometric.hpp>

namespace ik
{
    EulerAnglesJointLimits::EulerAnglesJointLimits(float minRx, float maxRx, float minRy, float maxRy, float minRz, float maxRz)
    {
        setLocalJointLimits(minRx, maxRx, minRy, maxRy, minRz, maxRz);
    }


    void EulerAnglesJointLimits::setLocalJointLimits(float minRx, float maxRx, float minRy, float maxRy, float minRz, float maxRz)
    {
        mLimits[0].lower() = minRx;
        mLimits[0].upper() = maxRx;
        mLimits[1].lower() = minRy;
        mLimits[1].upper() = maxRy;
        mLimits[2].lower() = minRz;
        mLimits[2].upper() = maxRz;     
    }

    void EulerAnglesJointLimits::bound(DualQuaternion& relPose) const
    { 
        Quaternion q = rotation(relPose);
        Vector3 p = translation(relPose);

        Scalar yaw, pitch, roll;
        toEuler(yaw, pitch, roll, q);

        yaw = clamp(yaw, mLimits[1]);
        pitch = clamp(pitch, mLimits[0]);
        roll = clamp(roll, mLimits[2]);
        
        q = mt::fromEuler(yaw, pitch, roll);
        if (mt::isnegative(q.w))
        {
            q = -q;
        }
        
        relPose = rigid(q, p);
    }

    
}
