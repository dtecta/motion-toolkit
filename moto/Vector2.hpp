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

#ifndef MT_VECTOR2_HPP
#define MT_VECTOR2_HPP

#ifdef USE_OSTREAM
#include <ostream>
#endif

#ifdef USE_ISTREAM
#include <istream>
#endif

#include <moto/Promote.hpp>
#include <moto/Scalar.hpp>
#include <moto/Algebra.hpp>

namespace mt
{
    template <typename Scalar>
    class Vector2
    {
    public:
        typedef Scalar ScalarType;
        
        Vector2();
        Vector2(Scalar x, Scalar y);     
        Vector2(Zero);
        template <int I> Vector2(Unit<I>);
        template <typename Scalar2> explicit Vector2(const Scalar2* v);
        template <typename Scalar2> Vector2(const Vector2<Scalar2>& a);
        
        operator const Scalar*() const;
        operator Scalar*();
                
        Vector2<Scalar>& operator=(Zero);
        Vector2<Scalar>& operator+=(Zero);
        Vector2<Scalar>& operator-=(Zero);
        Vector2<Scalar>& operator*=(Zero);

        template <int I> Vector2<Scalar>& operator=(Unit<I>);
        template <typename Scalar2> Vector2<Scalar>& operator=(const Scalar2* v);

        template <typename Scalar2> Vector2<Scalar>& operator=(const Vector2<Scalar2>& a);
        template <typename Scalar2> Vector2<Scalar>& operator+=(const Vector2<Scalar2>& a);
        template <typename Scalar2> Vector2<Scalar>& operator-=(const Vector2<Scalar2>& a);
        template <typename Scalar2> Vector2<Scalar>& operator*=(const Vector2<Scalar2>& a);
        
        Vector2<Scalar>& operator*=(Scalar s);
        Vector2<Scalar>& operator/=(Scalar s);
 
        Scalar x, y;
    };   

#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector2<Scalar>& a);

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Vector2<Scalar>& a);

