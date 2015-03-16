/*  Guts - Generic Utilities 
    Copyright (c) 2006 Gino van den Bergen, DTECTA

    Source published under the terms of the MIT License. 
    For details please see COPYING file or visit 
    http://opensource.org/licenses/MIT
*/

#ifndef GUTS_LOG_HPP
#define GUTS_LOG_HPP

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <guts/Singleton.hpp>

namespace guts
{  
    class OutputStream
    {
    public:
        virtual ~OutputStream() {}
        virtual void write(const char*) = 0;
    };

    class Log
        : public guts::Singleton<Log>
    {
    public:  
        Log() 
            : mOutputStream(0)
            , mSeverityLevel(INFO)
        {}

        enum Severity
        {
            DEBUG = 0,
            INFO,
            WARNING, 
            FATAL
        };
        
        enum { MAXSIZE = 1024 };


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
        OutputStream* mOutputStream;
        Severity mSeverityLevel;
    };
}

#endif
