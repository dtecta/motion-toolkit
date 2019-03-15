/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_ERRORTRACER_HPP
#define MT_ERRORTRACER_HPP

#ifdef USE_OSTREAM
#include <ostream>
#endif

#include "Scalar.hpp"
#include "ScalarTraits.hpp"

namespace mt
{
    template <typename T> 
    class ErrorTracer
    {
    public:    
        typedef T Value_type;

        explicit ErrorTracer(T value = T(), T error = T());

        /// Floating-point value.
        T value() const;

        /// Estimated error bound.  
        T error() const;

        /// Estimated upper bound for the relative rounding error of this value. The value returned by maxRelativeError() is equal to the value returned by error() times the machine epsilon.
        T maxRelativeError() const;

        /// Number of dirty bits in the significand of this value. The number of least-signinifant bits that are contaminated by rounding. 
        T dirtyBits() const;

        /// Implicit cast of floating-point value.
        operator T() const;
        
        ErrorTracer<T>& operator=(T value); 
        ErrorTracer<T>& operator+=(const ErrorTracer& x); 
        ErrorTracer<T>& operator-=(const ErrorTracer& x); 
        ErrorTracer<T>& operator*=(const ErrorTracer& x); 
        ErrorTracer<T>& operator/=(const ErrorTracer& x); 
        
    private:
        T mValue;
        T mError;
    };

    template <typename T> ErrorTracer<T> operator-(const ErrorTracer<T>& x);
    template <typename T> ErrorTracer<T> operator+(const ErrorTracer<T>& x,  const ErrorTracer<T>& y);
    template <typename T> ErrorTracer<T> operator-(const ErrorTracer<T>& x,  const ErrorTracer<T>& y);
    template <typename T> ErrorTracer<T> operator*(const ErrorTracer<T>& x,  const ErrorTracer<T>& y);
    template <typename T> ErrorTracer<T> operator/(const ErrorTracer<T>& x,  const ErrorTracer<T>& y);
 
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename T> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const ErrorTracer<T>& x);
    
