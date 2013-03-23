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
#define MT_MATRIX4X4_HPP

#include <moto/Matrix3x3.hpp>
#include <moto/Vector4.hpp>
#include <moto/Algebra.hpp>

namespace mt
{      
    template <typename Scalar>
    class Matrix4x4
    {
    public:
        typedef Scalar ScalarType;

        Matrix4x4();
        Matrix4x4(Identity);
        template <typename Scalar2> explicit Matrix4x4(const Scalar2* v);   
        Matrix4x4(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3);
        Matrix4x4(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2, const Vector4<Scalar>& c3);
        explicit Matrix4x4(const Vector3<Scalar>& p);
        explicit Matrix4x4(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& p = Zero());
        
        operator const Vector4<Scalar>*() const; 
        operator Vector4<Scalar>*();
        
        Matrix4x4<Scalar>& operator=(Identity);

        template <typename Scalar2> void setValue(const Scalar2* v);  
        void setValue(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3);
        void setValue(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2, const Vector4<Scalar>& c3);

        void setBasis(const Matrix3x3<Scalar>& basis);
        void setOrigin(const Vector3<Scalar>& origin);

        void setColumn(int i, const Vector3<Scalar>& v);
        void setColumn(int i, const Vector4<Scalar>& v);

        void setRow(int i, const Vector3<Scalar>& v);
        void setRow(int i, const Vector4<Scalar>& v);

    private:
        Vector4<Scalar> mCol[4];
    }; 

    template <typename Scalar> bool operator==(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b);
 
    template <typename Scalar> Scalar tdot(const Matrix4x4<Scalar>& a, int i, const Vector4<Scalar>& v);
    template <int I, int J, typename Scalar> Scalar cofactor(const Matrix4x4<Scalar>& a);

    template <typename Scalar> Vector4<Scalar> row(const Matrix4x4<Scalar>& a, int i);
    template <typename Scalar> Matrix3x3<Scalar> basis(const Matrix4x4<Scalar>& a);
    template <typename Scalar> const Vector3<Scalar>& origin(const Matrix4x4<Scalar>& a); 


#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix4x4<Scalar>& a);
     
#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix4x4<Scalar>& a);

#endif


    template <typename Scalar> Matrix4x4<Scalar> mul(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b);

    template <typename Scalar> Vector4<Scalar> mul(const Matrix4x4<Scalar>& a, const Vector4<Scalar>& v);
    template <typename Scalar> Vector4<Scalar> mul(const Vector4<Scalar>& v, const Matrix4x4<Scalar>& a);

