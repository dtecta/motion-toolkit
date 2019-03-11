#pragma once

#include <ostream>
#include <istream>
#include <vector>

#include "RefPtr.hpp"
#include "StaticAssert.hpp"

namespace guts
{
	template <typename CharT, typename Traits, typename Type>
	bool write(std::basic_ostream<CharT, Traits>& os, const Type& x)
	{
        STATIC_ASSERT(sizeof(CharT) == 1);
		return !os.write(reinterpret_cast<const CharT*>(&x), sizeof(Type)).fail();
	} 

	template <typename CharT, typename Traits, typename Type>
	bool write(std::basic_ostream<CharT, Traits>& os, const RefPtr<Type>& p)
	{
		return p->serialize(os);
	} 

    template <typename CharT, typename Traits, typename Type, typename Alloc>
    bool write(std::basic_ostream<CharT, Traits>& os, const std::vector<Type, Alloc>& v)
    {
        uint32_t size = uint32_t(v.size());
        if (!write(os, size))
		{
			return false;
		}

        typename std::vector<Type, Alloc>::const_iterator it = v.begin(), end = v.end();
		while (it != end && write(os, *it))
		{
			++it;
		}

        return it == end;
    }

    template <typename CharT, typename Traits, typename Type>
	bool read(std::basic_istream<CharT, Traits>& is, Type& x)
	{
        STATIC_ASSERT(sizeof(CharT) == 1);
		return !is.read(reinterpret_cast<char*>(&x), sizeof(Type)).fail();
	} 

	template <typename CharT, typename Traits, typename Type>
	bool read(std::basic_istream<CharT, Traits>& is, RefPtr<Type>& p)
	{
		p = CREATE(Type);
		return p->deserialize(is);
	}
	
    template <typename CharT, typename Traits, typename Type, typename Alloc>
    bool read(std::basic_istream<CharT, Traits>& is, std::vector<Type, Alloc>& v)
    { 
        uint32_t size;
        if (!read(is, size))
        {
            return false;
        }

        v.resize(size);

        typename std::vector<Type, Alloc>::iterator it = v.begin(), end = v.end();
		while (it != end && read(is, *it))
        {
            ++it;
        }

        return it == end;
    }
}