#endif

    template <typename Scalar1, typename Scalar2> bool operator==(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b);

    template <typename Scalar> Vector2<Scalar> operator-(const Vector2<Scalar>& a);

    template <typename Scalar1, typename Scalar2> 
    Vector2<typename Promote<Scalar1, Scalar2>::RT> operator+(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b);
 
    template <typename Scalar1, typename Scalar2>
    Vector2<typename Promote<Scalar1, Scalar2>::RT> operator-(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b); 
      
    template <typename Scalar1, typename Scalar2>
    Vector2<typename Promote<Scalar1, Scalar2>::RT> operator*(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b);

    template <typename Scalar1, typename Scalar2>
    Vector2<typename Promote<Scalar1, Scalar2>::RT> operator*(const Vector2<Scalar1>& a, Scalar2 s);

    template <typename Scalar1, typename Scalar2>
    Vector2<typename Promote<Scalar1, Scalar2>::RT> operator*(Scalar1 s, const Vector2<Scalar2>& a);

    template <typename Scalar1, typename Scalar2>
    Vector2<typename Promote<Scalar1, Scalar2>::RT> operator/(const Vector2<Scalar1>& a, Scalar2 s);
    
    template <typename Scalar1, typename Scalar2>
    typename Promote<Scalar1, Scalar2>::RT dot(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b); 
  
    template <typename Scalar> Vector2<Scalar> abs(const Vector2<Scalar>& a);
    
    template <typename Scalar> int maxAxis(const Vector2<Scalar>& a);
    template <typename Scalar> int minAxis(const Vector2<Scalar>& a);
   
    template <typename Scalar> int closestAxis(const Vector2<Scalar>& a);
    template <typename Scalar> int furthestAxis(const Vector2<Scalar>& a);

    template <typename Scalar1, typename Scalar2>
    bool dominates(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b);
    
    template <typename Scalar1, typename Scalar2>
    void convert(Scalar1* v, const Vector2<Scalar2>& a);





    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>::Vector2() 
    {}

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>::Vector2(Scalar x, Scalar y)
        : x(x)
        , y(y)
    {}

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>::Vector2(Zero)
        : x()
        , y()
    {}
    
    template <typename Scalar>
    template <int I>
    FORCEINLINE
    Vector2<Scalar>::Vector2(Unit<I>)
        : x(Scalar(I == 0)) 
        , y(Scalar(I == 1)) 
    {}
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Vector2<Scalar>::Vector2(const Scalar2* v)
        : x(Scalar(v[0]))
        , y(Scalar(v[1]))
    {}

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Vector2<Scalar>::Vector2(const Vector2<Scalar2>& a)
        : x(Scalar(a.x))
        , y(Scalar(a.y)) 
    {}
    
    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>::operator const Scalar*() const
    {
        return &x;
    }  

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>::operator Scalar*()
    {
        return &x;
    } 
    
    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator=(Zero)
    {
        x = Scalar();
        y = Scalar(); 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator+=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator-=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator*=(Zero)
    {
        return *this = Zero();
    }

    template <typename Scalar>
    template <int I>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator=(Unit<I>)
    {
        x = Scalar(I == 0);
        y = Scalar(I == 1);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator=(const Scalar2* v)
    {
        x = Scalar(v[0]);
        y = Scalar(v[1]);
        return *this;
    }


    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator=(const Vector2<Scalar2>& a)
    {
        x = Scalar(a.x);
        y = Scalar(a.y);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator+=(const Vector2<Scalar2>& a)
    {
        x += Scalar(a.x); 
        y += Scalar(a.y); 
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator-=(const Vector2<Scalar2>& a)
    {
        x -= Scalar(a.x); 
        y -= Scalar(a.y); 
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator*=(const Vector2<Scalar2>& a)
    {
        x *= Scalar(a.x); 
        y *= Scalar(a.y); 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator*=(Scalar s)
    {
        x *= s; 
        y *= s; 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar>& Vector2<Scalar>::operator/=(Scalar s)
    {
        ASSERT(!iszero(s));
        return *this *= Scalar(1) / s;
    }     
        
  
#ifdef USE_OSTREAM  

    template <typename CharT, typename Traits, typename Scalar>
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector2<Scalar>& a)
    {
        return os << a.x << ' ' << a.y;
    }

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Vector2<Scalar>& a)
    {
        return is >> a.x >> a.y;
    }

#endif

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    bool operator==(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b)
    {
        return a.x == b.x && a.y == b.y;
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector2<Scalar> operator-(const Vector2<Scalar>& a)
    {
        return Vector2<Scalar>(-a.x, 
                               -a.y);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector2<typename Promote<Scalar1, Scalar2>::RT> 
    operator+(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector2<RT>(a.x + b.x, 
                           a.y + b.y);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector2<typename Promote<Scalar1, Scalar2>::RT>
    operator-(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector2<RT>(a.x - b.x, 
                           a.y - b.y);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector2<typename Promote<Scalar1, Scalar2>::RT>
    operator*(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector2<RT>(a.x * b.x, 
                           a.y * b.y);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector2<typename Promote<Scalar1, Scalar2>::RT>
    operator*(const Vector2<Scalar1>& a, Scalar2 s)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector2<RT>(a.x * s,
                           a.y * s);
    }
    
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector2<typename Promote<Scalar1, Scalar2>::RT>
    operator*(Scalar1 s, const Vector2<Scalar2>& a)
    {
        return a * s;
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector2<typename Promote<Scalar1, Scalar2>::RT>
    operator/(const Vector2<Scalar1>& a, Scalar2 s)
    {
        ASSERT(!iszero(s)); 
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return a * (RT(1) / RT(s));
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    typename Promote<Scalar1, Scalar2>::RT 
    dot(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b)
    {
        return a.x * b.x + a.y * b.y;
    }
 
    template <typename Scalar>
    FORCEINLINE
    Vector2<Scalar> abs(const Vector2<Scalar>& a)
    {
        return Vector2<Scalar>(abs(a.x),
                               abs(a.y));
    }

    template <typename Scalar>
    FORCEINLINE 
    int maxAxis(const Vector2<Scalar>& a)
    {
        return islessnn(a.x, a.y);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    int minAxis(const Vector2<Scalar>& a)
    {
        return islessnn(a.y, a.x);
    }

    template <typename Scalar>
    FORCEINLINE 
    int closestAxis(const Vector2<Scalar>& a)
    {
        return maxAxis(a * a);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    int furthestAxis(const Vector2<Scalar>& a)
    {
        return minAxis(a * a);
    }   

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    bool dominates(const Vector2<Scalar1>& a, const Vector2<Scalar2>& b)
    {
        return !islessnn(a.x, b.x) && 
               !islessnn(a.y, b.y);
    }  
    
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    void convert(Scalar1* v, const Vector2<Scalar2>& a)
    {
        v[0] = Scalar1(a.x);
        v[1] = Scalar1(a.y);
    }
}

#endif
