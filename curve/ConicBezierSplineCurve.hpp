/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef CV_CONICBEZIERSPLINECURVE_HPP
#define CV_CONICBEZIERSPLINECURVE_HPP

#include "SplineCurve.hpp"

#include <vector>

namespace cv
{
    class ConicBezierSplineCurve
        : public SplineCurve
    {
    public:
      
        virtual DualVector3 eval(Scalar param) const OVERRIDE;

    };
}


#endif
