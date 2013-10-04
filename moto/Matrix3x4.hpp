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
#define MT_MATRIX3X4_HPP

#include <moto/Matrix3x3.hpp>
#include <moto/Vector4.hpp>
#include <moto/Algebra.hpp>

namespace mt
{      
    template <typename Scalar>
    class Matrix3x4
    {
    public:
        typedef Scalar ScalarType;

        Matrix3x4();
        Matrix3x4(Identity);
        template <typename Scalar2> explicit Matrix3x4(const Scalar2* v);   
        Matrix3x4(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3);
		Matrix3x4(const Vector4<Scalar>& r0, const Vector4<Scalar>& r1, const Vector4<Scalar>& r2);
        explicit Matrix3x4(const Vector3<Scalar>& p);
        explicit Matrix3x4(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& p = Zero());
        
        operator const Vector4<Scalar>*() const; 
        operator Vector4<Scalar>*();
        
        Matrix3x4<Scalar>& operator=(Identity);

        template <typename Scalar2> void setValue(const Scalar2* v);  
        void setColumns(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3);
        void setRows(const Vector4<Scalar>& r0, const Vector4<Scalar>& r1, const Vector4<Scalar>& r2);

        void setBasis(const Matrix3x3<Scalar>& basis);
        void setOrigin(const Vector3<Scalar>& origin);

        void setColumn(int j, const Vector3<Scalar>& v);

        void setRow(int i, const Vector3<Scalar>& v);
        void setRow(int i, const Vector4<Scalar>& v);

    private:
        Vector4<Scalar> mRow[3];
    }; 

    template <typename Scalar> bool operator==(const Matrix3x4<Scalar>& a, const Matrix3x4<Scalar>& b);
 
    template <typename Scalar> const Vector4<Scalar>& row(const Matrix3x4<Scalar>& a, int i);
    template <typename Scalar> Vector3<Scalar> column(const Matrix3x4<Scalar>& a, int j);
    template <typename Scalar> Matrix3x3<Scalar> basis(const Matrix3x4<Scalar>& a);
    template <typename Scalar> Vector3<Scalar> origin(const Matrix3x4<Scalar>& a); 


#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix3x4<Scalar>& a);
     
#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix3x4<Scalar>& a);

#endif
   
    template <typename Scalar> Vector4<Scalar> mul(const Matrix3x4<Scalar>& a, const Vector4<Scalar>& v);
	template <typename Scalar> Vector4<Scalar> mul(const Vector4<Scalar>& v, const Matrix3x4<Scalar>& a);

    template <typename Scalar> Matrix3x4<Scalar> mul(const Matrix3x4<Scalar>& a, const Matrix3x4<Scalar>& b);

    template <typename Scalar> Matrix3x4<Scalar> inverse(const Matrix3x4<Scalar>& a);
    template <typename Scalar> Matrix3x4<Scalar> inverseOrthogonal(const Matrix3x4<Scalar>& a);  
    
