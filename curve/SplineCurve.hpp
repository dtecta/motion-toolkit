/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef CV_SPLINECURVE_HPP
#define CV_SPLINECURVE_HPP

#include "Curve.hpp"

#include <vector>

namespace cv
{
    class SplineCurve
        : public Curve
    {
    public:
      
        void addPoint(const Vector3& point);
 
	protected: 
        std::vector<Vector3> mPoints;
    };
}


#endif
