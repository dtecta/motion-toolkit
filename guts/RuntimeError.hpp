/*
 * GUTS - Generic Utilities 
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
        enum { NCHARS = 256 };
        char mMessage[NCHARS];          
    };
}

#endif