    template <typename Scalar1, typename Scalar2> void convert(Scalar1* v, const Matrix3x4<Scalar2>& a);


    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar>::Matrix3x4() 
    {} 
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar>::Matrix3x4(Identity)
    {
        *this = Identity();
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Matrix3x4<Scalar>::Matrix3x4(const Scalar2* v) 
    {
        setValue(v);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar>::Matrix3x4(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3)
    {
        setColumns(c0, c1, c2, c3);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar>::Matrix3x4(const Vector4<Scalar>& r0, const Vector4<Scalar>& r1, const Vector4<Scalar>& r2)
    {
        setRows(r0, r1, r2);
    }
   
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar>::Matrix3x4(const Vector3<Scalar>& p)
    {
        mRow[0] = Vector4<Scalar>(Vector3<Scalar>(Unit<0>()), p.x);
        mRow[1] = Vector4<Scalar>(Vector3<Scalar>(Unit<1>()), p.y);
        mRow[2] = Vector4<Scalar>(Vector3<Scalar>(Unit<2>()), p.z);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar>::Matrix3x4(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& p)
    {
        mRow[0] = Vector4<Scalar>(a[0], p.x);
        mRow[1] = Vector4<Scalar>(a[1], p.y);
        mRow[2] = Vector4<Scalar>(a[2], p.z);
    }
    
    template <typename Scalar>
    FORCEINLINE
    Matrix3x4<Scalar>::operator const Vector4<Scalar>*() const
    {
        return mRow;
    } 

    template <typename Scalar>
    FORCEINLINE
    Matrix3x4<Scalar>::operator Vector4<Scalar>*()
    {
        return mRow;
    } 
   
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar>& Matrix3x4<Scalar>::operator=(Identity)
    {
        mRow[0] = Unit<0>();
        mRow[1] = Unit<1>();
        mRow[2] = Unit<2>();
        return *this;
    }

  
    template <typename Scalar>
    template <typename Scalar2> 
    FORCEINLINE
    void Matrix3x4<Scalar>::setValue(const Scalar2* v)
    {
		mRow[0] = Vector4<Scalar>(Scalar(v[0]), Scalar(v[4]), Scalar(v[8]), Scalar(v[12])); 
        mRow[1] = Vector4<Scalar>(Scalar(v[1]), Scalar(v[5]), Scalar(v[9]), Scalar(v[13])); 
        mRow[2] = Vector4<Scalar>(Scalar(v[2]), Scalar(v[6]), Scalar(v[10]), Scalar(v[14])); 
    }  

    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x4<Scalar>::setColumns(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3)
    {
        mRow[0] = Vector4<Scalar>(c0.x, c1.x, c2.x, c3.x);
        mRow[1] = Vector4<Scalar>(c0.y, c1.y, c2.y, c3.y);
        mRow[2] = Vector4<Scalar>(c0.z, c1.z, c2.z, c3.z);
    }

	template <typename Scalar>
    FORCEINLINE 
    void Matrix3x4<Scalar>::setRows(const Vector4<Scalar>& r0, const Vector4<Scalar>& r1, const Vector4<Scalar>& r2)
    {
        mRow[0] = r0;
        mRow[1] = r1;
        mRow[2] = r2;
    }

    
    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x4<Scalar>::setBasis(const Matrix3x3<Scalar>& a)
    {
        setRow(0, a[0]);
        setRow(1, a[1]);
        setRow(2, a[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x4<Scalar>::setOrigin(const Vector3<Scalar>& p)
    {
        setColumn(3, p);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x4<Scalar>::setColumn(int j, const Vector3<Scalar>& v)
    {
        mRow[0][j] = v.x;
        mRow[1][j] = v.y;
        mRow[2][j] = v.z;
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x4<Scalar>::setRow(int i, const Vector3<Scalar>& v)
    {
        mRow[i] = Vector4<Scalar>(v, mRow[i].w);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x4<Scalar>::setRow(int i, const Vector4<Scalar>& v)
    {
        mRow[i] = v;
    }

    template <typename Scalar> 
    FORCEINLINE
    bool operator==(const Matrix3x4<Scalar>& a, const Matrix3x4<Scalar>& b)
    {
        return all(a[0] == b[0]) && 
               all(a[1] == b[1]) && 
			   all(a[2] == b[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    const Vector4<Scalar>& row(const Matrix3x4<Scalar>& a, int i)
    {
        return a[i];
    }  
    
    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> column(const Matrix3x4<Scalar>& a, int j)
    {
        return Vector3<Scalar>(a[0][j], a[1][j], a[2][j]);
    }  
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> basis(const Matrix3x4<Scalar>& a)
    {
        return Matrix3x3<Scalar>(a[0][0], a[0][1], a[0][2],
								 a[1][0], a[1][1], a[1][2],
								 a[2][0], a[2][1], a[2][2]); 
    }
     
    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> origin(const Matrix3x4<Scalar>& a)
    {
        return Vector3<Scalar>(a[0][3], 
                               a[1][3], 
                               a[2][3]);
    }  
  


#ifdef USE_OSTREAM
     
    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix3x4<Scalar>& a)
    {
        return os << ' ' << row(a, 0) << ' ' << row(a, 1) << ' ' << row(a, 2);
    }

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix3x4<Scalar>& a)
    {
        is >> a[0] >> a[1] >> a[2];
        return is;
    }

#endif


    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> mul(const Matrix3x4<Scalar>& a, const Vector4<Scalar>& v)
    {
        return Vector4<Scalar>(dot(a[0], v), 
                               dot(a[1], v), 
                               dot(a[2], v),
			                   v.w);
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> mul(const Vector4<Scalar>& v, const Matrix3x4<Scalar>& a)
    {
        return v.x * a[0] + v.y * a[1] + v.z * a[2] + Vector4<Scalar>(v.w);
    }

	template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar> mul(const Matrix3x4<Scalar>& a, const Matrix3x4<Scalar>& b)
    {
        return Matrix3x4<Scalar>(mul(a[0], b), 
								 mul(a[1], b),
								 mul(a[2], b));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar> inverse(const Matrix3x4<Scalar>& a)
    {
        Matrix3x3<Scalar> invBasis = inverse(basis(a));

        return Matrix3x4<Scalar>(invBasis, mul(invBasis, -origin(a)));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar> inverseOrthogonal(const Matrix3x4<Scalar>& a)
    {
        Matrix3x3<Scalar> invBasis = transpose(basis(a));

        return Matrix3x4<Scalar>(invBasis, mul(invBasis, -origin(a)));
    }  

    template <typename Scalar1, typename Scalar2> 
    FORCEINLINE 
    void convert(Scalar1* v, const Matrix3x4<Scalar2>& a)
    {
		v[0] = Scalar1(a[0][0]); v[4] = Scalar1(a[0][1]); v[8] = Scalar1(a[0][2]); v[12] = Scalar1(a[0][3]); 
        v[1] = Scalar1(a[1][0]); v[5] = Scalar1(a[1][1]); v[9] = Scalar1(a[1][2]); v[13] = Scalar1(a[1][3]); 
        v[2] = Scalar1(a[2][0]); v[6] = Scalar1(a[2][1]); v[10] = Scalar1(a[2][2]); v[14] = Scalar1(a[2][3]);  
        v[3] = Scalar1(); v[7] = Scalar1(); v[11] = Scalar1(); v[15] = Scalar1(1);
    }

}

#if USE_SSE
#include <moto/Matrix3x4_SSE.hpp>
#endif



#endif
