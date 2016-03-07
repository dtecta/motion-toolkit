#ifndef IK_EULERANGLESJOINTLIMITS_HPP
#define IK_EULERANGLESJOINTLIMITS_HPP

#include "JointLimits.hpp"

namespace ik
{
    class EulerAnglesJointLimits
        : public JointLimits
    {
    public:
        EulerAnglesJointLimits(float minRx, float maxRx, float minRy, float maxRy, float minRz, float maxRz);

        void setLocalJointLimits(float minRx, float maxRx, float minRy, float maxRy, float minRz, float maxRz);


        // JointLimits overrides
        virtual void bound(DualQuaternion& relPose) const override;

    protected:
        Interval mLimits[3];   
    };

   
}

#endif
