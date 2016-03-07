#ifndef IK_TYPES_HPP
#define IK_TYPES_HPP

#include <moto/Interval.hpp>
#include <moto/Vector3.hpp>
#include <moto/Matrix3x3.hpp>
#include <moto/Vector4.hpp>

#include <moto/DualVector3.hpp>
#include <moto/DualVector4.hpp>
#include <moto/ScalarTraits.hpp>
#include <moto/Matrix3x4.hpp>
#include <moto/Matrix4x4.hpp>
#include <moto/Metric.hpp>
#include <moto/Diagonal3.hpp>

namespace ik
{
    typedef float   							Scalar;
    typedef mt::Interval<Scalar>                Interval;
    typedef mt::Vector3<Scalar>			        Vector3;
    typedef mt::Vector4<Scalar>			        Quaternion;
    typedef mt::Vector4<Scalar>			        Vector4;

    typedef mt::Matrix3x3<Scalar>				Matrix3x3;
    typedef mt::Matrix3x4<Scalar>				Matrix3x4;
    typedef mt::Matrix4x4<Scalar>				Matrix4x4;
    typedef mt::Diagonal3<Scalar>               Diagonal3;

    typedef mt::Dual<Scalar>                    Dual;
    typedef mt::Vector3<Dual>	                DualVector3;
    typedef mt::Vector4<Dual>	                DualQuaternion;

    typedef mt::Interval<Scalar>                Interval;
    typedef mt::Vector3<Interval>               BBox3;

    typedef mt::ScalarTraits<Scalar>            ScalarTraits;

    using mt::Zero;
    using mt::Identity;
    using mt::Unit;
}

#endif

