/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
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
        Matrix4x4(Zero);
        Matrix4x4(Identity);
        Matrix4x4(float s);
        template<typename Scalar2> explicit Matrix4x4(const Scalar2* v);   
        Matrix4x4(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3);
        Matrix4x4(const Vector4<float>& r0, const Vector4<float>& r1, const Vector4<float>& r2, const Vector4<float>& r3);
        Matrix4x4(const __m128& r0, const __m128& r1, const __m128& r2, const __m128& r3);
        explicit Matrix4x4(const Vector3<float>& p);
        explicit Matrix4x4(const Matrix3x3<float>& a, const Vector3<float>& p = Zero());
        explicit Matrix4x4(const Matrix3x4<float>& a);
        
        operator const Vector4<float>*() const; 
        operator Vector4<float>*();

        Matrix4x4<float>& operator=(Zero);
        Matrix4x4<float>& operator+=(Zero);
        Matrix4x4<float>& operator-=(Zero);
        Matrix4x4<float>& operator*=(Zero);

        Matrix4x4<float>& operator=(Identity);

        Matrix4x4<float>& operator=(float s);
        Matrix4x4<float>& operator*=(float s);
        Matrix4x4<float>& operator/=(float s);
        
        Matrix4x4<float>& operator+=(const Matrix4x4<float>& a);
        Matrix4x4<float>& operator-=(const Matrix4x4<float>& a);

#if USE_MATRIX_COMP_MULT
        Matrix4x4<float>& operator*=(const Matrix4x4<float>& a);
#endif
  
        template <typename Scalar2> void setValue(const Scalar2* v);  
        void setColumns(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3);
        void setColumns(const Vector4<float>& c0, const Vector4<float>& c1, const Vector4<float>& c2, const Vector4<float>& c3);
        void setRows(const Vector4<float>& r0, const Vector4<float>& r1, const Vector4<float>& r2, const Vector4<float>& r3);
        void setValue(const __m128& c0, const __m128& c1, const __m128& c2, const __m128& c3);
      
        void setBasis(const Matrix3x3<float>& basis);
        void setOrigin(const Vector3<float>& origin);

        void setColumn(int j, const Vector3<float>& v);
        void setColumn(int j, const Vector4<float>& v);

        void setRow(int i, const Vector3<float>& v);
        void setRow(int i, const Vector4<float>& v);

    private:
        Vector4<float> mRow[4];
    };

    Vector4<float> mul(const Matrix4x4<float>& a, const Vector4<float>& v);
    Vector4<float> mul(const Vector4<float>& v, const Matrix4x4<float>& a);

    Matrix4x4<float> transpose(const Matrix4x4<float>& a);


    
    
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4() 
    {}

    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(Zero)
    {
        *this = Zero();
    }
    
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(Identity)
    {
        *this = Identity();
    }

    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(float s)
    {
        *this = s;
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
        setColumns(c0, c1, c2, c3);
    }
   
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Vector4<float>& r0, const Vector4<float>& r1, const Vector4<float>& r2, const Vector4<float>& r3)
    {
        setRows(r0, r1, r2, r3);
    }

    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const __m128& r0, const __m128& r1, const __m128& r2, const __m128& r3)
    {
        setValue(r0, r1, r2, r3);
    }

    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Vector3<float>& p)
    {
        mRow[0] = Vector4<float>(Vector3<float>(Unit<0>()), p.x);
        mRow[1] = Vector4<float>(Vector3<float>(Unit<1>()), p.y);
        mRow[2] = Vector4<float>(Vector3<float>(Unit<2>()), p.z);
        mRow[3] = Unit<3>();
    }

    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Matrix3x3<float>& a, const Vector3<float>& p)
    {
        mRow[0] = Vector4<float>(a[0], p.x);
        mRow[1] = Vector4<float>(a[1], p.y);
        mRow[2] = Vector4<float>(a[2], p.z);
        mRow[3] = Unit<3>();
    }
        
    FORCEINLINE 
    Matrix4x4<float>::Matrix4x4(const Matrix3x4<float>& a)
    {
        mRow[0] = a[0];
        mRow[1] = a[1];
        mRow[2] = a[2];
        mRow[3] = Unit<3>();
    }
        
    FORCEINLINE
    Matrix4x4<float>::operator const Vector4<float>*() const
    {
        return mRow;
    } 

    FORCEINLINE
    Matrix4x4<float>::operator Vector4<float>*()
    {
        return mRow;
    } 
    
    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator=(Zero)
    {
        mRow[0] = Zero();
        mRow[1] = Zero();
        mRow[2] = Zero();   
        mRow[3] = Zero();
        return *this;
    }
     
    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator+=(Zero)
    {
        return *this;
    }

    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator-=(Zero)
    {
        return *this;
    }

    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator*=(Zero)
    {
        return *this = Zero();
    }

    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator=(Identity)
    {
        mRow[0] = Unit<0>();
        mRow[1] = Unit<1>();
        mRow[2] = Unit<2>();
        mRow[3] = Unit<3>();
        return *this;
    }

    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator=(float s)
    {
        mRow[0] = Vector4<float>(s, 0.0f, 0.0f, 0.0f);
        mRow[1] = Vector4<float>(0.0f, s, 0.0f, 0.0f);
        mRow[2] = Vector4<float>(0.0f, 0.0f, s, 0.0f);
        mRow[3] = Vector4<float>(0.0f, 0.0f, 0.0f, s);
        return *this;
    }

    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator*=(float s)
    {
        mRow[0] *= s; 
        mRow[1] *= s; 
        mRow[2] *= s;
        mRow[3] *= s;
        return *this;
    }

    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator/=(float s)
    {
        ASSERT(!iszero(s));
        return *this *= 1.0f / s;
    }

    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator+=(const Matrix4x4<float>& a)
    {
        mRow[0] += a[0]; 
        mRow[1] += a[1]; 
        mRow[2] += a[2];
        mRow[3] += a[3];
        return *this;
    }

    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator-=(const Matrix4x4<float>& a)
    {
        mRow[0] -= a[0]; 
        mRow[1] -= a[1]; 
        mRow[2] -= a[2];
        mRow[3] -= a[3];
        return *this;
    }

