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
        : Vector3<Interval<Scalar> >(v.x, v.y, v.z)
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
        return Vector3<Scalar>(lower(b.x), lower(b.y), lower(b.z));
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> upper(const BBox3<Scalar>& b)
    {
        return Vector3<Scalar>(upper(b.x), upper(b.y), upper(b.z));
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> width(const BBox3<Scalar>& b)
    {
        return Vector3<Scalar>(width(b.x), width(b.y), width(b.z));
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> median(const BBox3<Scalar>& b)
    {
        return Vector3<Scalar>(median(b.x), median(b.y), median(b.z));
    }
    
    template <typename Scalar>
    FORCEINLINE 
    BBox3<Scalar> hull(const Vector3<Scalar>& v1, const Vector3<Scalar>& v2)
    {
        return BBox3<Scalar>(hull(v1.x, v2.x), hull(v1.y, v2.y), hull(v1.z, v2.z));
    }
   
    template <typename Scalar>
    FORCEINLINE 
    BBox3<Scalar> hull(const BBox3<Scalar>& b, const Vector3<Scalar>& v)
    {
        return BBox3<Scalar>(hull(b.x, v.x), hull(b.y, v.y), hull(b.z, v.z));
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
        return BBox3<Scalar>(hull(b1.x, b2.x), hull(b1.y, b2.y), hull(b1.z, b2.z));
    }

    template <typename Scalar>
    FORCEINLINE 
    bool overlap(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2)
    {
        return overlap(b1.x, b2.x) && overlap(b1.y, b2.y) && overlap(b1.z, b2.z);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    bool subset(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2)
    {
        return subset(b1.x, b2.x) && subset(b1.y, b2.y) && subset(b1.z, b2.z);
    }
    
    
    template <typename Scalar>
    FORCEINLINE 
    bool in(const Vector3<Scalar>& v, const BBox3<Scalar>& b)
    {
        return in(v.x, b.x) && in(v.y, b.y) && in(v.z, b.z);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    BBox3<Scalar> clamp(const BBox3<Scalar>& b1, const BBox3<Scalar>& b2)
    {
        return BBox3<Scalar>(clamp(b1.x, b2.x), clamp(b1.y, b2.y), clamp(b1.z, b2.z));
    }
}

#endif


