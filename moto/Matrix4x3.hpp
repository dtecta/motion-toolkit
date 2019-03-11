/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_MATRIX4X3_HPP
#define MT_MATRIX4X3_HPP

#include <guts/TypeTraits.hpp>

#include <moto/Matrix3x4.hpp>

namespace mt
{      
    template <typename Scalar>
    class Matrix4x3
    {
    public:
        typedef Scalar ScalarType;

        Matrix4x3();
        Matrix4x3(Identity);
        template <typename Scalar2> explicit Matrix4x3(const Scalar2* v);   
        Matrix4x3(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2);
        Matrix4x3(const Vector3<Scalar>& r0, const Vector3<Scalar>& r1, const Vector3<Scalar>& r2, const Vector3<Scalar>& r3);
        Matrix4x3(const Vector3<Scalar>& p);
        Matrix4x3(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& r3 = Zero());

        operator const Vector3<Scalar>*() const; 
        operator Vector3<Scalar>*();

        Matrix4x3<Scalar>& operator=(Identity);

        template <typename Scalar2> void setValue(const Scalar2* v);  
        void setColumns(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2);
        void setRows(const Vector3<Scalar>& r0, const Vector3<Scalar>& r1, const Vector3<Scalar>& r2, const Vector3<Scalar>& r3);

        void setBasis(const Matrix3x3<Scalar>& basis);

        void setColumn(int j, const Vector4<Scalar>& v);

        void setRow(int i, const Vector3<Scalar>& v);

    private:
        Vector3<Scalar> mRow[4];
    }; 

    template <typename Scalar> bool operator==(const Matrix4x3<Scalar>& a, const Matrix4x3<Scalar>& b);

    template <typename Scalar> const Vector3<Scalar>& row(const Matrix4x3<Scalar>& a, int i);
    template <typename Scalar> Vector4<Scalar> column(const Matrix4x3<Scalar>& a, int j);
    template <typename Scalar> Matrix3x3<Scalar> basis(const Matrix4x3<Scalar>& a);


#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix4x3<Scalar>& a);

#endif

#ifdef USE_ISTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix4x3<Scalar>& a);

#endif

    template <typename Scalar> Vector4<Scalar> mul(const Matrix4x3<Scalar>& a, const Vector3<Scalar>& v);
    template <typename Scalar> Vector3<Scalar> mul(const Vector4<Scalar>& v, const Matrix4x3<Scalar>& a);

    template <typename Scalar> Matrix3x3<Scalar> mul(const Matrix3x4<Scalar>& a, const Matrix4x3<Scalar>& b);
    template <typename Scalar> Matrix4x3<Scalar> mul(const Matrix4x3<Scalar>& a, const Matrix3x3<Scalar>& b);

    template <typename Scalar> Matrix3x3<Scalar> transposeMul(const Matrix4x3<Scalar>& a, const Matrix4x3<Scalar>& b);
    template <typename Scalar> Matrix3x3<Scalar> mulTranspose(const Matrix3x4<Scalar>& a, const Matrix3x4<Scalar>& b);