#if USE_MATRIX_COMP_MULT
    FORCEINLINE 
    Matrix4x4<float>& Matrix4x4<float>::operator*=(const Matrix4x4<float>& a)
    {
        mRow[0] *= a[0]; 
        mRow[1] *= a[1]; 
        mRow[2] *= a[2];
        mRow[3] *= a[3];
        return *this;
    }
#endif

    template <typename Scalar2>
    FORCEINLINE
    void Matrix4x4<float>::setValue(const Scalar2* v)
    {
        mRow[0] = Vector4<float>(float(v[0]), float(v[4]), float(v[8]), float(v[12])); 
        mRow[1] = Vector4<float>(float(v[1]), float(v[5]), float(v[9]), float(v[13])); 
        mRow[2] = Vector4<float>(float(v[2]), float(v[6]), float(v[10]), float(v[14])); 
        mRow[3] = Vector4<float>(float(v[3]), float(v[7]), float(v[11]), float(v[15])); 
    }  

    
    FORCEINLINE 
    void Matrix4x4<float>::setColumns(const Vector3<float>& c0, const Vector3<float>& c1, const Vector3<float>& c2, const Vector3<float>& c3)
    {
        mRow[0] = Vector4<float>(c0.x, c1.x, c2.x, c3.x);
        mRow[1] = Vector4<float>(c0.y, c1.y, c2.y, c3.y);
        mRow[2] = Vector4<float>(c0.z, c1.z, c2.z, c3.z);
        mRow[3] = Unit<3>();
    }
   
    
    FORCEINLINE 
    void Matrix4x4<float>::setColumns(const Vector4<float>& c0, const Vector4<float>& c1, const Vector4<float>& c2, const Vector4<float>& c3)
    {
        mRow[0] = Vector4<float>(c0.x, c1.x, c2.x, c3.x);
        mRow[1] = Vector4<float>(c0.y, c1.y, c2.y, c3.y);
        mRow[2] = Vector4<float>(c0.z, c1.z, c2.z, c3.z);
        mRow[3] = Vector4<float>(c0.w, c1.w, c2.w, c3.w);
    }

    FORCEINLINE 
    void Matrix4x4<float>::setRows(const Vector4<float>& r0, const Vector4<float>& r1, const Vector4<float>& r2, const Vector4<float>& r3)
    {
        mRow[0] = r0;
        mRow[1] = r1;
        mRow[2] = r2;
        mRow[3] = r3;
    }

    FORCEINLINE 
    void Matrix4x4<float>::setValue(const __m128& r0, const __m128& r1, const __m128& r2, const __m128& r3)
    {
        mRow[0] = r0;
        mRow[1] = r1;
        mRow[2] = r2;
        mRow[3] = r3;
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
    void Matrix4x4<float>::setColumn(int j, const Vector3<float>& v)
    {
        mRow[0][j] = v.x;
        mRow[1][j] = v.y;
        mRow[2][j] = v.z;
    }

    
    FORCEINLINE 
    void Matrix4x4<float>::setColumn(int j, const Vector4<float>& v)
    {
        mRow[0][j] = v.x;
        mRow[1][j] = v.y;
        mRow[2][j] = v.z;
        mRow[3][j] = v.w;
    }

    
    FORCEINLINE 
    void Matrix4x4<float>::setRow(int i, const Vector3<float>& v)
    {
        mRow[i] = Vector4<float>(v, mRow[i].w);
    }

    
    FORCEINLINE 
    void Matrix4x4<float>::setRow(int i, const Vector4<float>& v)
    {
        mRow[i] = v;
    }

          
  

    
    FORCEINLINE 
    Vector4<float> mul(const Matrix4x4<float>& a, const Vector4<float>& v)
    {
        __m128 tmp0 = _mm_mul_ps(a[0].vec, v.vec);
        __m128 tmp1 = _mm_mul_ps(a[1].vec, v.vec);
        __m128 tmp2 = _mm_mul_ps(a[2].vec, v.vec);
        __m128 tmp3 = _mm_mul_ps(a[3].vec, v.vec);

        transpose(tmp0, tmp1, tmp2, tmp3);

        return Vector4<float>(_mm_add_ps(_mm_add_ps(_mm_add_ps(tmp0, tmp1), tmp2), tmp3));
    }

    
    FORCEINLINE 
    Vector4<float> mul(const Vector4<float>& v, const Matrix4x4<float>& a)
    {
        __m128 result = _mm_mul_ps(MT_SPLAT(v.vec, 0), a[0].vec);
        result = _mm_add_ps(result, _mm_mul_ps(MT_SPLAT(v.vec, 1), a[1].vec));
        result = _mm_add_ps(result, _mm_mul_ps(MT_SPLAT(v.vec, 2), a[2].vec));
        result = _mm_add_ps(result, _mm_mul_ps(MT_SPLAT(v.vec, 3), a[3].vec));

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
