#ifndef GUTS_OBSERVER_HPP
#define GUTS_OBSERVER_HPP

#include <guts/Vector.hpp>
#include <algorithm>

namespace guts
{
	class Observer
	{
	public:
        virtual ~Observer() {}
        virtual void update() = 0;
        virtual void expire() = 0;
	};

	class DefaultSubject
    {
    public:
		void attach(Observer* UNUSED(observer)) { } 
        void detach(Observer* UNUSED(observer)) { }
        void notify() const {}
    };

    class SingularSubject
    {
    public:
        void attach(Observer* observer) 
        {
            ASSERT(mObserver == 0);
            ASSERT(observer != 0);
            mObserver = observer;
        } 

        void detach(Observer* observer) 
        {
            ASSERT(mObserver == observer);
            mObserver = 0;
        }

        void notify() const
        {
            if (mObserver != 0)
            {
                mObserver->update();
            }
        }

        Observer* observer() const { return mObserver; }

	protected:
        SingularSubject()
            : mObserver(0)
        {}

        ~SingularSubject() 
        {
            if (mObserver != 0)
            {
                mObserver->expire();
            } 
        }  

	private:
        Observer* mObserver;
    };

    class PluralSubject
    {
    public:
        void attach(Observer* observer)
        {
            ASSERT(observer != 0);
            mObservers.push_back(observer);
        }

        void detach(Observer* observer)
        {
            ObserverList::iterator it = std::find(mObservers.begin(), mObservers.end(), observer);
            ASSERT(it != mObservers.end());
            if (it != mObservers.end() - 1)
            {
                *it = mObservers.back();
            }
            mObservers.pop_back();
        }

        void notify() const
        {
            for (ObserverList::const_iterator it = mObservers.begin(), end = mObservers.end(); it != end; ++it)
            {
                (*it)->update();
            } 
        }  

        template <typename Predicate>
        Observer* retrieveObserver(const Predicate& predicate) const
        {
            ObserverList::const_iterator it = mObservers.begin(), end = mObservers.end();
            while (it != end && !predicate(*it))
            {
                ++it;
            } 

            return it != end ? *it : 0;
        }

        size_t observerCount() const { return mObservers.size(); }

    protected:
        ~PluralSubject()
        {
            ObserverList observerList = mObservers; // Make a copy in case expire results in detachment
            for (ObserverList::const_iterator it = observerList.begin(), end = observerList.end(); it != end; ++it)
            {
                (*it)->expire();
            } 
        }

	private:
        typedef guts::Vector<Observer*>::RT ObserverList;

        ObserverList mObservers;
    };
}

#endif
