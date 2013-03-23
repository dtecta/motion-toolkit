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

#ifndef MT_MATRIX4X4_HPP
#error This header file should be included by Matrix4x4.hpp only.
#endif


namespace mt
{ 
    template <>
    class Matrix4x4<float>
    {
    public:
        typedef float ScalarType;

        Matrix4x4();
        Matrix4x4(Identity);
        template<typename Scalar2> explicit Matrix4x4(const Scalar2* v);   
        Matrix4x4(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3);
        Matrix4x4(const Vector4<float>& c0, const Vector4<float>& c1, const Vector4<float>& c2, const Vector4<float>& c3);
        Matrix4x4(const __m128& c0, const __m128& c1, const __m128& c2, const __m128& c3);
        explicit Matrix4x4(const Vector3<float>& p);
        explicit Matrix4x4(const Matrix3x3<float>& a, const Vector3<float>& p = Zero());
        
        operator const Vector4<float>*() const; 
        operator Vector4<float>*();

        Matrix4x4<float>& operator=(Identity);
  
        template <typename Scalar2> void setValue(const Scalar2* v);  
        void setValue(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3);
        void setValue(const Vector4<float>& c0, const Vector4<float>& c1, const Vector4<float>& c2, const Vector4<float>& c3);
        void setValue(const __m128& c0, const __m128& c1, const __m128& c2, const __m128& c3);
      
        void setBasis(const Matrix3x3<float>& basis);
        void setOrigin(const Vector3<float>& origin);

        void setColumn(int i, const Vector3<float>& v);
        void setColumn(int i, const Vector4<float>& v);

        void setRow(int i, const Vector3<float>& v);
        void setRow(int i, const Vector4<float>& v);

    private:
        Vector4<float> mCol[4];
    };

    Vector4<float> mul(const Matrix4x4<float>& a, const Vector4<float>& v);
    Vector4<float> mul(const Vector4<float>& v, const Matrix4x4<float>& a);

    Matrix4x4<float> transpose(const Matrix4x4<float>& a);


    
    
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4() 
    {} 
    
    
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(Identity)
    {
        *this = Identity();
    }