    template <typename Scalar> Matrix3x4<Scalar> transpose(const Matrix4x3<Scalar>& a);
    template <typename Scalar> Matrix4x3<Scalar> transpose(const Matrix3x4<Scalar>& a);


    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>::Matrix4x3()
    {} 

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>::Matrix4x3(Identity)
    {
        *this = Identity();
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Matrix4x3<Scalar>::Matrix4x3(const Scalar2* v)
    {
        setValue(v);
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>::Matrix4x3(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2)
    {
        setColumns(c0, c1, c2);
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>::Matrix4x3(const Vector3<Scalar>& r0, const Vector3<Scalar>& r1, const Vector3<Scalar>& r2, const Vector3<Scalar>& r3)
    {
        setRows(r0, r1, r2, r3);
    }
   
    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>::Matrix4x3(const Vector3<Scalar>& p)
    {
        mRow[0] = Vector3<Scalar>(Unit<0>());
        mRow[1] = Vector3<Scalar>(Unit<1>());
        mRow[2] = Vector3<Scalar>(Unit<2>());
        mRow[3] = p;
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>::Matrix4x3(const Matrix3x3<Scalar>& a, const Vector3<Scalar>& r3)
    {
        mRow[0] = a[0];
        mRow[1] = a[1];
        mRow[2] = a[2];
        mRow[3] = r3;
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>::operator const Vector3<Scalar>*() const
    {
        return mRow;
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>::operator Vector3<Scalar>*()
    {
        return mRow;
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar>& Matrix4x3<Scalar>::operator=(Identity)
    {
        mRow[0] = Unit<0>();
        mRow[1] = Unit<1>();
        mRow[2] = Unit<2>();
        mRow[3] = Zero();
        return *this;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    void Matrix4x3<Scalar>::setValue(const Scalar2* v)
    {
        mRow[0] = Vector3<Scalar>(Scalar(v[0]), Scalar(v[4]), Scalar(v[8]));
        mRow[1] = Vector3<Scalar>(Scalar(v[1]), Scalar(v[5]), Scalar(v[9]));
        mRow[2] = Vector3<Scalar>(Scalar(v[2]), Scalar(v[6]), Scalar(v[10]));
        mRow[3] = Vector3<Scalar>(Scalar(v[3]), Scalar(v[7]), Scalar(v[11]));
    }

    template <typename Scalar>
    FORCEINLINE
    void Matrix4x3<Scalar>::setColumns(const Vector4<Scalar>& c0, const Vector4<Scalar>& c1, const Vector4<Scalar>& c2)
    {
        mRow[0] = Vector3<Scalar>(c0.x, c1.x, c2.x);
        mRow[1] = Vector3<Scalar>(c0.y, c1.y, c2.y);
        mRow[2] = Vector3<Scalar>(c0.z, c1.z, c2.z);
        mRow[3] = Vector3<Scalar>(c0.w, c1.w, c2.w);
    }

    template <typename Scalar>
    FORCEINLINE
    void Matrix4x3<Scalar>::setRows(const Vector3<Scalar>& r0, const Vector3<Scalar>& r1, const Vector3<Scalar>& r2, const Vector3<Scalar>& r3)
    {
        mRow[0] = r0;
        mRow[1] = r1;
        mRow[2] = r2;
        mRow[3] = r3;
    }

    template <typename Scalar>
    FORCEINLINE
    void Matrix4x3<Scalar>::setBasis(const Matrix3x3<Scalar>& a)
    {
        setRow(0, a[0]);
        setRow(1, a[1]);
        setRow(2, a[2]);
    }

    template <typename Scalar>
    FORCEINLINE
    void Matrix4x3<Scalar>::setColumn(int j, const Vector4<Scalar>& v)
    {
        mRow[0][j] = v.x;
        mRow[1][j] = v.y;
        mRow[2][j] = v.z;
        mRow[3][j] = v.w;
    }

    template <typename Scalar>
    FORCEINLINE
    void Matrix4x3<Scalar>::setRow(int i, const Vector3<Scalar>& v)
    {
        mRow[i] = v;
    }

    template <typename Scalar> 
    FORCEINLINE
    bool operator==(const Matrix4x3<Scalar>& a, const Matrix4x3<Scalar>& b)
    {
        return all(a[0] == b[0]) &&
               all(a[1] == b[1]) &&
               all(a[2] == b[2]) &&
               all(a[3] == b[3]);
    }

    template <typename Scalar>
    FORCEINLINE
    const Vector3<Scalar>& row(const Matrix4x3<Scalar>& a, int i)
    {
        return a[i];
    }

    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> column(const Matrix4x3<Scalar>& a, int j)
    {
        return Vector4<Scalar>(a[0][j], a[1][j], a[2][j], a[3][j]);
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix3x3<Scalar> basis(const Matrix4x3<Scalar>& a)
    {
        return Matrix3x3<Scalar>(a[0][0], a[0][1], a[0][2],
                                 a[1][0], a[1][1], a[1][2],
                                 a[2][0], a[2][1], a[2][2]);
    }

#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Matrix4x3<Scalar>& a)
    {
        return os << ' ' << row(a, 0) << ' ' << row(a, 1) << ' ' << row(a, 2) << ' ' << row(a, 3);
    }

#endif

#ifdef USE_ISTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& is, Matrix4x3<Scalar>& a)
    {
        is >> a[0] >> a[1] >> a[2] >> a[3];
        return is;
    }

#endif


    template <typename Scalar>
    FORCEINLINE
    Vector4<Scalar> mul(const Matrix4x3<Scalar>& a, const Vector3<Scalar>& v)
    {
        return Vector4<Scalar>(dot(a[0], v),
                               dot(a[1], v),
                               dot(a[2], v),
                               dot(a[3], v));
    }

    template <typename Scalar>
    FORCEINLINE
    Vector3<Scalar> mul(const Vector4<Scalar>& v, const Matrix4x3<Scalar>& a)
    {
        return v.x * a[0] + v.y * a[1] + v.z * a[2] + v.w * a[3];
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix3x3<Scalar> mul(const Matrix3x4<Scalar>& a, const Matrix4x3<Scalar>& b)
    {
        return Matrix3x3<Scalar>(mul(a[0], b),
                                 mul(a[1], b),
                                 mul(a[2], b));
    }

    template <typename Scalar>
    FORCEINLINE
    Matrix4x3<Scalar> mul(const Matrix4x3<Scalar>& a, const Matrix3x3<Scalar>& b)
    {
        return Matrix4x3<Scalar>(mul(a[0], b),
                                 mul(a[1], b),
                                 mul(a[2], b),
                                 mul(a[3], b));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> transposeMul(const Matrix4x3<Scalar>& a, const Matrix4x3<Scalar>& b)
    {
        return Matrix3x3<Scalar>(mul(column(a, 0), b),
                                 mul(column(a, 1), b),
                                 mul(column(a, 2), b));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x3<Scalar> mulTranspose(const Matrix3x4<Scalar>& a, const Matrix3x4<Scalar>& b)
    {
        return Matrix3x3<Scalar>(mul(b, a[0]),
                                 mul(b, a[1]),
                                 mul(b, a[2]));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix3x4<Scalar> transpose(const Matrix4x3<Scalar>& a)
    {
        return Matrix3x4<Scalar>(a[0], a[1], a[2], a[3]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x3<Scalar> transpose(const Matrix3x4<Scalar>& a)
    {
        return Matrix3x4<Scalar>(a[0], a[1], a[2]);
    } 

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x3<Scalar> lquat4x3(const Vector4<Scalar>& q)
    {
        return Matrix4x3<Scalar>(Vector3<Scalar>( q.w, -q.z,  q.y),
                                 Vector3<Scalar>( q.z,  q.w, -q.x),
                                 Vector3<Scalar>(-q.y,  q.x,  q.w),
                                 Vector3<Scalar>(-q.x, -q.y, -q.z));
    }

    template <typename Scalar>
    FORCEINLINE 
    Matrix4x3<Scalar> rquat4x3(const Vector4<Scalar>& q)
    {
        return Matrix4x3<Scalar>(Vector3<Scalar>( q.w,  q.z, -q.y),
                                 Vector3<Scalar>(-q.z,  q.w,  q.x),
                                 Vector3<Scalar>( q.y, -q.x,  q.w),
                                 Vector3<Scalar>(-q.x, -q.y, -q.z));
    }

}

namespace guts
{
    template <> struct TypeTraits<mt::Matrix4x3<float> > { enum { ID = TT_FLOAT3 | TT_4 }; };
    template <> struct TypeTraits<mt::Matrix4x3<double> > { enum { ID = TT_DOUBLE3 | TT_4 }; };
}

#endif
