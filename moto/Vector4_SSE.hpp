/*  MoTo - Motion Toolkit
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_VECTOR4_HPP
#error This header file should be included by Vector4.hpp only.
#endif

#include <xmmintrin.h>

#define USE_FDIV 1
#define USE_APPROX 0


#define MT_SPLAT(a, i) _mm_shuffle_ps((a), (a), _MM_SHUFFLE((i), (i), (i), (i)))

namespace mt
{ 
    FORCEINLINE
    __m128 div(__m128 a, __m128 b)
    {
#if USE_APPROX
        return _mm_mul_ps(a, _mm_rcp_ps(b));
#else
        return _mm_div_ps(a, b);
#endif 
    }
    
    FORCEINLINE
    __m128 div(__m128 a, float s)
    {
        ASSERT(s != 0.0f);
        
#if USE_FDIV
        return _mm_mul_ps(a, _mm_set1_ps(1.0f / s));
#else
        return div(a, _mm_set1_ps(1));
#endif
    }

#if WASTE_CYCLES

    // This one taken straight from xmmintrin.h is more expensive than the one below. No BS.

    FORCEINLINE
    void transpose(__m128& r0, __m128& r1, __m128& r2, __m128& r3)
    {
        _MM_TRANSPOSE4_PS(r0, r1, r2, r3);
    }

#else

    FORCEINLINE
    void transpose(__m128& r0, __m128& r1, __m128& r2, __m128& r3)
    { 
        __m128 lo01 = _mm_unpacklo_ps(r0, r1); 
        __m128 lo23 = _mm_unpacklo_ps(r2, r3); 
        __m128 hi01 = _mm_unpackhi_ps(r0, r1);
        __m128 hi23 = _mm_unpackhi_ps(r2, r3);
        r0 = _mm_movelh_ps(lo01, lo23);
        r1 = _mm_movehl_ps(lo23, lo01);
        r2 = _mm_movelh_ps(hi01, hi23);
        r3 = _mm_movehl_ps(hi23, hi01);
    }

#endif

    template <>
    class Vector4<float>
    {
    public:
        typedef float ScalarType; 
      
        Vector4(); 
        Vector4(float x, float y, float z, float w = float());   
        explicit Vector4(__m128 v); 
        explicit Vector4(const float* v);  

        Vector4(Zero);
        Vector4(Identity);
        template <int I> Vector4(Unit<I>); 
        template <typename Scalar2> explicit Vector4(const Scalar2* v);  
        template <typename Scalar2> Vector4(const Vector4<Scalar2>& a);  
        template <typename Scalar2> explicit Vector4(const Vector3<Scalar2>& a, float w = float());   
        explicit Vector4(float w);

        operator const float*() const;
        operator float*();

        Vector4<float>& operator=(Zero);
        Vector4<float>& operator+=(Zero);
        Vector4<float>& operator-=(Zero);
        Vector4<float>& operator*=(Zero);
        
        Vector4<float>& operator=(Identity);
        template <int I> Vector4<float>& operator=(Unit<I>);    

        template <typename Scalar2> Vector4<float>& operator=(const Scalar2* v);
        template <typename Scalar2> Vector4<float>& operator=(const Vector4<Scalar2>& a);
        template <typename Scalar2> Vector4<float>& operator+=(const Vector4<Scalar2>& a);
        template <typename Scalar2> Vector4<float>& operator-=(const Vector4<Scalar2>& a);
        template <typename Scalar2> Vector4<float>& operator*=(const Vector4<Scalar2>& a);

        Vector4<float>& operator=(__m128 v);

        Vector4<float>& operator=(const float* v); 
        Vector4<float>& operator=(const Vector4<float>& a);
        Vector4<float>& operator+=(const Vector4<float>& a);
        Vector4<float>& operator-=(const Vector4<float>& a);
        Vector4<float>& operator*=(const Vector4<float>& a);
        
        Vector4<float>& operator*=(float s);
        Vector4<float>& operator/=(float s); 

        Vector3<float> operator()(const Vector3<float>& v) const;
        
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4201)
#endif

        union 
        {
            struct { float x, y, z, w; };
            __m128 vec; 
        };

#ifdef _MSC_VER
#pragma warning(pop)
#endif

    };   


    BitMask4 operator==(const Vector4<float>& a, const Vector4<float>& b);
    BitMask4 operator!=(const Vector4<float>& a, const Vector4<float>& b);
    BitMask4 operator<(const Vector4<float>& a, const Vector4<float>& b);
  
    Vector4<float> operator-(const Vector4<float>& a);

    Vector4<float> operator+(const Vector4<float>& a, const Vector4<float>& b);
    Vector4<float> operator-(const Vector4<float>& a, const Vector4<float>& b);  
    Vector4<float> operator*(const Vector4<float>& a, const Vector4<float>& b);
    
    Vector4<float> operator*(const Vector4<float>& a, float s);
    Vector4<float> operator/(const Vector4<float>& a, float s);
    
    float sum3(const Vector4<float>& a); 
    float sum4(const Vector4<float>& a); 
    
    Vector4<float> dot3(const Vector4<float>& a0, const Vector4<float>& b0,
                        const Vector4<float>& a1, const Vector4<float>& b1);
   
    Vector4<float> dot3(const Vector4<float>& a0, const Vector4<float>& b0,
                        const Vector4<float>& a1, const Vector4<float>& b1,
                        const Vector4<float>& a2, const Vector4<float>& b2);
    
    Vector4<float> dot3(const Vector4<float>& a0, const Vector4<float>& b0,
                        const Vector4<float>& a1, const Vector4<float>& b1,
                        const Vector4<float>& a2, const Vector4<float>& b2,
                        const Vector4<float>& a3, const Vector4<float>& b3);
   
    template <int X, int Y, int Z, int W> 
    Vector4<float> swizzle(const Vector4<float>& a);
    

    FORCEINLINE
    Vector4<float>::Vector4() 
    {}    
    
    FORCEINLINE
    Vector4<float>::Vector4(float x, float y, float z, float w)
        : vec(_mm_setr_ps(x, y, z, w))
    {}
 
    FORCEINLINE
    Vector4<float>::Vector4(__m128 v) 
        : vec(v)
    {}
   
    FORCEINLINE 
    Vector4<float>::Vector4(const float* v)
        : vec(_mm_loadu_ps(v))
    {} 

    FORCEINLINE
    Vector4<float>::Vector4(Zero)
        : vec(_mm_setzero_ps())
    {}

    FORCEINLINE
    Vector4<float>::Vector4(Identity)      
        : vec(_mm_setr_ps(float(), float(), float(), float(1)))
    {}
    
    template <int I>
    FORCEINLINE
    Vector4<float>::Vector4(Unit<I>)   
        : vec(_mm_setr_ps(float(I == 0), float(I == 1), float(I == 2), float(I == 3)))
    {}
  
    template <typename Scalar2>
    FORCEINLINE 
    Vector4<float>::Vector4(const Scalar2* v)
        : vec(_mm_setr_ps(float(v[0]), float(v[1]), float(v[2]), float(v[3])))
    {}

    template <typename Scalar2>
    FORCEINLINE 
    Vector4<float>::Vector4(const Vector4<Scalar2>& a)
        : vec(_mm_setr_ps(float(a.x), float(a.y), float(a.z), float(a.w)))
    {}

    template <typename Scalar2>
    FORCEINLINE 
    Vector4<float>::Vector4(const Vector3<Scalar2>& a, float w)
        : vec(_mm_setr_ps(float(a.x), float(a.y), float(a.z), w))
    {}
   
    FORCEINLINE
    Vector4<float>::Vector4(float w)
        : vec(_mm_setr_ps(float(), float(), float(), w))
    {}

    FORCEINLINE
    Vector4<float>::operator const float*() const
    {
        return &x;
    }  

    FORCEINLINE
    Vector4<float>::operator float*()
    {
        return &x;
    }   

    
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator=(Zero)
    {
        vec = _mm_setzero_ps();
        return *this;
    }
    
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator+=(Zero)
    {
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator-=(Zero)
    {
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator*=(Zero)
    {
        return *this = Zero();
    }   
    
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator=(Identity)
    {
        vec = _mm_setr_ps(float(), float(), float(), float(1));
        return *this;
    }
     
    template <int I>
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator=(Unit<I>)
    {
        vec = _mm_setr_ps(float(I == 0), float(I == 1), float(I == 2), float(I == 3));
        return *this;
    }

    template <typename Scalar2>
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator=(const Vector4<Scalar2>& a)
    {
        vec = _mm_setr_ps(float(a.x), float(a.y), float(a.z), float(a.w));
        return *this;
    }     

    template <typename Scalar2>
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator=(const Scalar2* v)
    { 
        vec = _mm_setr_ps(float(v[0]), float(v[1]), float(v[2]), float(v[3]));
        return *this;
    }


    template <typename Scalar2>
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator+=(const Vector4<Scalar2>& a)
    { 
        return *this += Vector4<float>(a);
    }

    template <typename Scalar2>
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator-=(const Vector4<Scalar2>& a)
    { 
        return *this -= Vector4<float>(a);
    }

    template <typename Scalar2>
    FORCEINLINE
    Vector4<float>& Vector4<float>::operator*=(const Vector4<Scalar2>& a)
    {
        return *this *= Vector4<float>(a);
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator=(__m128 v)
    {
        vec = v; 
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator=(const float* v)
    {
        vec = _mm_loadu_ps(v); 
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator=(const Vector4<float>& a)
    {
        vec = a.vec;
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator+=(const Vector4<float>& a)
    {
        vec = _mm_add_ps(vec, a.vec);
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator-=(const Vector4<float>& a)
    {
        vec = _mm_sub_ps(vec, a.vec);
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator*=(const Vector4<float>& a)
    {
        vec = _mm_mul_ps(vec, a.vec);
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator*=(float s)
    {
        vec = _mm_mul_ps(vec, _mm_set1_ps(s));
        return *this;
    }

    FORCEINLINE
    Vector4<float>& Vector4<float>::operator/=(float s)
    { 
        vec = div(vec, s);
        return *this;
    }    

    // TODO: This operator could use some SIMD-ing
    FORCEINLINE
    Vector3<float> Vector4<float>::operator()(const Vector3<float>& v) const
    {
        const Vector3<float>& u = xyz(*this); 
        return v + 2.0f * cross(u, cross(u, v) + v * w);
    }  

    FORCEINLINE 
    BitMask4 operator==(const Vector4<float>& a, const Vector4<float>& b)
    {
        return BitMask4(_mm_movemask_ps(_mm_cmpeq_ps(a.vec, b.vec)));
    }
   
    FORCEINLINE 
    BitMask4 operator!=(const Vector4<float>& a, const Vector4<float>& b)
    {
        return BitMask4(_mm_movemask_ps(_mm_cmpneq_ps(a.vec, b.vec)));
    }
    
    FORCEINLINE 
    BitMask4 operator<(const Vector4<float>& a, const Vector4<float>& b)
    {
        return BitMask4(_mm_movemask_ps(_mm_cmplt_ps(a.vec, b.vec)));
    }

    FORCEINLINE 
    Vector4<float> operator-(const Vector4<float>& a)
    {
        return Vector4<float>(_mm_sub_ps(_mm_setzero_ps(), a.vec));
    }
  
    FORCEINLINE 
    Vector4<float> 
    operator+(const Vector4<float>& a, const Vector4<float>& b)
    {
        return Vector4<float>(_mm_add_ps(a.vec, b.vec));
    }

    FORCEINLINE 
    Vector4<float> 
    operator-(const Vector4<float>& a, const Vector4<float>& b)
    {
        return Vector4<float>(_mm_sub_ps(a.vec, b.vec));
    } 

    FORCEINLINE 
    Vector4<float> 
    operator*(const Vector4<float>& a, const Vector4<float>& b)
    {
        return Vector4<float>(_mm_mul_ps(a.vec, b.vec));
    }

    FORCEINLINE 
    Vector4<float> operator*(const Vector4<float>& a, float s)
    {
        return Vector4<float>(_mm_mul_ps(a.vec, _mm_set1_ps(s)));
    }

    FORCEINLINE 
    Vector4<float> operator/(const Vector4<float>& a, float s)
    {
        return Vector4<float>(div(a.vec, s));
    }

    FORCEINLINE 
    float sum4(const Vector4<float>& a)
    {
        __m128 tmp = _mm_add_ps(a.vec, _mm_movehl_ps(a.vec, a.vec));
        tmp = _mm_add_ss(tmp, _mm_shuffle_ps(tmp, tmp, 1));
        return *reinterpret_cast<float*>(&tmp);
    } 
     
    FORCEINLINE 
    float sum3(const Vector4<float>& a)
    {
        __m128 tmp = _mm_add_ss(_mm_add_ss(a.vec, _mm_shuffle_ps(a.vec, a.vec, 1)), _mm_shuffle_ps(a.vec, a.vec, 2));
        return *reinterpret_cast<float*>(&tmp);
    } 
     
    FORCEINLINE
    void convert(float* a, const Vector4<float>& b)
    {
        _mm_storeu_ps(a, b.vec);
    }   
    
    FORCEINLINE
    Vector4<float> dot3(const Vector4<float>& a0, const Vector4<float>& b0,
                        const Vector4<float>& a1, const Vector4<float>& b1)
    { 
        __m128 tmp0 = _mm_mul_ps(a0.vec, b0.vec);
        __m128 tmp1 = _mm_mul_ps(a1.vec, b1.vec);
        __m128 tmp2 = _mm_setzero_ps();
        __m128 tmp3 = _mm_setzero_ps();

        transpose(tmp0, tmp1, tmp2, tmp3);
        
        return Vector4<float>(_mm_add_ps(_mm_add_ps(tmp0, tmp1), tmp2));
    }
    
    FORCEINLINE
    Vector4<float> dot3(const Vector4<float>& a0, const Vector4<float>& b0,
                        const Vector4<float>& a1, const Vector4<float>& b1,
                        const Vector4<float>& a2, const Vector4<float>& b2)
    { 
        __m128 tmp0 = _mm_mul_ps(a0.vec, b0.vec);
        __m128 tmp1 = _mm_mul_ps(a1.vec, b1.vec);
        __m128 tmp2 = _mm_mul_ps(a2.vec, b2.vec);
        __m128 tmp3 = _mm_setzero_ps();

        transpose(tmp0, tmp1, tmp2, tmp3);
        
        return Vector4<float>(_mm_add_ps(_mm_add_ps(tmp0, tmp1), tmp2));
    }
    
    FORCEINLINE
    Vector4<float> dot3(const Vector4<float>& a0, const Vector4<float>& b0,
                        const Vector4<float>& a1, const Vector4<float>& b1,
                        const Vector4<float>& a2, const Vector4<float>& b2,
                        const Vector4<float>& a3, const Vector4<float>& b3)
    { 
        __m128 tmp0 = _mm_mul_ps(a0.vec, b0.vec);
        __m128 tmp1 = _mm_mul_ps(a1.vec, b1.vec);
        __m128 tmp2 = _mm_mul_ps(a2.vec, b2.vec);
        __m128 tmp3 = _mm_mul_ps(a3.vec, b3.vec);

        transpose(tmp0, tmp1, tmp2, tmp3);
        
        return Vector4<float>(_mm_add_ps(_mm_add_ps(tmp0, tmp1), tmp2));
    } 
    
    template <int X, int Y, int Z, int W>
    FORCEINLINE
    Vector4<float> swizzle(const Vector4<float>& a)
    {
        return Vector4<float>(_mm_shuffle_ps(a.vec, a.vec, _MM_SHUFFLE(W, Z, Y, X)));
    }
    
    FORCEINLINE
    Vector4<float> homogenize(const Vector4<float>& a)
    {
        ASSERT(!iszero(a.w));
        return Vector4<float>(div(a.vec, MT_SPLAT(a.vec, 3)));
    }
}
