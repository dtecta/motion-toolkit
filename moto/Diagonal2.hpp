/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_DIAGONAL2_HPP
#define MT_DIAGONAL2_HPP

#include <moto/Vector2.hpp>
#include <moto/Algebra.hpp>

namespace mt
{
    template <typename Scalar>
    class Diagonal2
    {
    public:
        typedef Scalar ScalarType;
        
        Diagonal2();
        Diagonal2(Scalar a00, Scalar a11); 
        Diagonal2(Zero);
        Diagonal2(Identity);
        Diagonal2(Scalar s);
        template <typename Scalar2> explicit Diagonal2(const Scalar2* v);
        
        operator const Scalar*() const;
        operator Scalar*();
        
        Diagonal2<Scalar>& operator=(Zero);
        Diagonal2<Scalar>& operator+=(Zero);
        Diagonal2<Scalar>& operator-=(Zero);
        
        Diagonal2<Scalar>& operator=(Identity);
        
        Diagonal2<Scalar>& operator=(const Diagonal2<Scalar>& d);
        Diagonal2<Scalar>& operator+=(const Diagonal2<Scalar>& d);
        Diagonal2<Scalar>& operator-=(const Diagonal2<Scalar>& d);       
        
        
        Diagonal2<Scalar>& operator=(Scalar s);
        Diagonal2<Scalar>& operator*=(Scalar s);
        Diagonal2<Scalar>& operator/=(Scalar s);
                
        void setValue(Scalar a00, Scalar a11);       
        template <typename Scalar2> void setValue(const Scalar2* v); 
  
        Scalar x, y;
    };

#ifdef USE_OSTREAM
   
    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Diagonal2<Scalar>& d);
     
