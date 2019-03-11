/*  IK - Sample Code for Rotational Joint Limits in Quaternion Space
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "jointlimits/EulerAnglesJointLimits.hpp"
#include "jointlimits/SwingTwistJointLimits.hpp"
#include "jointlimits/EllipsoidJointLimits.hpp"
#include "jointlimits/EllipticCylinderJointLimits.hpp"


using namespace ik;

#include "gtest/gtest.h"
#include <moto/Trigonometric.hpp>
#include <moto/Random.hpp>

template <typename Vector>
void testFuzzyEqual(const Vector& lhs, const Vector& rhs)
{
    EXPECT_LE(lengthSquared(lhs - rhs), ScalarTraits::epsilon() * 10);
}

void testFuzzyEqual(const DualQuaternion& lhs, const DualQuaternion& rhs)
{
    testFuzzyEqual(real(lhs), real(rhs));
    testFuzzyEqual(dual(lhs), dual(rhs));
}

void testFuzzyEqual(const DualVector3& lhs, const DualVector3& rhs)
{
    testFuzzyEqual(real(lhs), real(rhs));
    testFuzzyEqual(dual(lhs), dual(rhs));
}



TEST(RotationalJointLimits, EllipseClamp)
{
    mt::Random<Scalar> random;

    Ellipse ellipse;
    
    for (int k = 0; k != 10000; ++k)
    {
        ellipse.setBounds(random.uniform(), random.uniform());

        Scalar x = random.uniform(-1, 1);
        Scalar y = random.uniform(-1, 1);

        ellipse.clamp(x, y);

        Scalar result = ellipse.eval(x, y);

        EXPECT_LE(result, 20 * ScalarTraits::epsilon()); 
    }
    
}

TEST(RotationalJointLimits, EllipsoidClamp)
{
    mt::Random<Scalar> random;

    Ellipsoid ellipsoid;
    
    for (int k = 0; k != 10000; ++k)
    {
        ellipsoid.setBounds(random.uniform(), random.uniform(), random.uniform());

        Scalar x = random.uniform(-1, 1);
        Scalar y = random.uniform(-1, 1);
        Scalar z = random.uniform(-1, 1);

        ellipsoid.clamp(x, y, z);

        Scalar result = ellipsoid.eval(x, y, z);

        EXPECT_LE(result, 20 * ScalarTraits::epsilon()); 
    }
    
}

void testNoClampInvariant(JointLimits& limits)
{
    mt::Random<Scalar> random;

    for (int k = 0; k != 10000; ++k)
    {
        Quaternion q0 = random.rotation();
        if (mt::isnegative(q0.w))
        {
            q0 = -q0;
        }
        Vector3 p0 = random.uniformVector3(-10, 10);
        DualQuaternion relPose0 = rigid(q0, p0);
        DualQuaternion relPose1 = relPose0;

        limits.bound(relPose1); // Should perform a clamp since limits are set to unlimited
        testFuzzyEqual(relPose0, relPose1);
    }

}


TEST(RotationalJointLimits, NoClampInvariant)
{      
    EulerAnglesJointLimits euler(mt::radians<Scalar>(-180), mt::radians<Scalar>(180), mt::radians<Scalar>(-180), mt::radians<Scalar>(180), mt::radians<Scalar>(-180), mt::radians<Scalar>(180));
    testNoClampInvariant(euler);

    SwingTwistJointLimits swingTwist(mt::radians<Scalar>(-180), mt::radians<Scalar>(180), mt::radians<Scalar>(180), mt::radians<Scalar>(180));
    testNoClampInvariant(swingTwist);

    EllipticCylinderJointLimits elliptic(mt::radians<Scalar>(-180), mt::radians<Scalar>(180), mt::radians<Scalar>(180), mt::radians<Scalar>(180));
    testNoClampInvariant(elliptic);

    EllipsoidJointLimits ellipsoid(mt::radians<Scalar>(180), mt::radians<Scalar>(180), mt::radians<Scalar>(180));
    testNoClampInvariant(ellipsoid); 
}


void testAngle(const JointLimits& limits, const Quaternion& orn, Scalar degrees)
{
    DualQuaternion relPose = orn;
  
    limits.bound(relPose);

    EXPECT_FLOAT_EQ(mt::acos(real(relPose.w)) * 2, mt::radians<Scalar>(degrees));

}

void testSingleAxis(const JointLimits& limits)
{
    testAngle(limits, mt::fromAxisAngle(1, mt::radians<Scalar>(0)), 0);
    testAngle(limits, mt::fromAxisAngle(2, mt::radians<Scalar>(0)), 0);

    testAngle(limits, mt::fromAxisAngle(1, mt::radians<Scalar>(30)), 30);
    testAngle(limits, mt::fromAxisAngle(2, mt::radians<Scalar>(30)), 30);

    testAngle(limits, mt::fromAxisAngle(1, mt::radians<Scalar>(45)), 45);
    testAngle(limits, mt::fromAxisAngle(2, mt::radians<Scalar>(45)), 45);

    testAngle(limits, mt::fromAxisAngle(1, mt::radians<Scalar>(60)), 45);
    testAngle(limits, mt::fromAxisAngle(2, mt::radians<Scalar>(60)), 60);

    testAngle(limits, mt::fromAxisAngle(1, mt::radians<Scalar>(90)), 45);
    testAngle(limits, mt::fromAxisAngle(2, mt::radians<Scalar>(90)), 60);
}


TEST(RotationalJointLimits, SingleAxis)
{
    EulerAnglesJointLimits euler(mt::radians<Scalar>(0), mt::radians<Scalar>(0), mt::radians<Scalar>(-45), mt::radians<Scalar>(45), mt::radians<Scalar>(-60), mt::radians<Scalar>(60));
    testSingleAxis(euler);

    SwingTwistJointLimits swingTwist(mt::radians<Scalar>(0), mt::radians<Scalar>(0), mt::radians<Scalar>(45), mt::radians<Scalar>(60));
    testSingleAxis(swingTwist);

    EllipticCylinderJointLimits elliptic(mt::radians<Scalar>(0), mt::radians<Scalar>(0), mt::radians<Scalar>(45), mt::radians<Scalar>(60));
    testSingleAxis(elliptic);

    EllipsoidJointLimits ellipsoid(mt::radians<Scalar>(30), mt::radians<Scalar>(45), mt::radians<Scalar>(60));
    testSingleAxis(ellipsoid);
}
