/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_MATRIX3X3_HPP
#define MT_MATRIX3X3_HPP

#include <guts/TypeTraits.hpp>

#include <moto/Vector3.hpp>
#include <moto/Vector4.hpp>
#include <moto/Algebra.hpp>
#include <moto/Diagonal3.hpp>

namespace mt
{      
    // Row-major 3x3 matrix

    template <typename Scalar>
    class Matrix3x3
    {
    public:
        typedef Scalar ScalarType;

        Matrix3x3();
        Matrix3x3(Scalar a00, Scalar a01, Scalar a02, 
                  Scalar a10, Scalar a11, Scalar a12, 
                  Scalar a20, Scalar a21, Scalar a22);
        Matrix3x3(Zero);
        Matrix3x3(Identity); 
        Matrix3x3(Scalar s);
        template <typename Scalar2> explicit Matrix3x3(const Scalar2* v);   
        Matrix3x3(const Vector3<Scalar>& r0, const Vector3<Scalar>& r1, const Vector3<Scalar>& r2);
        Matrix3x3(const Vector4<Scalar>& q); 
        Matrix3x3(const Diagonal3<Scalar>& d); 
       
        
        operator const Vector3<Scalar>*() const;
        operator Vector3<Scalar>*();

        Matrix3x3<Scalar>& operator=(Zero);
        Matrix3x3<Scalar>& operator+=(Zero);
        Matrix3x3<Scalar>& operator-=(Zero);
        Matrix3x3<Scalar>& operator*=(Zero);

        Matrix3x3<Scalar>& operator=(Identity);
          
        Matrix3x3<Scalar>& operator=(Scalar s);
        Matrix3x3<Scalar>& operator*=(Scalar s);
        Matrix3x3<Scalar>& operator/=(Scalar s);
        
        Matrix3x3<Scalar>& operator+=(const Matrix3x3<Scalar>& a);
        Matrix3x3<Scalar>& operator-=(const Matrix3x3<Scalar>& a);


#if USE_MATRIX_COMP_MULT
        Matrix3x3<Scalar>& operator*=(const Matrix3x3<Scalar>& a);
#endif

        void setValue(Scalar a00, Scalar a01, Scalar a02, 
                      Scalar a10, Scalar a11, Scalar a12, 
                      Scalar a20, Scalar a21, Scalar a22);

        template <typename Scalar2> void setValue(const Scalar2* v);  

        void setColumns(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2);
        void setRows(const Vector3<Scalar>& r0, const Vector3<Scalar>& r1, const Vector3<Scalar>& r2);

        Matrix3x3<Scalar>& operator=(const Vector4<Scalar>& q);  
        Matrix3x3<Scalar>& operator=(const Diagonal3<Scalar>& d);

    private:
        Vector3<Scalar> mRow[3];
    };

    template <typename Scalar> Scalar tdot(const Matrix3x3<Scalar>& a, int i, const Vector3<Scalar>& v);
    template <int I, int J, typename Scalar> Scalar cofactor(const Matrix3x3<Scalar>& a);
    template <typename Scalar> Vector3<Scalar> column(const Matrix3x3<Scalar>& a, int i);

#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix3x3<Scalar>& a);
     
#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix3x3<Scalar>& a);

#endif

    template <typename Scalar> bool operator==(const Matrix3x3<Scalar>& a, const Matrix3x3<Scalar>& b);
 
