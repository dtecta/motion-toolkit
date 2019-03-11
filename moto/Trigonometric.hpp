/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_TRIGONOMETRIC_HPP
#define MT_TRIGONOMETRIC_HPP

#include <complex>

#include <moto/Metric.hpp>
#include <moto/ScalarTraits.hpp>
#include <moto/Vector4.hpp>
#include <moto/ScalarTraits.hpp>

namespace mt
{
    template <typename Scalar> Scalar radians(Scalar degs);
    template <typename Scalar> Scalar degrees(Scalar rads);

    template <typename Vector> typename Vector::ScalarType angle(const Vector& v1, const Vector& v2);

    template <typename Vector, typename Scalar> 
    Vector slerp(const Vector& u1, const Vector& u2, typename Vector::ScalarType t); 

    template <typename Vector> typename Vector::ScalarType angle3(const Vector& v1, const Vector& v2);

    template <typename Vector, typename Scalar> 
    Vector slerp3(const Vector& u1, const Vector& u2, typename Vector::ScalarType t); 


    template <typename Scalar> std::complex<Scalar> euler(Scalar theta);

    template <typename Scalar> Vector4<Scalar> fromAxisAngle(const Vector3<Scalar>& axis, Scalar theta);
    template <typename Scalar> Vector4<Scalar> fromAxisAngle(int axis, Scalar theta);
    template <typename Scalar> void toAxisAngle(Vector3<Scalar>& axis, Scalar& theta, const Vector4<Scalar>& u);

    template <typename Scalar> Vector4<Scalar> exp(const Vector3<Scalar>& v);
    template <typename Scalar> Vector3<Scalar> logUnit(const Vector4<Scalar>& u);
    template <typename Scalar1, typename Scalar2> Vector4<Scalar1> powUnit(const Vector4<Scalar1>& u, Scalar2 t);
    template <typename Scalar1, typename Scalar2> Vector4<Scalar1> logLerpUnit(const Vector4<Scalar1>& u1, const Vector4<Scalar1>& u2, Scalar2 t);

    template <typename Scalar> Vector4<Scalar> exp(const Vector4<Scalar>& q); 
    template <typename Scalar> Vector4<Scalar> log(const Vector4<Scalar>& q); 
    template <typename Scalar1, typename Scalar2> Vector4<Scalar1> pow(const Vector4<Scalar1>& q, Scalar2 t);
    template <typename Scalar1, typename Scalar2> Vector4<Scalar1> logLerp(const Vector4<Scalar1>& q1, const Vector4<Scalar1>& q2, Scalar2 t);

    template <typename Scalar> Vector3<Scalar> dihedral(const Vector3<Scalar>& u1, const Vector3<Scalar>& u2);


    template <typename Scalar>
    Scalar radians(Scalar degs)
    {
        static const Scalar RADS_PER_DEG = ScalarTraits<Scalar>::pi() / Scalar(180);
        return RADS_PER_DEG * degs;
    }

    template <typename Scalar>
    Scalar degrees(Scalar rads)
    {
        static const Scalar DEGS_PER_RAD = Scalar(180) / ScalarTraits<Scalar>::pi();
        return DEGS_PER_RAD * rads;
    }

    template <typename Vector>
    typename Vector::ScalarType angle(const Vector& v1, const Vector& v2)
    {
        return acos(dot(v1, v2) * rsqrt(lengthSquared(v1) * lengthSquared(v2)));
    }

    template <typename Vector>
    Vector slerp(const Vector& u1, const Vector& u2, typename Vector::ScalarType t)
    {
        typedef typename Vector::ScalarType Scalar;
        Scalar costheta = dot(u1, u2);
        Scalar theta = acos(costheta);
        if (!iszero(theta))
        {
            Scalar r = rsqrt(Scalar(1) - square(costheta));
            Scalar s0 = sin((Scalar(1) - t) * theta) * r;
            Scalar s1 = sin(t * theta) * r;   
            return u1 * s0 + u2 * s1;
        }
        else
        {
            return u1;
        }
    }

