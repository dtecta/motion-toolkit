#pragma once

#include <cstring>

#include "Stream.hpp"
#include "Syntax.hpp"

#define MAJOR_VERSION 1
#define MINOR_VERSION 0

namespace guts
{
    template <typename Type>
    struct Serialization
    {
        static const char sHeader[4]; 
    };

    template <typename Type>
    const char Serialization<Type>::sHeader[4] = { 'd', 't', MAJOR_VERSION, MINOR_VERSION };

    template <typename Type>
    bool serialize(const Type& object, std::ostream& os)
    {
        SyntaxStream ss;
        Type::syntax(ss);

        return write(os, Serialization<Type>::sHeader) && write(os, ss) && object.serialize(os);
    }

    template <typename Type>
    bool deserialize(Type& object, std::istream& is)
    {
        char header[4];
        if (!read(is, header) || std::memcmp(header, Serialization<Type>::sHeader, 4) != 0)
        {
            return false;
        }

        SyntaxStream ss1;
        Type::syntax(ss1);

        SyntaxStream ss2;
        if (!read(is, ss2) || ss1 != ss2)
        {
            return false;
        }

        return object.deserialize(is);
    }
}
