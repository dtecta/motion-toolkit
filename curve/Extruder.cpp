/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#include "Extruder.hpp"
#include "Curve.hpp"



namespace cv
{
#if 1
    Scalar Extruder::tesselate(const Curve& curve)
    {
        mSamples.resize(0);
        DualVector3 from = curve.eval(Scalar());
        DualVector3 to = curve.eval(Scalar(1));
        Vector3 base = real(to) - real(from);
        Scalar dist2 = lengthSquared(base);
        Scalar arcLength = Scalar();
        auxTesselate(curve, from, Scalar(), to, Scalar(1), dist2, arcLength); 
        addSample(to, arcLength);
        return arcLength;
    }
 
    void Extruder::auxTesselate(const Curve& curve, const DualVector3& from, Scalar fromParam, const DualVector3& to, Scalar toParam, Scalar dist2, Scalar& arcLength)
    {
        Scalar midParam = (fromParam + toParam) * Scalar(0.5);

        DualVector3 mid = curve.eval(midParam);
          
        Vector3 l = real(from) - real(mid);
        Vector3 r = real(to) - real(mid);

        Scalar area2 = lengthSquared(cross(l, r)); // Squared area of parallellogram spanned by l and r

        if (area2 > dist2 * mTolerance)  // squared height of triangle = area2 / dist2
        {
            Scalar ldist2 = lengthSquared(l);
            Scalar rdist2 = lengthSquared(r);

            auxTesselate(curve, from, fromParam, mid, midParam, ldist2, arcLength);
            auxTesselate(curve, mid, midParam, to, toParam, rdist2, arcLength);
        }
        else
        {
            addSample(from, arcLength);
            arcLength += sqrt(dist2); 
        }      
    }

#else
    
    Scalar Extruder::tesselate(const Curve& curve)
    {
         mSamples.resize(0);

         DualVector3 sample = curve.eval(Scalar());
         addSample(sample, Scalar());
         Scalar arcLength = Scalar();
         Scalar step = 1 / 1000.0f;
         Scalar param = step;
         DualVector3 prev = real(sample); 

         for (int i = 1; i != 1001; ++i)
         { 
             sample = curve.eval(param);
             if (dot(dual(prev), dual(sample)) < Scalar())
             {
                 sample = curve.eval(param);
             }
             arcLength += distance(real(prev), real(sample));
             prev = sample; 
             addSample(sample, arcLength);
             param += step;
         }
         return arcLength;
    }
 

#endif

    void Extruder::addSample(const DualVector3& curveSample, Scalar arcLength)
    {
        Vector3 position = real(curveSample);
        Vector3 tangent = normalize(dual(curveSample));
        Vector3 binormal = normalize(Vector3(tangent[1], -tangent[0], Scalar())); 
        Vector3 normal = normalize(cross(binormal, tangent));

        Sample sample;
        sample.xform.setColumns(binormal, tangent, normal, position);
        sample.arcLength = arcLength;

        mSamples.push_back(sample);
    }

    bool Extruder::hasLoop() const
    {
        ASSERT(!mSamples.empty());
        for (auto it = mSamples.begin(), last = mSamples.end() - 1; it != last; ++it)
        {
            const Sample& from = *it;
            const Sample& to = *(it + 1);
            Scalar angle = angle3(from.xform[1], to.xform[1]);
            Scalar dist = to.arcLength - from.arcLength;
            if (dot(from.xform[1], to.xform[1]) < Scalar(0.85) || angle > dist)
            {
                return true;
            }
        }

        return false;
    } 

    bool Extruder::fixLoop()
    {
        ASSERT(mSamples.size() >= 2);
        for (auto it = mSamples.begin(), end = mSamples.end() - 2; it != end; ++it)
        {
            const Sample& from = *it;
            const Sample& to = *(it + 1);
            Scalar angle = angle3(from.xform[1], to.xform[1]);
            Scalar dist = to.arcLength - from.arcLength;
            if (dot(from.xform[1], to.xform[1]) < Scalar(0.85) || angle * Scalar(5) > dist)
            {
                mSamples.erase(it + 1); 
                return true;
            }
        }

        return false;
    }
}
