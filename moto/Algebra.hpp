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

#ifndef MT_ALGEBRA_HPP
#define MT_ALGEBRA_HPP

#include <consolid/consolid.h>

#ifdef USE_OSTREAM
#include <ostream>
#endif

namespace mt
{
    struct Zero 
    {
        template <typename Scalar> operator Scalar() const;
    };

    struct Identity 
    {
        template <typename Scalar> operator Scalar() const;
    }; 
    
    template <int> 
    struct Unit 
    {
    };    


    Zero     operator-(Zero);
    
    Zero     operator+(Zero, Zero);
    Identity operator+(Identity, Zero); 
    Identity operator+(Zero, Identity);

    template <typename Element> const Element& operator+(const Element& e, Zero); 
    template <typename Element> const Element& operator+(Zero, const Element& e);


    Zero     operator-(Zero, Zero);  
    Identity operator-(Identity, Zero);  
    Zero     operator-(Identity, Identity);     
    
    template <typename Element> const Element& operator-(const Element& e, Zero);   
    template <typename Element> Element        operator-(Zero, const Element& e);


    Zero     operator*(Zero, Zero);
    Zero     operator*(Identity, Zero); 
    Zero     operator*(Zero, Identity);

    template <typename Element> Zero operator*(const Element& e, Zero);
    template <typename Element> Zero operator*(Zero, const Element& e);


    Identity inverse(Identity); 
    
    Zero     mul(Zero, Zero); 
    Zero     mul(Zero, Identity);
    Zero     mul(Identity, Zero);
    
    template <typename Element> Zero mul(const Element& e, Zero);
    template <typename Element> Zero mul(Zero, const Element& e);
    
    Identity mul(Identity, Identity);

    template <typename Element> const Element& mul(const Element& e, Identity);
    template <typename Element> const Element& mul(Identity, const Element& e);
    
 
    Zero     dot(Zero, Zero);
    
    template <typename Vector> Zero dot(Zero, const Vector& v);
    template <typename Vector> Zero dot(const Vector& v, Zero);

    template <int I> Identity dot(Unit<I>, Unit<I>);
    template <int I, int J> Zero dot(Unit<I>, Unit<J>);

    template <typename Vector, int I> typename Vector::ScalarType dot(Unit<I>, const Vector& v);
    template <typename Vector, int I> typename Vector::ScalarType dot(const Vector& v, Unit<I>);

#ifdef USE_OSTREAM
   
    template <typename CharT, typename Traits> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Zero); 
    
    template <typename CharT, typename Traits> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Identity); 
    
    template <typename CharT, typename Traits, int I> 
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Unit<I>);
    
#endif


    // Member functions

    template <typename Scalar> 
    FORCEINLINE
    Zero::operator Scalar() const 
    { 
        return Scalar(); 
    } 

    template <typename Scalar> 
    FORCEINLINE
    Identity::operator Scalar() const 
    { 
        return Scalar(1); 
    } 
    
    // Non-member functions

    FORCEINLINE 
    Zero operator-(Zero)
    { 
        return Zero(); 
    }
    
    FORCEINLINE 
    Zero operator+(Zero, Zero) 
    { 
        return Zero(); 
    }

    FORCEINLINE 
    Identity operator+(Identity, Zero)
    { 
        return Identity();
    } 

    FORCEINLINE
    Identity operator+(Zero, Identity)
    { 
        return Identity(); 
    } 

    template <typename Element>
    FORCEINLINE 
    const Element& operator+(const Element& e, Zero)
    { 
        return e;
    }

    template <typename Element>
    FORCEINLINE
    const Element& operator+(Zero, const Element& e)
    {
        return e;
    }
    
    FORCEINLINE 
    Zero operator-(Zero, Zero)
    { 
        return Zero(); 
    }    
    
    
    FORCEINLINE 
    Identity operator-(Identity, Zero)
    { 
        return Identity();
    }     
    
    FORCEINLINE 
    Zero operator-(Identity, Identity)
    { 
        return Zero();
    }    
    
    
    template <typename Element>
    FORCEINLINE 
    const Element& operator-(const Element& e, Zero)
    { 
        return e; 
    }  

    template <typename Element>
    FORCEINLINE
    Element operator-(Zero, const Element& e)
    {
        return -e;
    }

    FORCEINLINE 
    Zero operator*(Zero, Zero) 
    { 
        return Zero(); 
    }

    FORCEINLINE 
    Zero operator*(Identity, Zero)
    { 
        return Zero();
    } 

    FORCEINLINE
    Zero operator*(Zero, Identity)
    { 
        return Zero(); 
    } 

    template <typename Element>
    FORCEINLINE
    Zero operator*(const Element& e, Zero)
    {
        return Zero();
    }
    
    template <typename Element>
    FORCEINLINE
    Zero operator*(Zero, const Element& e)
    {
        return Zero();
    } 

        
    FORCEINLINE
    Identity inverse(Identity)
    {
        return Identity(); 
    }

    FORCEINLINE
    Zero mul(Zero, Zero)
    { 
        return Zero(); 
    }

    FORCEINLINE 
    Zero mul(Zero, Identity)
    { 
        return Zero(); 
    }
     
    FORCEINLINE
    Zero mul(Identity, Zero)
    {
        return Zero(); 
    }

    template <typename Element>
    FORCEINLINE
    Zero mul(const Element& e, Zero)
    {
        return Zero();
    }
    
    template <typename Element>
    FORCEINLINE
    Zero mul(Zero, const Element& e)
    {
        return Zero();
    } 

    FORCEINLINE
    Identity mul(Identity, Identity)
    {
        return Identity(); 
    } 
 
    template <typename Element>
    FORCEINLINE 
    const Element& mul(const Element& e, Identity)
    { 
        return e;
    }

    template <typename Element>
    FORCEINLINE 
    const Element& mul(Identity, const Element& e)
    { 
        return e;
    }   

    FORCEINLINE 
    Zero dot(Zero, Zero)
    { 
        return Zero(); 
    }

    template <typename Vector> 
    FORCEINLINE 
    Zero dot(Zero, const Vector& v)
    { 
        return Zero(); 
    }

    template <typename Vector> 
    FORCEINLINE 
    Zero dot(const Vector& v, Zero)
    { 
        return Zero(); 
    }
  
    template <int I, int J> 
    FORCEINLINE 
    Zero dot(Unit<I>, Unit<J>) 
    { 
        return Zero(); 
    }

    template <int I> 
    FORCEINLINE
    Identity dot(Unit<I>, Unit<I>) 
    { 
        return Identity(); 
    }
    
    template <typename Vector, int I> 
    FORCEINLINE 
    typename Vector::ScalarType dot(Unit<I>, const Vector& v)
    { 
        return v[I];
    }  
    
    template <typename Vector, int I> 
    FORCEINLINE 
    typename Vector::ScalarType dot(const Vector& v, Unit<I>)
    { 
        return v[I];
    } 

#ifdef USE_OSTREAM
    
    template <typename CharT, typename Traits>  
    FORCEINLINE
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Zero)
    {
        return os << "Zero";
    }

    template <typename CharT, typename Traits>  
    FORCEINLINE    
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Identity)
    {
        return os << "Identity";
    }

    template <typename CharT, typename Traits, int I>  
    FORCEINLINE    
    std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, Unit<I>)
    {
        return os << "Unit" << I; 
    }

#endif

}

#endif
