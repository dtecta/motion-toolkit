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

#ifndef MT_MATRIX3X4_HPP
#error This header file should be included by Matrix3x4.hpp only.
#endif


namespace mt
{ 
    template <>
    class Matrix3x4<float>
    {
    public:
        typedef float ScalarType;

        Matrix3x4();
        Matrix3x4(Identity);
        template<typename Scalar2> explicit Matrix3x4(const Scalar2* v);   
        Matrix3x4(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3);
        Matrix3x4(const Vector4<float>& r0, const Vector4<float>& r1, const Vector4<float>& r2);
        Matrix3x4(const __m128& r0, const __m128& r1, const __m128& r2);
        explicit Matrix3x4(const Vector3<float>& p);
        explicit Matrix3x4(const Matrix3x3<float>& a, const Vector3<float>& p = Zero());
        
        operator const Vector4<float>*() const; 
        operator Vector4<float>*();

        Matrix3x4<float>& operator=(Identity);
  
        template <typename Scalar2> void setValue(const Scalar2* v);  
        void setColumns(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3);
        void setRows(const Vector4<float>& r0, const Vector4<float>& r1, const Vector4<float>& r2);
        void setValue(const __m128& r0, const __m128& r1, const __m128& r2);
      
        void setBasis(const Matrix3x3<float>& basis);
        void setOrigin(const Vector3<float>& origin);

        void setColumn(int j, const Vector3<float>& v);

        void setRow(int i, const Vector3<float>& v);
        void setRow(int i, const Vector4<float>& v);

    private:
        Vector4<float> mRow[3];
    };

    Vector4<float> mul(const Matrix3x4<float>& a, const Vector4<float>& v);
    Vector4<float> mul(const Vector4<float>& v, const Matrix3x4<float>& a);
    
    
    FORCEINLINE 
    Matrix3x4<float>::Matrix3x4() 
    {} 
    
    
    FORCEINLINE 
    Matrix3x4<float>::Matrix3x4(Identity)
    {
        *this = Identity();
    }

    template <typename Scalar2>
    FORCEINLINE 
    Matrix3x4<float>::Matrix3x4(const Scalar2* v) 
    {
        setValue(v);
    }

    
    FORCEINLINE 
    Matrix3x4<float>::Matrix3x4(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3)
    {
        setColumns(c0, c1, c2, c3);
    }
   

    
    FORCEINLINE 
    Matrix3x4<float>::Matrix3x4(const Vector4<float>& r0, const Vector4<float>& r1, const Vector4<float>& r2)
    {
        setRows(r0, r1, r2);
    }

    FORCEINLINE 
    Matrix3x4<float>::Matrix3x4(const __m128& r0, const __m128& r1, const __m128& r2)
    {
        setValue(r0, r1, r2);
    }

    
    FORCEINLINE 
    Matrix3x4<float>::Matrix3x4(const Vector3<float>& p)
    {
        mRow[0] = Vector4<float>(Vector3<float>(Unit<0>()), p.x);
        mRow[1] = Vector4<float>(Vector3<float>(Unit<1>()), p.y);
        mRow[2] = Vector4<float>(Vector3<float>(Unit<2>()), p.z);
    }

    
    FORCEINLINE 
    Matrix3x4<float>::Matrix3x4(const Matrix3x3<float>& a, const Vector3<float>& p)
    {
        mRow[0] = Vector4<float>(a[0], p.x);
        mRow[1] = Vector4<float>(a[1], p.y);
        mRow[2] = Vector4<float>(a[2], p.z);
    }
        
    FORCEINLINE
    Matrix3x4<float>::operator const Vector4<float>*() const
    {
        return mRow;
    } 

    FORCEINLINE
    Matrix3x4<float>::operator Vector4<float>*()
    {
        return mRow;
    } 
    
    FORCEINLINE 
    Matrix3x4<float>& Matrix3x4<float>::operator=(Identity)
    {   
        mRow[0] = Unit<0>();
        mRow[1] = Unit<1>();
        mRow[2] = Unit<2>();
        return *this;
    }

    template <typename Scalar2>
    FORCEINLINE
    void Matrix3x4<float>::setValue(const Scalar2* v)
    {
		mRow[0] = Vector4<float>(float(v[0]), float(v[4]), float(v[8]), float(v[12])); 
		mRow[1] = Vector4<float>(float(v[1]), float(v[5]), float(v[9]), float(v[13])); 
        mRow[2] = Vector4<float>(float(v[2]), float(v[6]), float(v[10]), float(v[14])); 
    }  

    FORCEINLINE 
    void Matrix3x4<float>::setColumns(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3)
    {
		mRow[0] = Vector4<float>(c0.x, c1.x, c2.x, c3.x);
        mRow[1] = Vector4<float>(c0.y, c1.y, c2.y, c3.y);
        mRow[2] = Vector4<float>(c0.z, c1.z, c2.z, c3.z);
    }

    FORCEINLINE 
    void Matrix3x4<float>::setRows(const Vector4<float>& r0, const Vector4<float>& r1, const Vector4<float>& r2)
    {
        mRow[0] = r0;
        mRow[1] = r1;
        mRow[2] = r2;
    }

	FORCEINLINE 
    void Matrix3x4<float>::setValue(const __m128& r0, const __m128& r1, const __m128& r2)
    {
        mRow[0] = r0;
        mRow[1] = r1;
        mRow[2] = r2;
    }

   
    FORCEINLINE 
    void Matrix3x4<float>::setBasis(const Matrix3x3<float>& a)
    {
        setRow(0, a[0]);
        setRow(1, a[1]);
        setRow(2, a[2]);
    }

    
    FORCEINLINE 
    void Matrix3x4<float>::setOrigin(const Vector3<float>& p)
    {
        setColumn(3, p);
    }

   
    
    FORCEINLINE 
    void Matrix3x4<float>::setColumn(int j, const Vector3<float>& v)
    {
		mRow[0][j] = v.x;
        mRow[1][j] = v.y;
        mRow[2][j] = v.z;
    }

    
    FORCEINLINE 
    void Matrix3x4<float>::setRow(int i, const Vector3<float>& v)
    {
        mRow[i] = Vector4<float>(v, mRow[i].w);
    }

    
    FORCEINLINE 
    void Matrix3x4<float>::setRow(int i, const Vector4<float>& v)
    {
        mRow[i] = v;
    }

          
  


	FORCEINLINE 
    Vector4<float> mul(const Matrix3x4<float>& a, const Vector4<float>& v)
    {
        __m128 tmp0 = _mm_mul_ps(a[0].vec, v.vec);
        __m128 tmp1 = _mm_mul_ps(a[1].vec, v.vec);
        __m128 tmp2 = _mm_mul_ps(a[2].vec, v.vec);
        __m128 tmp3 = _mm_setr_ps(float(), float(), float(), v.w);

        transpose(tmp0, tmp1, tmp2, tmp3);

        return Vector4<float>(_mm_add_ps(_mm_add_ps(_mm_add_ps(tmp0, tmp1), tmp2), tmp3));
    }


	FORCEINLINE 
    Vector4<float> mul(const Vector4<float>& v, const Matrix3x4<float>& a)
    {
        __m128 result = _mm_mul_ps(MT_SPLAT(v.vec, 0), a[0].vec);
        result = _mm_add_ps(result, _mm_mul_ps(MT_SPLAT(v.vec, 1), a[1].vec));
		result = _mm_add_ps(result, _mm_mul_ps(MT_SPLAT(v.vec, 2), a[2].vec));
		result = _mm_add_ps(result, _mm_setr_ps(float(), float(), float(), v.w));
        return Vector4<float>(result);
    }
}
