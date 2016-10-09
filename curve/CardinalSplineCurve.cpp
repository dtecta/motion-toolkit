/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "CardinalSplineCurve.hpp"


namespace cv
{
    DualVector3 CardinalSplineCurve::eval(Scalar param) const
    {
        ASSERT(Scalar() <= param && param <= Scalar(1));

        Scalar h = Scalar(mPoints.size() - 3);
            
        Scalar intg;
        Scalar frac = modf(param * h, &intg);
        int index = int(intg);
        if (index + 3 == int(mPoints.size()))
        {
            frac += Scalar(1);
            --index;
        }

        ASSERT(Scalar() <= frac && frac <= Scalar(1));
        ASSERT(0 <= index && index + 3 < int(mPoints.size()));
        
        Dual t = Dual(frac, Scalar(1));
        Dual t2 = t * t;
        Dual t3 = t2 * t;

        const Vector3* points = &mPoints[index];

        Vector3 m1 = (points[2] - points[0]) * mAlpha;
        Vector3 m2 = (points[3] - points[1]) * mAlpha;
        Vector3 d = points[2] - points[1];

        return (-Scalar(2) * d + m1 + m2) * t3 + 
               (Scalar(3) * d - Scalar(2) * m1 - m2) * t2 + 
               m1 * t + 
               points[1];
    }
}
