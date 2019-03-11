/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019-2018 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#pragma once

#include <consolid/consolid.h>

#include "Vector.hpp"
#include "TypeTraits.hpp"

namespace guts
{
    typedef Vector<uint8_t>::RT SyntaxStream;

    inline
    void addElement(SyntaxStream& ss, uint8_t x)
    {
        if (!ss.empty() && ss.back() == TT_ARRAY_BIT)
        {
            ss.back() |= x;
        }
        else
        {
            ss.push_back(x);
        }
    }

    inline
    void addArray(SyntaxStream& ss)
    {
        ss.push_back(TT_ARRAY_BIT);
    }

    inline
    void addStruct(SyntaxStream& ss, uint8_t size)
    {
        ASSERT(size < 64);
        addElement(ss, size);
    }

    inline
    void addPrimType(SyntaxStream& ss, uint8_t type)
    {
        ASSERT(isPrimType(type));
        addElement(ss, type);
    }
}
