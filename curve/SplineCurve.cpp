/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "SplineCurve.hpp"


namespace cv
{
    void SplineCurve::addPoint(const Vector3& point)
    {
        mPoints.push_back(point); 
    }
}
