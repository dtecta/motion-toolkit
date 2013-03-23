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

#ifndef MT_BBOX3_HPP
#define MT_BBOX3_HPP

#include <moto/Vector3.hpp>
#include <moto/Interval.hpp>

namespace mt
{  
    template <typename Scalar>
    class BBox3
        : public Vector3<Interval<Scalar> > 
    {
    public:
        BBox3();
        BBox3(Interval<Scalar> x, Interval<Scalar> y, Interval<Scalar> z);
        BBox3(Zero);
        template <typename Scalar2> BBox3(const Vector3<Scalar2>& v);  
        
        explicit BBox3(Scalar radius);
        BBox3(Scalar xabs, Scalar yabs, Scalar zabs);
        BBox3(Scalar xmin, Scalar xmax, Scalar ymin, Scalar ymax, Scalar zmin, Scalar zmax);  
    };

    template <typename Scalar> Vector3<Scalar> lower(const BBox3<Scalar>& b);
    template <typename Scalar> Vector3<Scalar> upper(const BBox3<Scalar>& b); 
    template <typename Scalar> Vector3<Scalar> width(const BBox3<Scalar>& b); 
    template <typename Scalar> Vector3<Scalar> median(const BBox3<Scalar>& b);
  
    template <typename Scalar> BBox3<Scalar> hull(const Vector3<Scalar>& v1, const Vector3<Scalar>& v2);
    template <typename Scalar> BBox3<Scalar> hull(const BBox3<Scalar>& b, const Vector3<Scalar>& v);
    template <typename Scalar> BBox3<Scalar> hull(const Vector3<Scalar>& v, const BBox3<Scalar>& b);
    template <typename Scalar> BBox3<Scalar> hull(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2);
   
    template <typename Scalar> bool overlap(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2);  
    template <typename Scalar> bool subset(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2); 
    template <typename Scalar> bool in(const Vector3<Scalar>& v, const BBox3<Scalar>& b);
    
    template <typename Scalar> BBox3<Scalar> clamp(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2);


    template <typename Scalar>
    FORCEINLINE
    BBox3<Scalar>::BBox3()
    {}
    
    template <typename Scalar>
    FORCEINLINE
    BBox3<Scalar>::BBox3(Interval<Scalar> x, Interval<Scalar> y, Interval<Scalar> z)
        : Vector3<Interval<Scalar> >(x, y, z)
    {}

    template <typename Scalar>
    FORCEINLINE
    BBox3<Scalar>::BBox3(Zero)
        : Vector3<Interval<Scalar> >(Zero())
    {}
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    BBox3<Scalar>::BBox3(const Vector3<Scalar2>& v)
        : Vector3<Interval<Scalar> >(v[0], v[1], v[2])
    {}
    
    template <typename Scalar>
    FORCEINLINE
    BBox3<Scalar>::BBox3(Scalar xmin, Scalar xmax, 
                         Scalar ymin, Scalar ymax, 
                         Scalar zmin, Scalar zmax)
        : Vector3<Interval<Scalar> >(Interval<Scalar>(xmin, xmax), 
                                     Interval<Scalar>(ymin, ymax), 
                                     Interval<Scalar>(zmin, zmax)) 
    {}
    
    template <typename Scalar>
    FORCEINLINE
    BBox3<Scalar>::BBox3(Scalar radius)
        : Vector3<Interval<Scalar> >(Interval<Scalar>(-radius, radius), 
                                     Interval<Scalar>(-radius, radius), 
                                     Interval<Scalar>(-radius, radius)) 
    {}
    
    template <typename Scalar>
    FORCEINLINE
    BBox3<Scalar>::BBox3(Scalar xabs, Scalar yabs, Scalar zabs)
        : Vector3<Interval<Scalar> >(Interval<Scalar>(-xabs, xabs), 
                                     Interval<Scalar>(-yabs, yabs), 
                                     Interval<Scalar>(-zabs, zabs)) 
    {}
    
    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> lower(const BBox3<Scalar>& b)
    {
        return Vector3<Scalar>(lower(b[0]), lower(b[1]), lower(b[2]));
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> upper(const BBox3<Scalar>& b)
    {
        return Vector3<Scalar>(upper(b[0]), upper(b[1]), upper(b[2]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> width(const BBox3<Scalar>& b)
    {
        return Vector3<Scalar>(width(b[0]), width(b[1]), width(b[2]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> median(const BBox3<Scalar>& b)
    {
        return Vector3<Scalar>(median(b[0]), median(b[1]), median(b[2]));
    }
    
    template <typename Scalar>
    FORCEINLINE 
    BBox3<Scalar> hull(const Vector3<Scalar>& v1, const Vector3<Scalar>& v2)
    {
        return BBox3<Scalar>(hull(v1[0], v2[0]), hull(v1[1], v2[1]), hull(v1[2], v2[2]));
    }
   
    template <typename Scalar>
    FORCEINLINE 
    BBox3<Scalar> hull(const BBox3<Scalar>& b, const Vector3<Scalar>& v)
    {
        return BBox3<Scalar>(hull(b[0], v[0]), hull(b[1], v[1]), hull(b[2], v[2]));
    }

    template <typename Scalar>
    FORCEINLINE 
    BBox3<Scalar> hull(const Vector3<Scalar>& v, const BBox3<Scalar>& b)
    {
        return hull(b, v);
    } 
    
    template <typename Scalar>
    FORCEINLINE 
    BBox3<Scalar> hull(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2)
    {
        return BBox3<Scalar>(hull(b1[0], b2[0]), hull(b1[1], b2[1]), hull(b1[2], b2[2]));
    }

    template <typename Scalar>
    FORCEINLINE 
    bool overlap(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2)
    {
        return overlap(b1[0], b2[0]) && overlap(b1[1], b2[1]) && overlap(b1[2], b2[2]);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    bool subset(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2)
    {
        return subset(b1[0], b2[0]) && subset(b1[1], b2[1]) && subset(b1[2], b2[2]);
    }
    
    
    template <typename Scalar>
    FORCEINLINE 
    bool in(const Vector3<Scalar>& v, const BBox3<Scalar>& b)
    {
        return in(v[0], b[0]) && in(v[1], b[1]) && in(v[2], b[2]);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    BBox3<Scalar> clamp(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2)
    {
        return BBox3<Scalar>(clamp(b1[0], b2[0]), clamp(b1[1], b2[1]), clamp(b1[2], b2[2]));
    }
}

#endif


