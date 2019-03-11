/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_VECTOR3_HPP
#define MT_VECTOR3_HPP

#ifdef USE_OSTREAM
#include <ostream>
#endif

#ifdef USE_ISTREAM
#include <istream>
#endif

#include <moto/Vector2.hpp>
#include <moto/Promote.hpp>
#include <moto/Scalar.hpp>
#include <moto/Algebra.hpp>

namespace mt
{
    template <typename Scalar>
    class Vector3
    {
    public:
        typedef Scalar ScalarType;
        
        Vector3();
        Vector3(Scalar x, Scalar y, Scalar z);     
        Vector3(Zero);
        template <int I> Vector3(Unit<I>);
        template <typename Scalar2> explicit Vector3(const Scalar2* v);
        template <typename Scalar2> Vector3(const Vector3<Scalar2>& a); 
              
        operator const Scalar*() const;
        operator Scalar*();

        Vector3<Scalar>& operator=(Zero);
        Vector3<Scalar>& operator+=(Zero);
        Vector3<Scalar>& operator-=(Zero); 
        Vector3<Scalar>& operator*=(Zero);
      
        template <int I> Vector3<Scalar>& operator=(Unit<I>);
        template <typename Scalar2> Vector3<Scalar>& operator=(const Scalar2* v);
        
        template <typename Scalar2> Vector3<Scalar>& operator=(const Vector3<Scalar2>& a);
        template <typename Scalar2> Vector3<Scalar>& operator+=(const Vector3<Scalar2>& a);
        template <typename Scalar2> Vector3<Scalar>& operator-=(const Vector3<Scalar2>& a);
        template <typename Scalar2> Vector3<Scalar>& operator*=(const Vector3<Scalar2>& a);
               
        Vector3<Scalar>& operator*=(Scalar s);
        Vector3<Scalar>& operator/=(Scalar s);
 
        Scalar x, y, z;
    };   

#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector3<Scalar>& a);

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Vector3<Scalar>& a);