    template <typename Vector>
    typename Vector::ScalarType angle3(const Vector& v1, const Vector& v2)
    {
        return acos(dot3(v1, v2) * rsqrt(lengthSquared3(v1) * lengthSquared3(v2)));
    }

    template <typename Vector>
    Vector slerp3(const Vector& u1, const Vector& u2, typename Vector::ScalarType t)
    {
        typedef typename Vector::ScalarType Scalar;
        Scalar costheta = dot3(u1, u2);
        Scalar theta = acos(costheta);
        if (!iszero(theta))
        {
            Scalar r = rsqrt(Scalar(1) - square(costheta));
            Scalar s0 = sin((Scalar(1) - t) * theta) * r;
            Scalar s1 = sin(t * theta) * r;   
            return u1 * s0 + u2 * s1;
        }
        else
        {
            return u1;
        }
    } 

    template <typename Scalar>
    FORCEINLINE 
    std::complex<Scalar> euler(Scalar theta)
    {
        return std::complex<Scalar>(cos(theta), sin(theta)); 
    }

#if HAVE_SINCOS

    FORCEINLINE 
    std::complex<float> euler(float angle)
    {
        float sine, cosine;
        sincosf(angle, &sine, &cosine);
        return std::complex<float>(cosine, sine);
    }

    FORCEINLINE 
    std::complex<double> euler(double angle)
    {
        double sine, cosine;
        sincos(angle, &sine, &cosine);
        return std::complex<double>(cosine, sine);
    }

