/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_INTERVAL_HPP
#define MT_INTERVAL_HPP

#include <guts/TypeTraits.hpp>

#include <moto/Promote.hpp>
#include <moto/Scalar.hpp>

namespace mt
{
    template <typename Scalar>
    class Interval
    {
    public:
        typedef Scalar ScalarType;
       
        Interval();
        Interval(Scalar x);
        Interval(Scalar lower, Scalar upper);
        template <typename Scalar2> Interval(const Interval<Scalar2>& z);
                    
        Scalar lower() const;
        Scalar& lower();
        
        Scalar upper() const;
        Scalar& upper();

        Interval<Scalar>& operator=(Scalar x);
        Interval<Scalar>& operator+=(Scalar x); 
        Interval<Scalar>& operator-=(Scalar x);
        
        template <typename Scalar2> Interval<Scalar>& operator=(const Interval<Scalar2>& z);
        template <typename Scalar2> Interval<Scalar>& operator+=(const Interval<Scalar2>& z);
        template <typename Scalar2> Interval<Scalar>& operator-=(const Interval<Scalar2>& z);

    private:
        Scalar mLower;
        Scalar mUpper;
    };
    
    template <typename Scalar> Scalar lower(const Interval<Scalar>& z); 
    template <typename Scalar> Scalar upper(const Interval<Scalar>& z);    
    template <typename Scalar> Scalar width(const Interval<Scalar>& z);
    template <typename Scalar> Scalar median(const Interval<Scalar>& z);
    
#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Interval<Scalar>& z);

#endif

    template <typename Scalar> Interval<Scalar> operator-(const Interval<Scalar>& z);

    template <typename Scalar> Interval<Scalar> operator+(const Interval<Scalar>& z, Scalar x);
    template <typename Scalar> Interval<Scalar> operator-(const Interval<Scalar>& z, Scalar x);
    template <typename Scalar> Interval<Scalar> operator*(const Interval<Scalar>& z, Scalar x);

    template <typename Scalar> Interval<Scalar> operator+(Scalar x, const Interval<Scalar>& z);
    template <typename Scalar> Interval<Scalar> operator-(Scalar x, const Interval<Scalar>& z);
    template <typename Scalar> Interval<Scalar> operator*(Scalar x, const Interval<Scalar>& z);

    template <typename Scalar1, typename Scalar2>
    Interval<typename Promote<Scalar1, Scalar2>::RT> operator+(const Interval<Scalar1>& z1, const Interval<Scalar2>& z2);
   
    template <typename Scalar1, typename Scalar2>
    Interval<typename Promote<Scalar1, Scalar2>::RT> operator-(const Interval<Scalar1>& z1, const Interval<Scalar2>& z2);
       
    
   
    template <typename Scalar1, typename Scalar2> bool overlap(const Interval<Scalar1>& z1, const Interval<Scalar2>& z2);
    template <typename Scalar1, typename Scalar2> bool subset(const Interval<Scalar1>& z1, const Interval<Scalar2>& z2);
    template <typename Scalar> bool in(Scalar x, const Interval<Scalar>& z);
   
    template <typename Scalar> Interval<Scalar> hull(Scalar x, Scalar y);
    template <typename Scalar> Interval<Scalar> hull(const Interval<Scalar>& z, Scalar x);
    template <typename Scalar> Interval<Scalar> hull(Scalar x, const Interval<Scalar>& z);
    template <typename Scalar> Interval<Scalar> hull(const Interval<Scalar>& z1, const Interval<Scalar>& z2);
    
    template <typename Scalar> Scalar           clamp(Scalar x, const Interval<Scalar>& z);
    template <typename Scalar> Interval<Scalar> clamp(const Interval<Scalar>& z1, const Interval<Scalar>& z2);
    

    // Member functions


    template <typename Scalar>
    FORCEINLINE
    Interval<Scalar>::Interval()
        : mLower()
        , mUpper()
    {}
    
