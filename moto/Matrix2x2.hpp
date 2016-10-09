/*  MoTo - Motion Toolkit
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_MATRIX2X2_HPP
#define MT_MATRIX2X2_HPP

#include <moto/Vector2.hpp>
#include <moto/Algebra.hpp>
#include <moto/Diagonal2.hpp>

#include <complex>

namespace mt
{
    // Row-major 2x2 matrix

    template <typename Scalar>
    class Matrix2x2
    {
    public:
        typedef Scalar ScalarType;

        Matrix2x2();
        Matrix2x2(Scalar a00, Scalar a01,
                  Scalar a10, Scalar a11);
        Matrix2x2(Zero);
        Matrix2x2(Identity);
        Matrix2x2(Scalar s);
        Matrix2x2(const Vector2<Scalar>& c0, const Vector2<Scalar>& c1);
        Matrix2x2(const std::complex<Scalar>& z); 
        Matrix2x2(const Diagonal2<Scalar>& d);
        
        operator const Vector2<Scalar>*() const;
        operator Vector2<Scalar>*();   
        
        Matrix2x2<Scalar>& operator=(Zero);
        Matrix2x2<Scalar>& operator+=(Zero);
        Matrix2x2<Scalar>& operator-=(Zero);
        Matrix2x2<Scalar>& operator*=(Zero);

        Matrix2x2<Scalar>& operator=(Identity);
              
        Matrix2x2<Scalar>& operator=(Scalar s);
        Matrix2x2<Scalar>& operator*=(Scalar s);
        Matrix2x2<Scalar>& operator/=(Scalar s);
        
        Matrix2x2<Scalar>& operator+=(const Matrix2x2<Scalar>& a);
        Matrix2x2<Scalar>& operator-=(const Matrix2x2<Scalar>& a);

#if USE_MATRIX_COMP_MULT
        Matrix2x2<Scalar>& operator*=(const Matrix2x2<Scalar>& a);
#endif

        void setValue(Scalar a00, Scalar a01,
                      Scalar a10, Scalar a11);
        
        void setRotation(const std::complex<Scalar>& z);  
        void setDiagonal(const Diagonal2<Scalar>& d);

    private:
        Vector2<Scalar> mRow[2];
    };

    template <typename Scalar> Scalar tdot(const Matrix2x2<Scalar>& a, int i, const Vector2<Scalar>& v);
    template <typename Scalar> Vector2<Scalar> column(const Matrix2x2<Scalar>& a, int i);
      

#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix2x2<Scalar>& a);
     
#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix2x2<Scalar>& a);

#endif


    template <typename Scalar> bool operator==(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b);
  
    template <typename Scalar> Matrix2x2<Scalar> operator-(const Matrix2x2<Scalar>& a);

    template <typename Scalar> Matrix2x2<Scalar> operator+(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b);
    template <typename Scalar> Matrix2x2<Scalar> operator-(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b);

#if USE_MATRIX_COMP_MULT
    template <typename Scalar> Matrix2x2<Scalar> operator*(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b);
#endif

    template <typename Scalar> Matrix2x2<Scalar> operator*(const Matrix2x2<Scalar>& a, Scalar s);
    template <typename Scalar> Matrix2x2<Scalar> operator*(Scalar s, const Matrix2x2<Scalar>& a);
    template <typename Scalar> Matrix2x2<Scalar> operator/(const Matrix2x2<Scalar>& a, Scalar s);

    
    template <typename Scalar> Matrix2x2<Scalar> mul(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b);
    template <typename Scalar> Matrix2x2<Scalar> transposeMul(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b);
    template <typename Scalar> Matrix2x2<Scalar> mulTranspose(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b);

    template <typename Scalar> Vector2<Scalar> mul(const Matrix2x2<Scalar>& a, const Vector2<Scalar>& v);
    template <typename Scalar> Vector2<Scalar> mul(const Vector2<Scalar>& v, const Matrix2x2<Scalar>& a);


    template <typename Scalar> Matrix2x2<Scalar> mul(const Matrix2x2<Scalar>& a, const Diagonal2<Scalar>& d);
    template <typename Scalar> Matrix2x2<Scalar> mul(const Diagonal2<Scalar>& d, const Matrix2x2<Scalar>& a);
   
    template <typename Scalar> Scalar determinant(const Matrix2x2<Scalar>& a);
    template <typename Scalar> Matrix2x2<Scalar> abs(const Matrix2x2<Scalar>& a);
    template <typename Scalar> Matrix2x2<Scalar> transpose(const Matrix2x2<Scalar>& a);
    template <typename Scalar> Matrix2x2<Scalar> adjoint(const Matrix2x2<Scalar>& a);
    template <typename Scalar> Matrix2x2<Scalar> inverse(const Matrix2x2<Scalar>& a);
    template <typename Scalar> Scalar trace(const Matrix2x2<Scalar>& a);  

    template <typename Scalar> Matrix2x2<Scalar> dyad(const Vector2<Scalar>& v1, const Vector2<Scalar>& v2);
	template <typename Scalar> void eigsym(Vector2<Scalar>& v1, Vector2<Scalar>& v2, const Matrix2x2<Scalar>& a);

    
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::Matrix2x2() 
    {} 
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::Matrix2x2(Scalar a00, Scalar a01,
                                 Scalar a10, Scalar a11)
    {
        setValue(a00, a01,
                 a10, a11);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::Matrix2x2(Zero)
    {
        *this = Zero();
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::Matrix2x2(Identity)
    {
        *this = Identity();
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::Matrix2x2(Scalar s)
    {
        *this = s;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::Matrix2x2(const Vector2<Scalar>& c0, const Vector2<Scalar>& c1)
    {
        setValue(c0.x, c1.x,
                 c0.y, c1.y);
    }
   
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::Matrix2x2(const std::complex<Scalar>& z)
    {
        setRotation(z);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::Matrix2x2(const Diagonal2<Scalar>& d)
    {
        setDiagonal(d);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::operator const Vector2<Scalar>*() const
    {
        return mRow;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>::operator Vector2<Scalar>*()
    {
        return mRow;
    }   

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator=(Zero)
    {
        mRow[0] = Zero();
        mRow[1] = Zero();
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator+=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator-=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator*=(Zero)
    {
        return *this = Zero();
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator=(Identity)
    {
        mRow[0] = Unit<0>();
        mRow[1] = Unit<1>();
        return *this;
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator=(Scalar s)
    {
        setValue(s, Scalar(), 
                 Scalar(), s);
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator*=(Scalar s)
    {
        mRow[0] *= s; 
        mRow[1] *= s; 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator/=(Scalar s)
    {
        ASSERT(!iszero(s));
        return *this *= Scalar(1) / s;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator+=(const Matrix2x2<Scalar>& a)
    {
        mRow[0] += a[0]; 
        mRow[1] += a[1]; 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator-=(const Matrix2x2<Scalar>& a)
    {
        mRow[0] -= a[0]; 
        mRow[1] -= a[1]; 
        return *this;
    }

#if USE_MATRIX_COMP_MULT
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar>& Matrix2x2<Scalar>::operator*=(const Matrix2x2<Scalar>& a)
    {
        mRow[0] *= a[0]; 
        mRow[1] *= a[1]; 
        return *this;
    }
#endif
   
    template <typename Scalar>
    FORCEINLINE 
    void Matrix2x2<Scalar>::setValue(Scalar a00, Scalar a01,
                                     Scalar a10, Scalar a11)
    {
        mRow[0] = Vector2<Scalar>(a00, a01); 
        mRow[1] = Vector2<Scalar>(a10, a11); 
    }
        
 
        
    template <typename Scalar>
    FORCEINLINE 
    void Matrix2x2<Scalar>::setRotation(const std::complex<Scalar>& z)
    {
        Scalar r = abs(z);
        ASSERT(!iszero(r));
        Scalar s = Scalar(1) / r;
        Scalar cs = z.real() * s;
        Scalar ss = z.imag() * s;
        setValue(cs, -ss, 
                 ss, cs);
    } 
    
    template <typename Scalar>
    FORCEINLINE 
    void Matrix2x2<Scalar>::setDiagonal(const Diagonal2<Scalar>& d)
    {
        setValue(d[0], Scalar(),
                 Scalar(), d[1]);
    }

    


    template <typename Scalar>
    FORCEINLINE 
    Scalar tdot(const Matrix2x2<Scalar>& a, int i, const Vector2<Scalar>& v)
    {
        return a[0][i] * v.x + a[1][i] * v.y;
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Vector2<Scalar> column(const Matrix2x2<Scalar>& a, int i)
    {
        return Vector2<Scalar>(a[0][i], a[1][i]);
    }

#ifdef USE_OSTREAM
     
    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix2x2<Scalar>& a)
    {
        return os << ' ' << a[0] << ' ' << a[1];
    }

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix2x2<Scalar>& a)
    {
        return is >> a[0] >> a[1];
    }

#endif

    template <typename Scalar>
    FORCEINLINE 
    bool operator==(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b)
    {
        return a[0] == b[0] && a[1] == b[1];
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> operator-(const Matrix2x2<Scalar>& a)
    {
        return Matrix2x2<Scalar>(-a[0][0], -a[0][1],
                                 -a[1][0], -a[1][1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> operator+(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b)
    {
        return Matrix2x2<Scalar>(a[0][0] + b[0][0], a[0][1] + b[0][1],
                                 a[1][0] + b[1][0], a[1][1] + b[1][1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> operator-(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b)
    {
        return Matrix2x2<Scalar>(a[0][0] - b[0][0], a[0][1] - b[0][1],
                                 a[1][0] - b[1][0], a[1][1] - b[1][1]);
    }

#if USE_MATRIX_COMP_MULT
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> operator*(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b)
    {
        return Matrix2x2<Scalar>(a[0][0] * b[0][0], a[0][1] * b[0][1],
                                 a[1][0] * b[1][0], a[1][1] * b[1][1]);
    }
#endif


    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> operator*(const Matrix2x2<Scalar>& a, Scalar s)
    {
        return Matrix2x2<Scalar>(a[0][0] * s, a[0][1] * s,
                                 a[1][0] * s, a[1][1] * s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> operator*(Scalar s, const Matrix2x2<Scalar>& a)
    {
        return a * s;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> operator/(const Matrix2x2<Scalar>& a, Scalar s)
    {
        ASSERT(!iszero(s));
        return a * (Scalar(1) / s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector2<Scalar> mul(const Matrix2x2<Scalar>& a, const Vector2<Scalar>& v)
    {
        return Vector2<Scalar>(dot(a[0], v), 
                               dot(a[1], v));
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector2<Scalar> mul(const Vector2<Scalar>& v, const Matrix2x2<Scalar>& a)
    {
        return Vector2<Scalar>(tdot(a, 0, v), 
                               tdot(a, 1, v));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> mul(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b)
    {
        return Matrix2x2<Scalar>(tdot(b, 0, a[0]), tdot(b, 1, a[0]),
                                 tdot(b, 0, a[1]), tdot(b, 1, a[1]));
    }


    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> transposeMul(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b)
    {
        return Matrix2x2<Scalar>(a[0][0] * b[0][0] + a[1][0] * b[1][0], a[0][0] * b[0][1] + a[1][0] * b[1][1],
                                 a[0][1] * b[0][0] + a[1][1] * b[1][0], a[0][1] * b[0][1] + a[1][1] * b[1][1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> mulTranspose(const Matrix2x2<Scalar>& a, const Matrix2x2<Scalar>& b)
    {
        return Matrix2x2<Scalar>(dot(a[0], b[0]), dot(a[0], b[1]),
                                 dot(a[1], b[0]), dot(a[1], b[1]));
    } 
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> mul(const Diagonal2<Scalar>& d, const Matrix2x2<Scalar>& a)
    {
        return Matrix2x2<Scalar>(d[0] * a[0][0], d[0] * a[0][1],
                                 d[1] * a[1][0], d[1] * a[1][1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> mul(const Matrix2x2<Scalar>& a, const Diagonal2<Scalar>& d)
    {
        return Matrix2x2<Scalar>(a[0][0] * d[0], a[0][1] * d[1],
                                 a[1][0] * d[0], a[1][1] * d[1]);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Scalar determinant(const Matrix2x2<Scalar>& a)
    {
        return a[0][0] * a[1][1] - a[0][1] * a[1][0];
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> abs(const Matrix2x2<Scalar>& a)
    {
        return Matrix2x2<Scalar>(abs(a[0][0]), abs(a[0][1]),
                                 abs(a[1][0]), abs(a[1][1]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> transpose(const Matrix2x2<Scalar>& a)
    {
        return Matrix2x2<Scalar>(a[0], a[1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> adjoint(const Matrix2x2<Scalar>& a)
    {
        return Matrix2x2<Scalar>( a[1][1], -a[0][1], 
                                 -a[1][0],  a[0][0]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> inverse(const Matrix2x2<Scalar>& a)
    {
        Scalar det = determinant(a);
        ASSERT(!iszero(det));
        Scalar s = Scalar(1) / det;
        return Matrix2x2<Scalar>( a[1][1] * s, -a[0][1] * s, 
                                 -a[1][0] * s,  a[0][0] * s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Scalar trace(const Matrix2x2<Scalar>& a)
    {
        return a[0][0] + a[1][1];
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix2x2<Scalar> dyad(const Vector2<Scalar>& v1, const Vector2<Scalar>& v2)
    {
        return Matrix2x2<Scalar>(v1[0] * v2[0], v1[0] * v2[1],
                                 v1[1] * v2[0], v1[1] * v2[1]);
    } 

    template <typename Scalar>
    FORCEINLINE 
    void eigsym(Vector2<Scalar>& v1, Vector2<Scalar>& v2, const Matrix2x2<Scalar>& a)
    {
		Scalar sd = sqrt(square(a[0][0] - a[1][1]) + square(a[0][1]) * Scalar(4));
		Scalar tr = trace(a);
        Scalar lambda1 = (tr + sd) * Scalar(0.5);
        Scalar lambda2 = (tr - sd) * Scalar(0.5);
		Scalar s1 = (lambda1 - a[0][0]) / a[0][1];	
		Scalar s2 = (lambda2 - a[0][0]) / a[0][1];
	    v1.x = rsqrt(square(s1) + 1);
	    v2.x = rsqrt(square(s2) + 1);
		v1.y = s1 * v1.x;
		v2.y = s2 * v2.x;
    }
}

#endif
