/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef CV_CARDINALSPLINECURVE_HPP
#define CV_CARDINALSPLINECURVE_HPP

#include "SplineCurve.hpp"

namespace cv
{
    class CardinalSplineCurve
        : public SplineCurve
    {
    public:
        CardinalSplineCurve()
            : mAlpha(0.5)
        {}

        virtual DualVector3 eval(Scalar param) const OVERRIDE;

        void setTension(Scalar tension) { mAlpha = (Scalar(1) - tension) * Scalar(0.5); }
        
    private:   
        Scalar mAlpha;
    };
}


#endif
