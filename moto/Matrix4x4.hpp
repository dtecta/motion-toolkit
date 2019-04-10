/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_MATRIX4X4_HPP
#define MT_MATRIX4X4_HPP

#include <guts/TypeTraits.hpp>

#include <moto/Matrix3x3.hpp>
#include <moto/Matrix3x4.hpp>
#include <moto/Matrix4x3.hpp>
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
        Matrix4x4(Zero);
        Matrix4x4(Identity);
        Matrix4x4(Scalar s);
        template <typename Scalar2> explicit Matrix4x4(const Scalar2* v);   
        Matrix4x4(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3);
        Matrix4x4(const Vector4<Scalar>& r0, const Vector4<Scalar>& r1, const Vector4<Scalar>& r2, const Vector4<Scalar>& r3);
        explicit Matrix4x4(const Vector3<Scalar>& p);
        explicit Matrix4x4(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& p = Zero());
        explicit Matrix4x4(const Matrix3x4<Scalar>& a);
        
        operator const Vector4<Scalar>*() const; 
        operator Vector4<Scalar>*();
        
        Matrix4x4<Scalar>& operator=(Zero);
        Matrix4x4<Scalar>& operator+=(Zero);
        Matrix4x4<Scalar>& operator-=(Zero);
        Matrix4x4<Scalar>& operator*=(Zero);

        Matrix4x4<Scalar>& operator=(Identity);
          
        Matrix4x4<Scalar>& operator=(Scalar s);
        Matrix4x4<Scalar>& operator*=(Scalar s);
        Matrix4x4<Scalar>& operator/=(Scalar s);
        
        Matrix4x4<Scalar>& operator+=(const Matrix4x4<Scalar>& a);
        Matrix4x4<Scalar>& operator-=(const Matrix4x4<Scalar>& a);

#if USE_MATRIX_COMP_MULT
        Matrix4x4<Scalar>& operator*=(const Matrix4x4<Scalar>& a);
#endif

        template <typename Scalar2> void setValue(const Scalar2* v);  
        void setColumns(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3);
        void setColumns(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2, const Vector4<Scalar>& c3);
        void setRows(const Vector4<Scalar>& r0, const Vector4<Scalar>& r1, const Vector4<Scalar>& r2, const Vector4<Scalar>& r3);

        void setBasis(const Matrix3x3<Scalar>& basis);
        void setOrigin(const Vector3<Scalar>& origin);

        void setColumn(int j, const Vector3<Scalar>& v);
        void setColumn(int j, const Vector4<Scalar>& v);

        void setRow(int i, const Vector3<Scalar>& v);
        void setRow(int i, const Vector4<Scalar>& v);

    private:
        Vector4<Scalar> mRow[4];
    }; 

    template <typename Scalar> bool operator==(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b);

    template <typename Scalar> Matrix4x4<Scalar> operator-(const Matrix4x4<Scalar>& a);

    template <typename Scalar1, typename Scalar2> 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT> operator+(const Matrix4x4<Scalar1>& a, const Matrix4x4<Scalar2>& b);

    template <typename Scalar1, typename Scalar2> 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT> operator-(const Matrix4x4<Scalar1>& a, const Matrix4x4<Scalar2>& b);

#if USE_MATRIX_COMP_MULT
    template <typename Scalar1, typename Scalar2> 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT> operator*(const Matrix4x4<Scalar1>& a, const Matrix4x4<Scalar2>& b);
#endif
    
    template <typename Scalar1, typename Scalar2> 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT> operator*(const Matrix4x4<Scalar1>& a, Scalar2 s);

    template <typename Scalar1, typename Scalar2> 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT> operator*(Scalar1 s, const Matrix4x4<Scalar2>& a);

    template <typename Scalar1, typename Scalar2> 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT> operator/(const Matrix4x4<Scalar1>& a, Scalar2 s);

    template <int I, int J, typename Scalar> Scalar cofactor(const Matrix4x4<Scalar>& a);

    template <typename Scalar> Vector4<Scalar> row(const Matrix4x4<Scalar>& a, int i);
    template <typename Scalar> Vector4<Scalar> column(const Matrix4x4<Scalar>& a, int i);
    
    template <typename Scalar> Matrix3x3<Scalar> basis(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Vector3<Scalar> origin(const Matrix4x4<Scalar>& a); 

#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix4x4<Scalar>& a);
     
#endif

#ifdef USE_ISTREAM
    
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix4x4<Scalar>& a);