#endif

    template <typename T> ErrorTracer<T> abs(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> acos(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> asin(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> atan(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> atan2(const ErrorTracer<T>& x, const ErrorTracer<T>& y); 
    template <typename T> ErrorTracer<T> cos(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> exp(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> log(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> pow(const ErrorTracer<T>& x, const ErrorTracer<T>& y); 
    template <typename T> ErrorTracer<T> sin(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> sqrt(const ErrorTracer<T>& x); 
    template <typename T> ErrorTracer<T> tan(const ErrorTracer<T>& x);

    template <typename T>
    FORCEINLINE
    ErrorTracer<T>::ErrorTracer(T value, T error) 
        : mValue(value)
        , mError(error) 
    {}

    template <typename T>
    FORCEINLINE
    T ErrorTracer<T>::value() const 
    {
        return mValue; 
    }
    
    template <typename T>
    FORCEINLINE
    T ErrorTracer<T>::error() const
    {  
        return mError; 
    }

    template <typename T>
    FORCEINLINE
    T ErrorTracer<T>::maxRelativeError() const
    {  
        T gMachineEpsilon = std::numeric_limits<T>::epsilon() * T(0.5);

        return mError * gMachineEpsilon; 
    }

    template <typename T>
    FORCEINLINE
    T ErrorTracer<T>::dirtyBits() const
    { 
        return log2(mError); 
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T>::operator T() const
    { 
        return mValue; 
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T>& ErrorTracer<T>::operator=(T value) 
    {
        mValue = value;
        mError = T();
        return *this;
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T>& ErrorTracer<T>::operator+=(const ErrorTracer<T>& x) 
    {
        *this = *this + x;
        return *this;
    }
    
    template <typename T>
    FORCEINLINE
    ErrorTracer<T>& ErrorTracer<T>::operator-=(const ErrorTracer<T>& x) 
    {
        *this = *this - x;
        return *this;
    }
    
    template <typename T>
    FORCEINLINE
    ErrorTracer<T>& ErrorTracer<T>::operator*=(const ErrorTracer<T>& x) 
    {
        *this = *this * x;
        return *this;
    }
    
    template <typename T>
    FORCEINLINE
    ErrorTracer<T>& ErrorTracer<T>::operator/=(const ErrorTracer<T>& x) 
    {
        *this = *this / x;
        return *this;
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T> operator-(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(-x.value(), 
                              x.error());
    }
    
    template <typename T>
    FORCEINLINE 
    ErrorTracer<T> operator+(const ErrorTracer<T>& x,  const ErrorTracer<T>& y) 
    {
        T value = x.value() + y.value();
        T error = abs(x.value()) * x.error() + abs(y.value()) * y.error();
        return ErrorTracer<T>(value, 
                              !iszero(value) ? error / abs(value) + T(1) : T());
    }
    
    template <typename T>
    FORCEINLINE
    ErrorTracer<T> operator-(const ErrorTracer<T>& x, const ErrorTracer<T>& y) 
    {
        T value = x.value() - y.value();
        T error = abs(x.value()) * x.error() + abs(y.value()) * y.error();
        return ErrorTracer<T>(value,
                              !iszero(value) ? error / abs(value) + T(1) : T());
    }
    
    template <typename T>
    FORCEINLINE 
    ErrorTracer<T> operator*(const ErrorTracer<T>& x, const ErrorTracer<T>& y)
    {
        return ErrorTracer<T>(x.value() * y.value(), 
                              x.error() + y.error() + T(1));
    }
    
    template <typename T>
    FORCEINLINE
    ErrorTracer<T> operator/(const ErrorTracer<T>& x, const ErrorTracer<T>& y) 
    {
        return ErrorTracer<T>(x.value() / y.value(), 
                              x.error() + y.error() + T(1));
    }
    
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename T> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const ErrorTracer<T>& x) 
    {
        return os << x.value() << '[' << x.error() << ']';
    }
    
#endif

    template <typename T>
    FORCEINLINE
    ErrorTracer<T> abs(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(abs(x.value()), x.error());
    }
    
    template <typename T>
    FORCEINLINE
    ErrorTracer<T> acos(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(acos(x.value()), x.error() + T(1));
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T> asin(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(asin(x.value()), x.error() + T(1));
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T> atan(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(atan(x.value()), x.error() + T(1));
    }

    template <typename T>
    FORCEINLINE 
    ErrorTracer<T> atan2(const ErrorTracer<T>& x, const ErrorTracer<T>& y) 
    {
        return ErrorTracer<T>(atan2(x.value(), y.value()), x.error() + y.error() + T(1));
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T> cos(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(cos(x.value()), x.error() + T(1));
    }

    template <typename T>
    FORCEINLINE 
    ErrorTracer<T> exp(const ErrorTracer<T>& x) 
    {
        T value = exp(x.value());
        return ErrorTracer<T>(value, value * x.error() + T(1));
    }

    template <typename T>
    FORCEINLINE 
    ErrorTracer<T> log(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(log(x.value()), x.error() / x.value() + T(1));
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T> pow(const ErrorTracer<T>& x, const ErrorTracer<T>& y) 
    {
        ASSERT(!isnegative(x.value()));
        T value = pow(x.value(), y.value());
        return ErrorTracer<T>(value, abs(y.value()) * x.error() + abs(value * log(x.value())) * y.error() + T(1));
    }

    template <typename T>
    FORCEINLINE
    ErrorTracer<T> sin(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(sin(x.value()), x.error() + T(1));
    }

    template <typename T>
    FORCEINLINE 
    ErrorTracer<T> sqrt(const ErrorTracer<T>& x) 
    {
        return ErrorTracer<T>(sqrt(x.value()), x.error() * T(0.5) + T(1));
    }
    
    template <typename T>
    FORCEINLINE 
    ErrorTracer<T> tan(const ErrorTracer<T>& x) 
    {
        T value = tan(x.value());
        return ErrorTracer<T>(value, (T(1) + value * value) * x.error() + T(1));
    }

    template <typename T>
    struct ScalarTraits<ErrorTracer<T> > 
    {
        static FORCEINLINE ErrorTracer<T> pi()
        {
            return ErrorTracer<T>(ScalarTraits<T>::pi());
        }
        
        static FORCEINLINE ErrorTracer<T> infinity()
        {
            return ErrorTracer<T>(ScalarTraits<T>::infinity());
        }

        static FORCEINLINE ErrorTracer<T> epsilon()
        {
            return ErrorTracer<T>(ScalarTraits<T>::epsilon());
        }
    };
}

namespace std
{
    template <typename T>
    class numeric_limits<mt::ErrorTracer<T> >
    {
    public:
        static mt::ErrorTracer<T> min() { return mt::ErrorTracer<T>(numeric_limits<T>::min()); }
        static mt::ErrorTracer<T> max() { return mt::ErrorTracer<T>(numeric_limits<T>::max()); }
        static mt::ErrorTracer<T> epsilon() { return mt::ErrorTracer<T>(numeric_limits<T>::epsilon()); }
        static mt::ErrorTracer<T> round_error() { return mt::ErrorTracer<T>(numeric_limits<T>::round_error()); }
        static mt::ErrorTracer<T> infinity() { return mt::ErrorTracer<T>(numeric_limits<T>::infinity()); }
        static mt::ErrorTracer<T> quiet_NaN() { return mt::ErrorTracer<T>(numeric_limits<T>::quiet_NaN()); }
        static mt::ErrorTracer<T> signaling_NaN() { return mt::ErrorTracer<T>(numeric_limits<T>::signaling_NaN()); }
        static mt::ErrorTracer<T> denorm_min() { return mt::ErrorTracer<T>(numeric_limits<T>::denorm_min()); }
    };
}

#endif