    template <typename Scalar> Matrix4x4<Scalar> transpose(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> adjoint(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> inverse(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> inverseAffine(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> inverseOrthogonal(const Matrix4x4<Scalar>& a);

    
    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4() 
    {} 
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(Identity)
    {
        *this = Identity();
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Scalar2* v) 
    {
        setValue(v);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3)
    {
        setValue(c0, c1, c2, c3);
    }
   

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2, const Vector4<Scalar>& c3)
    {
        setValue(c0, c1, c2, c3);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Vector3<Scalar>& p)
    {
        mCol[0] = Unit<0>();
        mCol[1] = Unit<1>();
        mCol[2] = Unit<2>();
        mCol[3] = Vector4<Scalar>(p, Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& p)
    {
        mCol[0] = Vector4<Scalar>(a[0][0], a[1][0], a[2][0], Scalar());
        mCol[1] = Vector4<Scalar>(a[0][1], a[1][1], a[2][1], Scalar());
        mCol[2] = Vector4<Scalar>(a[0][2], a[1][2], a[2][2], Scalar());
        mCol[3] = Vector4<Scalar>(p, Scalar(1));
    }
    
    template <typename Scalar>
    FORCEINLINE
    Matrix4x4<Scalar>::operator const Vector4<Scalar>*() const
    {
        return mCol;
    } 

    template <typename Scalar>
    FORCEINLINE
    Matrix4x4<Scalar>::operator Vector4<Scalar>*()
    {
        return mCol;
    } 
   
    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator=(Identity)
    {
        mCol[0] = Unit<0>();
        mCol[1] = Unit<1>();
        mCol[2] = Unit<2>();
        mCol[3] = Unit<3>();
        return *this;
    }

  
    template <typename Scalar>
    template <typename Scalar2> 
    FORCEINLINE
    void Matrix4x4<Scalar>::setValue(const Scalar2* v)
    {
        mCol[0] = Vector4<Scalar>(&v[0]); 
        mCol[1] = Vector4<Scalar>(&v[4]); 
        mCol[2] = Vector4<Scalar>(&v[8]); 
        mCol[3] = Vector4<Scalar>(&v[12]); 
    }  

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setValue(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3)
    {
        mCol[0] = Vector4<Scalar>(c0, Scalar());
        mCol[1] = Vector4<Scalar>(c1, Scalar());
        mCol[2] = Vector4<Scalar>(c2, Scalar());
        mCol[3] = Vector4<Scalar>(c3, Scalar(1));
    }
   
    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setValue(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2, const Vector4<Scalar>& c3)
    {
        mCol[0] = c0;
        mCol[1] = c1;
        mCol[2] = c2;
        mCol[3] = c3;
    }

      
    template <typename Scalar1, typename Scalar2> 
    FORCEINLINE 
    void convert(Scalar1* v, const Matrix4x4<Scalar2>& a)
    {
        convert(&v[0], a[0]);
        convert(&v[4], a[1]);
        convert(&v[8], a[2]);
        convert(&v[12], a[3]);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setBasis(const Matrix3x3<Scalar>& a)
    {
        setRow(0, a[0]);
        setRow(1, a[1]);
        setRow(2, a[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setOrigin(const Vector3<Scalar>& p)
    {
        setColumn(3, p);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setColumn(int i, const Vector3<Scalar>& v)
    {
        mCol[i] = Vector4<Scalar>(v, mCol[i].w);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setColumn(int i, const Vector4<Scalar>& v)
    {
        mCol[i] = v;
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setRow(int i, const Vector3<Scalar>& v)
    {
        mCol[0][i] = v[0]; mCol[1][i] = v[1]; mCol[2][i] = v[2];
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setRow(int i, const Vector4<Scalar>& v)
    {
        mCol[0][i] = v[0]; mCol[1][i] = v[1]; mCol[2][i] = v[2]; mCol[3][i] = v[3];
    }

    template <typename Scalar> 
    FORCEINLINE
    bool operator==(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b)
    {
        return all(a[0] == b[0]) && 
               all(a[1] == b[1]) && 
			   all(a[2] == b[2]) && 
			   all(a[3] == b[3]);
    }

  

    template <typename Scalar>
    FORCEINLINE 
    Scalar tdot(const Matrix4x4<Scalar>& a, int i, const Vector4<Scalar>& v)
    {
        return a[0][i] * v[0] + a[1][i] * v[1] + a[2][i] * v[2] + a[3][i] * v[3];
    }

    template <int I, int J, typename Scalar>
    FORCEINLINE 
    Scalar cofactor(const Matrix4x4<Scalar>& a)
    {
        return a[(I + 1) & 3][(J + 1) & 3] * (a[(I + 2) & 3][(J + 2) & 3] * a[(I + 3) & 3][(J + 3) & 3] - a[(I + 3) & 3][(J + 2) & 3] * a[(I + 2) & 3][(J + 3) & 3]) + 
               a[(I + 2) & 3][(J + 1) & 3] * (a[(I + 3) & 3][(J + 2) & 3] * a[(I + 1) & 3][(J + 3) & 3] - a[(I + 1) & 3][(J + 2) & 3] * a[(I + 3) & 3][(J + 3) & 3]) + 
               a[(I + 3) & 3][(J + 1) & 3] * (a[(I + 1) & 3][(J + 2) & 3] * a[(I + 2) & 3][(J + 3) & 3] - a[(I + 2) & 3][(J + 2) & 3] * a[(I + 1) & 3][(J + 3) & 3]);
    }  

    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> row(const Matrix4x4<Scalar>& a, int i)
    {
        return Vector4<Scalar>(a[0][i], a[1][i], a[2][i], a[3][i]);
    }  
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> basis(const Matrix4x4<Scalar>& a)
    {
        return Matrix3x3<Scalar>(xyz(a[0]), xyz(a[1]), xyz(a[2]));
    }
     
    template <typename Scalar>
    FORCEINLINE 
    const Vector3<Scalar>& origin(const Matrix4x4<Scalar>& a)
    {
        return xyz(a[3]);
    }  
  


#ifdef USE_OSTREAM
     
    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix4x4<Scalar>& a)
    {
        return os << ' ' << row(a, 0) << ' ' << row(a, 1) << ' ' << row(a, 2) << ' ' << row(a, 3);
    }

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix4x4<Scalar>& a)
    {
        is >> a[0] >> a[1] >> a[2] >> a[3];
        a = transpose(a);
        return is;
    }

#endif


    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> mul(const Vector4<Scalar>& v, const Matrix4x4<Scalar>& a)
    {
        return Vector4<Scalar>(dot(v, a[0]), 
                               dot(v, a[1]), 
                               dot(v, a[2]),
                               dot(v, a[3]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> mul(const Matrix4x4<Scalar>& a, const Vector4<Scalar>& v)
    {
        return Vector4<Scalar>(tdot(a, 0, v), 
                               tdot(a, 1, v), 
                               tdot(a, 2, v), 
                               tdot(a, 3, v));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> mul(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b)
    {
        return Matrix4x4<Scalar>(mul(a, b[0]), mul(a, b[1]), mul(a, b[2]), mul(a, b[3]));
    }



    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> transpose(const Matrix4x4<Scalar>& a)
    {
        return Matrix4x4<Scalar>(row(a, 0), row(a, 1), row(a, 2), row(a, 3));
    } 

    template <typename Scalar>
    FORCEINLINE
    Matrix4x4<Scalar> adjoint(const Matrix4x4<Scalar>& a)
    {
        Scalar tmp[12]; /* temp array for pairs */
     
        Matrix4x4<Scalar> dst;
        
        /* calculate pairs for first 8 elements (cofactors) */
        tmp[0] = a[2][2] * a[3][3];
        tmp[1] = a[3][2] * a[2][3];
        tmp[2] = a[1][2] * a[3][3];
        tmp[3] = a[3][2] * a[1][3];
        tmp[4] = a[1][2] * a[2][3];
        tmp[5] = a[2][2] * a[1][3];
        tmp[6] = a[0][2] * a[3][3];
        tmp[7] = a[3][2] * a[0][3];
        tmp[8] = a[0][2] * a[2][3];
        tmp[9] = a[2][2] * a[0][3];
        tmp[10] = a[0][2] * a[1][3];
        tmp[11] = a[1][2] * a[0][3];

        /* calculate first 8 elements (cofactors) */
        dst[0][0] = (tmp[0] - tmp[1]) * a[1][1] + (tmp[3] - tmp[2]) * a[2][1] + (tmp[4] - tmp[5]) * a[3][1];
        dst[0][1] = (tmp[1] - tmp[0]) * a[0][1] + (tmp[6] - tmp[7]) * a[2][1] + (tmp[9] - tmp[8]) * a[3][1];
        dst[0][2] = (tmp[2] - tmp[3]) * a[0][1] + (tmp[7] - tmp[6]) * a[1][1] + (tmp[10] - tmp[11]) * a[3][1];
        dst[0][3] = (tmp[5] - tmp[4]) * a[0][1] + (tmp[8] - tmp[9]) * a[1][1] + (tmp[11] - tmp[10]) * a[2][1];
        dst[1][0] = (tmp[1] - tmp[0]) * a[1][0] + (tmp[2] - tmp[3]) * a[2][0] + (tmp[5] - tmp[4]) * a[3][0];
        dst[1][1] = (tmp[0] - tmp[1]) * a[0][0] + (tmp[7] - tmp[6]) * a[2][0] + (tmp[8] - tmp[9]) * a[3][0];
        dst[1][2] = (tmp[3] - tmp[2]) * a[0][0] + (tmp[6] - tmp[7]) * a[1][0] + (tmp[11] - tmp[10]) * a[3][0];
        dst[1][3] = (tmp[4] - tmp[5]) * a[0][0] + (tmp[9] - tmp[8]) * a[1][0] + (tmp[10] - tmp[11]) * a[2][0];
       
        /* calculate pairs for second 8 elements (cofactors) */
        tmp[0] = a[2][0] * a[3][1];
        tmp[1] = a[3][0] * a[2][1];
        tmp[2] = a[1][0] * a[3][1];
        tmp[3] = a[3][0] * a[1][1];
        tmp[4] = a[1][0] * a[2][1];
        tmp[5] = a[2][0] * a[1][1];
        tmp[6] = a[0][0] * a[3][1];
        tmp[7] = a[3][0] * a[0][1];
        tmp[8] = a[0][0] * a[2][1];
        tmp[9] = a[2][0] * a[0][1];
        tmp[10] = a[0][0] * a[1][1];
        tmp[11] = a[1][0] * a[0][1];

        /* calculate second 8 elements (cofactors) */
        dst[2][0] = (tmp[0] - tmp[1]) * a[1][3] + (tmp[3] - tmp[2]) * a[2][3] + (tmp[4] - tmp[5]) * a[3][3];
        dst[2][1] = (tmp[1] - tmp[0]) * a[0][3] + (tmp[6] - tmp[7]) * a[2][3] + (tmp[9] - tmp[8]) * a[3][3];
        dst[2][2] = (tmp[2] - tmp[3]) * a[0][3] + (tmp[7] - tmp[6]) * a[1][3] + (tmp[10] - tmp[11]) * a[3][3];
        dst[2][3] = (tmp[5] - tmp[4]) * a[0][3] + (tmp[8] - tmp[9]) * a[1][3] + (tmp[11] - tmp[10]) * a[2][3];
        dst[3][0] = (tmp[2] - tmp[3]) * a[2][2] + (tmp[5] - tmp[4]) * a[3][2] + (tmp[1] - tmp[0]) * a[1][2];
        dst[3][1] = (tmp[8] - tmp[9]) * a[3][2] + (tmp[0] - tmp[1]) * a[0][2] + (tmp[7] - tmp[6]) * a[2][2];
        dst[3][2] = (tmp[6] - tmp[7]) * a[1][2] + (tmp[11] - tmp[10]) * a[3][2] + (tmp[3] - tmp[2]) * a[0][2];
        dst[3][3] = (tmp[10] - tmp[11]) * a[2][2] + (tmp[4] - tmp[5]) * a[0][2] + (tmp[9] - tmp[8]) * a[1][2];

        return dst;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> inverse(const Matrix4x4<Scalar>& a)
    {
        Scalar tmp[12]; /* temp array for pairs */
     
        Matrix4x4<Scalar> dst;
        
        /* calculate pairs for first 8 elements (cofactors) */
        tmp[0] = a[2][2] * a[3][3];
        tmp[1] = a[3][2] * a[2][3];
        tmp[2] = a[1][2] * a[3][3];
        tmp[3] = a[3][2] * a[1][3];
        tmp[4] = a[1][2] * a[2][3];
        tmp[5] = a[2][2] * a[1][3];
        tmp[6] = a[0][2] * a[3][3];
        tmp[7] = a[3][2] * a[0][3];
        tmp[8] = a[0][2] * a[2][3];
        tmp[9] = a[2][2] * a[0][3];
        tmp[10] = a[0][2] * a[1][3];
        tmp[11] = a[1][2] * a[0][3];

        /* calculate first 8 elements (cofactors) */
        dst[0][0] = (tmp[0] - tmp[1]) * a[1][1] + (tmp[3] - tmp[2]) * a[2][1] + (tmp[4] - tmp[5]) * a[3][1];
        dst[0][1] = (tmp[1] - tmp[0]) * a[0][1] + (tmp[6] - tmp[7]) * a[2][1] + (tmp[9] - tmp[8]) * a[3][1];
        dst[0][2] = (tmp[2] - tmp[3]) * a[0][1] + (tmp[7] - tmp[6]) * a[1][1] + (tmp[10] - tmp[11]) * a[3][1];
        dst[0][3] = (tmp[5] - tmp[4]) * a[0][1] + (tmp[8] - tmp[9]) * a[1][1] + (tmp[11] - tmp[10]) * a[2][1];
        dst[1][0] = (tmp[1] - tmp[0]) * a[1][0] + (tmp[2] - tmp[3]) * a[2][0] + (tmp[5] - tmp[4]) * a[3][0];
        dst[1][1] = (tmp[0] - tmp[1]) * a[0][0] + (tmp[7] - tmp[6]) * a[2][0] + (tmp[8] - tmp[9]) * a[3][0];
        dst[1][2] = (tmp[3] - tmp[2]) * a[0][0] + (tmp[6] - tmp[7]) * a[1][0] + (tmp[11] - tmp[10]) * a[3][0];
        dst[1][3] = (tmp[4] - tmp[5]) * a[0][0] + (tmp[9] - tmp[8]) * a[1][0] + (tmp[10] - tmp[11]) * a[2][0];
       
        /* calculate pairs for second 8 elements (cofactors) */
        tmp[0] = a[2][0] * a[3][1];
        tmp[1] = a[3][0] * a[2][1];
        tmp[2] = a[1][0] * a[3][1];
        tmp[3] = a[3][0] * a[1][1];
        tmp[4] = a[1][0] * a[2][1];
        tmp[5] = a[2][0] * a[1][1];
        tmp[6] = a[0][0] * a[3][1];
        tmp[7] = a[3][0] * a[0][1];
        tmp[8] = a[0][0] * a[2][1];
        tmp[9] = a[2][0] * a[0][1];
        tmp[10] = a[0][0] * a[1][1];
        tmp[11] = a[1][0] * a[0][1];

        /* calculate second 8 elements (cofactors) */
        dst[2][0] = (tmp[0] - tmp[1]) * a[1][3] + (tmp[3] - tmp[2]) * a[2][3] + (tmp[4] - tmp[5]) * a[3][3];
        dst[2][1] = (tmp[1] - tmp[0]) * a[0][3] + (tmp[6] - tmp[7]) * a[2][3] + (tmp[9] - tmp[8]) * a[3][3];
        dst[2][2] = (tmp[2] - tmp[3]) * a[0][3] + (tmp[7] - tmp[6]) * a[1][3] + (tmp[10] - tmp[11]) * a[3][3];
        dst[2][3] = (tmp[5] - tmp[4]) * a[0][3] + (tmp[8] - tmp[9]) * a[1][3] + (tmp[11] - tmp[10]) * a[2][3];
        dst[3][0] = (tmp[2] - tmp[3]) * a[2][2] + (tmp[5] - tmp[4]) * a[3][2] + (tmp[1] - tmp[0]) * a[1][2];
        dst[3][1] = (tmp[8] - tmp[9]) * a[3][2] + (tmp[0] - tmp[1]) * a[0][2] + (tmp[7] - tmp[6]) * a[2][2];
        dst[3][2] = (tmp[6] - tmp[7]) * a[1][2] + (tmp[11] - tmp[10]) * a[3][2] + (tmp[3] - tmp[2]) * a[0][2];
        dst[3][3] = (tmp[10] - tmp[11]) * a[2][2] + (tmp[4] - tmp[5]) * a[0][2] + (tmp[9] - tmp[8]) * a[1][2];

        /* calculate determinant */
        Scalar det = a[0][0] * dst[0][0] + a[1][0] * dst[0][1] + a[2][0] * dst[0][2] + a[3][0] * dst[0][3];

        ASSERT(!iszero(det));

        /* calculate matrix inverse */
        Scalar s = Scalar(1) / det;
      
        return Matrix4x4<Scalar>(dst[0] * s, dst[1] * s, dst[2] * s, dst[3] * s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> inverseAffine(const Matrix4x4<Scalar>& a)
    {
        Matrix3x3<Scalar> invBasis = inverse(basis(a));

        return Matrix4x4<Scalar>(invBasis, mul(invBasis, -origin(a)));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> inverseOrthogonal(const Matrix4x4<Scalar>& a)
    {
        Matrix3x3<Scalar> invBasis = transpose(basis(a));

        return Matrix4x4<Scalar>(invBasis, mul(invBasis, -origin(a)));
    }
}

#if USE_SSE
#include <moto/Matrix4x4_SSE.hpp>
#endif



#endif
