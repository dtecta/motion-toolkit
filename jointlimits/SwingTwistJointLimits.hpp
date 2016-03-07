#ifndef IK_SWINGTWISTJOINTLIMITS_HPP
#define IK_SWINGTWISTJOINTLIMITS_HPP

#include "JointLimits.hpp"
#include "Ellipse.hpp"

namespace ik
{
    class SwingTwistJointLimits
        : public JointLimits
    {
    public:
        SwingTwistJointLimits(Scalar minRx, Scalar maxRx, Scalar maxRy, Scalar maxRz);

        void setLocalJointLimits(Scalar minRx, Scalar maxRx, Scalar maxRy, Scalar maxRz);


        // JointLimits overrides

        virtual void bound(DualQuaternion& relPose) const override;  

    private:
        Interval mTwistLimit;
        Ellipse mSwingCone;
    };

   
}

#endif