#endif

    template <typename Scalar1, typename Scalar2> bool operator==(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b);
   
    template <typename Scalar> Vector3<Scalar> operator-(const Vector3<Scalar>& a);

    template <typename Scalar1, typename Scalar2> 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> operator+(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b);
    
    template <typename Scalar1, typename Scalar2>
    Vector3<typename Promote<Scalar1, Scalar2>::RT> operator-(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b);  
        
    template <typename Scalar1, typename Scalar2>
    Vector3<typename Promote<Scalar1, Scalar2>::RT> operator*(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b);

    template <typename Scalar1, typename Scalar2> 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> operator*(const Vector3<Scalar1>& a, Scalar2 s);

    template <typename Scalar1, typename Scalar2> 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> operator*(Scalar1 s, const Vector3<Scalar2>& a);
  
    template <typename Scalar1, typename Scalar2> 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> operator/(const Vector3<Scalar1>& a, Scalar2 s);

    template <typename Scalar> const Vector2<Scalar>& xy(const Vector3<Scalar>& a); 
    
    template <typename Scalar1, typename Scalar2>
    typename Promote<Scalar1, Scalar2>::RT dot(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b); 
    
    template <typename Scalar1, typename Scalar2> 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> cross(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b);

    template <typename Scalar>
    Scalar triple(const Vector3<Scalar>& a, const Vector3<Scalar>& b, const Vector3<Scalar>& c);

    template <typename Scalar>
    Vector3<Scalar> normal(const Vector3<Scalar>& a, const Vector3<Scalar>& b, const Vector3<Scalar>& c);

    template <typename Scalar> Vector3<Scalar> abs(const Vector3<Scalar>& a);

    template <typename Scalar> int maxAxis(const Vector3<Scalar>& a);
    template <typename Scalar> int minAxis(const Vector3<Scalar>& a);
  
    template <typename Scalar> int closestAxis(const Vector3<Scalar>& a); 
    template <typename Scalar> int furthestAxis(const Vector3<Scalar>& a);

    template <typename Scalar1, typename Scalar2>
    bool dominates(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b);

    template <typename Scalar1, typename Scalar2>
    void convert(Scalar1* v, const Vector3<Scalar2>& a);

    template <typename Scalar> bool isfinite(const Vector3<Scalar>& a);


    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>::Vector3() 
    {}

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>::Vector3(Scalar x, Scalar y, Scalar z)
        : x(x)
        , y(y)
        , z(z)
    {}

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>::Vector3(Zero)
        : x()
        , y()
        , z()
    {}
    
    template <typename Scalar>
    template <int I>
    FORCEINLINE
    Vector3<Scalar>::Vector3(Unit<I>)
        : x(Scalar(I == 0))
        , y(Scalar(I == 1))
        , z(Scalar(I == 2))
    {} 
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Vector3<Scalar>::Vector3(const Scalar2* v)
        : x(Scalar(v[0]))
        , y(Scalar(v[1]))
        , z(Scalar(v[2]))
    {}

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector3<Scalar>::Vector3(const Vector3<Scalar2>& a)
        : x(Scalar(a.x))
        , y(Scalar(a.y))
        , z(Scalar(a.z))
    {}

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>::operator const Scalar*() const
    {
        return &x;
    }  

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>::operator Scalar*()
    {
        return &x;
    } 
    
    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator=(Zero)
    {
        x = Scalar();
        y = Scalar();
        z = Scalar();
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator+=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator-=(Zero)
    {
        return *this;
    } 
    
    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator*=(Zero)
    {
        return *this = Zero();
    }

    template <typename Scalar>
    template <int I>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator=(Unit<I>)
    {
        x = Scalar(I == 0);
        y = Scalar(I == 1);
        z = Scalar(I == 2);
        return *this;
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator=(const Scalar2* v)
    {
        x = Scalar(v[0]);
        y = Scalar(v[1]);
        z = Scalar(v[2]);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator=(const Vector3<Scalar2>& a)
    {
        x = Scalar(a.x);
        y = Scalar(a.y);
        z = Scalar(a.z);
        return *this;
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator+=(const Vector3<Scalar2>& a)
    {
        x += Scalar(a.x); 
        y += Scalar(a.y); 
        z += Scalar(a.z);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator-=(const Vector3<Scalar2>& a)
    {
        x -= Scalar(a.x); 
        y -= Scalar(a.y); 
        z -= Scalar(a.z);
        return *this;
    }    
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator*=(const Vector3<Scalar2>& a)
    {
        x *= Scalar(a.x); 
        y *= Scalar(a.y); 
        z *= Scalar(a.z);
        return *this;
    }
    
    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator*=(Scalar s)
    {
        x *= s; 
        y *= s; 
        z *= s;
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar>& Vector3<Scalar>::operator/=(Scalar s)
    {
        ASSERT(!iszero(s));
        return *this *= Scalar(1) / s;
    }    

#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector3<Scalar>& a)
    {
        return os << a.x << ' ' << a.y << ' ' << a.z;
    }

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Vector3<Scalar>& a)
    {
        return is >> a.x >> a.y >> a.z;
    }

#endif

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    bool operator==(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> operator-(const Vector3<Scalar>& a)
    {
        return Vector3<Scalar>(-a.x, 
                               -a.y,
                               -a.z);
    }
  
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    operator+(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector3<RT>(a.x + b.x, 
                           a.y + b.y, 
                           a.z + b.z);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    operator-(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector3<RT>(a.x - b.x, 
                           a.y - b.y, 
                           a.z - b.z);
    }  

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector3<RT>(a.x * b.x, 
                           a.y * b.y, 
                           a.z * b.z);
    }

    template <typename Scalar1,typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(const Vector3<Scalar1>& a, Scalar2 s)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector3<RT>(a.x * s,
                           a.y * s,
                           a.z * s);
    }

    template <typename Scalar1,typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(Scalar1 s, const Vector3<Scalar2>& a)
    {
        return a * s;
    }

    template <typename Scalar1,typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    operator/(const Vector3<Scalar1>& a, Scalar2 s)
    {
        ASSERT(!iszero(s)); 
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return a * (RT(1) / RT(s));
    }

    template <typename Scalar> 
    FORCEINLINE
    const Vector2<Scalar>& xy(const Vector3<Scalar>& a)
    {
        return reinterpret_cast<const Vector2<Scalar>&>(a); 
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    typename Promote<Scalar1, Scalar2>::RT
    dot(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
 
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    cross(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector3<RT>(a.y * b.z - a.z * b.y, 
                           a.z * b.x - a.x * b.z,
                           a.x * b.y - a.y * b.x);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Scalar triple(const Vector3<Scalar>& a, const Vector3<Scalar>& b, const Vector3<Scalar>& c)
    {
#if SPEED_OVER_ACCURACY
        return dot(a, cross(b, c));
#else
        Vector3<Scalar> e[3];

        e[0] = a;
        e[1] = b;
        e[2] = c;

        Vector3<Scalar> d(dot(e[0], e[0]),
                          dot(e[1], e[1]),
                          dot(e[2], e[2]));

        int axis = maxAxis(d);

        return dot(e[axis], cross(e[(axis + 1) % 3], e[(axis + 2) % 3]));
#endif
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> normal(const Vector3<Scalar>& a, const Vector3<Scalar>& b, const Vector3<Scalar>& c)
    {
#if SPEED_OVER_ACCURACY
        return cross(b - a, c - b);
#else
        Vector3<Scalar> e[3];

        e[0] = b - a;
        e[1] = c - b;
        e[2] = a - c;

        Vector3<Scalar> d(dot(e[0], e[0]),
                          dot(e[1], e[1]),
                          dot(e[2], e[2]));

        int axis = maxAxis(d);

        return cross(e[(axis + 1) % 3], e[(axis + 2) % 3]);
#endif
    }

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar> abs(const Vector3<Scalar>& a)
    {
        return Vector3<Scalar>(abs(a.x),
                               abs(a.y),
                               abs(a.z));
    }
    
    template <typename Scalar>
    FORCEINLINE 
    int maxAxis(const Vector3<Scalar>& a)
    {
        int c0 = islessnn(a.x, a.y);
        int c1 = islessnn(a.x, a.z);
        int c2 = islessnn(a.y, a.z);
        return (c0 & ~c2) | ((c1 & c2) << 1);
    }

    template <typename Scalar>
    FORCEINLINE 
    int minAxis(const Vector3<Scalar>& a)
    {
        int c0 = islessnn(a.y, a.x);
        int c1 = islessnn(a.z, a.x);
        int c2 = islessnn(a.z, a.y);
        return (c0 & ~c2) | ((c1 & c2) << 1);
    }

    template <typename Scalar>
    FORCEINLINE 
    int closestAxis(const Vector3<Scalar>& a)
    {
        return maxAxis(a * a);
    } 
    
    template <typename Scalar>
    FORCEINLINE 
    int furthestAxis(const Vector3<Scalar>& a)
    {
        return minAxis(a * a);
    }   

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    bool dominates(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        return !islessnn(a.x, b.x) && 
               !islessnn(a.y, b.y) && 
               !islessnn(a.z, b.z); 
    }
  
    
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    void convert(Scalar1* v, const Vector3<Scalar2>& a)
    {
        v[0] = Scalar1(a.x);
        v[1] = Scalar1(a.y);
        v[2] = Scalar1(a.z);
    }  

    template <typename Scalar>
    bool isfinite(const Vector3<Scalar>& a)
    {
        return isfinite(a.x) && isfinite(a.y) && isfinite(a.z); 
    }
}

namespace guts
{
    template <typename Scalar> struct TypeTraits<mt::Vector3<Scalar> > { enum { ID = TypeTraits<Scalar>::ID | TT_3 }; };
}

#endif
