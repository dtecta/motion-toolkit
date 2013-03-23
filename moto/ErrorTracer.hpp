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

#ifndef MT_ERRORTRACER_HPP
#define MT_ERRORTRACER_HPP

#ifdef USE_OSTREAM
#include <ostream>
#endif

#include "Scalar.hpp"

namespace mt
{
    template <typename Scalar> 
    class ErrorTracer {
    public:    
        typedef Scalar Value_type;

        ErrorTracer();
        template <typename Scalar2> explicit ErrorTracer(Scalar2 value); 
        ErrorTracer(Scalar value, Scalar error); 
        
        Scalar value() const;
        Scalar error() const;

        void setError(Scalar error);

        operator Scalar() const;
        
        ErrorTracer<Scalar>& operator=(Scalar value); 
        ErrorTracer<Scalar>& operator+=(const ErrorTracer& x); 
        ErrorTracer<Scalar>& operator-=(const ErrorTracer& x); 
        ErrorTracer<Scalar>& operator*=(const ErrorTracer& x); 
        ErrorTracer<Scalar>& operator/=(const ErrorTracer& x); 
        
    private:
        Scalar mValue; // the value of the scalar
        Scalar mError; // an upper bound for the relative rounding error
    };

// `mError' times the machine epsilon (FLT_EPSILON for floats, DBL_EPSILON for doubles) 
// gives an estimated upper bound for the rounding error in `mValue'.
// The number of dirty bits in the mantissa is `log(mError) / log(2)', so if `mError'
// reaches 2^24 = 16777216 then we used up all bits in the mantissa of a float. 
// Note that the error is a rough upper bound. In reality i386 platforms may 
// evaluate compound expressions in higher precision, so the given machine epsilon
// is usually too large.   

    template <typename Scalar> ErrorTracer<Scalar> operator-(const ErrorTracer<Scalar>& x);
    template <typename Scalar> ErrorTracer<Scalar> operator+(const ErrorTracer<Scalar>& x,  const ErrorTracer<Scalar>& y);
    template <typename Scalar> ErrorTracer<Scalar> operator-(const ErrorTracer<Scalar>& x,  const ErrorTracer<Scalar>& y);
    template <typename Scalar> ErrorTracer<Scalar> operator*(const ErrorTracer<Scalar>& x,  const ErrorTracer<Scalar>& y);
    template <typename Scalar> ErrorTracer<Scalar> operator/(const ErrorTracer<Scalar>& x,  const ErrorTracer<Scalar>& y);
 
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const ErrorTracer<Scalar>& x);
    
