// vectorfix standard header fixed for aligned element types
#pragma once
#ifndef _MSVC100STDVECTORFIX_HPP_
#define _MSVC100STDVECTORFIX_HPP_
#ifndef RC_INVOKED
#include <memory>
#include <stdexcept>
#include <xfunctional>

 #pragma pack(push,_CRT_PACKING)
 #pragma warning(push,3)

 #pragma warning(disable: 4244)

_STD_BEGIN
 #define _VECTOR_ORPHAN_RANGE	(_ITERATOR_DEBUG_LEVEL == 2)

		// TEMPLATE CLASS _Vectorfix_const_iterator
template<class _Myvec>
	class _Vectorfix_const_iterator
		: public _Iterator012<random_access_iterator_tag,
			typename _Myvec::value_type,
			typename _Myvec::difference_type,
			typename _Myvec::const_pointer,
			typename _Myvec::const_reference,
			_Iterator_base>
	{	// iterator for nonmutable vector
public:
	typedef _Vectorfix_const_iterator<_Myvec> _Myiter;
	typedef random_access_iterator_tag iterator_category;

	typedef typename _Myvec::pointer _Tptr;
	typedef typename _Myvec::value_type value_type;
	typedef typename _Myvec::difference_type difference_type;
	typedef typename _Myvec::const_pointer pointer;
	typedef typename _Myvec::const_reference reference;

	_Vectorfix_const_iterator()
		: _Ptr(0)
		{	// construct with null pointer
		}

	_Vectorfix_const_iterator(_Tptr _Parg, const _Container_base *_Pvector)
		: _Ptr(_Parg)
		{	// construct with pointer _Parg
		this->_Adopt(_Pvector);
		}

	typedef pointer _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
		{	// reset from unchecked iterator
		this->_Ptr = (_Tptr)_Right;
		return (*this);
		}

	_Unchecked_type _Unchecked() const
		{	// make an unchecked iterator
		return (_Unchecked_type(this->_Ptr));
		}

	reference operator*() const
		{	// return designated object
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (this->_Getcont() == 0
			|| this->_Ptr == 0
			|| this->_Ptr < ((_Myvec *)this->_Getcont())->_Myfirst
			|| ((_Myvec *)this->_Getcont())->_Mylast <= this->_Ptr)
			{	// report error
			_DEBUG_ERROR("vector iterator not dereferencable");
			_SCL_SECURE_OUT_OF_RANGE;
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			this->_Ptr != 0
			&& ((_Myvec *)this->_Getcont())->_Myfirst <= this->_Ptr
			&& this->_Ptr < ((_Myvec *)this->_Getcont())->_Mylast);
 #endif /* _ITERATOR_DEBUG_LEVEL */

		__analysis_assume(this->_Ptr != 0);

		return (*this->_Ptr);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (&**this);
		}

	_Myiter& operator++()
		{	// preincrement
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (this->_Getcont() == 0
			|| this->_Ptr == 0
			|| ((_Myvec *)this->_Getcont())->_Mylast <= this->_Ptr)
			{	// report error
			_DEBUG_ERROR("vector iterator not incrementable");
			_SCL_SECURE_OUT_OF_RANGE;
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			this->_Ptr != 0
			&& this->_Ptr < ((_Myvec *)this->_Getcont())->_Mylast);
 #endif /* _ITERATOR_DEBUG_LEVEL */

		++this->_Ptr;
		return (*this);
		}

	_Myiter operator++(int)
		{	// postincrement
		_Myiter _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_Myiter& operator--()
		{	// predecrement
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (this->_Getcont() == 0
			|| this->_Ptr == 0
			|| this->_Ptr <= ((_Myvec *)this->_Getcont())->_Myfirst)
			{	// report error
			_DEBUG_ERROR("vector iterator not decrementable");
			_SCL_SECURE_OUT_OF_RANGE;
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			this->_Ptr != 0
			&& ((_Myvec *)this->_Getcont())->_Myfirst < this->_Ptr);
 #endif /* _ITERATOR_DEBUG_LEVEL */

		--this->_Ptr;
		return (*this);
		}

	_Myiter operator--(int)
		{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	_Myiter& operator+=(difference_type _Off)
		{	// increment by integer
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (this->_Getcont() == 0
			|| this->_Ptr + _Off < ((_Myvec *)this->_Getcont())->_Myfirst
			|| ((_Myvec *)this->_Getcont())->_Mylast < this->_Ptr + _Off)
			{	// report error
			_DEBUG_ERROR("vector iterator + offset out of range");
			_SCL_SECURE_OUT_OF_RANGE;
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0);
		_SCL_SECURE_VALIDATE_RANGE(
			((_Myvec *)this->_Getcont())->_Myfirst <= this->_Ptr + _Off
			&& this->_Ptr + _Off <= ((_Myvec *)this->_Getcont())->_Mylast);
 #endif /* _ITERATOR_DEBUG_LEVEL */

		_Ptr += _Off;
		return (*this);
		}

	_Myiter operator+(difference_type _Off) const
		{	// return this + integer
		_Myiter _Tmp = *this;
		return (_Tmp += _Off);
		}

	_Myiter& operator-=(difference_type _Off)
		{	// decrement by integer
		return (*this += -_Off);
		}

	_Myiter operator-(difference_type _Off) const
		{	// return this - integer
		_Myiter _Tmp = *this;
		return (_Tmp -= _Off);
		}

	difference_type operator-(const _Myiter& _Right) const
		{	// return difference of iterators
		_Compat(_Right);
		return (this->_Ptr - _Right._Ptr);
		}

	reference operator[](difference_type _Off) const
		{	// subscript
		return (*(*this + _Off));
		}

	bool operator==(const _Myiter& _Right) const
		{	// test for iterator equality
		_Compat(_Right);
		return (this->_Ptr == _Right._Ptr);
		}

	bool operator!=(const _Myiter& _Right) const
		{	// test for iterator inequality
		return (!(*this == _Right));
		}

	bool operator<(const _Myiter& _Right) const
		{	// test if this < _Right
		_Compat(_Right);
		return (this->_Ptr < _Right._Ptr);
		}

	bool operator>(const _Myiter& _Right) const
		{	// test if this > _Right
		return (_Right < *this);
		}

	bool operator<=(const _Myiter& _Right) const
		{	// test if this <= _Right
		return (!(_Right < *this));
		}

	bool operator>=(const _Myiter& _Right) const
		{	// test if this >= _Right
		return (!(*this < _Right));
		}

 #if _ITERATOR_DEBUG_LEVEL == 2
	void _Compat(const _Myiter& _Right) const
		{	// test for compatible iterator pair
		if (this->_Getcont() == 0
			|| this->_Getcont() != _Right._Getcont())
			{	// report error
			_DEBUG_ERROR("vector iterators incompatible");
			_SCL_SECURE_INVALID_ARGUMENT;
			}
		}

 #elif _ITERATOR_DEBUG_LEVEL == 1
	void _Compat(const _Myiter& _Right) const
		{	// test for compatible iterator pair
		_SCL_SECURE_VALIDATE(this->_Getcont() != 0);
		_SCL_SECURE_VALIDATE_RANGE(this->_Getcont() == _Right._Getcont());
		}

 #else /* _ITERATOR_DEBUG_LEVEL == 0 */
	void _Compat(const _Myiter&) const
		{	// test for compatible iterator pair
		}
 #endif /* _ITERATOR_DEBUG_LEVEL */

	_Tptr _Ptr;	// pointer to element in vector
	};

template<class _Myvec> inline
	typename _Vectorfix_const_iterator<_Myvec>::_Unchecked_type
		_Unchecked(_Vectorfix_const_iterator<_Myvec> _Iter)
	{	// convert to unchecked
	return (_Iter._Unchecked());
	}

template<class _Myvec> inline
	_Vectorfix_const_iterator<_Myvec>&
		_Rechecked(_Vectorfix_const_iterator<_Myvec>& _Iter,
			typename _Vectorfix_const_iterator<_Myvec>
				::_Unchecked_type _Right)
	{	// convert to checked
	return (_Iter._Rechecked(_Right));
	}

template<class _Myvec> inline
	_Vectorfix_const_iterator<_Myvec> operator+(
		typename _Vectorfix_const_iterator<_Myvec>::difference_type _Off,
		_Vectorfix_const_iterator<_Myvec> _Next)
	{	// add offset to iterator
	return (_Next += _Off);
	}

		// TEMPLATE CLASS _Vectorfix_iterator
template<class _Myvec>
	class _Vectorfix_iterator
		: public _Vectorfix_const_iterator<_Myvec>
	{	// iterator for mutable vector
public:
	typedef _Vectorfix_iterator<_Myvec> _Myiter;
	typedef _Vectorfix_const_iterator<_Myvec> _Mybase;
	typedef random_access_iterator_tag iterator_category;

	typedef typename _Myvec::value_type value_type;
	typedef typename _Myvec::difference_type difference_type;
	typedef typename _Myvec::pointer pointer;
	typedef typename _Myvec::reference reference;

	_Vectorfix_iterator()
		{	// construct with null vector pointer
		}

	_Vectorfix_iterator(pointer _Parg, const _Container_base *_Pvector)
		: _Mybase(_Parg, _Pvector)
		{	// construct with pointer _Parg
		}

	typedef pointer _Unchecked_type;

	_Myiter& _Rechecked(_Unchecked_type _Right)
		{	// reset from unchecked iterator
		this->_Ptr = _Right;
		return (*this);
		}

	_Unchecked_type _Unchecked() const
		{	// make an unchecked iterator
		return (_Unchecked_type(this->_Ptr));
		}

	reference operator*() const
		{	// return designated object
		return ((reference)**(_Mybase *)this);
		}

	pointer operator->() const
		{	// return pointer to class object
		return (&**this);
		}

	_Myiter& operator++()
		{	// preincrement
		++*(_Mybase *)this;
		return (*this);
		}

	_Myiter operator++(int)
		{	// postincrement
		_Myiter _Tmp = *this;
		++*this;
		return (_Tmp);
		}

	_Myiter& operator--()
		{	// predecrement
		--*(_Mybase *)this;
		return (*this);
		}

	_Myiter operator--(int)
		{	// postdecrement
		_Myiter _Tmp = *this;
		--*this;
		return (_Tmp);
		}

	_Myiter& operator+=(difference_type _Off)
		{	// increment by integer
		*(_Mybase *)this += _Off;
		return (*this);
		}

	_Myiter operator+(difference_type _Off) const
		{	// return this + integer
		_Myiter _Tmp = *this;
		return (_Tmp += _Off);
		}

	_Myiter& operator-=(difference_type _Off)
		{	// decrement by integer
		return (*this += -_Off);
		}

	_Myiter operator-(difference_type _Off) const
		{	// return this - integer
		_Myiter _Tmp = *this;
		return (_Tmp -= _Off);
		}

	difference_type operator-(const _Mybase& _Right) const
		{	// return difference of iterators
		return (*(_Mybase *)this - _Right);
		}

	reference operator[](difference_type _Off) const
		{	// subscript
		return (*(*this + _Off));
		}
	};

template<class _Myvec> inline
	typename _Vectorfix_iterator<_Myvec>::_Unchecked_type
		_Unchecked(_Vectorfix_iterator<_Myvec> _Iter)
	{	// convert to unchecked
	return (_Iter._Unchecked());
	}

template<class _Myvec> inline
	_Vectorfix_iterator<_Myvec>&
		_Rechecked(_Vectorfix_iterator<_Myvec>& _Iter,
			typename _Vectorfix_iterator<_Myvec>
				::_Unchecked_type _Right)
	{	// convert to checked
	return (_Iter._Rechecked(_Right));
	}

template<class _Myvec> inline
	_Vectorfix_iterator<_Myvec> operator+(
		typename _Vectorfix_iterator<_Myvec>::difference_type _Off,
		_Vectorfix_iterator<_Myvec> _Next)
	{	// add offset to iterator
	return (_Next += _Off);
	}

		// TEMPLATE CLASS _Vectorfix_val
template<class _Ty,
	class _Alloc>
	class _Vectorfix_val
		: public _Container_base
	{	// base class for vector to hold data
public:
	typedef typename _Alloc::template rebind<_Ty>::other _Alty;

 #if _ITERATOR_DEBUG_LEVEL == 0
	_Vectorfix_val(_Alloc _Al = _Alloc())
		: _Alval(_Al)
		{	// construct allocator from _Al
		_Myfirst = 0;
		_Mylast = 0;
		_Myend = 0;
		}

	~_Vectorfix_val()
		{	// destroy proxy
		}

 #else /* _ITERATOR_DEBUG_LEVEL == 0 */
	_Vectorfix_val(_Alloc _Al = _Alloc())
		: _Alval(_Al)
		{	// construct allocator from _Al
		typename _Alloc::template rebind<_Container_proxy>::other
			_Alproxy(_Alval);
		this->_Myproxy = _Alproxy.allocate(1);
		_Cons_val(_Alproxy, this->_Myproxy, _Container_proxy());
		this->_Myproxy->_Mycont = this;

		_Myfirst = 0;
		_Mylast = 0;
		_Myend = 0;
		}

	~_Vectorfix_val()
		{	// destroy proxy
		typename _Alloc::template rebind<_Container_proxy>::other
			_Alproxy(_Alval);
		this->_Orphan_all();
		_Dest_val(_Alproxy, this->_Myproxy);
		_Alproxy.deallocate(this->_Myproxy, 1);
		this->_Myproxy = 0;
		}
 #endif /* _ITERATOR_DEBUG_LEVEL == 0 */

	typedef typename _Alty::size_type size_type;
	typedef typename _Alty::difference_type difference_type;
	typedef typename _Alty::pointer pointer;
	typedef typename _Alty::const_pointer const_pointer;
	typedef typename _Alty::reference reference;
	typedef typename _Alty::const_reference const_reference;
	typedef typename _Alty::value_type value_type;

	pointer _Myfirst;	// pointer to beginning of array
	pointer _Mylast;	// pointer to current end of sequence
	pointer _Myend;	// pointer to end of array
	_Alty _Alval;	// allocator object for values
	};

		// TEMPLATE CLASS vectorfix
template<class _Ty,
	class _Ax = allocator<_Ty> >
	class vectorfix
		: public _Vectorfix_val<_Ty, _Ax>
	{	// varying size array of values
public:
	typedef vectorfix<_Ty, _Ax> _Myt;
	typedef _Vectorfix_val<_Ty, _Ax> _Mybase;
	typedef typename _Mybase::_Alty _Alloc;

	typedef _Alloc allocator_type;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::difference_type difference_type;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::const_pointer const_pointer;
	typedef typename _Alloc::reference reference;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::value_type value_type;

 #define _VICONT(it)	it._Getcont()
 #define _VIPTR(it)	(it)._Ptr

	typedef _Vectorfix_iterator<_Mybase> iterator;
	typedef _Vectorfix_const_iterator<_Mybase> const_iterator;

	typedef _STD reverse_iterator<iterator> reverse_iterator;
	typedef _STD reverse_iterator<const_iterator> const_reverse_iterator;

	vectorfix()
		: _Mybase()
		{	// construct empty vector
		}

	explicit vectorfix(const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct empty vector with allocator
		}

	explicit vectorfix(size_type _Count)
		: _Mybase()
		{	// construct from _Count * _Ty()
		resize(_Count);
		}

	vectorfix(size_type _Count, const _Ty& _Val)
		: _Mybase()
		{	// construct from _Count * _Val
		_Construct_n(_Count, _STD addressof(_Val));
		}

	vectorfix(size_type _Count, const _Ty& _Val, const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct from _Count * _Val, with allocator
		_Construct_n(_Count, _STD addressof(_Val));
		}

	vectorfix(const _Myt& _Right)
		: _Mybase(_Right._Alval)
		{	// construct by copying _Right
		if (_Buy(_Right.size()))
			_TRY_BEGIN
			this->_Mylast = _Ucopy(_Right.begin(), _Right.end(),
				this->_Myfirst);
			_CATCH_ALL
			_Tidy();
			_RERAISE;
			_CATCH_END
		}

	template<class _Iter>
		vectorfix(_Iter _First, _Iter _Last)
		: _Mybase()
		{	// construct from [_First, _Last)
		_Construct(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		vectorfix(_Iter _First, _Iter _Last, const _Alloc& _Al)
		: _Mybase(_Al)
		{	// construct from [_First, _Last), with allocator
		_Construct(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Construct(_Iter _Count, _Iter _Val, _Int_iterator_tag)
		{	// initialize with _Count * _Val
		size_type _Size = (size_type)_Count;
		_Ty _Newval = (_Ty)_Val;
		_Construct_n(_Size, _STD addressof(_Newval));
		}

	template<class _Iter>
		void _Construct(_Iter _First,
			_Iter _Last, input_iterator_tag)
		{	// initialize with [_First, _Last), input iterators
		_TRY_BEGIN
		insert(begin(), _First, _Last);
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	void _Construct_n(size_type _Count, const _Ty *_Pval)
		{	// construct from _Count * *_Pval
		if (_Buy(_Count))
			{	// nonzero, fill it
			_TRY_BEGIN
			this->_Mylast = _Ufill(this->_Myfirst, _Count, _Pval);
			_CATCH_ALL
			_Tidy();
			_RERAISE;
			_CATCH_END
			}
		}

	vectorfix(_Myt&& _Right)
		: _Mybase(_Right._Alval)
		{	// construct by moving _Right
		_Assign_rv(_STD forward<_Myt>(_Right));
		}

	_Myt& operator=(_Myt&& _Right)
		{	// assign by moving _Right
		_Assign_rv(_STD forward<_Myt>(_Right));
		return (*this);
		}

	void _Assign_rv(_Myt&& _Right)
		{	// assign by moving _Right
		if (this == &_Right)
			;
		else if (get_allocator() != _Right.get_allocator())
			{	// move construct a copy
			clear();
			for (iterator _Next = _Right.begin(); _Next != _Right.end();
				++_Next)
				push_back(_STD forward<_Ty>(*_Next));
			}
		else
			{	// clear this and steal from _Right
			_Tidy();
			this->_Swap_all((_Myt&)_Right);
			this->_Myfirst = _Right._Myfirst;
			this->_Mylast = _Right._Mylast;
			this->_Myend = _Right._Myend;

			_Right._Myfirst = 0;
			_Right._Mylast = 0;
			_Right._Myend = 0;
			}
		}

	void push_back(_Ty&& _Val)
		{	// insert element at end
		if (_Inside(_STD addressof(_Val)))
			{	// push back an element
			size_type _Idx = _STD addressof(_Val) - this->_Myfirst;
			if (this->_Mylast == this->_Myend)
				_Reserve(1);
			_Orphan_range(this->_Mylast, this->_Mylast);
			_Cons_val(this->_Alval,
				this->_Mylast,
				_STD forward<_Ty>(this->_Myfirst[_Idx]));
			++this->_Mylast;
			}
		else
			{	// push back a non-element
			if (this->_Mylast == this->_Myend)
				_Reserve(1);
			_Orphan_range(this->_Mylast, this->_Mylast);
			_Cons_val(this->_Alval,
				this->_Mylast,
				_STD forward<_Ty>(_Val));
			++this->_Mylast;
			}
		}

	void emplace_back(_Ty&& _Val)
		{	// insert element at end
		push_back(_STD forward<_Ty>(_Val));
		}

	template<class _Valty>
		void emplace_back(_Valty&& _Val)
		{	// insert element at end
		if (this->_Mylast == this->_Myend)
			_Reserve(1);
		_Orphan_range(this->_Mylast, this->_Mylast);
		_Cons_val(this->_Alval,
			this->_Mylast,
			_STD forward<_Valty>(_Val));
		++this->_Mylast;
		}

	template<class _Valty>
		iterator insert(const_iterator _Where, _Valty&& _Val)
		{	// insert _Val at _Where
		return (emplace(_Where, _STD forward<_Valty>(_Val)));
		}

	template<class _Valty>
		iterator emplace(const_iterator _Where, _Valty&& _Val)
		{	// insert _Val at _Where
		size_type _Off = _VIPTR(_Where) - this->_Myfirst;

 #if _ITERATOR_DEBUG_LEVEL == 2
		if (size() < _Off)
			_DEBUG_ERROR("vector emplace iterator outside range");
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		emplace_back(_STD forward<_Valty>(_Val));
		_STD rotate(begin() + _Off, end() - 1, end());
		return (begin() + _Off);
		}

	void swap(_Myt&& _Right)
		{	// exchange contents with movable _Right
		if (this != &_Right)
			{	// swap with emptied container
			clear();
			this->_Swap_all((_Myt&)_Right);
			_Assign_rv(_STD forward<_Myt>(_Right));
			}
		}

	~vectorfix()
		{	// destroy the object
		_Tidy();
		}

	_Myt& operator=(const _Myt& _Right)
		{	// assign _Right
		if (this != &_Right)
			{	// worth doing
			this->_Orphan_all();

			if (_Right.size() == 0)
				clear();	// new sequence empty, erase existing sequence
			else if (_Right.size() <= size())
				{	// enough elements, copy new and destroy old
				pointer _Ptr = _STD _Copy_impl(_Right._Myfirst, _Right._Mylast,
					this->_Myfirst);	// copy new
				_Destroy(_Ptr, this->_Mylast);	// destroy old
				this->_Mylast = this->_Myfirst + _Right.size();
				}
			else if (_Right.size() <= capacity())
				{	// enough room, copy and construct new
				pointer _Ptr = _Right._Myfirst + size();
				_STD _Copy_impl(_Right._Myfirst, _Ptr, this->_Myfirst);
				this->_Mylast = _Ucopy(_Ptr, _Right._Mylast, this->_Mylast);
				}
			else
				{	// not enough room, allocate new array and construct new
				if (this->_Myfirst != 0)
					{	// discard old array
					_Destroy(this->_Myfirst, this->_Mylast);
					this->_Alval.deallocate(this->_Myfirst,
						this->_Myend - this->_Myfirst);
					}
				if (_Buy(_Right.size()))
					this->_Mylast = _Ucopy(_Right._Myfirst, _Right._Mylast,
						this->_Myfirst);
				}
			}
		return (*this);
		}

	void reserve(size_type _Count)
		{	// determine new minimum length of allocated storage
		if (max_size() < _Count)
			_Xlen();	// result too long
		else if (capacity() < _Count)
			{	// not enough room, reallocate
			pointer _Ptr = this->_Alval.allocate(_Count);

			_TRY_BEGIN
			_Umove(this->_Myfirst, this->_Mylast, _Ptr);
			_CATCH_ALL
			this->_Alval.deallocate(_Ptr, _Count);
			_RERAISE;
			_CATCH_END

			size_type _Size = size();
			if (this->_Myfirst != 0)
				{	// destroy and deallocate old array
				_Destroy(this->_Myfirst, this->_Mylast);
				this->_Alval.deallocate(this->_Myfirst,
					this->_Myend - this->_Myfirst);
				}

			this->_Orphan_all();
			this->_Myend = _Ptr + _Count;
			this->_Mylast = _Ptr + _Size;
			this->_Myfirst = _Ptr;
			}
		}

	size_type capacity() const
		{	// return current length of allocated storage
		return (this->_Myend - this->_Myfirst);
		}

	iterator begin()
		{	// return iterator for beginning of mutable sequence
		return (iterator(this->_Myfirst, this));
		}

	const_iterator begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(this->_Myfirst, this));
		}

	iterator end()
		{	// return iterator for end of mutable sequence
		return (iterator(this->_Mylast, this));
		}

	const_iterator end() const
		{	// return iterator for end of nonmutable sequence
		return (const_iterator(this->_Mylast, this));
		}

	iterator _Make_iter(const_iterator _Where) const
		{	// make iterator from const_iterator
		return (iterator(_Where._Ptr, this));
		}

	reverse_iterator rbegin()
		{	// return iterator for beginning of reversed mutable sequence
		return (reverse_iterator(end()));
		}

	const_reverse_iterator rbegin() const
		{	// return iterator for beginning of reversed nonmutable sequence
		return (const_reverse_iterator(end()));
		}

	reverse_iterator rend()
		{	// return iterator for end of reversed mutable sequence
		return (reverse_iterator(begin()));
		}

	const_reverse_iterator rend() const
		{	// return iterator for end of reversed nonmutable sequence
		return (const_reverse_iterator(begin()));
		}

 #if _HAS_CPP0X
	const_iterator cbegin() const
		{	// return iterator for beginning of nonmutable sequence
		return (((const _Myt *)this)->begin());
		}

	const_iterator cend() const
		{	// return iterator for end of nonmutable sequence
		return (((const _Myt *)this)->end());
		}

	const_reverse_iterator crbegin() const
		{	// return iterator for beginning of reversed nonmutable sequence
		return (((const _Myt *)this)->rbegin());
		}

	const_reverse_iterator crend() const
		{	// return iterator for ebd of reversed nonmutable sequence
		return (((const _Myt *)this)->rend());
		}

	void shrink_to_fit()
		{	// reduce capacity
		if (size() < capacity())
			{	// worth shrinking, do it
			_Myt _Tmp(*this);
			swap(_Tmp);
			}
		}
 #endif /* _HAS_CPP0X */

	void resize(size_type _Newsize)
		{	// determine new length, padding with _Ty() elements as needed
		if (_Newsize < size())
			erase(begin() + _Newsize, end());
		else if (size() < _Newsize)
			{	// pad as needed
			_Reserve(_Newsize - size());
			_Uninitialized_default_fill_n(this->_Mylast, _Newsize - size(),
				(_Ty *)0, this->_Alval);
			this->_Mylast += _Newsize - size();
			}
		}

	void resize(size_type _Newsize, const _Ty& _Val)
		{	// determine new length, padding with _Val elements as needed
		if (size() < _Newsize)
			_Insert_n(end(), _Newsize - size(), _Val);
		else if (_Newsize < size())
			erase(begin() + _Newsize, end());
		}

	size_type size() const
		{	// return length of sequence
		return (this->_Mylast - this->_Myfirst);
		}

	size_type max_size() const
		{	// return maximum possible length of sequence
		return (this->_Alval.max_size());
		}

	bool empty() const
		{	// test if sequence is empty
		return (this->_Myfirst == this->_Mylast);
		}

	_Alloc get_allocator() const
		{	// return allocator object for values
		return (this->_Alval);
		}

	const_reference at(size_type _Pos) const
		{	// subscript nonmutable sequence with checking
		if (size() <= _Pos)
			_Xran();
		return (*(this->_Myfirst + _Pos));
		}

	reference at(size_type _Pos)
		{	// subscript mutable sequence with checking
		if (size() <= _Pos)
			_Xran();
		return (*(this->_Myfirst + _Pos));
		}

	const_reference operator[](size_type _Pos) const
		{	// subscript nonmutable sequence
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (size() <= _Pos)
			{	// report error
			_DEBUG_ERROR("vector subscript out of range");
			_SCL_SECURE_OUT_OF_RANGE;
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE_RANGE(_Pos < size());
 #endif /* _ITERATOR_DEBUG_LEVEL */

		return (*(this->_Myfirst + _Pos));
		}

	reference operator[](size_type _Pos)
		{	// subscript mutable sequence
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (size() <= _Pos)
			{	// report error
			_DEBUG_ERROR("vector subscript out of range");
			_SCL_SECURE_OUT_OF_RANGE;
			}

 #elif _ITERATOR_DEBUG_LEVEL == 1
		_SCL_SECURE_VALIDATE_RANGE(_Pos < size());
 #endif /* _ITERATOR_DEBUG_LEVEL */

		return (*(this->_Myfirst + _Pos));
		}

 #if _HAS_CPP0X
	pointer data()
		{	// return address of first element
		return (this->_Myfirst);
		}

	const_pointer data() const
		{	// return address of first element
		return (this->_Myfirst);
		}
 #endif /* _HAS_CPP0X */

	reference front()
		{	// return first element of mutable sequence
		return (*begin());
		}

	const_reference front() const
		{	// return first element of nonmutable sequence
		return (*begin());
		}

	reference back()
		{	// return last element of mutable sequence
		return (*(end() - 1));
		}

	const_reference back() const
		{	// return last element of nonmutable sequence
		return (*(end() - 1));
		}

	void push_back(const _Ty& _Val)
		{	// insert element at end
		if (_Inside(_STD addressof(_Val)))
			{	// push back an element
			size_type _Idx = _STD addressof(_Val) - this->_Myfirst;
			if (this->_Mylast == this->_Myend)
				_Reserve(1);
			_Orphan_range(this->_Mylast, this->_Mylast);
			_Cons_val(this->_Alval,
				this->_Mylast,
				this->_Myfirst[_Idx]);
			++this->_Mylast;
			}
		else
			{	// push back a non-element
			if (this->_Mylast == this->_Myend)
				_Reserve(1);
			_Orphan_range(this->_Mylast, this->_Mylast);
			_Cons_val(this->_Alval,
				this->_Mylast,
				_Val);
			++this->_Mylast;
			}
		}

 #if _ITERATOR_DEBUG_LEVEL == 2
	void pop_back()
		{	// erase element at end
		if (empty())
			_DEBUG_ERROR("vector empty before pop");
		else
			{	// erase last element
			_Orphan_range(this->_Mylast - 1, this->_Mylast);
			_Dest_val(this->_Alval,
				this->_Mylast - 1);
			--this->_Mylast;
			}
		}

 #else /* _ITERATOR_DEBUG_LEVEL == 2 */
	void pop_back()
		{	// erase element at end
		if (!empty())
			{	// erase last element
			_Dest_val(this->_Alval,
				this->_Mylast - 1);
			--this->_Mylast;
			}
		}
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

	template<class _Iter>
		void assign(_Iter _First, _Iter _Last)
		{	// assign [_First, _Last)
		_Assign(_First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Assign(_Iter _Count, _Iter _Val, _Int_iterator_tag)
		{	// assign _Count * _Val
		_Assign_n((size_type)_Count, (_Ty)_Val);
		}

	template<class _Iter>
		void _Assign(_Iter _First, _Iter _Last, input_iterator_tag)
		{	// assign [_First, _Last), input iterators
		erase(begin(), end());
		insert(begin(), _First, _Last);
		}

	void assign(size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		_Assign_n(_Count, _Val);
		}

	iterator insert(const_iterator _Where, const _Ty& _Val)
		{	// insert _Val at _Where
		size_type _Off = size() == 0 ? 0 : _Where - begin();
		_Insert_n(_Where, (size_type)1, _Val);
		return (begin() + _Off);
		}

	void insert(const_iterator _Where, size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, _Count, _Val);
		}

	template<class _Iter>
		void insert(const_iterator _Where, _Iter _First, _Iter _Last)
		{	// insert [_First, _Last) at _Where
		_Insert(_Where, _First, _Last, _Iter_cat(_First));
		}

	template<class _Iter>
		void _Insert(const_iterator _Where, _Iter _First, _Iter _Last,
			_Int_iterator_tag)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, (size_type)_First, (_Ty)_Last);
		}

	template<class _Iter>
		void _Insert(const_iterator _Where, _Iter _First, _Iter _Last,
			input_iterator_tag)
		{	// insert [_First, _Last) at _Where, input iterators
		size_type _Off = _VIPTR(_Where) - this->_Myfirst;

 #if _ITERATOR_DEBUG_LEVEL == 2
		if (size() < _Off)
			_DEBUG_ERROR("vector insert iterator outside range");
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		if (_First != _Last)
			{	// worth doing, gather at end and rotate into place
			size_type _Oldsize = size();

			_TRY_BEGIN
			for (; _First != _Last; ++_First)
				push_back(*_First);	// append

			_CATCH_ALL
			erase(begin() + _Oldsize, end());
			_RERAISE;
			_CATCH_END

			_STD rotate(begin() + _Off, begin() + _Oldsize, end());
			}
		}

	template<class _Iter>
		void _Insert(const_iterator _Where,
			_Iter _First, _Iter _Last, forward_iterator_tag)
		{	// insert [_First, _Last) at _Where, forward iterators
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_VICONT(_Where) != this
			|| _VIPTR(_Where) < this->_Myfirst
			|| this->_Mylast < _VIPTR(_Where))
			_DEBUG_ERROR("vector insert iterator outside range");
		_DEBUG_RANGE(_First, _Last);
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		size_type _Count = 0;
		_Distance(_First, _Last, _Count);

		if (_Count == 0)
			;
		else if (max_size() - size() < _Count)
			_Xlen();	// result too long
		else if (capacity() < size() + _Count)
			{	// not enough room, reallocate
			size_type _Capacity = _Grow_to(size() + _Count);
			pointer _Newvec = this->_Alval.allocate(_Capacity);
			pointer _Ptr = _Newvec;

			_TRY_BEGIN
			_Ptr = _Umove(this->_Myfirst, _VIPTR(_Where),
				_Newvec);	// copy prefix
			_Ptr = _Ucopy(_First, _Last, _Ptr);	// add new stuff
			_Umove(_VIPTR(_Where), this->_Mylast,
				_Ptr);	// copy suffix
			_CATCH_ALL
			_Destroy(_Newvec, _Ptr);
			this->_Alval.deallocate(_Newvec, _Capacity);
			_RERAISE;
			_CATCH_END

			_Count += size();
			if (this->_Myfirst != 0)
				{	// destroy and deallocate old array
				_Destroy(this->_Myfirst, this->_Mylast);
				this->_Alval.deallocate(this->_Myfirst,
					this->_Myend - this->_Myfirst);
				}

			this->_Orphan_all();
			this->_Myend = _Newvec + _Capacity;
			this->_Mylast = _Newvec + _Count;
			this->_Myfirst = _Newvec;
			}
		else
			{	// new stuff fits, append and rotate into place
			_Ucopy(_First, _Last, this->_Mylast);
			_STD rotate(_VIPTR(_Where), this->_Mylast,
				this->_Mylast + _Count);
			this->_Mylast += _Count;
			_Orphan_range(_VIPTR(_Where), this->_Mylast);
			}
		}

 #if _ITERATOR_DEBUG_LEVEL == 2
	iterator erase(const_iterator _Where)
		{	// erase element at where
		if (_VICONT(_Where) != this
			|| _VIPTR(_Where) < this->_Myfirst
			|| this->_Mylast <= _VIPTR(_Where))
			_DEBUG_ERROR("vector erase iterator outside range");
		_Move(_VIPTR(_Where) + 1, this->_Mylast, _VIPTR(_Where));
		_Destroy(this->_Mylast - 1, this->_Mylast);
		_Orphan_range(_VIPTR(_Where), this->_Mylast);
		--this->_Mylast;
		return (_Make_iter(_Where));
		}

 #else /* _ITERATOR_DEBUG_LEVEL == 2 */
	iterator erase(const_iterator _Where)
		{	// erase element at where
		_Move(_VIPTR(_Where) + 1, this->_Mylast,
			_VIPTR(_Where));
		_Destroy(this->_Mylast - 1, this->_Mylast);
		--this->_Mylast;
		return (_Make_iter(_Where));
		}
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

	iterator erase(const_iterator _First_arg,
		const_iterator _Last_arg)
		{	// erase [_First, _Last)
		iterator _First = _Make_iter(_First_arg);
		iterator _Last = _Make_iter(_Last_arg);

		if (_First != _Last)
			{	// worth doing, copy down over hole
 #if _ITERATOR_DEBUG_LEVEL == 2
			if (_Last < _First || _VICONT(_First) != this
				|| _VIPTR(_First) < this->_Myfirst
				|| this->_Mylast < _VIPTR(_Last))
				_DEBUG_ERROR("vector erase iterator outside range");
			pointer _Ptr = _Move(_VIPTR(_Last), this->_Mylast,
				_VIPTR(_First));
			_Orphan_range(_VIPTR(_First), this->_Mylast);

 #else /* _ITERATOR_DEBUG_LEVEL == 2 */
			pointer _Ptr = _Move(_VIPTR(_Last), this->_Mylast,
				_VIPTR(_First));
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

			_Destroy(_Ptr, this->_Mylast);
			this->_Mylast = _Ptr;
			}
		return (_Make_iter(_First));
		}

	void clear()
		{	// erase all
		erase(begin(), end());
		}

	void swap(_Myt& _Right)
		{	// exchange contents with _Right
		if (this == &_Right)
			;	// same object, do nothing
		else if (this->_Alval == _Right._Alval)
			{	// same allocator, swap control information
			this->_Swap_all(_Right);
			_STD swap(this->_Myfirst, _Right._Myfirst);
			_STD swap(this->_Mylast, _Right._Mylast);
			_STD swap(this->_Myend, _Right._Myend);
			}
		else
			{	// different allocator, do multiple assigns
			_Myt _Ts = _Move(*this);

			*this = _Move(_Right);
			_Right = _Move(_Ts);
			}
		}

protected:
	void _Assign_n(size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		_Ty _Tmp = _Val;	// in case _Val is in sequence
		erase(begin(), end());
		insert(begin(), _Count, _Tmp);
		}

	bool _Buy(size_type _Capacity)
		{	// allocate array with _Capacity elements
		this->_Myfirst = 0;
		this->_Mylast = 0;
		this->_Myend = 0;

		if (_Capacity == 0)
			return (false);
		else if (max_size() < _Capacity)
			_Xlen();	// result too long
		else
			{	// nonempty array, allocate storage
			this->_Myfirst = this->_Alval.allocate(_Capacity);
			this->_Mylast = this->_Myfirst;
			this->_Myend = this->_Myfirst + _Capacity;
			}
		return (true);
		}

	void _Destroy(pointer _First, pointer _Last)
		{	// destroy [_First, _Last) using allocator
		_Destroy_range(_First, _Last, this->_Alval);
		}

	size_type _Grow_to(size_type _Count) const
		{	// grow by 50% or at least to _Count
		size_type _Capacity = capacity();

		_Capacity = max_size() - _Capacity / 2 < _Capacity
			? 0 : _Capacity + _Capacity / 2;	// try to grow by 50%
		if (_Capacity < _Count)
			_Capacity = _Count;
		return (_Capacity);
		}

	bool _Inside(const _Ty *_Ptr) const
		{	// test if _Ptr points inside vector
		return (_Ptr < this->_Mylast && this->_Myfirst <= _Ptr);
		}

	void _Reserve(size_type _Count)
		{	// ensure room for _Count new elements, grow exponentially
		size_type _Size = size();
		if (max_size() - _Count < _Size)
			_Xlen();
		else if ((_Size += _Count) <= capacity())
			;
		else
			reserve(_Grow_to(_Size));
		}

	void _Tidy()
		{	// free all storage
		if (this->_Myfirst != 0)
			{	// something to free, destroy and deallocate it
			this->_Orphan_all();
			_Destroy(this->_Myfirst, this->_Mylast);
			this->_Alval.deallocate(this->_Myfirst,
				this->_Myend - this->_Myfirst);
			}
		this->_Myfirst = 0;
		this->_Mylast = 0;
		this->_Myend = 0;
		}

	template<class _Iter>
		pointer _Ucopy(_Iter _First, _Iter _Last, pointer _Ptr)
		{	// copy initializing [_First, _Last), using allocator
		return (_Uninitialized_copy(_First, _Last,
			_Ptr, this->_Alval));
		}

	template<class _Iter>
		pointer _Umove(_Iter _First, _Iter _Last, pointer _Ptr)
		{	// move initializing [_First, _Last), using allocator
		return (_Uninitialized_move(_First, _Last,
			_Ptr, this->_Alval));
		}

	void _Insert_n(const_iterator _Where,
		size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
 #if _ITERATOR_DEBUG_LEVEL == 2
		if (_VICONT(_Where) != this
			|| _VIPTR(_Where) < this->_Myfirst
			|| this->_Mylast < _VIPTR(_Where))
			_DEBUG_ERROR("vector insert iterator outside range");
 #endif /* _ITERATOR_DEBUG_LEVEL == 2 */

		if (_Count == 0)
			;
		else if (max_size() - size() < _Count)
			_Xlen();	// result too long
		else if (capacity() < size() + _Count)
			{	// not enough room, reallocate
			size_type _Capacity = _Grow_to(size() + _Count);
			pointer _Newvec = this->_Alval.allocate(_Capacity);
			size_type _Whereoff = _VIPTR(_Where) - this->_Myfirst;
			int _Ncopied = 0;

			_TRY_BEGIN
			_Ufill(_Newvec + _Whereoff, _Count,
				_STD addressof(_Val));	// add new stuff
			++_Ncopied;
			_Umove(this->_Myfirst, _VIPTR(_Where),
				_Newvec);	// copy prefix
			++_Ncopied;
			_Umove(_VIPTR(_Where), this->_Mylast,
				_Newvec + (_Whereoff + _Count));	// copy suffix
			_CATCH_ALL
			if (1 < _Ncopied)
				_Destroy(_Newvec, _Newvec + _Whereoff);
			if (0 < _Ncopied)
				_Destroy(_Newvec + _Whereoff, _Newvec + _Whereoff + _Count);
			this->_Alval.deallocate(_Newvec, _Capacity);
			_RERAISE;
			_CATCH_END

			_Count += size();
			if (this->_Myfirst != 0)
				{	// destroy and deallocate old array
				_Destroy(this->_Myfirst, this->_Mylast);
				this->_Alval.deallocate(this->_Myfirst,
					this->_Myend - this->_Myfirst);
				}

			this->_Orphan_all();
			this->_Myend = _Newvec + _Capacity;
			this->_Mylast = _Newvec + _Count;
			this->_Myfirst = _Newvec;
			}
		else if ((size_type)(this->_Mylast - _VIPTR(_Where))
			< _Count)
			{	// new stuff spills off end
			_Ty _Tmp = _Val;	// in case _Val is in sequence

			_Umove(_VIPTR(_Where), this->_Mylast,
				_VIPTR(_Where) + _Count);	// copy suffix

			_TRY_BEGIN
			_Ufill(this->_Mylast,
				_Count - (this->_Mylast - _VIPTR(_Where)),
				_STD addressof(_Tmp));	// insert new stuff off end
			_CATCH_ALL
			_Destroy(_VIPTR(_Where) + _Count,
				this->_Mylast + _Count);
			_RERAISE;
			_CATCH_END

			this->_Mylast += _Count;
			_Orphan_range(_VIPTR(_Where), this->_Mylast);
			_STD fill(_VIPTR(_Where), this->_Mylast - _Count,
				_Tmp);	// insert up to old end
			}
		else
			{	// new stuff can all be assigned
			_Ty _Tmp = _Val;	// in case _Val is in sequence

			pointer _Oldend = this->_Mylast;
			this->_Mylast = _Umove(_Oldend - _Count, _Oldend,
				this->_Mylast);	// copy suffix

			_Orphan_range(_VIPTR(_Where), this->_Mylast);
			_STD _Copy_backward(_VIPTR(_Where), _Oldend - _Count,
				_Oldend);	// copy hole
			_STD fill(_VIPTR(_Where),
				_VIPTR(_Where) + _Count, _Tmp);	// insert into hole
			}
		}

	pointer _Ufill(pointer _Ptr, size_type _Count, const _Ty *_Pval)
		{	// copy initializing _Count * _Val, using allocator
		_Uninitialized_fill_n(_Ptr, _Count, _Pval, this->_Alval);
		return (_Ptr + _Count);
		}

	__declspec(noreturn) void _Xlen() const
		{	// report a length_error
		_Xlength_error("vector<T> too long");
		}

	__declspec(noreturn) void _Xran() const
		{	// report an out_of_range error
		_Xout_of_range("invalid vector<T> subscript");
		}

 #if _VECTOR_ORPHAN_RANGE
	void _Orphan_range(pointer _First, pointer _Last) const
		{	// orphan iterators within specified (inclusive) range
		_Lockit _Lock(_LOCK_DEBUG);
		const_iterator **_Pnext = (const_iterator **)this->_Getpfirst();
		if (_Pnext != 0)
			while (*_Pnext != 0)
				if ((*_Pnext)->_Ptr < _First || _Last < (*_Pnext)->_Ptr)
					_Pnext = (const_iterator **)(*_Pnext)->_Getpnext();
				else
					{	// orphan the iterator
					(*_Pnext)->_Clrcont();
					*_Pnext = *(const_iterator **)(*_Pnext)->_Getpnext();
					}
		}

 #else /* _VECTOR_ORPHAN_RANGE */
	void _Orphan_range(pointer, pointer) const
		{	// orphan iterators within specified (inclusive) range
		}
 #endif /* _VECTOR_ORPHAN_RANGE */
	};

		// vector TEMPLATE OPERATORS

template<class _Ty,
	class _Alloc> inline
	void swap(vectorfix<_Ty, _Alloc>& _Left, vectorfix<_Ty, _Alloc>& _Right)
	{	// swap _Left and _Right vectors
	_Left.swap(_Right);
	}

template<class _Ty,
	class _Alloc> inline
	void swap(vectorfix<_Ty, _Alloc>& _Left, vectorfix<_Ty, _Alloc>&& _Right)
	{	// swap _Left and _Right vectors
	typedef vectorfix<_Ty, _Alloc> _Myt;
	_Left.swap(_STD forward<_Myt>(_Right));
	}

template<class _Ty,
	class _Alloc> inline
	void swap(vectorfix<_Ty, _Alloc>&& _Left, vectorfix<_Ty, _Alloc>& _Right)
	{	// swap _Left and _Right vectors
	typedef vectorfix<_Ty, _Alloc> _Myt;
	_Right.swap(_STD forward<_Myt>(_Left));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator==(const vectorfix<_Ty, _Alloc>& _Left,
		const vectorfix<_Ty, _Alloc>& _Right)
	{	// test for vector equality
	return (_Left.size() == _Right.size()
		&& equal(_Left.begin(), _Left.end(), _Right.begin()));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator!=(const vectorfix<_Ty, _Alloc>& _Left,
		const vectorfix<_Ty, _Alloc>& _Right)
	{	// test for vector inequality
	return (!(_Left == _Right));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator<(const vectorfix<_Ty, _Alloc>& _Left,
		const vectorfix<_Ty, _Alloc>& _Right)
	{	// test if _Left < _Right for vectors
	return (lexicographical_compare(_Left.begin(), _Left.end(),
		_Right.begin(), _Right.end()));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator>(const vectorfix<_Ty, _Alloc>& _Left,
		const vectorfix<_Ty, _Alloc>& _Right)
	{	// test if _Left > _Right for vectors
	return (_Right < _Left);
	}

template<class _Ty,
	class _Alloc> inline
	bool operator<=(const vectorfix<_Ty, _Alloc>& _Left,
		const vectorfix<_Ty, _Alloc>& _Right)
	{	// test if _Left <= _Right for vectors
	return (!(_Right < _Left));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator>=(const vectorfix<_Ty, _Alloc>& _Left,
		const vectorfix<_Ty, _Alloc>& _Right)
	{	// test if _Left >= _Right for vectors
	return (!(_Left < _Right));
	}
_STD_END

 #pragma warning(pop)
 #pragma pack(pop)

#endif /* RC_INVOKED */
#endif /* _VECTOR_ */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Hewlett-Packard Company makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
 */

/*
 * Copyright (c) 1992-2009 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V5.20:0009 */
