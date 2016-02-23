//file : mstl_iterator.h
#ifndef MSTL_ITERATOR_H
#define MSTL_ITERATOR_H

namespace mstl {
	
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

#include <cstddef> // for ptrdiff_t

template <class Catogory
		  class T,
		  class Distance = ptrdiff_t,
		  class Pointer = T*,
		  class Reference = T&>
struct iterator {
	typedef Catogory  iterator_catogory;
	typedef T         value_type;
	typedef Distance  difference_type;
	typedef Pointer   pointer;
	typedef Reference reference;
};

template <class Iterator>
struct iterator_traits {
	typedef typename Iterator::iterator_catogory iterator_catogory;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
};

//偏特化版 for native pointer
template <class T>
struct iterator_traits<T*> {
	typedef random_access_iterator_tag iterator_catogory;
	typedef T                          value_type;
	typedef ptrdiff_t                  difference_type;
	typedef T*                         pointer;
	typedef T&                         reference;
};

//偏特化版 for native pointer-to const
template <class T>
struct iterator_traits<const T*> {
	typedef random_access_iterator_tag iterator_catogory;
	typedef T                          value_type;
	typedef ptrdiff_t                  difference_type;
	typedef const T*                   pointer;
	typedef const T&                   reference;
};

template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_catogory
iterator_catogory(const Iterator&) {
	typedef typename iterator_traits<Iterator>::iterator_catogory category;
	return category();
}

template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&) {
	return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&) {
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

// 整组distance函数

template <class InputIterator>
inline iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
	iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last) {
		++first; ++n;
	}
	return n;
}

template <class RandomAccessIterator>
inline iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag
) {
	return last - first;
}

template <class InputIterator>
inline iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
	typedef typename iterator_traits<InputIterator>::iterator_catogory category;
	return __distance(first, last, category());
}

// 整组advance函数
template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag) {
	while (n--) ++i;
}

template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, bidirectional_iterator_tag) {
	if (n >= 0)
		while (n--) ++i;
	else 
		while (n++) --i;
}

template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, random_access_iterator_tag) {
	i += n;
}
template <class Container>
class back_insert_iterator {
protected:
	Container* container;
public:
	typedef output_iterator_tag iterator_catogory;
	typedef void                value_type;
	typedef void                difference_type;
	typedef void                pointer;
	typedef void                reference;
	
	explicit back_insert_iterator(Container& x) : container(&x) {}
	
	back_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		container->push_back(value);
		return *this;
	}
	
	// do not work (close its function)
	back_insert_iterator<Container>& operator*() {
		return *this;
	}
	back_insert_iterator<Container>& operator++() {
		return *this;
	}
	back_insert_iterator<Container>& operator++(int) {
		return *this;
	}
}; /* class back_insert_iterator */
	
//help function to easily use back_insert_iterator
template <class Container>
inline back_insert_iterator<Container> back_inserter(Container& x) {
	return back_insert_iterator<Container>(x);
}
	
template <class Container>
class front_insert_iterator {
protected:
	Container* container;
public:
	typedef output_iterator_tag iterator_catogory;
	typedef void                value_type;
	typedef void                difference_type;
	typedef void                pointer;
	typedef void                reference;
	
	explicit front_insert_iterator(Container& x) : container(&x) {}
	
	// do not work on vector
	front_insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		container->push_front(value);
		return *this;
	}
	
	// do not work (close its function)
	front_insert_iterator<Container>& operator*() {
		return *this;
	}
	front_insert_iterator<Container>& operator++() {
		return *this;
	}
	front_insert_iterator<Container>& operator++(int) {
		return *this;
	}
}; /* class front_insert_iterator  */
	
template <class Container>
inline front_insert_iterator<Container> front_inserter(Container& x) {
	return front_insert_iterator<Container>(x);
}


template <class Container>
class insert_iterator {
protected:
	Container* container;
	typename Container::iterator iter;
public:
	typedef output_iterator_tag iterator_catogory;
	typedef void                value_type;
	typedef void                difference_type;
	typedef void                pointer;
	typedef void                reference;
	
