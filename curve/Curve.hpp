/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef CV_CURVE_HPP 
#define CV_CURVE_HPP 

#include "Types.hpp"

namespace cv
{
    class Curve
    {
    public:
        virtual ~Curve() {}
        virtual DualVector3 eval(Scalar param) const = 0;
    };
}

#endif
