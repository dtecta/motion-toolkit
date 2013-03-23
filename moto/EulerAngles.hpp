/*
 * MoTo - Motion Toolkit 
 * Copyright (c) 2006-2010 Gino van den Bergen, DTECTA 
 * http://www.dtecta.com
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Gino van den Bergen makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

#ifndef MT_EULERANGLES_HPP
#define MT_EULERANGLES_HPP

#include <moto/Trigonometric.hpp>
#include <moto/Matrix3x3.hpp>

namespace mt
{
   
    template <typename Scalar> Vector4<Scalar> euler(Scalar yaw, Scalar pitch, Scalar roll);
   
    template <typename Scalar>
    Vector4<Scalar> euler(Scalar yaw, Scalar pitch, Scalar roll)
    {   
        // yaw is CW around y-axis, pitch is CCW around x-axis, and roll is CW around z-axis
        
        std::complex<Scalar> ey = euler(yaw * Scalar(0.5));
        std::complex<Scalar> ep = euler(pitch * Scalar(0.5));
        std::complex<Scalar> er = euler(roll * Scalar(0.5));
        return Vector4<Scalar>(ey.real() * ep.imag() * er.real() + ey.imag() * ep.real() * er.imag(),
                               ey.real() * ep.imag() * er.imag() - ey.imag() * ep.real() * er.real(),
                               ey.imag() * ep.imag() * er.real() - ey.real() * ep.real() * er.imag(),
                               ey.real() * ep.real() * er.real() + ey.imag() * ep.imag() * er.imag());
    }
    
    

    template <typename Scalar>
    void fromEuler(Matrix3x3<Scalar>& mat, Scalar yaw, Scalar pitch, Scalar roll)
    {   
        // yaw is CW around y-axis, pitch is CCW around x-axis, and roll is CW around z-axis
            
        std::complex<Scalar> ey = euler(yaw);
        std::complex<Scalar> ep = euler(pitch);
        std::complex<Scalar> er = euler(roll);
        Scalar cc = ey.real() * er.real(); 
        Scalar cs = ey.real() * er.imag(); 
        Scalar sc = ey.imag() * er.real(); 
        Scalar ss = ey.imag() * er.imag();
        mat.setValue(   cc + ep.imag() * ss,   cs - ep.imag() * sc, -ey.imag() * ep.real(), 
                     -ep.real() * er.imag(), ep.real() * er.real(),             -ep.imag(),
                        sc - ep.imag() * cs,   ss + ep.imag() * cc,  ey.real() * ep.real());
    }

    template <typename Scalar>
    void toEuler(Scalar& yaw, Scalar& pitch, Scalar& roll, const Matrix3x3<Scalar>& mat)
    {
        if (mat[1][2] < Scalar(1))
        {
            if (mat[1][2] > -Scalar(1))
            { 
                yaw = Scalar(atan2(-mat[0][2], mat[2][2]));
                pitch = Scalar(asin(-mat[1][2]));
                roll = Scalar(atan2(-mat[1][0], mat[1][1]));
            }
            else
            {
                yaw = Scalar(atan2(-mat[0][1], mat[0][0]));
                pitch = ScalarTraits<Scalar>::pi() * Scalar(0.5);
                roll = Scalar();
            }
        }
        else
        {
            yaw = Scalar(atan2(mat[0][1], mat[0][0]));
            pitch = -ScalarTraits<Scalar>::pi() * Scalar(0.5);
            roll = Scalar();
        }
    }
}

#endif