#endif

    template <typename Scalar> ErrorTracer<Scalar> sqrt(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> abs(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> cos(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> sin(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> tan(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> acos(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> asin(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> atan(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> atan2(const ErrorTracer<Scalar>& x, const ErrorTracer<Scalar>& y); 
    template <typename Scalar> ErrorTracer<Scalar> exp(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> log(const ErrorTracer<Scalar>& x); 
    template <typename Scalar> ErrorTracer<Scalar> pow(const ErrorTracer<Scalar>& x, const ErrorTracer<Scalar>& y); 

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar>::ErrorTracer() 
        : mValue()
        , mError()
    {}

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    ErrorTracer<Scalar>::ErrorTracer(Scalar2 value) 
        : mValue(Scalar(value))
        , mError() 
    {}

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar>::ErrorTracer(Scalar value, Scalar error) 
        : mValue(value)
        , mError(error) 
    {}

    template <typename Scalar>
    FORCEINLINE
    Scalar ErrorTracer<Scalar>::value() const 
    {
        return mValue; 
    }
    
    template <typename Scalar>
    FORCEINLINE
    Scalar ErrorTracer<Scalar>::error() const
    { 
        return mError; 
    }

    template <typename Scalar>
    FORCEINLINE
    void ErrorTracer<Scalar>::setError(Scalar error)
    { 
        mError = error; 
    }

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar>::operator Scalar() const
    { 
        return mValue; 
    }

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar>& ErrorTracer<Scalar>::operator=(Scalar value) 
    {
        mValue = value;
        mError = Scalar();
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar>& ErrorTracer<Scalar>::operator+=(const ErrorTracer<Scalar>& x) 
    {
        *this = *this + x;
        return *this;
    }
    
    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar>& ErrorTracer<Scalar>::operator-=(const ErrorTracer<Scalar>& x) 
    {
        *this = *this - x;
        return *this;
    }
    
    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar>& ErrorTracer<Scalar>::operator*=(const ErrorTracer<Scalar>& x) 
    {
        *this = *this * x;
        return *this;
    }
    
    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar>& ErrorTracer<Scalar>::operator/=(const ErrorTracer<Scalar>& x) 
    {
        *this = *this / x;
        return *this;
    }


    
    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> operator-(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(-x.value(), 
                                    x.error());
    }
    
    template <typename Scalar>
    FORCEINLINE 
    ErrorTracer<Scalar> operator+(const ErrorTracer<Scalar>& x,  const ErrorTracer<Scalar>& y) 
    {
        Scalar value = x.value() + y.value();
        return ErrorTracer<Scalar>(value, 
                                   !iszero(value) ? (abs(x.value()) * x.error() + abs(y.value()) * y.error()) / abs(value) + Scalar(1) : Scalar());
    }
    
    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> operator-(const ErrorTracer<Scalar>& x, const ErrorTracer<Scalar>& y) 
    {
        Scalar value = x.value() - y.value();
        return ErrorTracer<Scalar>(value,
                                   !iszero(value) ? (abs(x.value()) * x.error() + abs(y.value()) * y.error()) / abs(value) + Scalar(1) : Scalar());
    }
    
    template <typename Scalar>
    FORCEINLINE 
    ErrorTracer<Scalar> operator*(const ErrorTracer<Scalar>& x, const ErrorTracer<Scalar>& y)
    {
        return ErrorTracer<Scalar>(x.value() * y.value(), 
                                    x.error() + y.error() + Scalar(1));
    }
    
    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> operator/(const ErrorTracer<Scalar>& x, const ErrorTracer<Scalar>& y) 
    {
        return ErrorTracer<Scalar>(x.value() / y.value(), 
                                    x.error() + y.error() + Scalar(1));
    }
    
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const ErrorTracer<Scalar>& x) 
    {
        return os << x.value() << '[' << x.error() << ']';
    }
    
#endif

    template <typename Scalar>
    FORCEINLINE 
    ErrorTracer<Scalar> sqrt(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(sqrt(x.value()), x.error() * Scalar(0.5) + Scalar(1));
    }
    
    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> abs(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(abs(x.value()), x.error());
    }
    
    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> cos(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(cos(x.value()), x.error() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> sin(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(sin(x.value()), x.error() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE 
    ErrorTracer<Scalar> tan(const ErrorTracer<Scalar>& x) 
    {
        Scalar value = tan(x.value());
        return ErrorTracer<Scalar>(value, (Scalar(1) + value * value) * x.error() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> acos(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(acos(x.value()), x.error() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> asin(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(asin(x.value()), x.error() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> atan(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(atan(x.value()), x.error() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE 
    ErrorTracer<Scalar> atan2(const ErrorTracer<Scalar>& x, const ErrorTracer<Scalar>& y) 
    {
        return ErrorTracer<Scalar>(atan2(x.value(), y.value()), x.error() + y.error() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE 
    ErrorTracer<Scalar> exp(const ErrorTracer<Scalar>& x) 
    {
        Scalar value = exp(x.value());
        return ErrorTracer<Scalar>(value, value * x.error() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE 
    ErrorTracer<Scalar> log(const ErrorTracer<Scalar>& x) 
    {
        return ErrorTracer<Scalar>(log(x.value()), x.error() / x.value() + Scalar(1));
    }

    template <typename Scalar>
    FORCEINLINE
    ErrorTracer<Scalar> pow(const ErrorTracer<Scalar>& x, const ErrorTracer<Scalar>& y) 
    {
        ASSERT(!isnegative(x.value()));
        Scalar value = pow(x.value(), y.value());
        return ErrorTracer<Scalar>(value, abs(y.value()) * x.error() + abs(value * log(x.value())) * y.error() + Scalar(1));
    }

    template <typename Scalar>
    struct ScalarTraits<ErrorTracer<Scalar> > 
    {
        static FORCEINLINE ErrorTracer<Scalar> pi()
        {
            return ErrorTracer<Scalar>(ScalarTraits<Scalar>::pi());
        }
        
        static FORCEINLINE ErrorTracer<Scalar> infinity()
        {
            return ErrorTracer<Scalar>(ScalarTraits<Scalar>::infinity());
        }

        static FORCEINLINE ErrorTracer<Scalar> epsilon()
        {
            return ErrorTracer<Scalar>(ScalarTraits<Scalar>::epsilon());
        }
    };

}

#endif
