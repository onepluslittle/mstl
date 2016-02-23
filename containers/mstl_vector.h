#ifndef MSTL_VECTOR_H
#define MSTL_VECTOR_H

#include "mmalloc.h"
#include "mstl_simple_alloc.h"
#include "mstl_construct.h"
#include "mstl_uninitialized.h"
#include <cstddef>

namespace mstl {
	
//using namespace mstl;
//typedef mstl::allocate alloc;
template <class T, class Alloc = std::allocator>
class vector {
public:
//nested define
typedef T           value_type;
typedef value_type* pointer;
typedef value_type* iterator;
typedef value_type& reference;
typedef size_t      size_type;
typedef ptrdiff_t   difference_type;

protected:
typedef simple_alloc<value_type, Alloc> data_allocator;
iterator start;
iterator finish;
iterator end_of_storage;

void insert_aux(iterator position, const T& x){
	if (finish != end_of_storage) {
		construct(finish,*(finish-1));
		++finish;
		T x_copy = x;
		copy_backward(position, finish-2, finish-1);
		*position = x_copy;
	} else {
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2*old_size : 1;
		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;
		try {
			new_finish = uninitialized_copy(start, position, new_start);
			construct(new_finish,x);
			++new_finish;
			new_finish = uninitialized_copy
			(position, finish, new_finish);
		}
		catch (...) {
			destroy(new_start, new_finish);
			data_allocator::deallocate(new_start,len);
			throw;
		}
		
		destroy(begin(),end());
		deallocate();
		
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}

void deallocate(void) {
	if (start)
		data_allocator::deallocate(start, end_of_storage, start);
}

void fill_initialize(size_type n, const T& value) {
	start = allocate_and_fill(n, value);
	finish = start + n;
	end_of_storage = finish;
}

public:
iterator begin(void) {return start;}
iterator end(void) {return finish;}
size_type size(void) {return size_type(end() - begin());}
size_type capacity(void) const 
	{return size_type(end_of_storage-begin());}
bool empty(void) const {return begin() == end();}
reference operator[](size_type n) {return *(begin() + n);}

/*construct*/
vector(void) : start(0), finish(0), end_of_storage(0) {}
vector(size_type n, const T& value) {fill_initialize(n, value);}
vector(int n, const T& value) {fill_initialize(n, value);}
vector(long n, const T& value) {fill_initialize(n, value);}
explicit vector(size_type n) {finish_initialize(n, T());}
~vector(void) {destroy(start, finish);deallocate();}

reference front(void) {return *begin();}
reference back(void) {return *(end()-1);}
void push_back(const T& x) {
	if (finish != end_of_storage) {
		construct(finish,x);
		++finish;
	} else {
		insert_aux(end(), x);
	}
}

void pop_back(void) {
	--finish;
	destroy(finish);
}

iterator erase(iterator position) {
	if (position + 1 != end())
		copy(position + 1, finish, position);
	--finish;
	destroy(finish);
	return position;
}

void resize(size_type new_sz, const T& x) {
	if (new_sz < size())
		erase(begin() + new_sz, end());
	else
		insert(end(),new_sz-size(),x);
}

void resize(size_type new_sz) {resize(new_sz, T());}
void clear() {erase(begin(),end());}

protected:
iterator allocate_and_fill(size_type n, const T& x) {
	iterator result = data_allocator::allocate(n);
	uninitialized_fill_n(result, n, x);
	return result;
}

void insert(iterator position, size_type n, const T& x) {
	if (n != 0) {
		if (size_type(end_of_storage - finish) >= n) {
			T x_copy = x;
			const size_type elems_after = finish - position;
			iterator old_finish = finish;
			if (elems_after > n) {
				uninitialized_copy(finish - n, finish, finish);
				finish += n;
				copy_backward(position, old_finish - n, old_finish);
				fill(position, position + n, x_copy);
			} else {
				uninitialized_fill_n(finish, n - elems_after, x_copy);
				finish += n - elems_after;
				uninitialized_copy(position, old_finish, finish);
				finish += elems_after;
				fill(position, old_finish, x_copy);
			}
		} else {
			const size_type old_size = size();
			const size_type len = old_size + max(old_size, n);
			iterator new_start = data_allocator::allocate(len);
			iterator new_finish = new_start;
			__STL_TRY {
				new_finish = uninitialized_copy(start, position, new_start);
				new_finish = uninitialized_fill_n(new_finish, n, x);
				new_finish = uninitialized_copy(position, finish, new_finish);
			}
			#ifdef __STL_USE_EXCEPTIONS
			catch (...) {
				destroy(new_start, new_finish);
				data_allocator::deallocate(new_start, len);
				throw;
			}
			#endif 
			destroy(start, finish);
			deallocate();
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
		}
	}
}
	
}; /* vector */
}; /* mstl */

#endif