/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include <iostream>

#define USE_OSTREAM 1

#include "moto/Scalar.hpp"
#include "moto/Vector3.hpp"
#include "moto/Vector4.hpp"
#include "moto/Matrix2x2.hpp"
#include "moto/Matrix3x3.hpp"
#include "moto/Matrix4x4.hpp"
#include "moto/Metric.hpp"
#include "moto/Trigonometric.hpp"
#include "moto/Random.hpp"

#include "moto/Dual.hpp"
#include "moto/DualVector3.hpp"
#include "moto/DualVector4.hpp"
#include "moto/DualMatrix3x3.hpp"

#include "moto/Matrix3x4.hpp"
#include "moto/Matrix4x3.hpp"

typedef float Scalar;  // We use "Scalar" as the abstract type for real values. Change "float" to "double" here for double precision.

typedef mt::ScalarTraits<Scalar> ScalarTraits; // Rather then extending std::numeric_limits, we chose to define our won traits class for numerical types. This one includes "pi".

// We instatiate a number of class templates for our Scalar type           
typedef mt::Vector2<Scalar> Vector2;
typedef mt::Vector3<Scalar> Vector3;
typedef mt::Matrix2x2<Scalar> Matrix2x2; // Matrix multiplication uses "mul" as well.
typedef mt::Vector4<Scalar> Quaternion; // mt::Vector4 is our template for quaternions. The quaternion product is "mul"
typedef mt::Matrix3x3<Scalar> Matrix3x3; // Matrix multiplication uses "mul" as well.
typedef mt::Matrix4x4<Scalar> Matrix4x4;
typedef mt::Matrix3x4<Scalar> Matrix3x4;
typedef mt::Matrix4x3<Scalar> Matrix4x3;

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
