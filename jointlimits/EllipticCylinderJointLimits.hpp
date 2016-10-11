/*  IK - Sample Code for Rotational Joint Limits in Quaternion Space
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

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

        virtual void bound(DualQuaternion& relPose) const OVERRIDE;  

    private:
        Interval mLimit;
        Ellipse mEllipse;
    };

   
}

#endif
