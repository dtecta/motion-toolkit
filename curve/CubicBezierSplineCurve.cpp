/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "CubicBezierSplineCurve.hpp"


namespace cv
{

    DualVector3 CubicBezierSplineCurve::eval(Scalar param) const
    {
        ASSERT(Scalar() <= param && param <= Scalar(1));

        Scalar h = Scalar((mPoints.size() - 1) / 3);
            
        Scalar intg;
        Scalar frac = mt::modf(param * h, &intg);
        int index = int(intg) * 3;
        if (index + 1 == int(mPoints.size()))
        {
            frac += Scalar(1);
            index -= 3;
        }

        ASSERT(Scalar() <= frac && frac <= Scalar(1));
        ASSERT(0 <= index && index + 3 < int(mPoints.size()));  

		const Vector3* points = &mPoints[index];
        
		Dual t = Dual(frac, Scalar(1));
		Dual oneMinusT = Scalar(1) - t; 
        Dual oneMinusTSquared = mt::square(oneMinusT);
        Dual oneMinusTCubed = oneMinusTSquared * oneMinusT;
        Dual tSquared = mt::square(t);
        Dual tCubed = tSquared * t;

        return points[0] * oneMinusTCubed + 
               points[1] * (Scalar(3) * oneMinusTSquared * t) + 
               points[2] * (Scalar(3) * oneMinusT * tSquared) +
               points[3] * tCubed; 
    }

}
