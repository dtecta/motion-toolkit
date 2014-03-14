#ifndef GUTS_MEMALLOCLOG_HPP
#define GUTS_MEMALLOCLOG_HPP

#include "List.hpp"
#include "Log.hpp"
#include "MemAlloc.hpp"

namespace guts
{
    class MemAllocLog
        : public guts::Singleton<MemAllocLog>
    {
    public:
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

		template <typename ReportLeakFunc>
        void reportLeaks(ReportLeakFunc& func) const
        {
            for (Link* it = mList.begin(); it != mList.end(); it = it->next())
            {
                Allocation* link = static_cast<Allocation*>(it);
				func(link->file(), link->line());
            }
        }

		void logLeaks() const
        {
            for (Link* it = mList.begin(); it != mList.end(); it = it->next())
            {
                Allocation* link = static_cast<Allocation*>(it);
				Log::instance().notify(Log::WARNING, "Memory allocated in source %s line %d leaked.\n", link->file(), link->line());
            }
        }

    private:
        class Allocation
            : public Link        
        {
        public:
            Allocation(const char* file, unsigned line)
                : mFile(file)
                , mLine((line & 0xffff) | CHECK_MARK)
            {} 
 
            const char* file() const { return mFile; }
            unsigned line() const { return mLine & 0xffff; }

            bool isOK() const { return (mLine & 0xffff0000) == CHECK_MARK; } 

        private:
            enum { CHECK_MARK = 0xA11C0000 };

            const char* mFile;
            union 
            {
                uint32_t mLine;
                char mPadding[sizeof(void*)];  
            };
        };

        List mList;
    };
}

#endif
