/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include <gtest/gtest.h>

#include "moto/Scalar.hpp"
#include "moto/ErrorTracer.hpp"
#include "moto/Vector3.hpp"
#include "moto/Metric.hpp"

typedef mt::ErrorTracer<float> Scalar;
typedef mt::Vector3<Scalar> Vector3;

TEST(Numerical, Traits)
{
    EXPECT_TRUE(mt::isnan(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_FALSE(mt::isnan(std::numeric_limits<float>::infinity()));

    EXPECT_FALSE(mt::isinf(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_TRUE(mt::isinf(std::numeric_limits<float>::infinity()));

    EXPECT_FALSE(mt::isfinite(std::numeric_limits<float>::quiet_NaN()));
    EXPECT_FALSE(mt::isfinite(std::numeric_limits<float>::infinity()));
    EXPECT_TRUE(mt::isfinite(std::numeric_limits<float>::max()));

    EXPECT_TRUE(mt::isnan(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(mt::isnan(std::numeric_limits<double>::infinity()));

    EXPECT_FALSE(mt::isinf(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_TRUE(mt::isinf(std::numeric_limits<double>::infinity()));

    EXPECT_FALSE(mt::isfinite(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_FALSE(mt::isfinite(std::numeric_limits<double>::infinity()));
    EXPECT_TRUE(mt::isfinite(std::numeric_limits<double>::max()));

    EXPECT_TRUE(mt::isnan(std::numeric_limits<Scalar>::quiet_NaN()));
    EXPECT_FALSE(mt::isnan(std::numeric_limits<Scalar>::infinity()));

    EXPECT_FALSE(mt::isinf(std::numeric_limits<Scalar>::quiet_NaN()));
    EXPECT_TRUE(mt::isinf(std::numeric_limits<Scalar>::infinity()));

    EXPECT_FALSE(mt::isfinite(std::numeric_limits<Scalar>::quiet_NaN()));
    EXPECT_FALSE(mt::isfinite(std::numeric_limits<Scalar>::infinity()));
    EXPECT_TRUE(mt::isfinite(std::numeric_limits<Scalar>::max()));
}

TEST(Numerical, Cancellation)
{
    Vector3 a(Scalar(1), Scalar(2), Scalar(3));
    Vector3 b(Scalar(100), Scalar(200), Scalar(300));
    Vector3 c(Scalar(100), Scalar(200), Scalar(301));

    // Compute the area of triangle abc in three different ways. Each result uses a different pair of edges.  

    Vector3 cross1 = cross(b - a, c - a);
    Vector3 cross2 = cross(c - b, a - b);
    Vector3 cross3 = cross(a - c, b - c);

    Scalar area1 = length(cross1) * Scalar(0.5);
    Scalar area2 = length(cross2) * Scalar(0.5);
    Scalar area3 = length(cross3) * Scalar(0.5);

    float r1 = area1.maxRelativeError();
    float r2 = area2.maxRelativeError();
    float r3 = area3.maxRelativeError();

    // Since area1 uses the longest pair of edges, its rounding error is greatest.
    EXPECT_GT(r1, r2);
    EXPECT_GT(r1, r3);
    
    // There is a dedicated function that returns the cross product with the least error.
    Vector3 cross4 = mt::normal(a, b, c);
    Scalar area4 = length(cross4) * Scalar(0.5);

    float r4 = area4.maxRelativeError();
    
    EXPECT_LE(r4, r1);
    EXPECT_LE(r4, r2);
    EXPECT_LE(r4, r3);
}

TEST(Numerical, OrderOfOperations)
{
    Vector3 a(Scalar(1), Scalar(2), Scalar(3));
    Vector3 b(Scalar(100), Scalar(200), Scalar(300));
    Vector3 c(Scalar(100), Scalar(200), Scalar(301));
    Vector3 d(Scalar(100), Scalar(201), Scalar(300));

    Vector3 y1 = b - a;
    Vector3 y2 = c - a;
    Vector3 y3 = d - a;


    // Dot product distributes over additions and subtractions, so the following result should be equal.
    Scalar d1 = dot(y1, y2 - y3);
    Scalar d2 = dot(y1, y2) - dot(y1, y3);

    // However, the latter result is much less robust.

    float r1 = d1.dirtyBits();
    float r2 = d2.dirtyBits();
    
    EXPECT_LT(r1, r2);
}
