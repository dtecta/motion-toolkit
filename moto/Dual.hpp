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

#ifndef MT_DUAL_HPP
#define MT_DUAL_HPP

#ifdef USE_OSTREAM
#include <ostream>
#endif

#include <moto/Promote.hpp>
#include <moto/Scalar.hpp>
#include <moto/ScalarTraits.hpp>

namespace mt
{
    template <typename Scalar>
    class Dual
    {
    public:
        typedef Scalar ScalarType;
        
        Dual(Scalar real = Scalar(), Scalar dual = Scalar());
        template <typename Scalar2> Dual(const Dual<Scalar2>& rhs);
        
        Scalar real() const;
        Scalar dual() const;
  
        Dual<Scalar>& operator=(Scalar rhs);
        Dual<Scalar>& operator+=(Scalar rhs); 
        Dual<Scalar>& operator-=(Scalar rhs);  
        Dual<Scalar>& operator*=(Scalar rhs); 
        Dual<Scalar>& operator/=(Scalar rhs);
        
        template <typename Scalar2> Dual<Scalar>& operator=(const Dual<Scalar2>& rhs);
        template <typename Scalar2> Dual<Scalar>& operator+=(const Dual<Scalar2>& rhs);
        template <typename Scalar2> Dual<Scalar>& operator-=(const Dual<Scalar2>& rhs); 
        template <typename Scalar2> Dual<Scalar>& operator*=(const Dual<Scalar2>& rhs);
        template <typename Scalar2> Dual<Scalar>& operator/=(const Dual<Scalar2>& rhs);

    private:
        Scalar mReal;
        Scalar mDual;
    };
        
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Dual<Scalar>& rhs);

