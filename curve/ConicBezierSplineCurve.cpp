/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "ConicBezierSplineCurve.hpp"


namespace cv
{

    DualVector3 ConicBezierSplineCurve::eval(Scalar param) const
    {
        ASSERT(Scalar() <= param && param <= Scalar(1));

        Scalar h = Scalar((mPoints.size() - 1) / 2);
            
        Scalar intg;
        Scalar frac = mt::modf(param * h, &intg);
        int index = int(intg) * 2;
        if (index + 1 == int(mPoints.size()))
        {
            frac += Scalar(1);
            index -= 2;
        }

        ASSERT(Scalar() <= frac && frac <= Scalar(1));
        ASSERT(0 <= index && index + 2 < int(mPoints.size()));  

		const Vector3* points = &mPoints[index];

		Dual t = Dual(frac, Scalar(1));
		Dual oneMinusT = Scalar(1) - t; 
      
        return points[0] * mt::square(oneMinusT) + 
               points[1] * (Scalar(2) * (oneMinusT) * t) + 
               points[2] * mt::square(t); 
    }

}
