#ifndef IK_ELLIPSOIDJOINTLIMITS_HPP
#define IK_ELLIPSOIDJOINTLIMITS_HPP

#include "JointLimits.hpp"
#include "Ellipsoid.hpp"

namespace ik
{
    class EllipsoidJointLimits
        : public JointLimits
    {
    public:
         EllipsoidJointLimits(Scalar maxRx, Scalar maxRy, Scalar maxRz);

        void setLocalJointLimits(Scalar maxRx, Scalar maxRy, Scalar maxRz);


        // JointLimits overrides

        virtual void bound(DualQuaternion& relPose) const override;  

    private:
        Ellipsoid mEllipsoid;
    };

   
}

#endif
