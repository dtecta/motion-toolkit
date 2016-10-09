/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "CircleCurve.hpp"


namespace cv
{
    DualVector3 CircleCurve::eval(Scalar param) const
    {
        Dual t = Dual(param * ScalarTraits::pi() * Scalar(2), Scalar(1));
      
        return mCenter + DualVector3(mRadius * cos(t), mRadius * sin(t), Dual());
    }
}
