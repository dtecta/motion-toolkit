/*  MoTo - Motion Toolkit
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_DIAGONAL3_HPP
#define MT_DIAGONAL3_HPP

#include <moto/Vector3.hpp>
#include <moto/Algebra.hpp>

namespace mt
{
    template <typename Scalar>
    class Diagonal3
    {
    public:
        typedef Scalar ScalarType;
        
        Diagonal3();
        Diagonal3(Scalar a00, Scalar a11, Scalar a22); 
        Diagonal3(Zero);
        Diagonal3(Identity);
        Diagonal3(Scalar s);
        template <typename Scalar2> explicit Diagonal3(const Scalar2* v);
        
        operator const Scalar*() const;
        operator Scalar*();
        
        Diagonal3<Scalar>& operator=(Zero);
        Diagonal3<Scalar>& operator+=(Zero);
        Diagonal3<Scalar>& operator-=(Zero);
        
        Diagonal3<Scalar>& operator=(Identity);
              
        Diagonal3<Scalar>& operator=(const Diagonal3<Scalar>& d);
        Diagonal3<Scalar>& operator+=(const Diagonal3<Scalar>& d);
        Diagonal3<Scalar>& operator-=(const Diagonal3<Scalar>& d);
         
        Diagonal3<Scalar>& operator=(Scalar s);
        Diagonal3<Scalar>& operator*=(Scalar s);
        Diagonal3<Scalar>& operator/=(Scalar s);
        
              
        void setValue(Scalar a00, Scalar a11, Scalar a22);       
        template <typename Scalar2> void setValue(const Scalar2* v); 
    
        Scalar x, y, z;
    };

#ifdef USE_OSTREAM
   
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Diagonal3<Scalar>& d);
     
#endif

    template <typename Scalar> bool operator==(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2);

    template <typename Scalar> Diagonal3<Scalar> operator+(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2);
    template <typename Scalar> Diagonal3<Scalar> operator-(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2);
    template <typename Scalar> Diagonal3<Scalar> operator-(const Diagonal3<Scalar>& d);
    template <typename Scalar> Diagonal3<Scalar> operator*(const Diagonal3<Scalar>& d, Scalar s);
    template <typename Scalar> Diagonal3<Scalar> operator*(Scalar s, const Diagonal3<Scalar>& d);
    template <typename Scalar> Diagonal3<Scalar> operator/(const Diagonal3<Scalar>& d, Scalar s);

    template <typename Scalar> Vector3<Scalar> mul(const Diagonal3<Scalar>& d, const Vector3<Scalar>& v);
    template <typename Scalar> Vector3<Scalar> mul(const Vector3<Scalar>& v, const Diagonal3<Scalar>& d);

    template <typename Scalar> Diagonal3<Scalar> mul(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2);
    template <typename Scalar> Diagonal3<Scalar> transposeMul(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2);
    template <typename Scalar> Diagonal3<Scalar> mulTranspose(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2);

    template <typename Scalar> Scalar determinant(const Diagonal3<Scalar>& d);
    template <typename Scalar> Diagonal3<Scalar> abs(const Diagonal3<Scalar>& d);
    template <typename Scalar> const Diagonal3<Scalar>& transpose(const Diagonal3<Scalar>& d);
    template <typename Scalar> Diagonal3<Scalar> adjoint(const Diagonal3<Scalar>& d);
    template <typename Scalar> Diagonal3<Scalar> inverse(const Diagonal3<Scalar>& d);
    template <typename Scalar> Scalar trace(const Diagonal3<Scalar>& d);  
    
   
    
    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>::Diagonal3() 
    {} 

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>::Diagonal3(Scalar a00, Scalar a11, Scalar a22)
    {
        setValue(a00, a11, a22);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>::Diagonal3(Zero)
    {
        setValue(Scalar(), Scalar(), Scalar());
    }
        
    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>::Diagonal3(Identity)
    {
       setValue(Scalar(1), Scalar(1), Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>::Diagonal3(Scalar s)
    {
       setValue(s, s, s);
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Diagonal3<Scalar>::Diagonal3(const Scalar2* v)
    {
        setValue(v);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>::operator const Scalar*() const
    {
        return &x;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>::operator Scalar*()
    {
        return &x;
    }   

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator=(Zero)
    {
        setValue(Scalar(), Scalar(), Scalar());
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator+=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator-=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator=(Identity)
    {
        setValue(Scalar(1), Scalar(1), Scalar(1));
        return *this;
    }

   

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator=(const Diagonal3<Scalar>& d)
    {
        x = d[0]; 
        y = d[1]; 
        z = d[2];
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator+=(const Diagonal3<Scalar>& d)
    {
        x += d[0]; 
        y += d[1]; 
        z += d[2];
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator-=(const Diagonal3<Scalar>& d)
    {
        x -= d[0]; 
        y -= d[1]; 
        z -= d[2];
        return *this;
    }


    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator=(Scalar s)
    {
        setValue(s, s, s);
        return *this;
    }

   
  
    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator*=(Scalar s)
    {
        x *= s; 
        y *= s; 
        z *= s;
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar>& Diagonal3<Scalar>::operator/=(Scalar s)
    {
        ASSERT(!iszero(s));
        return *this *= Scalar(1) / s;
    }

   

    template <typename Scalar>
    FORCEINLINE 
    void Diagonal3<Scalar>::setValue(Scalar a00, Scalar a11, Scalar a22)
    {
        x = a00; 
        y = a11; 
        z = a22;
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    void Diagonal3<Scalar>::setValue(const Scalar2* v)
    {
        setValue(Scalar(v[0]), Scalar(v[1]), Scalar(v[2])); 
    }
                        
   
    
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Diagonal3<Scalar>& d)
    {
        return os << "diag(" << d[0] << ", " <<  d[1] << ", " << d[2] << ')';
    }

#endif

    template <typename Scalar>
    FORCEINLINE 
    bool operator==(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2)
    {
        return d1[0] == d2[0] && d1[1] == d2[1] && d1[2] == d2[2];
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> operator+(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2)
    {
        return Diagonal3<Scalar>(d1[0] + d2[0], d1[1] + d2[1], d1[2] + d2[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> operator-(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2)
    {
        return Diagonal3<Scalar>(d1[0] - d2[0], d1[1] - d2[1], d1[2] - d2[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> operator-(const Diagonal3<Scalar>& d)
    {
        return Diagonal3<Scalar>(-d[0], -d[1], -d[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> operator*(const Diagonal3<Scalar>& d, Scalar s)
    {
        return Diagonal3<Scalar>(d[0] * s, d[1] * s, d[2] * s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> operator*(Scalar s, const Diagonal3<Scalar>& d)
    {
        return d * s;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> operator/(const Diagonal3<Scalar>& d, Scalar s)
    {
        ASSERT(!iszero(s));
        return d * (Scalar(1) / s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> mul(const Diagonal3<Scalar>& d, const Vector3<Scalar>& v)
    {
        return Vector3<Scalar>(d[0] * v[0], 
                               d[1] * v[1], 
                               d[2] * v[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector3<Scalar> mul(const Vector3<Scalar>& v, const Diagonal3<Scalar>& d)
    {
        return mul(d, v);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> mul(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2)
    {
        return Diagonal3<Scalar>(d1[0] * d2[0], 
                                 d1[1] * d2[1], 
                                 d1[2] * d2[2]);
    }


    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> transposeMul(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2)
    {
        return mul(d1, d2);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> mulTranspose(const Diagonal3<Scalar>& d1, const Diagonal3<Scalar>& d2)
    {
        return mul(d1, d2);
    } 
      
    template <typename Scalar>
    FORCEINLINE 
    Scalar determinant(const Diagonal3<Scalar>& d)
    {
        return d[0] * d[1] * d[2];
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> abs(const Diagonal3<Scalar>& d)
    {
        return Diagonal3<Scalar>(abs(d[0]), abs(d[1]), abs(d[2]));
    }

    template <typename Scalar>
    FORCEINLINE 
    const Diagonal3<Scalar>& transpose(const Diagonal3<Scalar>& d)
    {
        return d;
    }

    template <typename Scalar>
    FORCEINLINE
    Diagonal3<Scalar> adjoint(const Diagonal3<Scalar>& d)
    {
        return Diagonal3<Scalar>(d[1] * d[2], d[0] * d[2], d[0] * d[1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal3<Scalar> inverse(const Diagonal3<Scalar>& d)
    {
        ASSERT(!iszero(determinant(d)));
        return Diagonal3<Scalar>(Scalar(1) / d[0], Scalar(1) / d[1], Scalar(1) / d[2]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Scalar trace(const Diagonal3<Scalar>& d)
    {
        return d[0] + d[1] + d[2];
    }
}

#endif