    template <typename Scalar> Matrix3x3<Scalar> operator-(const Matrix3x3<Scalar>& a);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> operator+(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> operator-(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b);

#if USE_MATRIX_COMP_MULT
    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> operator*(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b);
#endif
    
    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> operator*(const Matrix3x3<Scalar1>& a, Scalar2 s);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> operator*(Scalar1 s, const Matrix3x3<Scalar2>& a);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> operator/(const Matrix3x3<Scalar1>& a, Scalar2 s);

    template <typename Scalar1, typename Scalar2> 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> mul(const Matrix3x3<Scalar1>& a, const Vector3<Scalar2>& v);

    template <typename Scalar1, typename Scalar2> 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> mul(const Vector3<Scalar1>& v, const Matrix3x3<Scalar2>& a);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> mul(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> transposeMul(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> mulTranspose(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> mul(const Matrix3x3<Scalar1>& a, const Diagonal3<Scalar2>& d);

    template <typename Scalar1, typename Scalar2> 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> mul(const Diagonal3<Scalar1>& d, const Matrix3x3<Scalar2>& a);
   
    template <typename Scalar> Scalar determinant(const Matrix3x3<Scalar>& a);
    template <typename Scalar> Matrix3x3<Scalar> abs(const Matrix3x3<Scalar>& a);
    template <typename Scalar> Matrix3x3<Scalar> transpose(const Matrix3x3<Scalar>& a);
    template <typename Scalar> Matrix3x3<Scalar> adjoint(const Matrix3x3<Scalar>& a);
    template <typename Scalar> Matrix3x3<Scalar> inverse(const Matrix3x3<Scalar>& a);
    template <typename Scalar> Matrix3x3<Scalar> orthonormalize(const Matrix3x3<Scalar>& a);
    template <typename Scalar> Scalar trace(const Matrix3x3<Scalar>& a);  
    template <typename Scalar> Vector4<Scalar> rotation(const Matrix3x3<Scalar>& a);
    template <typename Scalar> Vector3<Scalar> diagonal(const Matrix3x3<Scalar>& a);
      
    template <typename Scalar> Matrix3x3<Scalar> diag(const Vector3<Scalar>& v);
    template <typename Scalar> Matrix3x3<Scalar> skew(const Vector3<Scalar>& v);
    template <typename Scalar> Matrix3x3<Scalar> dyad(const Vector3<Scalar>& v1, const Vector3<Scalar>& v2);

    template <typename Scalar> Matrix3x3<Scalar> cholesky(const Matrix3x3<Scalar> a);
    template <typename Scalar> Vector3<Scalar> solveTranspose(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& v);
    template <typename Scalar> Vector3<Scalar> solve(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& v);

    template <typename Scalar1, typename Scalar2> void convert(Scalar1* v, const Matrix3x3<Scalar2>& a);
       
      
   

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3() 
    {} 
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3(Scalar a00, Scalar a01, Scalar a02, 
                                 Scalar a10, Scalar a11, Scalar a12, 
                                 Scalar a20, Scalar a21, Scalar a22)
    {
        setValue(a00, a01, a02,
                 a10, a11, a12,
                 a20, a21, a22);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3(Zero)
    {
        *this = Zero();    
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3(Identity)
    {
        *this = Identity();
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3(Scalar s)
    {
        *this = s;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3(const Scalar2* v) 
    {
        setValue(v);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3(const Vector3<Scalar>& r0, const Vector3<Scalar>& r1, const Vector3<Scalar>& r2)                   
    {
        setRows(r0, r1, r2);
    }
   
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3(const Vector4<Scalar>& q)
    {
        *this = q;
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::Matrix3x3(const Diagonal3<Scalar>& d)
    {
        *this = d;
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::operator const Vector3<Scalar>*() const
    {
        return mRow;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>::operator Vector3<Scalar>*()
    {
        return mRow;
    }   

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator=(Zero)
    {
        mRow[0] = Zero();
        mRow[1] = Zero();
        mRow[2] = Zero();   
        return *this;
    }
     
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator+=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator-=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator*=(Zero)
    {
        return *this = Zero();
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator=(Identity)
    {
        mRow[0] = Unit<0>();
        mRow[1] = Unit<1>();
        mRow[2] = Unit<2>();   
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator=(Scalar s)
    {
        setValue(s, Scalar(), Scalar(), 
                 Scalar(), s, Scalar(), 
                 Scalar(), Scalar(), s);
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator*=(Scalar s)
    {
        mRow[0] *= s; 
        mRow[1] *= s; 
        mRow[2] *= s;
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator/=(Scalar s)
    {
        ASSERT(!iszero(s));
        return *this *= Scalar(1) / s;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator+=(const Matrix3x3<Scalar>& a)
    {
        mRow[0] += a[0]; 
        mRow[1] += a[1]; 
        mRow[2] += a[2];
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator-=(const Matrix3x3<Scalar>& a)
    {
        mRow[0] -= a[0]; 
        mRow[1] -= a[1]; 
        mRow[2] -= a[2];
        return *this;
    }


#if USE_MATRIX_COMP_MULT
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator*=(const Matrix3x3<Scalar>& a)
    {
        mRow[0] *= a[0]; 
        mRow[1] *= a[1]; 
        mRow[2] *= a[2];
        return *this;
    }
#endif
   
    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x3<Scalar>::setValue(Scalar a00, Scalar a01, Scalar a02, 
                                     Scalar a10, Scalar a11, Scalar a12, 
                                     Scalar a20, Scalar a21, Scalar a22)
    {
        mRow[0] = Vector3<Scalar>(a00, a01, a02);
        mRow[1] = Vector3<Scalar>(a10, a11, a12);
        mRow[2] = Vector3<Scalar>(a20, a21, a22);
    }

    template <typename Scalar>
    template <typename Scalar2> 
    FORCEINLINE
    void Matrix3x3<Scalar>::setValue(const Scalar2* v)
    {
        mRow[0] = Vector3<Scalar>(Scalar(v[0]), Scalar(v[4]), Scalar(v[8])); 
        mRow[1] = Vector3<Scalar>(Scalar(v[1]), Scalar(v[5]), Scalar(v[9])); 
        mRow[2] = Vector3<Scalar>(Scalar(v[2]), Scalar(v[6]), Scalar(v[10])); 
    }  
       
    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x3<Scalar>::setColumns(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2)
    {
        mRow[0] = Vector3<Scalar>(c0.x, c1.x, c2.x);
        mRow[1] = Vector3<Scalar>(c0.y, c1.y, c2.y);
        mRow[2] = Vector3<Scalar>(c0.z, c1.z, c2.z);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix3x3<Scalar>::setRows(const Vector3<Scalar>& r0, const Vector3<Scalar>& r1, const Vector3<Scalar>& r2)
    {
        mRow[0] = r0;
        mRow[1] = r1;
        mRow[2] = r2;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator=(const Vector4<Scalar>& q)
    {
        Scalar r = dot(q, q);
        ASSERT(!iszero(r));
        Scalar s = Scalar(2) / r;
        Scalar xs = q.x * s, ys = q.y * s, zs = q.z * s;
        Scalar wx = q.w * xs, wy = q.w * ys, wz = q.w * zs;
        Scalar xx = q.x * xs, xy = q.x * ys, xz = q.x * zs;
        Scalar yy = q.y * ys, yz = q.y * zs, zz = q.z * zs;
        setValue(Scalar(1) - (yy + zz), xy - wz, xz + wy, 
                 xy + wz, Scalar(1) - (xx + zz), yz - wx, 
                 xz - wy, yz + wx, Scalar(1) - (xx + yy));
        return *this;
    } 
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar>& Matrix3x3<Scalar>::operator=(const Diagonal3<Scalar>& d)
    {
        setValue(d.x, Scalar(), Scalar(), 
                 Scalar(), d.y, Scalar(), 
                 Scalar(), Scalar(), d.z);
        return *this;
    }

    


    template <typename Scalar>
    FORCEINLINE 
    Scalar tdot(const Matrix3x3<Scalar>& a, int i, const Vector3<Scalar>& v)
    {
        return a[0][i] * v.x + a[1][i] * v.y + a[2][i] * v.z;
    }

    template <int I, int J, typename Scalar>
    FORCEINLINE 
    Scalar cofactor(const Matrix3x3<Scalar>& a)
    {
        return a[(I + 1) % 3][(J + 1) % 3] * a[(I + 2) % 3][(J + 2) % 3] - 
               a[(I + 2) % 3][(J + 1) % 3] * a[(I + 1) % 3][(J + 2) % 3];
    }  
    
    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> column(const Matrix3x3<Scalar>& a, int i)
    {
        return Vector3<Scalar>(a[0][i], a[1][i], a[2][i]);
    }

#ifdef USE_OSTREAM
     
    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix3x3<Scalar>& a)
    {
        return os << ' ' << a[0] << ' ' << a[1] << ' ' << a[2];
    }

#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix3x3<Scalar>& a)
    {
        return is >> a[0] >> a[1] >> a[2];
    }

#endif


    template <typename Scalar>
    FORCEINLINE 
    bool operator==(const Matrix3x3<Scalar>& a, const Matrix3x3<Scalar>& b)
    {
        return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> operator-(const Matrix3x3<Scalar>& a)
    {
        return Matrix3x3<Scalar>(-a[0][0], -a[0][1], -a[0][2],
                                 -a[1][0], -a[1][1], -a[1][2], 
                                 -a[2][0], -a[2][1], -a[2][2]);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    operator+(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(a[0][0] + b[0][0], a[0][1] + b[0][1], a[0][2] + b[0][2],
                             a[1][0] + b[1][0], a[1][1] + b[1][1], a[1][2] + b[1][2],
                             a[2][0] + b[2][0], a[2][1] + b[2][1], a[2][2] + b[2][2]);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    operator-(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(a[0][0] - b[0][0], a[0][1] - b[0][1], a[0][2] - b[0][2],
                             a[1][0] - b[1][0], a[1][1] - b[1][1], a[1][2] - b[1][2],
                             a[2][0] - b[2][0], a[2][1] - b[2][1], a[2][2] - b[2][2]);
    }


#if USE_MATRIX_COMP_MULT
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(a[0][0] * b[0][0], a[0][1] * b[0][1], a[0][2] * b[0][2],
                             a[1][0] * b[1][0], a[1][1] * b[1][1], a[1][2] * b[1][2],
                             a[2][0] * b[2][0], a[2][1] * b[2][1], a[2][2] * b[2][2]);
    }
#endif
   
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(const Matrix3x3<Scalar1>& a, Scalar2 s)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(a[0][0] * s, a[0][1] * s, a[0][2] * s, 
                             a[1][0] * s, a[1][1] * s, a[1][2] * s, 
                             a[2][0] * s, a[2][1] * s, a[2][2] * s);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    operator*(Scalar1 s, const Matrix3x3<Scalar2>& a)
    {
        return a * s;
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    operator/(const Matrix3x3<Scalar1>& a, Scalar2 s)
    {
        ASSERT(!iszero(s));
        return a * (Scalar2(1) / s);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Matrix3x3<Scalar1>& a, const Vector3<Scalar2>& v)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Vector3<RT>(dot(a[0], v), 
                           dot(a[1], v), 
                           dot(a[2], v));
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Vector3<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Vector3<Scalar1>& v, const Matrix3x3<Scalar2>& a)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Vector3<RT>(tdot(a, 0, v), 
                           tdot(a, 1, v), 
                           tdot(a, 2, v));
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(tdot(b, 0, a[0]), tdot(b, 1, a[0]), tdot(b, 2, a[0]), 
                             tdot(b, 0, a[1]), tdot(b, 1, a[1]), tdot(b, 2, a[1]), 
                             tdot(b, 0, a[2]), tdot(b, 1, a[2]), tdot(b, 2, a[2]));
    }


    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    transposeMul(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(a[0][0] * b[0][0] + a[1][0] * b[1][0] + a[2][0] * b[2][0],
                             a[0][0] * b[0][1] + a[1][0] * b[1][1] + a[2][0] * b[2][1],
                             a[0][0] * b[0][2] + a[1][0] * b[1][2] + a[2][0] * b[2][2],
                             a[0][1] * b[0][0] + a[1][1] * b[1][0] + a[2][1] * b[2][0],
                             a[0][1] * b[0][1] + a[1][1] * b[1][1] + a[2][1] * b[2][1],
                             a[0][1] * b[0][2] + a[1][1] * b[1][2] + a[2][1] * b[2][2],
                             a[0][2] * b[0][0] + a[1][2] * b[1][0] + a[2][2] * b[2][0],
                             a[0][2] * b[0][1] + a[1][2] * b[1][1] + a[2][2] * b[2][1],
                             a[0][2] * b[0][2] + a[1][2] * b[1][2] + a[2][2] * b[2][2]);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    mulTranspose(const Matrix3x3<Scalar1>& a, const Matrix3x3<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(dot(a[0], b[0]), dot(a[0], b[1]), dot(a[0], b[2]), 
                             dot(a[1], b[0]), dot(a[1], b[1]), dot(a[1], b[2]), 
                             dot(a[2], b[0]), dot(a[2], b[1]), dot(a[2], b[2]));
    } 
    
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Diagonal3<Scalar1>& d, const Matrix3x3<Scalar2>& a)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(d[0] * a[0][0], d[0] * a[0][1], d[0] * a[0][2],
                             d[1] * a[1][0], d[1] * a[1][1], d[1] * a[1][2],
                             d[2] * a[2][0], d[2] * a[2][1], d[2] * a[2][2]);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix3x3<typename Promote<Scalar1, Scalar2>::RT> 
    mul(const Matrix3x3<Scalar1>& a, const Diagonal3<Scalar2>& d)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix3x3<RT>(a[0][0] * d[0], a[0][1] * d[1], a[0][2] * d[2],
                             a[1][0] * d[0], a[1][1] * d[1], a[1][2] * d[2],
                             a[2][0] * d[0], a[2][1] * d[1], a[2][2] * d[2]);
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Scalar determinant(const Matrix3x3<Scalar>& a)
    {
        return triple(a[0], a[1], a[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> abs(const Matrix3x3<Scalar>& a)
    {
        return Matrix3x3<Scalar>(abs(a[0][0]), abs(a[0][1]), abs(a[0][2]), 
                                 abs(a[1][0]), abs(a[1][1]), abs(a[1][2]), 
                                 abs(a[2][0]), abs(a[2][1]), abs(a[2][2]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> transpose(const Matrix3x3<Scalar>& a)
    {
        return Matrix3x3<Scalar>(a[0][0], a[1][0], a[2][0],
                                 a[0][1], a[1][1], a[2][1],
                                 a[0][2], a[1][2], a[2][2]);
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix3x3<Scalar> adjoint(const Matrix3x3<Scalar>& a)
    {
        return Matrix3x3<Scalar>(cofactor<0, 0>(a), cofactor<1, 0>(a), cofactor<2, 0>(a), 
                                 cofactor<0, 1>(a), cofactor<1, 1>(a), cofactor<2, 1>(a), 
                                 cofactor<0, 2>(a), cofactor<1, 2>(a), cofactor<2, 2>(a)); 
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> inverse(const Matrix3x3<Scalar>& a)
    {
        Vector3<Scalar> co(cofactor<0, 0>(a), 
                           cofactor<0, 1>(a), 
                           cofactor<0, 2>(a));
        Scalar det = dot(a[0], co);
        ASSERT(!iszero(det));
        Scalar s = Scalar(1) / det;
        return Matrix3x3<Scalar>(co[0] * s, cofactor<1, 0>(a) * s, cofactor<2, 0>(a) * s, 
                                 co[1] * s, cofactor<1, 1>(a) * s, cofactor<2, 1>(a) * s,
                                 co[2] * s, cofactor<1, 2>(a) * s, cofactor<2, 2>(a) * s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> orthonormalize(const Matrix3x3<Scalar>& a)
    {
        Matrix3x3<Scalar> result;
        result[0] = normalize(a[0]);
        result[1] = normalize(a[1]);
        result[2] = cross(result[0], result[1]);
        result[1] = cross(result[2], result[0]);
        return result;
    }

    template <typename Scalar>
    FORCEINLINE 
    Scalar trace(const Matrix3x3<Scalar>& a)
    {
        return a[0][0] + a[1][1] + a[2][2];
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> rotation(const Matrix3x3<Scalar>& a)
    {
        Scalar t = trace(a);

        if (ispositive(t))
        {
            Scalar d = sqrt(t + Scalar(1));
            Scalar s = Scalar(0.5) / d;

            return Vector4<Scalar>((a[2][1] - a[1][2]) * s,
                                   (a[0][2] - a[2][0]) * s,
                                   (a[1][0] - a[0][1]) * s,
                                   d * Scalar(0.5));
        }
        else
        {  
            Vector4<Scalar> result;

            int i = a[0][0] < a[1][1] ? (a[1][1] < a[2][2] ? 2 : 1) : (a[0][0] < a[2][2] ? 2 : 0); 
            int j = (i + 1) % 3;  
            int k = (i + 2) % 3;

            Scalar d = sqrt(a[i][i] - a[j][j] - a[k][k] + Scalar(1));     
            Scalar s = Scalar(0.5) / d;

            result[i] = d * Scalar(0.5);
            result[j] = (a[j][i] + a[i][j]) * s;
            result[k] = (a[k][i] + a[i][k]) * s; 
            result[3] = (a[k][j] - a[j][k]) * s;
                
            return result;
        }   
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> diagonal(const Matrix3x3<Scalar>& a)
    {
        return Vector3<Scalar>(a[0][0], a[1][1], a[2][2]);
    }
    

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> diag(const Vector3<Scalar>& v)
    {
        return Matrix3x3<Scalar>(v.x, Scalar(), Scalar(),
                                 Scalar(), v.y, Scalar(),
                                 Scalar(), Scalar(), v.z);
    }


    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> skew(const Vector3<Scalar>& v)
    {
        return Matrix3x3<Scalar>(Scalar(), -v.z, v.y,
                                 v.z, Scalar(), -v.x,
                                 -v.y, v.x, Scalar());
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> dyad(const Vector3<Scalar>& v1, const Vector3<Scalar>& v2)
    {
        return Matrix3x3<Scalar>(v1.x * v2.x, v1.x * v2.y, v1.x * v2.z, 
                                 v1.y * v2.x, v1.y * v2.y, v1.y * v2.z, 
                                 v1.z * v2.x, v1.z * v2.y, v1.z * v2.z);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> cholesky(Matrix3x3<Scalar> a)
    {
        for (int k = 0; k != 3 ; ++k)
        {
            ASSERT(!isnegative(a[k][k]));
            a[k][k] = sqrt(a[k][k]);
    
            for (int i = k + 1; i != 3; ++i)
            {
                a[i][k] /= a[k][k];
            }

            for (int j = k + 1; j != 3; ++j)
            {
                for (int i = j; i != 3; ++i)
                {
                    a[i][j] -= a[i][k] * a[j][k];
                }
            }
        }

        a[0][1] = a[0][2] = a[1][2] = Scalar(); 
        return a;
    }


    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> solveTranspose(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& v)
    {
        // Cramer's rule
        Scalar det = determinant(a);
        ASSERT(!iszero(det));
        return Vector3<Scalar>(triple(v, a[1], a[2]) / det, 
                               triple(a[0], v, a[2]) / det,
                               triple(a[0], a[1], v) / det);
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> solve(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& v)
    {
        // Cramer's rule
        return solveTranspose(transpose(a), v);
    }     
    
    template <typename Scalar1, typename Scalar2> 
    FORCEINLINE 
    void convert(Scalar1* v, const Matrix3x3<Scalar2>& a)
    {
        v[0] = Scalar1(a[0][0]); v[4] = Scalar1(a[0][1]); v[8] = Scalar1(a[0][2]); 
        v[1] = Scalar1(a[1][0]); v[5] = Scalar1(a[1][1]); v[9] = Scalar1(a[1][2]); 
        v[2] = Scalar1(a[2][0]); v[6] = Scalar1(a[2][1]); v[10] = Scalar1(a[2][2]);  
    }

}

namespace guts
{
    template <> struct TypeTraits<mt::Matrix3x3<float> > { enum { ID = TT_FLOAT3 | TT_3 }; };
    template <> struct TypeTraits<mt::Matrix3x3<double> > { enum { ID = TT_DOUBLE3 | TT_3 }; };
}

#endif
