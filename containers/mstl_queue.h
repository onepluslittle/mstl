#ifndef MSTL_QUEUE_H
#define MSTL_QUEUE_H
namespace mstl{
	
template <class T, class Sequence = deque<T> >
class queue {
friend bool operator==__STL_NULL_TMPL_ARGS {const queue&, const queue&};
friend bool operator<__STL_NULL_TMPL_ARGS {const queue&, const queue&};

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
reference front(void) {return c.front();}
const_reference front(void) const {return c.front();}
reference back(void) {return c.back();}
const_reference back(void) const {return c.back();}
void push(const value_type& x) {c.push_back(x);}
void pop(void) {c.pop_front();}
	
}; /* class queue */

template <class T, class Sequence>
bool operator==(const queue<T, Sequence>& lhs, const queue<T, Sequence>& rhs) {
	return lhs.c == rhs.c;
}

template <class T, class Sequence>
bool operator<(const queue<T, Sequence>& lhs, const queue<T, Sequence>& rhs) {
	return lhs.c < rhs.c;
}
	
}; /* mstl */
#endif