    template <typename Scalar2>
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Scalar2* v) 
    {
        setValue(v);
    }

    
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3)
    {
        setValue(c0, c1, c2, c3);
    }
   

    
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Vector4<float>& c0, const Vector4<float>& c1, const Vector4<float>& c2, const Vector4<float>& c3)
    {
        setValue(c0, c1, c2, c3);
    }
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const __m128& c0, const __m128& c1, const __m128& c2, const __m128& c3)
    {
        setValue(c0, c1, c2, c3);
    }

    
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Vector3<float>& p)
    {
        mCol[0] = Unit<0>();
        mCol[1] = Unit<1>();
        mCol[2] = Unit<2>();
        mCol[3] = Vector4<float>(p, float(1));
    }

    
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Matrix3x3<float>& a, const Vector3<float>& p)
    {
        mCol[0] = Vector4<float>(a[0][0], a[1][0], a[2][0], float());
        mCol[1] = Vector4<float>(a[0][1], a[1][1], a[2][1], float());
        mCol[2] = Vector4<float>(a[0][2], a[1][2], a[2][2], float());
        mCol[3] = Vector4<float>(p, float(1));
    }
        
    FORCEINLINE
    Matrix4x4<float>::operator const Vector4<float>*() const
    {
        return mCol;
    } 

    FORCEINLINE
    Matrix4x4<float>::operator Vector4<float>*()
    {
        return mCol;
    } 
    
    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator=(Identity)
    {
        mCol[0] = Unit<0>();
        mCol[1] = Unit<1>();
        mCol[2] = Unit<2>();
        mCol[3] = Unit<3>();
        return *this;
    }

    template <typename Scalar2>
    FORCEINLINE
    void Matrix4x4<float>::setValue(const Scalar2* v)
    {
        mCol[0] = Vector4<float>(&v[0]); 
        mCol[1] = Vector4<float>(&v[4]); 
        mCol[2] = Vector4<float>(&v[8]); 
        mCol[3] = Vector4<float>(&v[12]); 
    }  

   



    
    FORCEINLINE 
    void Matrix4x4<float>::setValue(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3)
    {
        mCol[0] = Vector4<float>(c0, float());
        mCol[1] = Vector4<float>(c1, float());
        mCol[2] = Vector4<float>(c2, float());
        mCol[3] = Vector4<float>(c3, float(1));
    }
   
    
    FORCEINLINE 
    void Matrix4x4<float>::setValue(const Vector4<float>& c0, const Vector4<float>& c1, const Vector4<float>& c2, const Vector4<float>& c3)
    {
        mCol[0] = c0;
        mCol[1] = c1;
        mCol[2] = c2;
        mCol[3] = c3;
    }

    FORCEINLINE 
    void Matrix4x4<float>::setValue(const __m128& c0, const __m128& c1, const __m128& c2, const __m128& c3)
    {
        mCol[0] = c0;
        mCol[1] = c1;
        mCol[2] = c2;
        mCol[3] = c3;
    }
        
    FORCEINLINE 
    void Matrix4x4<float>::setBasis(const Matrix3x3<float>& a)
    {
        setRow(0, a[0]);
        setRow(1, a[1]);
        setRow(2, a[2]);
    }

    
    FORCEINLINE 
    void Matrix4x4<float>::setOrigin(const Vector3<float>& p)
    {
        setColumn(3, p);
    }

    
    FORCEINLINE 
    void Matrix4x4<float>::setColumn(int i, const Vector3<float>& v)
    {
        mCol[i] = Vector4<float>(v, mCol[i].w);
    }

    
    FORCEINLINE 
    void Matrix4x4<float>::setColumn(int i, const Vector4<float>& v)
    {
        mCol[i] = v;
    }

    
    FORCEINLINE 
    void Matrix4x4<float>::setRow(int i, const Vector3<float>& v)
    {
        mCol[0][i] = v[0]; mCol[1][i] = v[1]; mCol[2][i] = v[2];
    }

    
    FORCEINLINE 
    void Matrix4x4<float>::setRow(int i, const Vector4<float>& v)
    {
        mCol[0][i] = v[0]; mCol[1][i] = v[1]; mCol[2][i] = v[2]; mCol[3][i] = v[3];
    }

          
  

    
    FORCEINLINE 
    Vector4<float> mul(const Vector4<float>& v, const Matrix4x4<float>& a)
    {
        __m128 tmp0 = _mm_mul_ps(v.vec, a[0].vec);
        __m128 tmp1 = _mm_mul_ps(v.vec, a[1].vec);
        __m128 tmp2 = _mm_mul_ps(v.vec, a[2].vec);
        __m128 tmp3 = _mm_mul_ps(v.vec, a[3].vec);

        transpose(tmp0, tmp1, tmp2, tmp3);

        return Vector4<float>(_mm_add_ps(_mm_add_ps(_mm_add_ps(tmp0, tmp1), tmp2), tmp3));
    }

    
    FORCEINLINE 
    Vector4<float> mul(const Matrix4x4<float>& a, const Vector4<float>& v)
    {
        __m128 result = _mm_mul_ps(a[0].vec, MT_SPLAT(v.vec, 0));
        result = _mm_add_ps(result, _mm_mul_ps(a[1].vec, MT_SPLAT(v.vec, 1)));
        result = _mm_add_ps(result, _mm_mul_ps(a[2].vec, MT_SPLAT(v.vec, 2)));
        result = _mm_add_ps(result, _mm_mul_ps(a[3].vec, MT_SPLAT(v.vec, 3)));

        return Vector4<float>(result);
    }
    
    FORCEINLINE 
    Matrix4x4<float> transpose(const Matrix4x4<float>& a)
    {
        __m128 tmp0 = a[0].vec;
        __m128 tmp1 = a[1].vec;
        __m128 tmp2 = a[2].vec;
        __m128 tmp3 = a[3].vec;

        transpose(tmp0, tmp1, tmp2, tmp3);
        
        return Matrix4x4<float>(tmp0, tmp1, tmp2, tmp3);
    }
}
