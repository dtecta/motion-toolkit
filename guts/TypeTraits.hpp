#pragma once

#include <vector>
#include <string>

#include <consolid/consolid.h>

#define TT_ARRAY_BIT 0x80
#define TT_PRIM_BIT 0x40

#define TT_2 0x01
#define TT_3 0x02
#define TT_4 0x03

#define TT_INT8 0x40
#define TT_UINT8 0x44
#define TT_INT16 0x48
#define TT_UINT16 0x4C
#define TT_INT32 0x50
#define TT_UINT32 0x54
#define TT_INT64 0x58
#define TT_UINT64 0x5C
#define TT_FLOAT 0x60
#define TT_FLOAT2 0x64
#define TT_FLOAT3 0x68
#define TT_FLOAT4 0x6C
#define TT_DOUBLE 0x70
#define TT_DOUBLE2 0x74
#define TT_DOUBLE3 0x78
#define TT_DOUBLE4 0x7C

namespace guts
{
    inline
    bool isArray(uint8_t x)
    {
        return (x & TT_ARRAY_BIT) != 0;
    }

    inline
    uint8_t elemType(uint8_t x)
    {
        return x & ~TT_ARRAY_BIT;
    }

    inline
    bool isPrimType(uint8_t x)
    {
        return (x & TT_PRIM_BIT) != 0;
    }

    template <typename Type> struct TypeTraits;

    template <> struct TypeTraits<int8_t> { enum { ID = TT_INT8 }; };
    template <> struct TypeTraits<uint8_t> { enum { ID = TT_UINT8 }; };
    template <> struct TypeTraits<int16_t> { enum { ID = TT_INT16 }; };
    template <> struct TypeTraits<uint16_t> { enum { ID = TT_UINT16 }; };
    template <> struct TypeTraits<int32_t> { enum { ID = TT_INT32 }; };
    template <> struct TypeTraits<uint32_t> { enum { ID = TT_UINT32 }; };
    template <> struct TypeTraits<int64_t> { enum { ID = TT_INT64 }; };
    template <> struct TypeTraits<uint64_t> { enum { ID = TT_UINT64 }; };
    template <> struct TypeTraits<float> { enum { ID = TT_FLOAT }; };
    template <> struct TypeTraits<double> { enum { ID = TT_DOUBLE }; };

    template <typename Type> struct TypeTraits<Type[1]> { enum { ID = TypeTraits<Type>::ID }; };
    template <typename Type> struct TypeTraits<Type[2]> { enum { ID = TypeTraits<Type>::ID | TT_2 }; };
    template <typename Type> struct TypeTraits<Type[3]> { enum { ID = TypeTraits<Type>::ID | TT_3 }; };
    template <typename Type> struct TypeTraits<Type[4]> { enum { ID = TypeTraits<Type>::ID | TT_4 }; };

    template <typename Type, int N> struct TypeTraits<Type[N]> { enum { ID = TT_ARRAY_BIT | TypeTraits<Type>::ID }; };

    template <typename Type, typename Alloc> 
    struct TypeTraits<std::vector<Type, Alloc> > { enum { ID = TT_ARRAY_BIT | TypeTraits<Type>::ID }; };

    template <typename CharT, typename Traits, typename Alloc> 
    struct TypeTraits<std::basic_string<CharT, Traits, Alloc> > { enum { ID = TT_ARRAY_BIT | TypeTraits<CharT>::ID }; };
}