    template <typename Scalar>
    FORCEINLINE
    Interval<Scalar>::Interval(Scalar x)
        : mLower(x)
        , mUpper(x)
    {} 
    
    template <typename Scalar>
    FORCEINLINE
    Interval<Scalar>::Interval(Scalar lower, Scalar upper)
        : mLower(lower)
        , mUpper(upper)
    {
        ASSERT(!(upper < lower));
    }

    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Interval<Scalar>::Interval(const Interval<Scalar2>& z)
        : mLower(z.lower())
        , mUpper(z.upper())
    {}

    template <typename Scalar>
    FORCEINLINE
    Interval<Scalar>& Interval<Scalar>::operator=(Scalar x)
    {
        mLower = x; 
        mUpper = x; 
        return *this;
    }

    template <typename Scalar>
    FORCEINLINE
    Interval<Scalar>& Interval<Scalar>::operator+=(Scalar x)
    {
        mLower += x; 
        mUpper += x; 
        return *this;
    }
    
    template <typename Scalar>
    FORCEINLINE
    Interval<Scalar>& Interval<Scalar>::operator-=(Scalar x)
    {
        mLower -= x; 
        mUpper -= x; 
        return *this;
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Interval<Scalar>& Interval<Scalar>::operator=(const Interval<Scalar2>& z)
    {
        mLower = z.lower(); 
        mUpper = z.upper(); 
        return *this;
    }
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Interval<Scalar>& Interval<Scalar>::operator+=(const Interval<Scalar2>& z)
    {
        mLower += z.lower(); 
        mUpper += z.upper(); 
        return *this;
    }  
    
    template <typename Scalar>
    template <typename Scalar2>
    FORCEINLINE
    Interval<Scalar>& Interval<Scalar>::operator-=(const Interval<Scalar2>& z)
    {
        mLower -= z.upper(); 
        mUpper -= z.lower(); 
        return *this;
    }
    
    template <typename Scalar>
    FORCEINLINE
    Scalar Interval<Scalar>::lower() const
    {
        return mLower;
    }
    
    template <typename Scalar>
    FORCEINLINE
    Scalar& Interval<Scalar>::lower()
    {
        return mLower;
    }

    template <typename Scalar>
    FORCEINLINE
    Scalar Interval<Scalar>::upper() const
    {
        return mUpper;
    }
    
    template <typename Scalar>
    FORCEINLINE
    Scalar& Interval<Scalar>::upper()
    {
        return mUpper;
    }


    // Non-member functions


    template <typename Scalar>
    FORCEINLINE
    Scalar lower(const Interval<Scalar>& z)
    {   
        return z.lower();
    }  
    
    template <typename Scalar>
    FORCEINLINE 
    Scalar upper(const Interval<Scalar>& z)
    {   
        return z.upper();
    }   
        
    template <typename Scalar>
    FORCEINLINE 
    Scalar width(const Interval<Scalar>& z)
    {
        return z.upper() - z.lower();
    }

    template <typename Scalar>
    FORCEINLINE 
    Scalar median(const Interval<Scalar>& z)
    {
        return (z.lower() + z.upper()) * Scalar(0.5);
    } 


#ifdef USE_OSTREAM

    template <typename CharT, typename Traits, typename Scalar> 
    FORCEINLINE 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const Interval<Scalar>& z)
    {
        return os << '[' << z.lower() << ", " << z.upper() << ']';
    } 

#endif

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> operator-(const Interval<Scalar>& z)
    {
        return Interval<Scalar>(-z.upper(), -z.lower());
    }

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> operator+(const Interval<Scalar>& z, Scalar x)
    {
        return Interval<Scalar>(z.lower() + x, z.upper() + x);
    }

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> operator-(const Interval<Scalar>& z, Scalar x)
    {
        return Interval<Scalar>(z.lower() - x, z.upper() - x);
    }

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> operator*(const Interval<Scalar>& z, Scalar x)
    {
        return Interval<Scalar>(z.lower() * x, z.upper() * x);
    }

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> operator+(Scalar x, const Interval<Scalar>& z)
    {
        return z + x;
    }
    
    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> operator-(Scalar x, const Interval<Scalar>& z)
    {
         return Interval<Scalar>(x - z.upper(), x - z.lower());
    }

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> operator*(Scalar x, const Interval<Scalar>& z)
    {
         return Interval<Scalar>(x * z.upper(), x * z.lower());
    }
    
    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Interval<typename Promote<Scalar1, Scalar2>::RT> operator+(const Interval<Scalar1>& z1,
                                                               const Interval<Scalar2>& z2)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Interval<RT>(z1.lower() + z2.lower(), z1.upper() + z2.upper());
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    Interval<typename Promote<Scalar1, Scalar2>::RT> operator-(const Interval<Scalar1>& z1,
                                                               const Interval<Scalar2>& z2)
    {
        typedef typename Promote<Scalar1, Scalar2>::RT RT; 
        return Interval<RT>(z1.lower() - z2.upper(), z1.upper() - z2.lower());
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    bool overlap(const Interval<Scalar1>& z1, const Interval<Scalar2>& z2)
    {
        return !(z1.upper() < z2.lower() || z2.upper() < z1.lower());
    }

    template <typename Scalar1, typename Scalar2>
    FORCEINLINE 
    bool subset(const Interval<Scalar1>& z1, const Interval<Scalar2>& z2)
    {
        return !(z1.lower() < z2.lower() || z2.upper() < z1.upper());
    }

    template <typename Scalar>
    FORCEINLINE 
    bool in(Scalar x, const Interval<Scalar>& z)
    {
        return !(x < z.lower() || z.upper() < x);
    }

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> hull(Scalar x, Scalar y)
    {
        return y < x ? Interval<Scalar>(y, x) : Interval<Scalar>(x, y);
    }  

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> hull(const Interval<Scalar>& z, Scalar x)
    {
        return x < z.lower() ? Interval<Scalar>(x, z.upper()) : Interval<Scalar>(z.lower(), max(x, z.upper())); 
    }   

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> hull(Scalar x, const Interval<Scalar>& z)
    {
        return hull(z, x);
    } 
    
    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> hull(const Interval<Scalar>& z1, const Interval<Scalar>& z2)
    {
        return Interval<Scalar>(min(z1.lower(), z2.lower()), max(z1.upper(), z2.upper()));
    }  
     
    template <typename Scalar>
    FORCEINLINE 
    Scalar clamp(Scalar x, const Interval<Scalar>& z2)
    {
        return x < z2.lower() ? z2.lower() :
               z2.upper() < x ? z2.upper() :
               x;
    }  

    template <typename Scalar>
    FORCEINLINE 
    Interval<Scalar> clamp(const Interval<Scalar>& z1, const Interval<Scalar>& z2)
    {
        return z1.upper() < z2.lower() ? Interval<Scalar>(z2.lower(), z2.lower()) : 
               z2.upper() < z1.lower() ? Interval<Scalar>(z2.upper(), z2.upper()) :
               Interval<Scalar>(max(z1.lower(), z2.lower()), min(z1.upper(), z2.upper()));
    }  
    
#ifndef HAVE_TYPEOF

    template <typename Scalar1, typename Scalar2>
    struct Promote<Scalar1, Interval<Scalar2> >
    {
        typedef Interval<typename Promote<Scalar1, Scalar2>::RT> RT;
    }; 
    
    template <typename Scalar1, typename Scalar2>
    struct Promote<Interval<Scalar1>, Interval<Scalar2> >
    {
        typedef Interval<typename Promote<Scalar1, Scalar2>::RT> RT;
    };

#endif

}
namespace guts
{
    template <> struct TypeTraits<mt::Interval<float> > { enum { ID = TT_FLOAT2 }; };
    template <> struct TypeTraits<mt::Interval<double> > { enum { ID = TT_DOUBLE2 }; };
}
#endif
