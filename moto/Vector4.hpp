/*  MoTo - Motion Toolkit
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_VECTOR4_HPP
#define MT_VECTOR4_HPP

#ifdef USE_OSTREAM
#include <ostream>
#endif

#ifdef USE_ISTREAM
#include <istream>
#endif

#include <moto/Vector3.hpp>
#include <moto/Promote.hpp>
#include <moto/Scalar.hpp>
#include <moto/Algebra.hpp>
#include <moto/BitMask4.hpp>

namespace mt
{
    template <typename Scalar>
    class Vector4
    {
    public:
        typedef Scalar ScalarType; 
      
        Vector4();
        Vector4(Scalar x, Scalar y, Scalar z, Scalar w);  
        
        Vector4(Zero);
        Vector4(Identity);
        template <int I> Vector4(Unit<I>); 
      
        template <typename Scalar2> explicit Vector4(const Scalar2* v);   
        template <typename Scalar2> Vector4(const Vector4<Scalar2>& a);
        template <typename Scalar2> explicit Vector4(const Vector3<Scalar2>& a, Scalar w = Scalar());
        explicit Vector4(Scalar w); 
        
        operator const Scalar*() const;
        operator Scalar*();
        
        Vector4<Scalar>& operator=(Zero);
        Vector4<Scalar>& operator+=(Zero);
        Vector4<Scalar>& operator-=(Zero);
        Vector4<Scalar>& operator*=(Zero);
        
        Vector4<Scalar>& operator=(Identity);
        template <int I> Vector4<Scalar>& operator=(Unit<I>); 

        template <typename Scalar2> Vector4<Scalar>& operator=(const Scalar2* v);
        template <typename Scalar2> Vector4<Scalar>& operator=(const Vector4<Scalar2>& a);
        template <typename Scalar2> Vector4<Scalar>& operator+=(const Vector4<Scalar2>& a);
        template <typename Scalar2> Vector4<Scalar>& operator-=(const Vector4<Scalar2>& a);
        template <typename Scalar2> Vector4<Scalar>& operator*=(const Vector4<Scalar2>& a);
        
        Vector4<Scalar>& operator*=(Scalar s);
        Vector4<Scalar>& operator/=(Scalar s);
        
        template <typename Scalar2> Vector3<typename Promote<Scalar, Scalar2>::RT> operator()(const Vector3<Scalar2>& v) const;

        Scalar x, y, z, w;
    };   

#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector4<Scalar>& a);

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Vector4<Scalar>& a);

#endif


    template <typename Scalar1, typename Scalar2> BitMask4 operator==(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b);
    template <typename Scalar1, typename Scalar2> BitMask4 operator!=(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b);
    template <typename Scalar1, typename Scalar2> BitMask4 operator<(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b);
  
    template <typename Scalar> Vector4<Scalar> operator-(const Vector4<Scalar>& a);

    template <typename Scalar1, typename Scalar2> 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> operator+(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b);
    
    template <typename Scalar1, typename Scalar2>
    Vector4<typename Promote<Scalar1, Scalar2>::RT> operator-(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b);  
    
    template <typename Scalar1, typename Scalar2>
    Vector4<typename Promote<Scalar1, Scalar2>::RT> operator*(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b);
    
    template <typename Scalar1, typename Scalar2> 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> operator*(const Vector4<Scalar1>& a, Scalar2 s);
    
    template <typename Scalar1, typename Scalar2> 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> operator*(Scalar1 s, const Vector4<Scalar2>& a);

    template <typename Scalar1, typename Scalar2> 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> operator/(const Vector4<Scalar1>& a, Scalar2 s);
        
    template <typename Scalar> Scalar sum(const Vector4<Scalar>& a);
    template <typename Scalar> Scalar sum3(const Vector4<Scalar>& a);
    template <typename Scalar> Scalar sum4(const Vector4<Scalar>& a); 
    
    template <typename Scalar> const Vector3<Scalar>& xyz(const Vector4<Scalar>& a); 
    
    template <typename Scalar1, typename Scalar2>
    typename Promote<Scalar1, Scalar2>::RT dot(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b); 

    template <typename Scalar1, typename Scalar2>
    typename Promote<Scalar1, Scalar2>::RT dot3(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b); 

    template <typename Scalar1, typename Scalar2>
    typename Promote<Scalar1, Scalar2>::RT dot4(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b); 

    template <typename Scalar> Scalar norm(const Vector4<Scalar>& a);  
    template <typename Scalar> Scalar abs(const Vector4<Scalar>& a);    
    template <typename Scalar> Scalar arg(const Vector4<Scalar>& a);  

    template <typename Scalar1, typename Scalar2>
    void convert(Scalar1* v, const Vector4<Scalar2>& a);

    template <typename Scalar>
    Vector4<Scalar> dot3(const Vector4<Scalar>& a0, const Vector4<Scalar>& b0,
                         const Vector4<Scalar>& a1, const Vector4<Scalar>& b1);
  
    template <typename Scalar>
    Vector4<Scalar> dot3(const Vector4<Scalar>& a0, const Vector4<Scalar>& b0,
                         const Vector4<Scalar>& a1, const Vector4<Scalar>& b1,
                         const Vector4<Scalar>& a2, const Vector4<Scalar>& b2);
    
    template <typename Scalar>
    Vector4<Scalar> dot3(const Vector4<Scalar>& a0, const Vector4<Scalar>& b0,
                         const Vector4<Scalar>& a1, const Vector4<Scalar>& b1,
                         const Vector4<Scalar>& a2, const Vector4<Scalar>& b2,
                         const Vector4<Scalar>& a3, const Vector4<Scalar>& b3);


    template <int X, int Y, int Z, int W, typename Scalar>
    Vector4<Scalar> swizzle(const Vector4<Scalar>& a);

    template <typename Scalar>
    Vector4<Scalar> homogenize(const Vector4<Scalar>& a);

    // Quaternion ops 

    template <typename Scalar1, typename Scalar2>
    Vector4<typename Promote<Scalar1, Scalar2>::RT> mul(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b);

    template <typename Scalar1, typename Scalar2>
    Vector4<typename Promote<Scalar1, Scalar2>::RT> mul(const Vector4<Scalar1>& a, const Vector3<Scalar2>& b);

    template <typename Scalar1, typename Scalar2>
    Vector4<typename Promote<Scalar1, Scalar2>::RT> mul(const Vector3<Scalar1>& a, const Vector4<Scalar2>& b);

    template <typename Scalar1, typename Scalar2>
    Vector4<typename Promote<Scalar1, Scalar2>::RT> mul(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b);

    template <typename Scalar1, typename Scalar2>
    Vector3<typename Promote<Scalar1, Scalar2>::RT> cross(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b);

    template <typename Scalar> Vector4<Scalar> conjugate(const Vector4<Scalar>& a);
    template <typename Scalar> Vector4<Scalar> inverse(const Vector4<Scalar>& a);

    // Plane ops

    template <typename Scalar> Vector4<Scalar> plane(const Vector3<Scalar>& normal, const Vector3<Scalar>& point);
    template <typename Scalar> Vector4<Scalar> plane(const Vector3<Scalar>& v0, const Vector3<Scalar>& v1, const Vector3<Scalar>& v2);
    
    template <typename Scalar1, typename Scalar2>
    typename Promote<Scalar1, Scalar2>::RT signedDistance(const Vector4<Scalar1>& plane, const Vector3<Scalar2>& point); 

    template <typename Scalar> Vector4<Scalar> align(const Vector3<Scalar>& u1, const Vector3<Scalar>& u2);
    
 
    template <typename Scalar> void decomposeZ(const Vector4<Scalar>& q, Vector4<Scalar>& qxy, Vector4<Scalar>& qz);

    template <typename Scalar> bool isfinite(const Vector4<Scalar>& a);



    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>::Vector4() 
    {}

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>::Vector4(Scalar x, Scalar y, Scalar z, Scalar w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {}


    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>::Vector4(Zero)
        : x()
        , y()
        , z()
        , w()
    {}

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>::Vector4(Identity)
        : x()
        , y()
        , z()
        , w(1)
    {}
       
    template <typename Scalar>
    template <int I>
    FORCEINLINE
    Vector4<Scalar>::Vector4(Unit<I>)       
        : x(Scalar(I == 0))
        , y(Scalar(I == 1))
        , z(Scalar(I == 2))
        , w(Scalar(I == 3))
    {}
      
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Vector4<Scalar>::Vector4(const Scalar2* v)  
        : x(Scalar(v[0]))
        , y(Scalar(v[1]))
        , z(Scalar(v[2]))
        , w(Scalar(v[3]))
    {}

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Vector4<Scalar>::Vector4(const Vector4<Scalar2>& a)      
        : x(Scalar(a.x))
        , y(Scalar(a.y))
        , z(Scalar(a.z))
        , w(Scalar(a.w))
    {}

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Vector4<Scalar>::Vector4(const Vector3<Scalar2>& a, Scalar w) 
        : x(Scalar(a.x))
        , y(Scalar(a.y))
        , z(Scalar(a.z))
        , w(w)
    {}  

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>::Vector4(Scalar w)
        : x()
        , y()
        , z()
        , w(w)
    {}
    
    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>::operator const Scalar*() const
    {
        return &x;
    }  

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>::operator Scalar*()
    {
        return &x;
    }  
       
    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator=(Zero)
    {
        x = Scalar();
        y = Scalar();
        z = Scalar();
        w = Scalar(); 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator+=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator-=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator*=(Zero)
    {
        return *this = Zero();
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator=(Identity)
    {
        x = Scalar();
        y = Scalar();
        z = Scalar();
        w = Scalar(1); 
        return *this;
    } 

    template <typename Scalar>
    template <int I>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator=(Unit<I>)
    {
        x = Scalar(I == 0);
        y = Scalar(I == 1);
        z = Scalar(I == 2);
        w = Scalar(I == 3);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator=(const Scalar2* v)
    {
        x = Scalar(v[0]);
        y = Scalar(v[1]);
        z = Scalar(v[2]);
        w = Scalar(v[3]);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator=(const Vector4<Scalar2>& a)
    {
        x = Scalar(a.x);
        y = Scalar(a.y);
        z = Scalar(a.z);
        w = Scalar(a.w);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator+=(const Vector4<Scalar2>& a)
    {
        x += Scalar(a.x); 
        y += Scalar(a.y); 
        z += Scalar(a.z);
        w += Scalar(a.w);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator-=(const Vector4<Scalar2>& a)
    {
        x -= Scalar(a.x); 
        y -= Scalar(a.y); 
        z -= Scalar(a.z);
        w -= Scalar(a.w);
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator*=(const Vector4<Scalar2>& a)
    {
        x *= Scalar(a.x); 
        y *= Scalar(a.y); 
        z *= Scalar(a.z);
        w *= Scalar(a.w);
        return *this;
    }


    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator*=(Scalar s)
    {
        x *= s; 
        y *= s; 
        z *= s;
        w *= s;
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar>& Vector4<Scalar>::operator/=(Scalar s)
    {
        ASSERT(!iszero(s));
        return *this *= Scalar(1) / s;
    }    

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Vector3<typename Promote<Scalar, Scalar2>::RT> 
    Vector4<Scalar>::operator()(const Vector3<Scalar2>& v) const
    {
        const Vector3<Scalar>& u = xyz(*this); 
        return v + Scalar(2) * cross(u, cross(u, v) + v * w);
    }
     

#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Vector4<Scalar>& a)
    {
        return os << a.x << ' ' << a.y << ' ' << a.z << ' ' << a.w;
    }

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Vector4<Scalar>& a)
    {
        return is >> a.x >> a.y >> a.z >> a.w;
    }

#endif

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    BitMask4 operator==(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        return BitMask4(a.x == b.x, 
                        a.y == b.y, 
                        a.z == b.z, 
                        a.w == b.w);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    BitMask4 operator!=(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        return BitMask4(a.x != b.x, 
                        a.y != b.y, 
                        a.z != b.z, 
                        a.w != b.w);
    }
     
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    BitMask4 operator<(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        return BitMask4(a.x < b.x, 
                        a.y < b.y, 
                        a.z < b.z, 
                        a.w < b.w);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> operator-(const Vector4<Scalar>& a)
    {
        return Vector4<Scalar>(-a.x, 
                               -a.y,
                               -a.z,
                               -a.w);
    }
  
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    operator+(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector4<RT>(a.x + b.x, 
						   a.y + b.y, 
						   a.z + b.z, 
						   a.w + b.w);
    }

  
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    operator-(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector4<RT>(a.x - b.x, 
						   a.y - b.y, 
						   a.z - b.z, 
						   a.w - b.w);
    }  

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector4<RT>(a.x * b.x, 
						   a.y * b.y, 
						   a.z * b.z, 
						   a.w * b.w);
    }  


    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(const Vector4<Scalar1>& a, Scalar2 s)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector4<RT>(a.x * s,
                           a.y * s,
                           a.z * s,
                           a.w * s);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(Scalar1 s, const Vector4<Scalar2>& a)
    {
        return a * s;
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    operator/(const Vector4<Scalar1>& a, Scalar2 s)
    { 
        ASSERT(!iszero(s));
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return a * (RT(1) / RT(s));
    }
    
    template <typename Scalar> 
    FORCEINLINE
    Scalar sum(const Vector4<Scalar>& a)
    {
        return sum4(a); 
    }

    template <typename Scalar> 
    FORCEINLINE
    Scalar sum3(const Vector4<Scalar>& a)
    {
        return a.x + a.y + a.z;  
    }    
    
    template <typename Scalar> 
    FORCEINLINE
    Scalar sum4(const Vector4<Scalar>& a)
    {
        return a.x + a.y + a.z + a.w;   
    }
    
    template <typename Scalar> 
    FORCEINLINE
    const Vector3<Scalar>& xyz(const Vector4<Scalar>& a)
    {
        return reinterpret_cast<const Vector3<Scalar>&>(a); 
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    typename Promote<Scalar1, Scalar2>::RT 
    dot(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        return dot4(a, b);
    } 

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    typename Promote<Scalar1, Scalar2>::RT 
    dot3(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        return sum3(a * b);
    } 
    
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    typename Promote<Scalar1, Scalar2>::RT 
    dot4(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        return sum4(a * b);
    } 

    template <typename Scalar>
    FORCEINLINE
    Scalar norm(const Vector4<Scalar>& a)
    {
        return dot(a, a);
    }    

    template <typename Scalar>
    FORCEINLINE
    Scalar abs(const Vector4<Scalar>& a)
    {
        return sqrt(norm(a));
    }  

    template <typename Scalar>
    FORCEINLINE
    Scalar arg(const Vector4<Scalar>& a)
    {
        return atan2(length(xyz(a)), a.w);
    }    
 
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    void convert(Scalar1* v, const Vector4<Scalar2>& a)
    {
        v[0] = Scalar1(a.x);
        v[1] = Scalar1(a.y);
        v[2] = Scalar1(a.z);
        v[3] = Scalar1(a.w);
    }
    
    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> dot3(const Vector4<Scalar>& a0, const Vector4<Scalar>& b0,
                         const Vector4<Scalar>& a1, const Vector4<Scalar>& b1)
    { 
        return Vector4<Scalar>(dot3(a0, b0), 
                               dot3(a1, b1),
                               Scalar(),
                               Scalar());
    }
    
    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> dot3(const Vector4<Scalar>& a0, const Vector4<Scalar>& b0,
                         const Vector4<Scalar>& a1, const Vector4<Scalar>& b1,
                         const Vector4<Scalar>& a2, const Vector4<Scalar>& b2)
    { 
        return Vector4<Scalar>(dot3(a0, b0), 
                               dot3(a1, b1), 
                               dot3(a2, b2),
                               Scalar());
    }
    
    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> dot3(const Vector4<Scalar>& a0, const Vector4<Scalar>& b0,
                         const Vector4<Scalar>& a1, const Vector4<Scalar>& b1,
                         const Vector4<Scalar>& a2, const Vector4<Scalar>& b2,
                         const Vector4<Scalar>& a3, const Vector4<Scalar>& b3)
    { 
        return Vector4<Scalar>(dot3(a0, b0), 
                               dot3(a1, b1),
                               dot3(a2, b2),
                               dot3(a3, b3));
    }
   
    template <int X, int Y, int Z, int W, typename Scalar>
    FORCEINLINE
    Vector4<Scalar> swizzle(const Vector4<Scalar>& a)
    {
        return Vector4<Scalar>(a[X], a[Y], a[Z], a[W]);
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> homogenize(const Vector4<Scalar>& a)
    {
        Scalar s = Scalar(1) / a.w;
        return Vector4<Scalar>(a.x * s, a.y * s, a.z * s, Scalar(1));
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector4<RT>(a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
						   a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
						   a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
						   a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Vector4<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector4<RT>( a.w * b.x + a.y * b.z - a.z * b.y,
							a.w * b.y + a.z * b.x - a.x * b.z,
							a.w * b.z + a.x * b.y - a.y * b.x,
						   -a.x * b.x - a.y * b.y - a.z * b.z);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Vector3<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector4<RT>( a.x * b.w + a.y * b.z - a.z * b.y,
							a.y * b.w + a.z * b.x - a.x * b.z,
							a.z * b.w + a.x * b.y - a.y * b.x,
						   -a.x * b.x - a.y * b.y - a.z * b.z);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    Vector4<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Vector3<Scalar1>& a, const Vector3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Vector4<RT>( a.y * b.z - a.z * b.y,
							a.z * b.x - a.x * b.z,
							a.x * b.y - a.y * b.x,
						   -a.x * b.x - a.y * b.y - a.z * b.z);
    }   

  



    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    cross(const Vector4<Scalar1>& a, const Vector4<Scalar2>& b)
    {
        return cross(xyz(a), xyz(b));
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> conjugate(const Vector4<Scalar>& a)
    {
        return Vector4<Scalar>(-a.x, 
                               -a.y,
                               -a.z,
                                a.w);
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> inverse(const Vector4<Scalar>& a)
    {
        return conjugate(a) / dot(a, a);
    }

    template <typename Scalar> 
    FORCEINLINE
    Vector4<Scalar> plane(const Vector3<Scalar>& normal, const Vector3<Scalar>& point)
    {
        return Vector4<Scalar>(normal, -dot(normal, point)); 
    }

    template <typename Scalar> 
    FORCEINLINE
    Vector4<Scalar> plane(const Vector3<Scalar>& v0, const Vector3<Scalar>& v1, const Vector3<Scalar>& v2)
    {
        Vector3<Scalar> normal = cross(v1 - v0, v2 - v0); 
        return plane(normal, v0); 
    }  

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE
    typename Promote<Scalar1, Scalar2>::RT signedDistance(const Vector4<Scalar1>& plane, const Vector3<Scalar2>& point)
    {
        return dot4(plane, Vector4<Scalar2>(point, Scalar2(1)));    
    } 

    template <typename Scalar> 
    FORCEINLINE
    Vector4<Scalar> align(const Vector3<Scalar>& u1, const Vector3<Scalar>& u2)
    {
        Vector3<Scalar> h = u1 + u2;    
        Scalar s = lengthSquared(h);
        return ispositive(s) ? mul(h * rsqrt(s), -u1) : Unit<2>(); 
    }    
 
    // This is the one from Jonathan Blow's Inner Product article "Inverse Kinematics with Quaternion Joint Limits"
    template <typename Scalar> 
    FORCEINLINE
    Vector4<Scalar> alignBlow(const Vector3<Scalar>& u1, const Vector3<Scalar>& u2)
    {
        Vector4<Scalar> q(cross(u1, u2), dot(u1, u2) + 1.0f);
        Scalar s = lengthSquared(q);
        return ispositive(s) ? q * rsqrt(s) : Unit<2>();    
    } 

    // Which is a simplification of
    template <typename Scalar> 
    FORCEINLINE
    Vector4<Scalar> alignBlow2(const Vector3<Scalar>& u1, const Vector3<Scalar>& u2)
    {
        Vector3<Scalar> n = normalize(cross(u1, u2));
        Scalar d = dot(u1, u2);
        return Vector4<Scalar>(n * sqrt((1 - d) * 0.5f), sqrt((1 + d) * 0.5f));
    } 
 
    template <typename Scalar> 
    FORCEINLINE
    void decomposeX(const Vector4<Scalar>& q, Vector4<Scalar>& qyz, Vector4<Scalar>& qx)
    {
        Scalar r = rsqrt(q.x * q.x + q.w * q.w);
       
        qyz = Vector4<Scalar>(Scalar(),
                              (q.w * q.y - q.x * q.z) * r, 
                              (q.w * q.z + q.x * q.y) * r, 
                              Scalar(1) / r);
        qx = Vector4<Scalar>(q.x * r,
                             Scalar(), 
                             Scalar(), 
                             q.w * r); 
    } 

    template <typename Scalar> 
    FORCEINLINE
    void decomposeY(const Vector4<Scalar>& q, Vector4<Scalar>& qxz, Vector4<Scalar>& qy)
    {
        Scalar r = rsqrt(q.y * q.y + q.w * q.w);
       
        qxz = Vector4<Scalar>((q.w * q.x + q.y * q.z) * r,
                              Scalar(), 
                              (q.w * q.z - q.y * q.x) * r, 
                              Scalar(1) / r);
        qy = Vector4<Scalar>(Scalar(),
                             q.y * r,
                             Scalar(),  
                             q.w * r); 
    }

    template <typename Scalar> 
    FORCEINLINE
    void decomposeZ(const Vector4<Scalar>& q, Vector4<Scalar>& qxy, Vector4<Scalar>& qz)
    {
        Scalar r = rsqrt(q.z * q.z + q.w * q.w);
       
        qxy = Vector4<Scalar>((q.w * q.x - q.z * q.y) * r, 
                              (q.w * q.y + q.z * q.x) * r, 
                              Scalar(), 
                              Scalar(1) / r);
        qz = Vector4<Scalar>(Scalar(), 
                             Scalar(), 
                             q.z * r, 
                             q.w * r); 
    }

    template <typename Scalar>
    bool isfinite(const Vector4<Scalar>& a)
    {
        return isfinite(a.x) && isfinite(a.y) && isfinite(a.z) && isfinite(a.w); 
    }

}

#if USE_SSE
#include <moto/Vector4_SSE.hpp>
#endif

#endif
