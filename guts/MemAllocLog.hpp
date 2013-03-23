#ifndef GUTS_MEMALLOCLOG_HPP
#define GUTS_MEMALLOCLOG_HPP

#include "List.hpp"
#include "Log.hpp"
#include "MemAlloc.hpp"

namespace guts
{
    class MemAllocLog
    {
    public:
        static MemAllocLog& instance() 
        { 
            static MemAllocLog theMemoryLogger; 
            return theMemoryLogger; 
        }

        void* alloc(size_t n, const char* file, unsigned line) 
        {  
            Allocation* link = static_cast<Allocation*>(MemAlloc::instance().alloc(sizeof(Allocation) + n));
            new (link) Allocation(file, line);
            mList.push_back(link);
            return link + 1;
        }

        void free(void* p)
        {  
            if (p != 0)
            {
                Allocation* link = static_cast<Allocation*>(p) - 1;
                ASSERT(link->isOK());
                ASSERT(!link->isFree());
                link->remove();
                MemAlloc::instance().free(link);
            }
        }

        void reportLeaks() const
        {
            for (Link* it = mList.begin(); it != mList.end(); it = it->next())
            {
                Allocation* link = static_cast<Allocation*>(it);

                Log::instance().notify(Log::WARNING, "Memory allocated in source %s line %d leaked.\n", link->file(), link->line());
            }
        }

    private:
        MemAllocLog() {}
        ~MemAllocLog() {}
      

        class Allocation
            : public Link        
        {
        public:
            Allocation(const char* file, unsigned line)
                : mFile(file)
                , mLine(line)
                , mMark(CHECK_MARK)
            {} 
 
            const char* file() const { return mFile; }
            unsigned line() const { return mLine; }

            bool isOK() const { return mMark == CHECK_MARK; } 

        private:
            enum { CHECK_MARK = 0xA11C };

            const char* mFile;
            union 
            {
                struct 
                {
                    unsigned mLine : 16;
                    unsigned mMark : 16;
                };
                char mPadding[sizeof(void*)];  
            };
        };

        List mList;
    };
}

#endif