#endif  

    template <typename Scalar> bool operator==(const Dual<Scalar>& a, Scalar b);
    template <typename Scalar> bool operator==(Scalar a, const Dual<Scalar>& b);
    template <typename Scalar1, typename Scalar2> bool operator==(const Dual<Scalar1>& a, const Dual<Scalar2>& b);
  
    template <typename Scalar> bool operator<(const Dual<Scalar>& a, Scalar b);
    template <typename Scalar> bool operator<(Scalar a, const Dual<Scalar>& b);
    template <typename Scalar1, typename Scalar2> bool operator<(const Dual<Scalar1>& a, const Dual<Scalar2>& b);
  
    template <typename Scalar> Dual<Scalar> operator-(const Dual<Scalar>& rhs);
    
    template <typename Scalar> Dual<Scalar> operator+(const Dual<Scalar>& lhs, Scalar rhs);
    template <typename Scalar> Dual<Scalar> operator-(const Dual<Scalar>& lhs, Scalar rhs);
    template <typename Scalar> Dual<Scalar> operator*(const Dual<Scalar>& lhs, Scalar rhs);
    template <typename Scalar> Dual<Scalar> operator/(const Dual<Scalar>& lhs, Scalar rhs);

    template <typename Scalar> Dual<Scalar> operator-(Scalar lhs, const Dual<Scalar>& rhs);
    template <typename Scalar> Dual<Scalar> operator+(Scalar lhs, const Dual<Scalar>& rhs);
    template <typename Scalar> Dual<Scalar> operator*(Scalar lhs, const Dual<Scalar>& rhs);
    template <typename Scalar> Dual<Scalar> operator/(Scalar lhs, const Dual<Scalar>& rhs);
     
    template <typename Scalar1, typename Scalar2>
    Dual<typename Promote<Scalar1, Scalar2>::RT> operator+(const Dual<Scalar1>& lhs, const Dual<Scalar2>& rhs);

    template <typename Scalar1, typename Scalar2>
    Dual<typename Promote<Scalar1, Scalar2>::RT> operator-(const Dual<Scalar1>& lhs, const Dual<Scalar2>& rhs);

    template <typename Scalar1, typename Scalar2>
    Dual<typename Promote<Scalar1, Scalar2>::RT> operator*(const Dual<Scalar1>& lhs, const Dual<Scalar2>& rhs);

    template <typename Scalar1, typename Scalar2>
    Dual<typename Promote<Scalar1, Scalar2>::RT> operator/(const Dual<Scalar1>& lhs, const Dual<Scalar2>& rhs);
   
    // This is a convenience function template similar to std::make_pair.
    template <typename Scalar> Dual<Scalar> makeDual(Scalar re, Scalar du);


    // We define generic functions real, dual, and conf... 

    template <typename Element> const Element& real(const Element& x);
    template <typename Element> Zero dual(const Element& x);       
    template <typename Element> const Element& conj(const Element& x); 
    
    //...and specialize them for anything dual.
    template <typename Scalar> Scalar real(const Dual<Scalar>& z); 
    template <typename Scalar> Scalar dual(const Dual<Scalar>& z);  
    template <typename Scalar> Dual<Scalar> conj(const Dual<Scalar>& z);

    template <typename Scalar> Dual<Scalar> acos(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> asin(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> atan(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> atan2(const Dual<Scalar>& y, const Dual<Scalar>& x);
    template <typename Scalar> Dual<Scalar> cos(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> cosh(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> exp(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> log(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> log10(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> pow(const Dual<Scalar>& x, const Dual<Scalar>& y);
    template <typename Scalar> Dual<Scalar> sin(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> sinh(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> sqrt(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> tan(const Dual<Scalar>& z);
    template <typename Scalar> Dual<Scalar> tanh(const Dual<Scalar>& z);

    template <typename Scalar> bool isfinite(const Dual<Scalar>& z);


    // Member functions


    template <typename Scalar>
    FORCEINLINE
    Dual<Scalar>::Dual(Scalar real, Scalar dual)
        : mReal(real)
        , mDual(dual)
    {}
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Dual<Scalar>::Dual(const Dual<Scalar2>& rhs)
        : mReal(rhs.real())
        , mDual(rhs.dual())
    {}
    
    template <typename Scalar>
    FORCEINLINE
    Scalar Dual<Scalar>::real() const
    {
        return mReal;
    }
    
    template <typename Scalar>
    FORCEINLINE
    Scalar Dual<Scalar>::dual() const
    {
        return mDual;
    }

    template <typename Scalar>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator=(Scalar rhs)
    {
        mReal = rhs; 
        mDual = Scalar(); 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator+=(Scalar rhs)
    {
        mReal += rhs; 
        return *this;
    }
    
    template <typename Scalar>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator-=(Scalar rhs)
    {
        mReal -= rhs; 
        return *this;
    } 
    
    template <typename Scalar>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator*=(Scalar rhs)
    {
        mReal *= rhs;
        mDual *= rhs;
        return *this;
    } 
    
    template <typename Scalar>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator/=(Scalar rhs)
    {
        mReal /= rhs;
        mDual /= rhs;
        return *this;
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator=(const Dual<Scalar2>& rhs)
    {
        mReal = rhs.real(); 
        mDual = rhs.dual(); 
        return *this;
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator+=(const Dual<Scalar2>& rhs)
    {
        mReal += rhs.real(); 
        mDual += rhs.dual(); 
        return *this;
    }  
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator-=(const Dual<Scalar2>& rhs)
    {
        mReal -= rhs.real(); 
        mDual -= rhs.dual(); 
        return *this;
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator*=(const Dual<Scalar2>& rhs)
    {
        mDual *= rhs.real();
        mDual += mReal * rhs.dual();
        mReal *= rhs.real(); 
        return *this;
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Dual<Scalar>& Dual<Scalar>::operator/=(const Dual<Scalar2>& rhs)
    {
        mReal /= rhs.real(); 
        mDual -= mReal * rhs.dual();
        mDual /= rhs.real();
        return *this;
    }
    
    
    // Non-member functions
 
    
    
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Dual<Scalar>& rhs)
    {
        return os << rhs.real() << " + \xee " << rhs.dual();
    } 

#endif  

    template <typename Scalar> 
    FORCEINLINE 
    bool operator==(const Dual<Scalar>& a, Scalar b)
    {
        return real(a) == b;
    }
    
    template <typename Scalar> 
    FORCEINLINE
    bool operator==(Scalar a, const Dual<Scalar>& b)
    {
        return a == real(b);
    }

    template <typename Scalar1, typename Scalar2> 
    FORCEINLINE
    bool operator==(const Dual<Scalar1>& a, const Dual<Scalar2>& b)
    {
        return real(a) == real(b);
    }

    template <typename Scalar> 
    FORCEINLINE 
    bool operator<(const Dual<Scalar>& a, Scalar b)
    {
        return real(a) < b;
    }
    
    template <typename Scalar> 
    FORCEINLINE
    bool operator<(Scalar a, const Dual<Scalar>& b)
    {
        return a < real(b);
    }

    template <typename Scalar1, typename Scalar2> 
    FORCEINLINE
    bool operator<(const Dual<Scalar1>& a, const Dual<Scalar2>& b)
    {
        return real(a) < real(b);
    }

    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator-(const Dual<Scalar>& rhs)
    {
        return Dual<Scalar>(-rhs.real(), -rhs.dual());
    } 
    
    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator+(const Dual<Scalar>& lhs, Scalar rhs)
    {
        return Dual<Scalar>(lhs.real() + rhs, lhs.dual());
    }

    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator-(const Dual<Scalar>& lhs, Scalar rhs)
    {
        return Dual<Scalar>(lhs.real() - rhs, lhs.dual());
    }

    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator*(const Dual<Scalar>& lhs, Scalar rhs)
    {
        return Dual<Scalar>(lhs.real() * rhs, lhs.dual() * rhs);
    }

    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator/(const Dual<Scalar>& lhs, Scalar rhs)
    {
        return Dual<Scalar>(lhs.real() / rhs, lhs.dual() / rhs);
    }

    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator+(Scalar lhs, const Dual<Scalar>& rhs)
    {
        return rhs + lhs;
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator-(Scalar lhs, const Dual<Scalar>& rhs)
    {
         return Dual<Scalar>(lhs - rhs.real(), -rhs.dual());
    }
     
    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator*(Scalar lhs, const Dual<Scalar>& rhs)
    {
         return rhs * lhs;
    }
     
    template <typename Scalar>
    FORCEINLINE 
    Dual<Scalar> operator/(Scalar lhs, const Dual<Scalar>& rhs)
    {
        lhs /= rhs.real(); 
        return Dual<Scalar>(lhs, -lhs * rhs.dual() / rhs.real());
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Dual<typename Promote<Scalar1, Scalar2>::RT> operator+(const Dual<Scalar1>& lhs, const Dual<Scalar2>& rhs)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Dual<RT>(lhs.real() + rhs.real(), lhs.dual() + rhs.dual());
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Dual<typename Promote<Scalar1, Scalar2>::RT> operator-(const Dual<Scalar1>& lhs, const Dual<Scalar2>& rhs)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Dual<RT>(lhs.real() - rhs.real(), lhs.dual() - rhs.dual());
    }
    
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Dual<typename Promote<Scalar1, Scalar2>::RT> operator*(const Dual<Scalar1>& lhs, const Dual<Scalar2>& rhs)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Dual<RT>(lhs.real() * rhs.real(), lhs.real() * rhs.dual() + lhs.dual() * rhs.real());
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Dual<typename Promote<Scalar1, Scalar2>::RT> operator/(const Dual<Scalar1>& lhs, const Dual<Scalar2>& rhs)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        RT r = RT(1) / rhs.real();
        RT x = lhs.real() * r;  
        return Dual<RT>(x, (lhs.dual() - x * rhs.dual()) * r);
    }

    template <typename Scalar>
    FORCEINLINE
    Dual<Scalar> makeDual(Scalar re, Scalar du)
    {   
        return Dual<Scalar>(re, du);
    }   

    template <typename Element>
    FORCEINLINE
    const Element& real(const Element& x)
    {   
        return x;
    }  
 
    template <typename Scalar>
    FORCEINLINE
    Scalar real(const Dual<Scalar>& z)
    {   
        return z.real();
    }  
    
    
    template <typename Element>
    FORCEINLINE 
    Zero dual(const Element&)
    {   
        return Zero();
    }   

    template <typename Scalar>
    FORCEINLINE 
    Scalar dual(const Dual<Scalar>& z)
    {   
        return z.dual();
    }   

    template <typename Element> 
    FORCEINLINE    
    const Element& conj(const Element& x)
    {
        return x;
    }   
    
    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> conj(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(z.real(), -z.dual());
    } 
    
    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> acos(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(acos(z.real()), -z.dual() / sqrt(Scalar(1) - z.real() * z.real()));
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> asin(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(asin(z.real()), z.dual() / sqrt(Scalar(1) - z.real() * z.real()));
    }
    
    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> atan(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(atan(z.real()), z.dual() / (Scalar(1) + z.real() * z.real()));
    }
    
    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> atan2(const Dual<Scalar>& y, const Dual<Scalar>& x)
    {
        Dual<Scalar> z = y / x;
        Scalar quadrant = isnegative(x.real()) ? 
                          (isnegative(y.real()) ? -ScalarTraits<Scalar>::pi() : ScalarTraits<Scalar>::pi()) : 
                          Scalar(); 
        return Dual<Scalar>(atan(z.real()) + quadrant, z.dual() / (Scalar(1) + square(z.real())));
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> cos(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(cos(z.real()), -z.dual() * sin(z.real()));
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> cosh(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(cosh(z.real()), z.dual() * sinh(z.real()));
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> exp(const Dual<Scalar>& z)
    {
        Scalar x = exp(z.real());
        return Dual<Scalar>(x, z.dual() * x);
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> log(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(log(z.real()), z.dual() / z.real());
    }
  
    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> log10(const Dual<Scalar>& z)
    {
        return log(z) / log(10);
    }
  
    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> pow(const Dual<Scalar>& x, const Dual<Scalar>& y)
    {
        return exp(log(x) * y);
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> sin(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(sin(z.real()), z.dual() * cos(z.real()));
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> sinh(const Dual<Scalar>& z)
    {
        return Dual<Scalar>(sinh(z.real()), z.dual() * cosh(z.real()));
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> sqrt(const Dual<Scalar>& z)
    {
        Scalar x = sqrt(z.real());
        return Dual<Scalar>(x, z.dual() / (Scalar(2) * x));
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> tan(const Dual<Scalar>& z)
    {
        Scalar x = tan(z.real());
        return Dual<Scalar>(x, z.dual() * (Scalar(1) + x * x));
    }

    template <typename Scalar> 
    FORCEINLINE    
    Dual<Scalar> tanh(const Dual<Scalar>& z)
    {
        Scalar x = tanh(z.real());
        return Dual<Scalar>(x, z.dual() * (Scalar(1) - x * x));
    }

  
     
#ifndef HAVE_TYPEOF

    template <typename Scalar1, typename Scalar2>
    struct Promote<Scalar1, Dual<Scalar2> >
    {
        typedef Dual<typename Promote<Scalar1, Scalar2>::RT> RT;
    }; 
    
    template <typename Scalar1, typename Scalar2>
    struct Promote<Dual<Scalar1>, Dual<Scalar2> >
    {
        typedef Dual<typename Promote<Scalar1, Scalar2>::RT> RT;
    };

#endif 

    template <typename Scalar>
    struct ScalarTraits<Dual<Scalar> >
    {

        // These are all constants and thus have a zero dual part.

        static Dual<Scalar> pi()
        {
            return Dual<Scalar>(ScalarTraits<Scalar>::pi());
        }

        static Dual<Scalar> infinity()
        {
            return Dual<Scalar>(ScalarTraits<Scalar>::infinity());
        }

        static Dual<Scalar> epsilon()
        {
            return Dual<Scalar>(ScalarTraits<Scalar>::epsilon());
        }  

        static Dual<Scalar> max()
        {
            return Dual<Scalar>(ScalarTraits<Scalar>::max());
        }
    };   

    template <typename Scalar>
    bool isfinite(const Dual<Scalar>& z)
    {
        return isfinite(z.real()) && isfinite(z.dual());
    }


}

#endif
