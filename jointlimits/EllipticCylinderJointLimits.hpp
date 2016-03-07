#ifndef IK_ELLIPTICCYLINDERJOINTLIMITS_HPP
#define IK_ELLIPTICCYLINDERJOINTLIMITS_HPP

#include "JointLimits.hpp"
#include "Ellipse.hpp"

namespace ik
{
    class EllipticCylinderJointLimits
        : public JointLimits
    {
    public:
         EllipticCylinderJointLimits(Scalar minRx, Scalar maxRx, Scalar maxRy, Scalar maxRz);

        void setLocalJointLimits(Scalar minRx, Scalar maxRx, Scalar maxRy, Scalar maxRz);


        // JointLimits overrides

        virtual void bound(DualQuaternion& relPose) const override;  

    private:
        Interval mLimit;
        Ellipse mEllipse;
    };

   
}

#endif
