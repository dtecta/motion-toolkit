#ifndef GUTS_TRACELOG_HPP
#define GUTS_TRACELOG_HPP

#include "Singleton.hpp"
#include "SStream.hpp"

namespace guts
{
	template <typename Time = long long>
    class TraceLog
        : public Singleton<TraceLog<Time> >
    {
    public:
		enum ValueType
		{
			VT_TIME,
			VT_VECTOR3,
			VT_QUATERNION,
            VT_PLANE
		};

		TraceLog();

		template <typename Value>
		bool write(ValueType type, const Value& value);

        template <typename Value>
		bool read(ValueType type, Value& value);

        const StringBuf* rdbuf() const { return mLogBuffer.rdbuf(); }

        StringStream& stream() { return mLogBuffer; }

        void clear()
        {
            mLogBuffer.clear();
        } 
 
    private:
		StringStream mLogBuffer;
    };

	template <typename Time> 
	TraceLog<Time>::TraceLog()
		: mLogBuffer(StringStream::in|StringStream::out|StringStream::binary)
	{}


	template <typename Time>
	template <typename Value>
    bool TraceLog<Time>::write(ValueType type, const Value& value)
	{
		if (mLogBuffer.put(char(type)))
        {
            if (mLogBuffer.write(reinterpret_cast<const char*>(&value), sizeof(Value)))
            {
                return true;
            }
        }
        return false;
	}

    template <typename Time>
	template <typename Value>
    bool TraceLog<Time>::read(ValueType type, Value& value)
	{
        char c;
		if (mLogBuffer.get(c) && ValueType(c) == type)
        { 
            Value tmp;
            if (mLogBuffer.read(reinterpret_cast<char*>(&tmp), sizeof(Value)))
            {
               value = tmp;
               return true;
            }
        } 
        return false;
	}



    
}

#endif
