/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/


#include "TestHelpers.hpp"

TEST(Matrix, Matrix4x3)
{
    Random random;

    Quaternion q = random.rotation();

    Matrix4x3 psi = lquat4x3(q);
   
    Matrix3x3 rp1 = transposeMul(psi, psi);
    testFuzzyEqual(Matrix3x3(Identity()), rp1);
    
    Matrix3x3 rp2 = mul(transpose(psi), psi);
    testFuzzyEqual(Matrix3x3(Identity()), rp2);   

    Matrix4x4 rp3 = mulTranspose(psi, psi);
    testFuzzyEqual(Matrix4x4(Identity()) - dyad(q, q), rp3);

    Vector3 rp4 = mul(q, psi);
    testFuzzyEqual(Vector3(Zero()), rp4);


    Matrix4x3 xsi = rquat4x3(q);

    Matrix3x3 rx1 = transposeMul(xsi, xsi);
    testFuzzyEqual(Matrix3x3(Identity()), rx1);

    Matrix3x3 rx2 = mul(transpose(xsi), xsi);
    testFuzzyEqual(Matrix3x3(Identity()), rx2);

    Matrix4x4 rx3 = mulTranspose(xsi, xsi);
    testFuzzyEqual(Matrix4x4(Identity()) - dyad(q, q), rx3);

    Vector3 rx4 = mul(q, xsi);
    testFuzzyEqual(Vector3(Zero()), rx4);
}
