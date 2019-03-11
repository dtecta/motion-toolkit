/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include <gtest/gtest.h>

#include "Types.hpp"

template <typename Vector>
void testFuzzyEqual(const Vector& lhs, const Vector& rhs)
{
    EXPECT_LE(lengthSquared(lhs - rhs), ScalarTraits::epsilon());
}

inline
void testFuzzyEqual(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
    testFuzzyEqual(lhs[0], rhs[0]);
    testFuzzyEqual(lhs[1], rhs[1]);
    testFuzzyEqual(lhs[2], rhs[2]);
}

inline
void testFuzzyEqual(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
    testFuzzyEqual(lhs[0], rhs[0]);
    testFuzzyEqual(lhs[1], rhs[1]);
    testFuzzyEqual(lhs[2], rhs[2]);
    testFuzzyEqual(lhs[3], rhs[3]);
}

inline
void testFuzzyEqual(const DualQuaternion& lhs, const DualQuaternion& rhs)
{
    testFuzzyEqual(real(lhs), real(rhs));
    testFuzzyEqual(dual(lhs), dual(rhs));
}

inline
void testFuzzyEqual(const DualVector3& lhs, const DualVector3& rhs)
{
    testFuzzyEqual(real(lhs), real(rhs));
    testFuzzyEqual(dual(lhs), dual(rhs));
}
