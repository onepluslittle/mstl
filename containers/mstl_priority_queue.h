#ifndef MSTL_PRIORITY_QUEUE_H
#define MSTL_PRIORITY_QUEUE_H

#include "mstl_heap.h"
namespace mstl {
	
template <class T, class Sequence = vector<T>, class Compare = less<typename Sequence::value_type> >
class priority_queue {
public:
typedef typename Sequence::value_type value_type;
typedef typename Sequence::size_type size_type;
typedef typename Sequence::reference reference;
typedef typename Sequence::const_reference const_reference;

protected:
Sequence c;
Compare comp;

public:
priority_queue() : c() {}
explicit priority_queue(const Compare& x) : c(), comp(x) {}


template <class InputIterator>
priority_queue(InputIterator first, InputIterator last, const Compare& x)
: c(first, last), comp(x) {
	make_heap(c.begin(), c.end(), comp);
}
template <class InputIterator>
priority_queue(InputIterator first, InputIterator last)
: c(first, last), comp(x) {
	make_heap(c.begin(), c.end(), comp);
}

bool empty(void) const {return c.empty();}
size_type size(void) const {return c.size();}
const_reference top(void) const {return c.front();}
void push(const value_type& x) {
	__STL_TRY {
		c.push_back(x);
		push_heap(c.begin(), c.end(), comp);
	}
	__STL_UNWIND(c.clear());
}
void pop(void) {
	__STL_TRY {
		pop_heap(c.begin(), c.end(), comp);
		c.pop_back();
	}
	__STL_UNWIND(c.clear());
}

}; /* class priority_queue */
}; /* mstl */

#endif