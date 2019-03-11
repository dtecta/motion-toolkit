/*  Guts - Generic Utilities 
    Copyright (c) 2006-2019 Gino van den Bergen, DTECTA

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

#define SCOPED_FUNCTION_LOG guts::ScopedFunctionLog guard(__FUNCTION__);


namespace guts
{  
	typedef void (*LogCallback)(void* clientData, int level, const char* format, va_list args);

    class Log
        : public guts::Singleton<Log>
    {
    public:
        enum Severity
        {
            DEBUG = 0,
            INFO,
            WARNING, 
            FATAL
        };

        Log() 
            : mCallback(0)
            , mClientData(0)
			, mSeverityLevel(0)
        {}

        void notify(int level, const char* format, ...)
        {
            if (mCallback != 0 && level >= mSeverityLevel)
            {
                va_list args;
                va_start(args, format);
                (*mCallback)(mClientData, level, format, args);
                va_end(args);	
            }
        }

        void setCallback(LogCallback callback, void* clientData) 
        { 
            mCallback = callback; 
            mClientData = clientData;
        }
        
        void setSeverityLevel(int severityLevel) 
        { 
            mSeverityLevel = severityLevel; 
        }

    private:
        LogCallback mCallback;
        void* mClientData;
        int mSeverityLevel;
    };

    class ScopedFunctionLog
    {
    public:
        ScopedFunctionLog(const char* function)
            : mFunction(function)
        {
            Log::instance().notify(Log::DEBUG, "Entering %s\n", function);
        }

        ~ScopedFunctionLog()
        {
            Log::instance().notify(Log::DEBUG, "Exiting %s\n", mFunction);
        }

    private:
        const char* mFunction;
    };
}

#endif