    FORCEINLINE 
    std::complex<long double> euler(long double angle)
    {
        long double sine, cosine;
        sincosl(angle, &sine, &cosine);
        return std::complex<long double>(cosine, sine);
    }

#endif

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> fromAxisAngle(const Vector3<Scalar>& axis, Scalar theta)
    {
        std::complex<Scalar> c = euler(theta * Scalar(0.5));
        Scalar r = lengthSquared(axis);
        ASSERT(ispositive(r));
        Scalar s = c.imag() * rsqrt(r);
        return Vector4<Scalar>(axis * s, c.real());
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> fromAxisAngle(int axis, Scalar theta)
    {
        ASSERT(0 <= axis && axis < 3);
        std::complex<Scalar> c = euler(theta * Scalar(0.5));
        Vector4<Scalar> result(c.real());
        result[axis] = c.imag();
        return result;
    }

    template <typename Scalar>
    FORCEINLINE
    void toAxisAngle(Vector3<Scalar>& axis, Scalar& theta, const Vector4<Scalar>& u)
    {
        Scalar s = length3(u);
        if (!mt::iszero(s))
        {
            theta = atan2(s, u.w) * Scalar(2);
            axis = xyz(u) / s;
        }
        else
        {
            theta = Scalar();
            axis = Unit<0>();
        }
    }

    template <typename Scalar>
    Vector4<Scalar> exp(const Vector3<Scalar>& v)
    {
        Scalar theta = length(v);
        if (ispositive(theta))
        {
            std::complex<Scalar> c = euler(theta);
            Scalar s = c.imag() / theta;
            return Vector4<Scalar>(v * s, c.real());
        }
        else
        {
            return Vector4<Scalar>(v, Scalar(1));
        }
    }

    template <typename Scalar>
    Vector3<Scalar> logUnit(const Vector4<Scalar>& u)
    {
        Scalar s = length3(u);
        return mt::ispositive(s) ? xyz(u) * (atan2(s, u.w) / s) : xyz(u);
    }

    template <typename Scalar1, typename Scalar2>
    Vector4<Scalar1> powUnit(const Vector4<Scalar1>& u, Scalar2 t)
    {
        return exp(logUnit(u) * t);  
    }

    template <typename Scalar1, typename Scalar2>
    Vector4<Scalar1> logLerpUnit(const Vector4<Scalar1>& u1, const Vector4<Scalar1>& u2, Scalar2 t)
    {
        return exp(lerp(logUnit(u1), logUnit(u2), t));  
    } 
    
    template <typename Scalar>
    Vector4<Scalar> exp(const Vector4<Scalar>& q)
    {
        return exp(xyz(q)) * exp(q.w);
    }

    template <typename Scalar>
    Vector4<Scalar> log(const Vector4<Scalar>& q)
    {
        Scalar r = length(q);
        ASSER(mt::ispositive(r));
        return Vector4<Scalar>(logUnit(q / r), log(r));
    }
    
    template <typename Scalar1, typename Scalar2>
    Vector4<Scalar1> pow(const Vector4<Scalar1>& q, Scalar2 t)
    {
        return exp(log(q) * t);  
    }

    template <typename Scalar1, typename Scalar2>
    Vector4<Scalar1> logLerp(const Vector4<Scalar1>& q1, const Vector4<Scalar1>& q2, Scalar2 t)
    {
        return exp(lerp(log(q1), log(q2), t));  
    }

    template <typename Scalar>
    Vector3<Scalar> dihedral(const Vector3<Scalar>& u1, const Vector3<Scalar>& u2)
    {
        // This is the same as
        //return logUnit(Vector4<Scalar>(cross(u1, u2), dot(u1, u2))); 

        Scalar theta = acos(dot(u1, u2));
        ASSERT(isfinite(theta));
        return normalize(cross(u1, u2)) * theta; 
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> euler(Scalar theta, Scalar phi)
    { 
        std::complex<Scalar> c1 = euler(theta);
        std::complex<Scalar> c2 = euler(phi);
        return Vector3<Scalar>(c1.real() * c2.real(), c1.imag() * c2.real(), c2.imag());
    } 

    template <typename Scalar>
    FORCEINLINE 
    void toEuler(Scalar& theta, Scalar& phi, const Vector3<Scalar>& u)
    { 
        phi = asin(u.z);
        theta = !mt::iszero(u.y) || !mt::iszero(u.x) ? atan2(u.y, u.x) : Scalar();
    } 

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> fromSpherical(Scalar rho, Scalar phi, Scalar theta)
    {
        std::complex<Scalar> c1 = euler(theta);
        std::complex<Scalar> c2 = euler(phi);
        Vector3<Scalar> axis(c1.real() * c2.imag(), c1.imag() * c2.imag(), c2.real());
        return axisAngle(axis, rho);  
    }

    template <typename Scalar>
    FORCEINLINE
    void toSpherical(Scalar& rho, Scalar& phi, Scalar& theta, const Vector4<Scalar>& u)
    {
        rho = acos(u.w) * Scalar(2);
        Vector3<Scalar> axis = normalize(xyz(u));
        phi = acos(axis.z);
        theta = atan2(axis.y, axis.x);  
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> fromEuler(Scalar yaw, Scalar pitch, Scalar roll)
    {
        std::complex<Scalar> qyaw   = euler(yaw * Scalar(0.5));
        std::complex<Scalar> qpitch = euler(pitch * Scalar(0.5));
        std::complex<Scalar> qroll  = euler(roll * Scalar(0.5));
        return mul(Vector4<Scalar>(Scalar(), qyaw.imag(), Scalar(), qyaw.real()),
                   Vector4<Scalar>(qpitch.imag(), Scalar(), Scalar(), qpitch.real()),
                   Vector4<Scalar>(Scalar(), Scalar(), qroll.imag(), qroll.real()));
    }

    template <typename Scalar>
    FORCEINLINE
    void toEuler(Scalar& yaw, Scalar& pitch, Scalar& roll, const Vector4<Scalar>& q)
    {
        yaw   = atan2(Scalar(2) * (q.w * q.y + q.z * q.x), Scalar(1) - Scalar(2) * (q.x * q.x + q.y * q.y));
        pitch = asin(Scalar(2) * (q.w * q.x - q.y * q.z));
        roll  = atan2(Scalar(2) * (q.w * q.z + q.x * q.y), Scalar(1) - Scalar(2) * (q.z * q.z + q.x * q.x));
    }



}

#endif
