/*  MoTo - Motion Toolkit
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include <iostream>

#define USE_OSTREAM 1

#include "Scalar.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix2x2.hpp"
#include "Matrix3x3.hpp"
#include "Matrix4x4.hpp"
#include "Metric.hpp"
#include "Trigonometric.hpp"
#include "Random.hpp"

#include "Dual.hpp"
#include "DualVector3.hpp"
#include "DualVector4.hpp"
#include "DualMatrix3x3.hpp"



typedef float Scalar;  // We use "Scalar" as the abstract type for real values. Change "float" to "double" here for double precision.

typedef mt::ScalarTraits<Scalar> ScalarTraits; // Rather then extending std::numeric_limits, we chose to define our won traits class for numerical types. This one includes "pi".

// We instatiate a number of class templates for our Scalar type           
typedef mt::Vector2<Scalar> Vector2;
typedef mt::Vector3<Scalar> Vector3;
typedef mt::Matrix2x2<Scalar> Matrix2x2; // Matrix multiplication uses "mul" as well.
typedef mt::Vector4<Scalar> Quaternion; // mt::Vector4 is our template for quaternions. The quaternion product is "mul"
typedef mt::Matrix3x3<Scalar> Matrix3x3; // Matrix multiplication uses "mul" as well.
typedef mt::Matrix4x4<Scalar> Matrix4x4;

// These class templates are instatiated for our dual numbers type.
typedef mt::Dual<Scalar> Dual; 
typedef mt::Dual<Dual> Dual2;
typedef mt::Vector3<Dual> DualVector3;
typedef mt::Vector4<Dual> DualQuaternion;
typedef mt::Matrix3x3<Dual> DualMatrix3x3;

typedef mt::Random<Scalar> Random;

// These are types and templates that represent algebraic constants. We will use them in constructors of our vector and matrix types
using mt::Identity; // The identity for "mul" in all types
using mt::Zero; // The additive zero (in vector classes)
using mt::Unit; // A template for representing standard coordinate axes


// This function template performs a cubic interpolation over [0, 1] and is used as a sample function to illustrate automatic differentiation.
template <typename T>
T smoothstep(T x)
{  
    if (x < T())
        x = T();
    else if (x > T(1))
        x = T(1);
    return (T(3) - T(2) * x) * x * x;
} 

template <typename T>
T smoothstepprime(T x)
{  
    return dual(smoothstep(mt::Dual<T>(x, 1)));
} 


template <typename Vector>
bool fuzzyEqual(const Vector& lhs, const Vector& rhs)
{
    return lengthSquared(lhs - rhs) < ScalarTraits::epsilon();
}

bool fuzzyEqual(const DualQuaternion& lhs, const DualQuaternion& rhs)
{
    return fuzzyEqual(real(lhs), real(rhs)) && fuzzyEqual(dual(lhs), dual(rhs));
}

bool fuzzyEqual(const DualVector3& lhs, const DualVector3& rhs)
{
    return fuzzyEqual(real(lhs), real(rhs)) && fuzzyEqual(dual(lhs), dual(rhs));
}

int main()
{  
    Dual z1; // zero initialized
    Dual z2(2); // zero dual part
    Dual z3(2, 1); // Both real and dual part initialized

    // An example showing the use of dual numbers for automatic differentiation. 

    // smoothstep is a cubic function that takes a real number and returns a real number.
    for (int k = 0; k != 11; ++k)
    {
        // We go from zero to one, using a step of 0.1   
        Scalar x = Scalar(k) / Scalar(10);

        // and output the function values f(x) as follows.
        std::cout << "x = " << x << "\tf(x) = " << smoothstep(x) << std::endl;
    }
    
    // Since smoothstep is a template we can compute the first-order derivative by calling it using a dual number. 
    for (int k = 0; k != 11; ++k)
    {
        Scalar x = Scalar(k) / Scalar(10);

        // We differentiate f'(x) = d/dx f(x). This is perfomed automatically using dual number artihmetic.
        // smootstep is called using x + ε, ε is the dual unit.
        Dual y = smoothstep(Dual(x, 1));

        // The function value f(x) is the real part and the value of the first-order derivative f'(x) is the dual part.
        std::cout << "x = " << x << "\tf(x) = " << real(y) << "\tf'(x) = " << dual(y) << std::endl;
    } 

    // Let's represent the first-order derivative as a template function smoothstepprime.
    for (int k = 0; k != 11; ++k)
    {
        Scalar x = Scalar(k) / Scalar(10);

        // We output the derivative's values to show that this is indeed the first-order derivative.
        std::cout << "x = " << x << "\tf'(x) = " << smoothstepprime(x) << std::endl;
    }

    // We can compute the second-order derivative by calling smoothstepprime using a dual number. 
    for (int k = 0; k != 11; ++k)
    {
        Scalar x = Scalar(k) / Scalar(10);

        // We call smoothstepprime with x + ε.
        Dual y = smoothstepprime(Dual(x, 1));

        // So, the dual part of the result is the second-order derivative f''(x).
        std::cout << "x = " << x << "\tf'(x) = " << real(y) << "\tf''(x) = " << dual(y) << std::endl;
    }  

    // Or, we can compute function value, first-order derivative and second-order derivative in one go using a dual of duals.
    for (int k = 0; k != 11; ++k)
    {
        Scalar x = Scalar(k) / Scalar(10);

        // We call smoothstep using a dual number of duals. A dual of duals holds four scalars: a dual number as a real part,
        // and a dual number as a dual part.
        Dual2 y = smoothstep(Dual2(Dual(x, 1), 1));

        // The function value f(x) is the real part of the real part. 
        // The value of the first-order derivative f'(x) is the real part of the dual part (or the dual part of the real part).
        // The value of the second-order derivative f''(x) is the dual part of the dual part.
        std::cout << "x = " << x << "\tf(x) = " << real(real(y)) << "\tf'(x) = " << real(dual(y)) << "\tf''(x) = " << dual(dual(y)) << std::endl;
    } 
   
    // Dual numbers in line geometry and dual quaternions

    // PLUECKER COORDINATES

    Random random;

    // These are two random points inside a cube of size 20.     
    Vector3 p1 = random.uniformVector3(-10, 10);
    Vector3 q1 = random.uniformVector3(-10, 10);

    // Pluecker coordinates of the line through p and q
    DualVector3 linep1q1 = makeLine(p1, q1);

    // Generate a second line 
    Vector3 p2 = random.uniformVector3(-10, 10);
    Vector3 q2 = random.uniformVector3(-10, 10);

    // Pluecker coordinates of the line through p2 and q2
    DualVector3 linep2q2 = makeLine(p2, q2);

    // The permuted dot product on Pluecker coordinates is the dual of the dot product on dual vectors
    Dual linedot = dot(linep1q1, linep2q2);

    std::cout << "Line 1 and line 2 are ";
    if (dual(linedot) < Scalar())
    {
        std::cout << "oriented left-handed." << std::endl;
    }
    else if (dual(linedot) > Scalar())
    {
        std::cout << "oriented right-handed." << std::endl;
    }
    else
    {
        std::cout << "intersecting." << std::endl;
    }

    // Compute the angle between lines. The angle is acos(linedot) / sqrt(dot(linep1q1, linep1q1) * dot(linep2q2, linep2q2))
    // NB: the sign of the signed distance is opposite to the sign of dual(linedot). 
    Dual dualangle = angle(linep1q1, linep2q2);  

    std::cout << "The angle between line1 and line2 is " << mt::degrees(real(dualangle)) << " degrees," << std::endl;
    std::cout << "and the signed distance is " << dual(dualangle) << std::endl;


    // RIGID BODY TRANSFORMATIONS

    // Generate a random orientation. This quaternion is used for constructing a random rigid body transformation
    Quaternion orn = random.rotation();

    // A 3x3 basis at an arbitrary orientation is created.
    Matrix3x3 basis(orn);

    // The coordinate system is placed at an origin inside the same cube of size 20
    Vector3 origin = random.uniformVector3(-10, 10);

    // These are the points p and q after being transformed  
    Vector3 tp1 = mul(basis, p1) + origin;
    Vector3 tq1 = mul(basis, q1) + origin;

    // The transformed line can be constructed from the transformed points
    DualVector3 tlinepq = makeLine(tp1, tq1);

    // We can also transform the line directly through a dual 3x3 matrix
    DualMatrix3x3 xform = makeDual(basis, mul(cross(origin), basis));

    // The transformation is performed by 
    DualVector3 tlinepq2 = mul(xform, linep1q1);

    // tlinepq and tlinepg2 should be equal give or take a few rounding differences      
    ASSERT(fuzzyEqual(tlinepq, tlinepq2));


    // DUAL QUATERNIONS

    // The dual quaternion that performs the same rigid body transformation is 
    DualQuaternion dq = rigid(orn, origin);

    // Rotation and translation can be retrieved from a dual quaternion.

    Quaternion orn1 = rotation(dq);
    ASSERT(fuzzyEqual(orn, orn1));

    Vector3 origin1 = translation(dq);
    ASSERT(fuzzyEqual(origin, origin1));
    

    // The function operator on (dual) quaternions performs the transformation: dq(x) = mul(dq, mul(x, conjugate(dq)))
    DualVector3 tlinepq3 = dq(linep1q1);

    ASSERT(fuzzyEqual(tlinepq, tlinepq3));

    // Dual quaternions can be normalized, however, dq already has unit length
    DualQuaternion ndq = normalize(dq);

    DualQuaternion u = mul(dq, inverse(dq));
    DualQuaternion n = mul(dq, conjugate(dq)); 
    DualQuaternion nn = mul(ndq, conjugate(ndq));

    std::cout << "u = " << u << std::endl << "n = " << n << std::endl << "nn = " << nn << std::endl;

    // The dual matrix initialized using dq is equal to the one constructed directly from orn and origin.
    DualMatrix3x3 xform2(dq);

    DualMatrix3x3 diff = xform - xform2;

    // We generate another rigid body pose
    Quaternion orn2 = random.rotation();
    Vector3 origin2 = random.uniformVector3(-10, 10);

    DualQuaternion dq2 = rigid(orn2, origin2);


    // Three methods can be used for interpolation of unit dual quaternions and all three methods give us a unit dual quaternion, although the results are not equal.

    // Before we begin, make sure we use the closest transformation
    if (mt::isnegative(dot(dq, dq2)))
    {
        dq2 = -dq2; // dq2 and -dq2 are the same pose, but -dq2 is closer to dq than dq2 is.
    } 

    // Method #1: normalized lerp: normalize(lerp(dq, dq2, t)). 
    //            This one is commonly used in dual quaternion skinning since it is the simplest and is applicable to more than two poses.

    Scalar t = random.uniform();

    DualQuaternion method1 = nlerp(dq, dq2, t);

    // Method #2: spherical lerp. 
    //            This one interpolates with 'constant velocity' but only works between two poses. 

    DualQuaternion method2 = slerp(dq, dq2, t); 

    // Method #3: exponential of the lerp of the logarithms: exp(lerp(logUnit(dq), logUnit(dq2), t)). 
    //             This one is applicable to more than two poses, has 'constant velocity' as well, but does not necessarily follow the shortest path

    DualQuaternion method3 = logLerpUnit(dq, dq2, t);


    // SCREWS

    // Dual quaternions represent screw motions
    Dual screwangle = acos(dq.w);

    std::cout << "Screw angle is " << mt::degrees(real(screwangle)) << " degrees, pitch is " << dual(screwangle) << ',' << std::endl;

    DualVector3 axis = normalize(xyz(dq));

    std::cout << "and axis is " << axis << std::endl;



    // A point can be transformed directly by a dual quaternion. First create a dual quaternion from the point. 
    DualQuaternion dqp = makeDual(Quaternion(Identity()), Quaternion(p1, Scalar()));

    // Transform dqp using both the dual and quaternion conjugate, respectively denoted by "conj" and "conjugate".
    DualQuaternion tdqp = mul(dq, mul(dqp, conj(conjugate(dq))));

    // The resulting vector is obtained by
    Vector3 tdp = xyz(dual(tdqp));

    // which is equal to tp1 as verified below.
    ASSERT(fuzzyEqual(tp1, tdp));

   

    DualVector3 localvel = makeDual(Vector3(0, 0, -1), Vector3(1, 0, 0));
    DualQuaternion pose = rigid(Quaternion(Identity()), Vector3(0, 1, 0));
    
    Scalar step = Scalar(0.01);
    for (int k = 0; k != 100; ++k)
    {
        Dual angle = acos(pose.w) * Dual(2);

        std::cout << "Pose: " << pose << "Orientation: " << rotation(pose) << "\tPosition: " << translation(pose) << "\tAngle: " << angle << std::endl;

        DualVector3 worldvel = pose(localvel);
        DualQuaternion dPose = mul(worldvel, pose) * (step * Scalar(0.5));
        pose = normalize(pose + dPose);
      
    }

    Scalar theta = 1;
    for (int k = 0; k != 12; ++k)
    {
        DualQuaternion dqt = rigid(fromAxisAngle(Vector3(0, 1, 0), theta), Vector3(0, 0, 1));
        DualVector3 logdqt = logUnit(dqt); 
        DualQuaternion dqt2 = exp(logdqt);

        ASSERT(fuzzyEqual(dqt, dqt2));

        theta *= Scalar(0.5);
    }

    getchar();
    
    return 0;
}
