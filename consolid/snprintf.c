/*  Consolid - Consolidates C compilers
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#if defined(_MSC_VER) && (_MSC_VER < 1900)

#include "consolid.h"
#include <stdarg.h>

int snprintf(char* str, size_t size, const char* format, ...)
{
    int count;
    va_list ap;   
	
    va_start(ap, format);
	count = _vscprintf(format, ap);
    if (size)
    {
        _vsnprintf_s(str, size, _TRUNCATE, format, ap);
    }
    va_end(ap);
    
    return count;
}

#endif
