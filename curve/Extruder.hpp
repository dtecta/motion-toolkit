/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef CV_EXTRUDER_HPP
#define CV_EXTRUDER_HPP

#include "Types.hpp"

#include <vector>

namespace cv
{
    class Curve;

    struct Sample
    {
        Matrix4x4 xform;
        Scalar arcLength;
    };

    class Extruder
    {
    public:
        Extruder(Scalar tolerance = Scalar(1))
        {
            setTolerance(tolerance);
        }
		
        Scalar tolerance() const { return sqrt(mTolerance); }
        void setTolerance(Scalar tolerance) { mTolerance = tolerance * tolerance; }

        Scalar tesselate(const Curve& curve);

        size_t sampleCount() const { return mSamples.size(); }

        const Sample& sample(size_t index) const { return mSamples[index]; } 

        bool hasLoop() const;
        bool fixLoop();

    private:
        void auxTesselate(const Curve& curve, const DualVector3& from, Scalar fromParam, const DualVector3& to, Scalar toParam, Scalar dist2, Scalar& arcLength);

        void addSample(const DualVector3& sample, Scalar arcLength);

        Scalar mTolerance;
        std::vector<Sample> mSamples;
    };
}


#endif
