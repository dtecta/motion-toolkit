/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "TestHelpers.hpp"

TEST(Trigonometry, EulerAngles)
{
    Random random;

    for (int k = 0; k != 1000; ++k)
    {
        Quaternion q = random.rotation();
        if (mt::isnegative(q.w))
        {
            q = -q;
        }
        Scalar yaw, pitch, roll;
        toEuler(yaw, pitch, roll, q);
        Quaternion q1 = mt::fromEuler(yaw, pitch, roll);
        if (mt::isnegative(q1.w))
        {
            q1 = -q1;
        }
        testFuzzyEqual(q, q1);
    }

}