	explicit insert_iterator(Container& x, typename Container::iterator i) : container(&x), iter(i) {}
	
	// do not work on vector
	insert_iterator<Container>& operator=(const typename Container::value_type& value) {
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}
	
	// do not work (close its function)
	insert_iterator<Container>& operator*() {
		return *this;
	}
	insert_iterator<Container>& operator++() {
		return *this;
	}
	insert_iterator<Container>& operator++(int) {
		return *this;
	}
}; /* class insert_iterator  */
	
template <class Container, class Iterator>
inline insert_iterator<Container> inserter(Container& x, Iterator i) {
	typedef typename Container::iterator iter;
	return insert_iterator<Container>(x, iter(i));
}

template <class Iterator>
class reverse_iterator {
protected:
	Iterator current;
public:
	//associated types are the same as the 
	typedef typename iterator_traits<Iterator>::iterator_catogory iterator_catogory;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;
	
	typedef Iterator iterator_type;
	typedef reverse_iterator<Iterator> self;
	
public:
	reverse_iterator() {}
	explicit reverse_iterator(iterator_type x) : current(x) {}
	reverse_iterator(const self& x) : current(x.current) {}
	
	iterator_type base() const {return current;}
	reference operator*() const {
		Iterator tmp = current;
		return *--tmp;
	}
	
	pointer operator->() const {
		return &(operator*());
	}
	
	self& operator++() {
		--current;
		return *this;
	}
	
	self operator++(int) {
		self tmp = *this;
		--current;
		return tmp;
	}
	
	self& operator--() {
		++current;
		return *this;
	}
	
	self operator--(int) {
		self tmp = *this;
		++current;
		return tmp;
	}
	
	self operator+(difference_type n) const {
		return self(current - n);
	}
	
	self& operator+=(difference_type n) {
		current -= n;
		return *this;
	}
	
	self operator-(difference_type n) const {
		return self(current + n);
	}
	
	self& operator-=(difference_type n) {
		current += n;
		return *this;
	}
	
	//[n] 表示前进n格，与正向迭代器相反
	reference operator[](difference_type n) const {
		return *(*this + n);
	}
	
}; /* class reverse_iterator */

template <class T, class Distance = ptrdiff_t>
class istream_iterator {
	//c++ primer 3th p834
	friend bool operator== __STL_NULL_TEML_ARGS (const istream_iterator<T, Distance>& x, const istream_iterator<T, Distance>& y);
	
protected:
	istream* stream;
	T value;
	bool end_marker;
	void read() {
		end_marker = (*stream) ? true : false;
		if (end_marker) *stream >> value;
		end_marker = (*stream) ? true : false;
	}

public:
	typedef input_iterator_tag iterator_catogory;
	typedef T                  value_type;
	typedef Distance           difference_type;
	typedef const T*           pointer;
	typedef const T&           reference;
	
	istream_iterator() : stream(&cin), end_marker(false) {}
	istream_iterator(istream& s) : stream(&s) {read();}
	
	reference operator*() const {return value;}
	pointer operator->() const {return &(operator*());}
	
	istream_iterator<T, Distance>& operator++() {
		read();
		return *this;
	}
	istream_iterator<T, Distance>& operator++(int) {
		istream_iterator<T, Distance> tmp = *this;
		read();
		return tmp;
	}	
}; /* class istream_iterator */

template <class T>
class ostream_iterator {
protected:
ostream* stream;
const char* space_string;

public:
	typedef output_iterator_tag iterator_catogory;
	typedef void                value_type;
	typedef void                difference_type;
	typedef void                pointer;
	typedef void                reference;
	
	ostream_iterator(ostream& s) : stream(&s), space_string(0) {}
	ostream_iterator(ostream& s, const char* c) : stream(&s), space_string(c) {}
	
	ostream_iterator<T>& operator=(const T& value) {
		*stream << value;
		if (space_string) *stream << space_string;
		return *this;
	}
	
	ostream_iterator<T>& operator*() {return *this;}
	ostream_iterator<T>& operator++() {return *this;}
	ostream_iterator<T>& operator++(int) {return *this;}
}; /* class ostream_iterator */

}; /* mstl */


#endif