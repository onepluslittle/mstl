//file:mmalloc.h
#ifndef _MMALLOC_
#define _MMALLOC_
#include <new>     // for placement new
#include <cstddef> // for ptrdiff_t, size_t
#include <cstdlib> // for exit()
#include <climits> // for UINT_MAX
#include <iostream>// for cerr

namespace mstl
{

template <class T>
inline T* _allocate(ptrdiff_t size, T*){
	set_new_handler(0);
	T* tmp = (T*)(::operator new{(size_t)(size * sizeof(T))});
	if (tmp == 0){
		std::cerr << "out of memory" << std::endl;
	}
	return tmp;
}

template <class T>
inline void _deallocate(T* buffer){
	::operator delete(buffer);
}

template <class T1, class T2>
inline void _construct(T1* p, const T2& value){
	new(p) T1(value);
}

template <class T>
inline void _destroy(T* ptr){
	ptr->~T();
}

template <class T>
class allocate{
public:
	typedef T		  value_type;
	typedef T*		  pointer;
	typedef const T*  const_pointer;
	typedef T&		  reference;
	typedef const T&  const_reference;
	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;
	
	//rebind allocate of type U
	template <class U>
	struct rebind {
		typedef allocate<U> other;
	};
	
	pointer allocate(size_type n, const void* hint = 0){
		return _allocate((difference_type)n,(pointer)0);
	}
	
	void deallocate(pointer p, size_type n) { _deallocate(p); }
	
	void destroy(pointer p) { _destroy(p); }
	
	void construct(pointer p, const T& value){
		_construct(p,value);
	}
	
	pointer address(reference x){ return (pointer)&x; }
	
	const_pointer const_address(const_reference x){
		return (const_pointer)&x;
	}
	
	size_type max_size() const{
		return size_type(UINT_MAX/sizeof(T));
	}
};

} // end of namespace mstl

#endif // _MMALLOC_