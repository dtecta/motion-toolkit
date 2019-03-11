/*  MoTo - Motion Toolkit
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef MT_BITMASK4_HPP
#define MT_BITMASK4_HPP

#include <moto/Algebra.hpp>

namespace mt
{
    class BitMask4
    {
    public:
        BitMask4();
        explicit BitMask4(uint32_t bits);
        BitMask4(bool x, bool y, bool z, bool w);     
        BitMask4(Zero);
        template <int I> BitMask4(Unit<I>);
             
        operator uint32_t() const;
        bool operator[](int i) const; 
        
        BitMask4& operator|=(BitMask4 rhs);
        BitMask4& operator&=(BitMask4 rhs);
        BitMask4& operator^=(BitMask4 rhs);

    private:
        uint32_t mBits;
    }; 
    
    bool operator<=(BitMask4 lhs, BitMask4 rhs);

    bool any(BitMask4 a);
    bool all(BitMask4 a);

    
   
    FORCEINLINE
    BitMask4::BitMask4()
    {}  
    
    FORCEINLINE
    BitMask4::BitMask4(uint32_t bits)
        : mBits(bits)
    {}

    FORCEINLINE
    BitMask4::BitMask4(bool x, bool y, bool z, bool w)
        : mBits(uint32_t(x) | (uint32_t(y) << 1) | (uint32_t(z) << 2) | (uint32_t(w) << 3))
    {}

    FORCEINLINE
    BitMask4::BitMask4(Zero)
        : mBits()
    {}

    template <int I>
    FORCEINLINE
    BitMask4::BitMask4(Unit<I>)
        : mBits(1 << I)
    {}

    FORCEINLINE
    bool BitMask4::operator[](int i) const 
    {
        return mBits & (1 << i); 
    }

   
    FORCEINLINE
    BitMask4& BitMask4::operator|=(BitMask4 rhs) 
    {
        mBits |= rhs.mBits;
        return *this;
    }

    FORCEINLINE
    BitMask4& BitMask4::operator&=(BitMask4 rhs) 
    {
        mBits &= rhs.mBits;
        return *this;
    } 
    
    FORCEINLINE
    BitMask4& BitMask4::operator^=(BitMask4 rhs) 
    {
        mBits ^= rhs.mBits;
        return *this;
    }     

    FORCEINLINE
    BitMask4::operator uint32_t() const 
    { 
        return mBits; 
    }

    FORCEINLINE
    bool operator<=(BitMask4 lhs, BitMask4 rhs)
    {
        return (lhs & rhs) == lhs; 
    } 

    FORCEINLINE
    bool any(BitMask4 a)
    {
        return a != 0x0;
    }

    FORCEINLINE
    bool all(BitMask4 a)
    {
        return a == 0xf;
    }



}

#endif


 