#endif

    template <typename Scalar> Vector4<Scalar> mul(const Matrix4x4<Scalar>& a, const Vector4<Scalar>& v);
    template <typename Scalar> Vector4<Scalar> mul(const Vector4<Scalar>& v, const Matrix4x4<Scalar>& a);

    template <typename Scalar> Matrix4x4<Scalar> mul(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b);
    template <typename Scalar> Matrix4x4<Scalar> mul(const Matrix4x3<Scalar>& a, const Matrix3x4<Scalar>& b);
    template <typename Scalar> Matrix3x4<Scalar> mul(const Matrix3x4<Scalar>& a, const Matrix4x4<Scalar>& b);
    template <typename Scalar> Matrix4x3<Scalar> mul(const Matrix4x4<Scalar>& a, const Matrix4x3<Scalar>& b);

    template <typename Scalar> Matrix4x4<Scalar> transposeMul(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b);
    template <typename Scalar> Matrix4x4<Scalar> transposeMul(const Matrix3x4<Scalar>& a, const Matrix3x4<Scalar>& b);
    template <typename Scalar> Matrix3x4<Scalar> transposeMul(const Matrix4x3<Scalar>& a, const Matrix4x4<Scalar>& b);
    template <typename Scalar> Matrix4x3<Scalar> transposeMul(const Matrix4x4<Scalar>& a, const Matrix3x4<Scalar>& b);

    template <typename Scalar> Matrix4x4<Scalar> mulTranspose(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b);
    template <typename Scalar> Matrix4x4<Scalar> mulTranspose(const Matrix4x3<Scalar>& a, const Matrix4x3<Scalar>& b);
    template <typename Scalar> Matrix3x4<Scalar> mulTranspose(const Matrix3x4<Scalar>& a, const Matrix4x4<Scalar>& b);
    template <typename Scalar> Matrix4x3<Scalar> mulTranspose(const Matrix4x4<Scalar>& a, const Matrix3x4<Scalar>& b);

    template <typename Scalar> Scalar determinant(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> transpose(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> adjoint(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> inverse(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> inverseAffine(const Matrix4x4<Scalar>& a);
    template <typename Scalar> Matrix4x4<Scalar> inverseOrthogonal(const Matrix4x4<Scalar>& a);
    
    template <typename Scalar> Matrix4x4<Scalar> frustum(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar zNear, Scalar zFar);

    // mul(lquat(q1), q2) = mul(q1, q2) 
   template <typename Scalar> Matrix4x4<Scalar> lquat(const Vector4<Scalar>& q);

    // mul(rquat(q2), q1) = mul(q1, q2)
   template <typename Scalar> Matrix4x4<Scalar> rquat(const Vector4<Scalar>& q);

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4() 
    {} 

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(Zero)
    {
        *this = Zero();
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(Identity)
    {
        *this = Identity();
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(Scalar s)
    {
        *this = s;
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
        setColumns(c0, c1, c2, c3);
    }
   

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Vector4<Scalar>& r0, const Vector4<Scalar>& r1, const Vector4<Scalar>& r2, const Vector4<Scalar>& r3)
    {
        setRows(r0, r1, r2, r3);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Vector3<Scalar>& p)
    {
        mRow[0] = Vector4<Scalar>(Vector3<Scalar>(Unit<0>()), p.x);
        mRow[1] = Vector4<Scalar>(Vector3<Scalar>(Unit<1>()), p.y);
        mRow[2] = Vector4<Scalar>(Vector3<Scalar>(Unit<2>()), p.z);
        mRow[3] = Unit<3>();
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& p)
    {
        mRow[0] = Vector4<Scalar>(a[0], p.x);
        mRow[1] = Vector4<Scalar>(a[1], p.y);
        mRow[2] = Vector4<Scalar>(a[2], p.z);
        mRow[3] = Unit<3>();
    }
   
    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>::Matrix4x4(const Matrix3x4<Scalar>& a)
    {
        mRow[0] = a[0];
        mRow[1] = a[1];
        mRow[2] = a[2];
        mRow[3] = Unit<3>();
    }
    
    template <typename Scalar>
    FORCEINLINE
    Matrix4x4<Scalar>::operator const Vector4<Scalar>*() const
    {
        return mRow;
    } 

    template <typename Scalar>
    FORCEINLINE
    Matrix4x4<Scalar>::operator Vector4<Scalar>*()
    {
        return mRow;
    } 
   
    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator=(Zero)
    {
        mRow[0] = Zero();
        mRow[1] = Zero();
        mRow[2] = Zero();   
        mRow[3] = Zero();
        return *this;
    }
     
    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator+=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator-=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator*=(Zero)
    {
        return *this = Zero();
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator=(Identity)
    {
        mRow[0] = Unit<0>();
        mRow[1] = Unit<1>();
        mRow[2] = Unit<2>();
        mRow[3] = Unit<3>();
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator=(Scalar s)
    {
        mRow[0] = Vector4<Scalar>(s, Scalar(), Scalar(), Scalar());
        mRow[1] = Vector4<Scalar>(Scalar(), s, Scalar(), Scalar());
        mRow[2] = Vector4<Scalar>(Scalar(), Scalar(), s, Scalar());
        mRow[3] = Vector4<Scalar>(Scalar(), Scalar(), Scalar(), s);
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator*=(Scalar s)
    {
        mRow[0] *= s; 
        mRow[1] *= s; 
        mRow[2] *= s;
        mRow[3] *= s;
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator/=(Scalar s)
    {
        ASSERT(!iszero(s));
        return *this *= Scalar(1) / s;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator+=(const Matrix4x4<Scalar>& a)
    {
        mRow[0] += a[0]; 
        mRow[1] += a[1]; 
        mRow[2] += a[2];
        mRow[3] += a[3];
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator-=(const Matrix4x4<Scalar>& a)
    {
        mRow[0] -= a[0]; 
        mRow[1] -= a[1]; 
        mRow[2] -= a[2];
        mRow[3] -= a[3];
        return *this;
    }

#if USE_MATRIX_COMP_MULT
    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar>& Matrix4x4<Scalar>::operator*=(const Matrix4x4<Scalar>& a)
    {
        mRow[0] *= a[0]; 
        mRow[1] *= a[1]; 
        mRow[2] *= a[2];
        mRow[3] *= a[3];
        return *this;
    }
#endif

    template <typename Scalar>
    template <typename Scalar2> 
    FORCEINLINE
    void Matrix4x4<Scalar>::setValue(const Scalar2* v)
    {
        mRow[0] = Vector4<Scalar>(Scalar(v[0]), Scalar(v[4]), Scalar(v[8]), Scalar(v[12])); 
        mRow[1] = Vector4<Scalar>(Scalar(v[1]), Scalar(v[5]), Scalar(v[9]), Scalar(v[13])); 
        mRow[2] = Vector4<Scalar>(Scalar(v[2]), Scalar(v[6]), Scalar(v[10]), Scalar(v[14]));
        mRow[3] = Vector4<Scalar>(Scalar(v[3]), Scalar(v[7]), Scalar(v[11]), Scalar(v[15])); 
    }  

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setColumns(const Vector3<Scalar>& c0, const Vector3<Scalar>& c1, const Vector3<Scalar>& c2, const Vector3<Scalar>& c3)
    {
        mRow[0] = Vector4<Scalar>(c0.x, c1.x, c2.x, c3.x);
        mRow[1] = Vector4<Scalar>(c0.y, c1.y, c2.y, c3.y);
        mRow[2] = Vector4<Scalar>(c0.z, c1.z, c2.z, c3.z);
        mRow[3] = Unit<3>();
    }
   
    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setColumns(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2, const Vector4<Scalar>& c3)
    {
        mRow[0] = Vector4<Scalar>(c0.x, c1.x, c2.x, c3.x);
        mRow[1] = Vector4<Scalar>(c0.y, c1.y, c2.y, c3.y);
        mRow[2] = Vector4<Scalar>(c0.z, c1.z, c2.z, c3.z);
        mRow[3] = Vector4<Scalar>(c0.w, c1.w, c2.w, c3.w);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setRows(const Vector4<Scalar>& r0, const Vector4<Scalar>& r1, const Vector4<Scalar>& r2, const Vector4<Scalar>& r3)
    {
        mRow[0] = r0;
        mRow[1] = r1;
        mRow[2] = r2;
        mRow[3] = r3;
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
    void Matrix4x4<Scalar>::setColumn(int j, const Vector3<Scalar>& v)
    {
        mRow[0][j] = v.x;
        mRow[1][j] = v.y;
        mRow[2][j] = v.z;
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setColumn(int j, const Vector4<Scalar>& v)
    {
        mRow[0][j] = v.x;
        mRow[1][j] = v.y;
        mRow[2][j] = v.z;
        mRow[3][j] = v.w;
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setRow(int i, const Vector3<Scalar>& v)
    {
        mRow[i] = Vector4<Scalar>(v, mRow[i].w);
    }

    template <typename Scalar>
    FORCEINLINE 
    void Matrix4x4<Scalar>::setRow(int i, const Vector4<Scalar>& v)
    {
        mRow[i] = v;
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
    Matrix4x4<Scalar> operator-(const Matrix4x4<Scalar>& a)
    {
        return Matrix4x4<Scalar>(-a[0],
                                 -a[1],
                                 -a[2],
                                 -a[3]);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT>
    operator+(const Matrix4x4<Scalar1>& a, const Matrix4x4<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix4x4<RT>(a[0] + b[0],
                             a[1] + b[1],
                             a[2] + b[2],
                             a[3] + b[3]);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT>
    operator-(const Matrix4x4<Scalar1>& a, const Matrix4x4<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix4x4<RT>(a[0] - b[0],
                             a[1] - b[1],
                             a[2] - b[2],
                             a[3] - b[3]);
    }

#if USE_MATRIX_COMP_MULT
  
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT>
    operator*(const Matrix4x4<Scalar1>& a, const Matrix4x4<Scalar2>& b)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix4x4<RT>(a[0] * b[0],
                             a[1] * b[1],
                             a[2] * b[2],
                             a[3] * b[3]);
    }

#endif

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT>
    operator*(const Matrix4x4<Scalar1>& a, Scalar2 s)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT;
        return Matrix4x4<RT>(a[0] * s,
                             a[1] * s,
                             a[2] * s,
                             a[3] * s);
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT>
    operator*(Scalar1 s, const Matrix4x4<Scalar2>& a)
    {
        return a * s;
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Matrix4x4<typename Promote<Scalar1, Scalar2>::RT>
    operator/(const Matrix4x4<Scalar1>& a, Scalar2 s)
    {
        ASSERT(!iszero(s));
        return a * (Scalar2(1) / s);
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
        return a[i];
    }  

    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> column(const Matrix4x4<Scalar>& a, int j)
    {
        return Vector4<Scalar>(a[0][j], a[1][j], a[2][j], a[3][j]);
    }  
    
    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> basis(const Matrix4x4<Scalar>& a)
    {
        return Matrix3x3<Scalar>(a[0][0], a[0][1], a[0][2],
                                 a[1][0], a[1][1], a[1][2],
                                 a[2][0], a[2][1], a[2][2]);
    }
     
    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> origin(const Matrix4x4<Scalar>& a)
    {
        return Vector3<Scalar>(a[0][3], 
                               a[1][3], 
                               a[2][3]);
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
        return is;
    }

#endif


    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> mul(const Matrix4x4<Scalar>& a, const Vector4<Scalar>& v)
    {
        return Vector4<Scalar>(dot(a[0], v),
                               dot(a[1], v),
                               dot(a[2], v),
                               dot(a[3], v));
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector4<Scalar> mul(const Vector4<Scalar>& v, const Matrix4x4<Scalar>& a)
    {
        return v.x * a[0] + v.y * a[1] + v.z * a[2] + v.w * a[3];
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> mul(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b)
    {
        return Matrix4x4<Scalar>(mul(a[0], b),
                                 mul(a[1], b),
                                 mul(a[2], b),
                                 mul(a[3], b));
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x4<Scalar> mul(const Matrix4x3<Scalar>& a, const Matrix3x4<Scalar>& b)
    {
        return Matrix4x4<Scalar>(mul(a[0], b),
                                 mul(a[1], b),
                                 mul(a[2], b),
                                 mul(a[3], b));
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix3x4<Scalar> mul(const Matrix3x4<Scalar>& a, const Matrix4x4<Scalar>& b)
    {
        return Matrix3x4<Scalar>(mul(a[0], b),
                                 mul(a[1], b),
                                 mul(a[2], b));
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar> mul(const Matrix4x4<Scalar>& a, const Matrix4x3<Scalar>& b)
    {
        return Matrix4x3<Scalar>(mul(a[0], b),
                                 mul(a[1], b),
                                 mul(a[2], b),
                                 mul(a[3], b));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> transposeMul(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b)
    {
        return Matrix4x4<Scalar>(mul(column(a, 0), b),
                                 mul(column(a, 1), b),
                                 mul(column(a, 2), b),
                                 mul(column(a, 3), b));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> transposeMul(const Matrix3x4<Scalar>& a, const Matrix3x4<Scalar>& b)
    {
        return Matrix4x4<Scalar>(mul(column(a, 0), b),
                                 mul(column(a, 1), b),
                                 mul(column(a, 2), b),
                                 mul(column(a, 3), b));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar> transposeMul(const Matrix4x3<Scalar>& a, const Matrix4x4<Scalar>& b)
    {
        return Matrix3x4<Scalar>(mul(column(a, 0), b),
                                 mul(column(a, 1), b),
                                 mul(column(a, 2), b));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x3<Scalar> transposeMul(const Matrix4x4<Scalar>& a, const Matrix4x3<Scalar>& b)
    {
        return Matrix4x3<Scalar>(mul(column(a, 0), b),
                                 mul(column(a, 1), b),
                                 mul(column(a, 2), b),
                                 mul(column(a, 3), b));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> mulTranspose(const Matrix4x4<Scalar>& a, const Matrix4x4<Scalar>& b)
    {
        return Matrix4x4<Scalar>(mul(b, a[0]),
                                 mul(b, a[1]),
                                 mul(b, a[2]),
                                 mul(b, a[3]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> mulTranspose(const Matrix4x3<Scalar>& a, const Matrix4x3<Scalar>& b)
    {
        return Matrix4x4<Scalar>(mul(b, a[0]),
                                 mul(b, a[1]),
                                 mul(b, a[2]),
                                 mul(b, a[3]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar> mulTranspose(const Matrix3x4<Scalar>& a, const Matrix4x4<Scalar>& b)
    {
        return Matrix3x4<Scalar>(mul(b, a[0]),
                                 mul(b, a[1]),
                                 mul(b, a[2]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x3<Scalar> mulTranspose(const Matrix4x4<Scalar>& a, const Matrix3x4<Scalar>& b)
    {
        return Matrix4x3<Scalar>(mul(b, a[0]),
                                 mul(b, a[1]),
                                 mul(b, a[2]),
                                 mul(b, a[3]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> transpose(const Matrix4x4<Scalar>& a)
    {
        return Matrix4x4<Scalar>(column(a, 0), column(a, 1), column(a, 2), column(a, 3));
    } 

    template <typename Scalar>
    FORCEINLINE
    Matrix4x4<Scalar> adjoint(const Matrix4x4<Scalar>& a)
    {
        // From: Streaming SIMD Extensions - Inverse of 4x4 Matrix, Intel

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
    Scalar determinant(const Matrix4x4<Scalar>& a)
    {
        // From: Streaming SIMD Extensions - Inverse of 4x4 Matrix, Intel

        Scalar tmp[12]; /* temp array for pairs */

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

        Scalar cof[4];

        /* calculate first 4 cofactors */
        cof[0] = (tmp[0] - tmp[1]) * a[1][1] + (tmp[3] - tmp[2]) * a[2][1] + (tmp[4] - tmp[5]) * a[3][1];
        cof[1] = (tmp[1] - tmp[0]) * a[0][1] + (tmp[6] - tmp[7]) * a[2][1] + (tmp[9] - tmp[8]) * a[3][1];
        cof[2] = (tmp[2] - tmp[3]) * a[0][1] + (tmp[7] - tmp[6]) * a[1][1] + (tmp[10] - tmp[11]) * a[3][1];
        cof[3] = (tmp[5] - tmp[4]) * a[0][1] + (tmp[8] - tmp[9]) * a[1][1] + (tmp[11] - tmp[10]) * a[2][1];

        /* calculate determinant */
        return a[0][0] * cof[0] + a[1][0] * cof[1] + a[2][0] * cof[2] + a[3][0] * cof[3];
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> inverse(const Matrix4x4<Scalar>& a)
    {
        // From: Streaming SIMD Extensions - Inverse of 4x4 Matrix, Intel
        
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

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> frustum(Scalar left, Scalar right, Scalar bottom, Scalar top, Scalar zNear, Scalar zFar)
    {
        Scalar oneOverWidth = Scalar(1) / (right - left);
        Scalar oneOverHeight = Scalar(1) / (top - bottom); 
        Scalar oneOverDepth = Scalar(1) / (zNear - zFar);
        return Matrix4x4<Scalar>(Vector4<Scalar>(zNear * Scalar(2) * oneOverWidth, Scalar(), (right + left) * oneOverWidth),
                                 Vector4<Scalar>(Scalar(), zNear * Scalar(2) * oneOverHeight, (top + bottom) * oneOverHeight),
                                 Vector4<Scalar>(Scalar(), Scalar(), (zNear + zFar) * oneOverDepth, zNear * zFar * Scalar(2) * oneOverDepth),
                                 Vector4<Scalar>(Scalar(), Scalar(), Scalar(-1)));
    }

    template <typename Scalar1, typename Scalar2> 
    FORCEINLINE 
    void convert(Scalar1* v, const Matrix4x4<Scalar2>& a)
    {
        v[0] = Scalar1(a[0][0]); v[4] = Scalar1(a[0][1]); v[8] = Scalar1(a[0][2]); v[12] = Scalar1(a[0][3]); 
        v[1] = Scalar1(a[1][0]); v[5] = Scalar1(a[1][1]); v[9] = Scalar1(a[1][2]); v[13] = Scalar1(a[1][3]); 
        v[2] = Scalar1(a[2][0]); v[6] = Scalar1(a[2][1]); v[10] = Scalar1(a[2][2]); v[14] = Scalar1(a[2][3]);  
        v[3] = Scalar1(a[3][0]); v[7] = Scalar1(a[3][1]); v[11] = Scalar1(a[3][2]); v[15] = Scalar1(a[3][3]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> lquat(const Vector4<Scalar>& q)
    {
        return Matrix4x4<Scalar>(Vector4<Scalar>( q.w, -q.z,  q.y, q.x),
                                 Vector4<Scalar>( q.z,  q.w, -q.x, q.y),
                                 Vector4<Scalar>(-q.y,  q.x,  q.w, q.z),
                                 Vector4<Scalar>(-q.x, -q.y, -q.z, q.w));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> rquat(const Vector4<Scalar>& q)
    {
        return Matrix4x4<Scalar>(Vector4<Scalar>( q.w,  q.z, -q.y, q.x),
                                 Vector4<Scalar>(-q.z,  q.w,  q.x, q.y),
                                 Vector4<Scalar>( q.y, -q.x,  q.w, q.z),
                                 Vector4<Scalar>(-q.x, -q.y, -q.z, q.w));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x4<Scalar> dyad(const Vector4<Scalar>& v1, const Vector4<Scalar>& v2)
    {
        return Matrix4x4<Scalar>(Vector4<Scalar>(v1.x * v2.x, v1.x * v2.y, v1.x * v2.z, v1.x * v2.w), 
                                 Vector4<Scalar>(v1.y * v2.x, v1.y * v2.y, v1.y * v2.z, v1.y * v2.w), 
                                 Vector4<Scalar>(v1.z * v2.x, v1.z * v2.y, v1.z * v2.z, v1.z * v2.w),
                                 Vector4<Scalar>(v1.w * v2.x, v1.w * v2.y, v1.w * v2.z, v1.w * v2.w));
    }

}

namespace guts
{
    template <> struct TypeTraits<mt::Matrix4x4<float> > { enum { ID = TT_FLOAT4 | TT_4 }; };
    template <> struct TypeTraits<mt::Matrix4x4<double> > { enum { ID = TT_DOUBLE4 | TT_4 }; };
}

#if USE_SSE
#include <moto/Matrix4x4_SSE.hpp>
#endif

#endif
