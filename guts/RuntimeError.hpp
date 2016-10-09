/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_RUNTIMEERROR_HPP
#define GUTS_RUNTIMEERROR_HPP

#include <stdio.h>
#include <stdarg.h>
#include <exception>

namespace guts
{
    class RuntimeError
        : public std::exception
    {
    public:
        RuntimeError(const char* format, ...)
        {
            va_list args;	
            va_start(args, format);	
            vsnprintf(mMessage, NCHARS, format, args);
            va_end(args);	
        }

        virtual const char* what() const throw() { return mMessage; }
 
    private:
        enum { NCHARS = 2048 };
        char mMessage[NCHARS];          
    };
}

#endif
