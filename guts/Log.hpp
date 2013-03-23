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

#ifndef GUTS_LOG_HPP
#define GUTS_LOG_HPP

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

namespace guts
{  
    class OutputStream
    {
    public:
        virtual ~OutputStream() {}
        virtual void write(const char*) = 0;
    };

    class Log
    {
    public:
        enum Severity
        {
            DEBUG = 0,
            INFO,
            WARNING, 
            FATAL
        };
        
        enum { MAXSIZE = 1024 };

        static Log& instance()
        {
            static Log theLog;
            return theLog;
        }

        void notify(Severity severity, const char* format, ...)
        {
            if (mOutputStream != 0 && severity >= mSeverityLevel)
            {
                char buffer[MAXSIZE];	
        
                va_list args;	
                va_start(args, format);	
                vsnprintf(buffer, MAXSIZE, format, args);
                mOutputStream->write(buffer);
                va_end(args);	
            }
        }

        void setOutputStream(OutputStream* outputStream) 
        { 
            mOutputStream = outputStream; 
        }
        
        void setSeverityLevel(Severity severityLevel) 
        { 
            mSeverityLevel = severityLevel; 
        }

    private:
        Log() 
            : mOutputStream(0)
            , mSeverityLevel(INFO)
        {}

        ~Log() {}

        OutputStream* mOutputStream;
        Severity mSeverityLevel;
    };
}

#endif
