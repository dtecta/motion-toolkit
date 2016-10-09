/*  MoTo - Motion Toolkit
    Copyright (c) 2016 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef CV_TYPES_HPP
#define CV_TYPES_HPP

#define FUZZY_EQUAL 0

#include <moto/Vector2.hpp>
#include <moto/Matrix4x4.hpp>
#include <moto/Metric.hpp>
#include <moto/ScalarTraits.hpp>
#include <moto/DualVector3.hpp>
#include <moto/Trigonometric.hpp>


namespace cv
{
    typedef float Scalar; 

    typedef mt::Matrix3x3<Scalar> Matrix3x3; 
	typedef mt::Matrix4x4<Scalar> Matrix4x4; 
    typedef mt::Vector2<Scalar> Vector2;  
    typedef mt::Vector3<Scalar> Vector3;  
    typedef mt::Vector4<Scalar> Vector4;
    typedef mt::Vector4<Scalar> Quaternion;
    typedef mt::Diagonal3<Scalar> Diagonal3;
    typedef mt::ScalarTraits<Scalar> ScalarTraits;
    typedef mt::Dual<Scalar> Dual;
    typedef mt::Vector3<Dual> DualVector3;
   
   	using mt::Zero;
	using mt::Identity;
	using mt::Unit;
 
#if FUZZY_EQUAL
    inline
    bool operator==(const Vector3& lhs, const Vector3& rhs)
    {
        return distanceSquared(lhs, rhs) < Scalar(1); 
    }
#endif

}

#endif

