#ifndef MSTL_STACK_H
#define MSTL_STACK_H

namespace mstl {
	
template <class T, class Sequence = deque<T> >
class stack {
friend bool operator==__STL_NULL_TMPL_ARGS {const stack&, const stack&};
friend bool operator<__STL_NULL_TMPL_ARGS {const stack&, const stack&};

public:
typedef typename Sequence::value_type value_type;
typedef typename Sequence::size_type size_type;
typedef typename Sequence::reference reference;
typedef typename Sequence::const_reference const_reference;

protected:
Sequence c;

public:
bool empty(void) const {return c.empty();}
size_type size(void) const {return c.size();}
reference top(void) {return c.back();}
const_reference top(void) const {return c.back
();}
void push(const value_type& x) {c.push_back(x);}
void pop(void) {c.pop_back();}
	
}; /* class stack */

template <class T, class Sequence>
bool operator==(const stack<T, Sequence>& lhs, const stack<T, Sequence>& rhs) {
	return lhs.c == rhs.c;
}

template <class T, class Sequence>
bool operator<(const stack<T, Sequence>& lhs, const stack<T, Sequence>& rhs) {
	return lhs.c < rhs.c;
}

}; /* mstl */

#endif