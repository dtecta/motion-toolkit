#ifndef GUTS_FILEUTILS_HPP
#define GUTS_FILEUTILS_HPP

#include <consolid/consolid.h>
#include <istream>
#include <string>

namespace guts
{ 
    template <typename Char>
    const Char* skipSpace(const Char* str)
    {
        while (isspace(*str))
        {
            ++str;
        }
        return str; 
    }   

	template <typename Char>
    void toLowerCase(Char* str)
    {
        while (*str != '\0')
        {
            *str = tolower(*str);
            ++str;
        }
    }   

    template <typename Char, typename Traits, typename Allocator>
    std::basic_string<Char, Traits, Allocator> directory(const std::basic_string<Char, Traits, Allocator>& path)
    {
        typedef typename std::basic_string<Char, Traits, Allocator>::size_type size_type;

        size_type found = path.find_last_of("/\\");
        return found != std::basic_string<Char, Traits, Allocator>::npos ? path.substr(0, found+1) : "";
    }

    template <typename Char, typename Traits, typename Allocator>
    std::basic_string<Char, Traits, Allocator> extension(const std::basic_string<Char, Traits, Allocator>& path)
    {
        typedef typename std::basic_string<Char, Traits, Allocator>::size_type size_type;

        size_type found = path.find_last_of('.');
        return found != std::basic_string<Char, Traits, Allocator>::npos ? path.substr(found+1) : "";
    }

    template <typename Char, typename Traits, typename Allocator>
    std::basic_string<Char, Traits, Allocator> basename(const std::basic_string<Char, Traits, Allocator>& path)
    {
        typedef typename std::basic_string<Char, Traits, Allocator>::size_type size_type;

        size_type found = path.find_last_of("/\\");
        size_type first = found != std::basic_string<Char, Traits, Allocator>::npos ? found+1 : 0;
        size_type last = path.find_last_of('.');
        return path.substr(first, last - first);
    } 

    template <typename Char, typename Traits, typename Allocator>
    std::basic_string<Char, Traits, Allocator> stripExtension(const std::basic_string<Char, Traits, Allocator>& path)
    {
        typedef typename std::basic_string<Char, Traits, Allocator>::size_type size_type;

        size_type found = path.find_last_of('.');
        return path.substr(0, found);
    }

    template <typename Char, typename Traits, typename Allocator>
    std::basic_string<Char, Traits, Allocator> stripDirectory(const std::basic_string<Char, Traits, Allocator>& path)
    {
        typedef typename std::basic_string<Char, Traits, Allocator>::size_type size_type;

        size_type found = path.find_last_of("/\\");
        return found != std::basic_string<Char, Traits, Allocator>::npos ? path.substr(found+1) : path;
    }

    template <typename Char, typename Traits>
    std::streamsize readLogicalLine(std::basic_istream<Char, Traits>& is, Char* str, std::streamsize count)
    {
        std::streamsize bytes = 0;

        while (is.getline(str, count) || is.gcount() != 0)
        {
            if ((is.rdstate() & std::basic_istream<Char, Traits>::failbit) != 0)
            {
                // Length of logical line exceeds buffer size 
                bytes = -1;
                break;
            }

            std::streamsize pos = is.eof() ? is.gcount() : is.gcount() - 1;  
  
            ASSERT(str[pos] == '\0');

#if 0
            while (pos != 0 && isspace(str[pos - 1]))
            {
                --pos;
            }
#endif
           
            bytes += pos;
            if (pos != 0 && str[pos - 1] == '\\')
            { 
                str[pos-1] = ' ';
                str += pos;
                count -= pos; 
            } 
            else
            {
                break;
            }
        }

        return bytes;
    }
}


#endif
