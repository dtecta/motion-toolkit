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

#ifndef GUTS_INVARIANT_HPP
#define GUTS_INVARIANT_HPP

// A bug in VC7.1 and 8.0 does not allow me to declare friend class templates from a different namespace.
#if _MSC_VER < 1500 
#   define INVARIANT public: void _invariant_() const
#else 
#   define INVARIANT template <typename> friend class ::guts::InvariantGuard; void _invariant_() const
#endif

#if !defined(NDEBUG) && defined(GUARD_INVARIANTS)
#   define GUARD_INVARIANT(ptr) const guts::Guard& _guard_ = guts::makeInvariantGuard(ptr); ((void)_guard_)
#   define GUARD_INVARIANT_AT_EXIT(ptr) const guts::Guard& _guard_ = guts::makeInvariantGuardExit(ptr); ((void)_guard_)
#else
#   define GUARD_INVARIANT(ptr) ((void)0)
#   define GUARD_INVARIANT_AT_EXIT(ptr) ((void)0)
#endif

namespace guts
{
    class Guard {};

    template <typename T>
    class InvariantGuard
        : public Guard
    {
    public: 
        InvariantGuard(const T* ptr, int)
            : mPtr(ptr)
        {}

        InvariantGuard(const T* ptr)
            : mPtr(ptr)
        {
            mPtr->_invariant_();
        }

        ~InvariantGuard()
        {
            mPtr->_invariant_();   
        }

    private:
        const T* mPtr;
    };

    template <typename T>
    InvariantGuard<T> makeInvariantGuard(T* ptr)
    {
        return InvariantGuard<T>(ptr);
    } 

    template <typename T>
    InvariantGuard<T> makeInvariantGuardExit(T* ptr)
    {
        return InvariantGuard<T>(ptr, 0);
    }
}

#endif