#endif

    template <typename Scalar> bool operator==(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2);
   
    template <typename Scalar> Diagonal2<Scalar> operator+(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2);
    template <typename Scalar> Diagonal2<Scalar> operator-(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2);
    template <typename Scalar> Diagonal2<Scalar> operator-(const Diagonal2<Scalar>& d);
    template <typename Scalar> Diagonal2<Scalar> operator*(const Diagonal2<Scalar>& d, Scalar s);
    template <typename Scalar> Diagonal2<Scalar> operator*(Scalar s, const Diagonal2<Scalar>& d);
    template <typename Scalar> Diagonal2<Scalar> operator/(const Diagonal2<Scalar>& d, Scalar s);

    template <typename Scalar> Vector2<Scalar> mul(const Diagonal2<Scalar>& d, const Vector2<Scalar>& v);
    template <typename Scalar> Vector2<Scalar> mul(const Vector2<Scalar>& v, const Diagonal2<Scalar>& d);

    template <typename Scalar> Diagonal2<Scalar> mul(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2);

    template <typename Scalar> Diagonal2<Scalar> tmul(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2);
    template <typename Scalar> Diagonal2<Scalar> mult(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2);

    template <typename Scalar> Scalar determinant(const Diagonal2<Scalar>& d);
    template <typename Scalar> Diagonal2<Scalar> abs(const Diagonal2<Scalar>& d);
    template <typename Scalar> const Diagonal2<Scalar>& transpose(const Diagonal2<Scalar>& d);
    template <typename Scalar> Diagonal2<Scalar> adjoint(const Diagonal2<Scalar>& d);
    template <typename Scalar> Diagonal2<Scalar> inverse(const Diagonal2<Scalar>& d);
    template <typename Scalar> Scalar trace(const Diagonal2<Scalar>& d);  
    
   
    
    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>::Diagonal2() 
    {} 

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>::Diagonal2(Scalar a00, Scalar a11)
    {
        setValue(a00, a11);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>::Diagonal2(Zero)
    {
        setValue(Scalar(), Scalar()); 
    }
        
    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>::Diagonal2(Identity)
    {
        setValue(Scalar(1), Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>::Diagonal2(Scalar s)
    {
        setValue(s, s);
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    Diagonal2<Scalar>::Diagonal2(const Scalar2* v)
    {
        setValue(v);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>::operator const Scalar*() const
    {
        return &x;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>::operator Scalar*()
    {
        return &x;
    }   

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator=(Zero)
    {
        setValue(Scalar(), Scalar());
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator+=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator-=(Zero)
    {
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator=(Identity)
    {
        setValue(Scalar(1), Scalar(1));
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator=(const Diagonal2<Scalar>& d)
    {
        x = d[0]; 
        y = d[1]; 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator+=(const Diagonal2<Scalar>& d)
    {
        x += d[0]; 
        y += d[1]; 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator-=(const Diagonal2<Scalar>& d)
    {
        x -= d[0]; 
        y -= d[1]; 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator=(Scalar s)
    {
        setValue(s, s);
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator*=(Scalar s)
    {
        x *= s; 
        y *= s; 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar>& Diagonal2<Scalar>::operator/=(Scalar s)
    {
        ASSERT(!iszero(s));
        return *this *= Scalar(1) / s;
    }

    template <typename Scalar>
    FORCEINLINE 
    void Diagonal2<Scalar>::setValue(Scalar a00, Scalar a11)
    {
        x = a00; 
        y = a11; 
    }
         
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE 
    void Diagonal2<Scalar>::setValue(const Scalar2* v)
    {
        setValue(v[0], v[1]); 
    }
                        
   
    
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Diagonal2<Scalar>& d)
    {
        return os << "diag(" << d[0] << ", " <<  d[1] << ')';
    }

#endif

    template <typename Scalar>
    FORCEINLINE 
    bool operator==(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2)
    {
        return d1[0] == d2[0] && d1[1] == d2[1];
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> operator+(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2)
    {
        return Diagonal2<Scalar>(d1[0] + d2[0], d1[1] + d2[1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> operator-(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2)
    {
        return Diagonal2<Scalar>(d1[0] - d2[0], d1[1] - d2[1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> operator-(const Diagonal2<Scalar>& d)
    {
        return Diagonal2<Scalar>(-d[0], -d[1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> operator*(const Diagonal2<Scalar>& d, Scalar s)
    {
        return Diagonal2<Scalar>(d[0] * s, d[1] * s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> operator*(Scalar s, const Diagonal2<Scalar>& d)
    {
        return d * s;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> operator/(const Diagonal2<Scalar>& d, Scalar s)
    {
        ASSERT(!iszero(s));
        return d * (Scalar(1) / s);
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector2<Scalar> mul(const Diagonal2<Scalar>& d, const Vector2<Scalar>& v)
    {
        return Vector2<Scalar>(d[0] * v[0], 
                               d[1] * v[1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Vector2<Scalar> mul(const Vector2<Scalar>& v, const Diagonal2<Scalar>& d)
    {
        return d * v;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> mul(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2)
    {
        return Diagonal2<Scalar>(d1[0] * d2[0], 
                                 d1[1] * d2[1]);
    }


    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> tmul(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2)
    {
        return d1 * d2;
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> mult(const Diagonal2<Scalar>& d1, const Diagonal2<Scalar>& d2)
    {
        return d1 * d2;
    } 
      
    template <typename Scalar>
    FORCEINLINE 
    Scalar determinant(const Diagonal2<Scalar>& d)
    {
        return d[0] * d[1];
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> abs(const Diagonal2<Scalar>& d)
    {
        return Diagonal2<Scalar>(abs(d[0]), abs(d[1]));
    }

    template <typename Scalar>
    FORCEINLINE 
    const Diagonal2<Scalar>& transpose(const Diagonal2<Scalar>& d)
    {
        return d;
    }

    template <typename Scalar>
    FORCEINLINE
    Diagonal2<Scalar> adjoint(const Diagonal2<Scalar>& d)
    {
        return Diagonal2<Scalar>(d[1], d[0]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Diagonal2<Scalar> inverse(const Diagonal2<Scalar>& d)
    {
        ASSERT(!iszero(determinant(d)));
        return Diagonal2<Scalar>(Scalar(1) / d[0], Scalar(1) / d[1]);
    }

    template <typename Scalar>
    FORCEINLINE 
    Scalar trace(const Diagonal2<Scalar>& d)
    {
        return d[0] + d[1];
    }
}

#endif
