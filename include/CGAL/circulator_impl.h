// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/circulator_impl.h
// package       : Circulator (3.17)
// chapter       : $CGAL_Chapter: Circulators $
// source        : circulator.fw
// revision      : $Revision: 1.1.1.1 $
// revision_date : $Date: 1999/09/06 12:31:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Support to build own circulators (internal and undocumented).
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CIRCULATOR_IMPL_H
#define CGAL_CIRCULATOR_IMPL_H 1

#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>
#endif

CGAL_BEGIN_NAMESPACE

template < class  S>
class Forward_circulator_over_struct
    : public Forward_circulator_ptrbase<S,std::ptrdiff_t,std::size_t>{
public:

// DEFINITION
//
// Given a structure `S' that have a data member `S* next' that realizes a
// ring like data structure the adaptor
// `Forward_circulator_over_struct< S>' provides a forward circulator
// for it. If the structure `S' has additionally a second data member of
// type `S* prev' that realizes the reverse direction the adaptor
// `Bidirectional_circulator_over_struct< S>' provides a bidirectional
// circulator for it. In addition, adaptors for const circulators are
// provided with the names `Forward_const_circulator_over_struct< S>'
// and `Bidirectional_const_circulator_over_struct< S>'. A circulator
// becomes invalid whenever the object it refers to gets deleted from the
// data structure.

    typedef Forward_circulator_over_struct<S> Self;
    typedef Forward_circulator_ptrbase<S,std::ptrdiff_t,std::size_t> Base1;
    typedef typename Base1::reference reference;
    typedef typename Base1::pointer   pointer;

// CREATION
//
// New creation variable is: `circ'

    Forward_circulator_over_struct() {}
        // a circulator `circ' with singular value.

    Forward_circulator_over_struct( S* ptr)
        : Forward_circulator_ptrbase<S,std::ptrdiff_t,std::size_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c)    const { return _ptr == c._ptr; }
    bool operator!=( const Self& c)    const { return !(*this == c); }
    reference  operator*()             const { return *(S*)_ptr;}
    pointer    operator->()            const { return  (S*)_ptr;}

    Self& operator++() {
        _ptr = ((S*)_ptr)->next;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
};


template < class  S>
class Forward_const_circulator_over_struct
    : public Forward_circulator_ptrbase<S,std::ptrdiff_t,std::size_t>{
public:

    typedef Forward_const_circulator_over_struct<S> Self;
    typedef const S&  reference;
    typedef const S*  pointer;

// CREATION

    Forward_const_circulator_over_struct() {}
        // a circulator `circ' with singular value.

    Forward_const_circulator_over_struct( const S* ptr)
        : Forward_circulator_ptrbase<S,std::ptrdiff_t,
                                     std::size_t>((void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c)    const { return _ptr == c._ptr; }
    bool operator!=( const Self& c)    const { return !(*this == c); }
    reference  operator*()             const { return *(const S*)_ptr;}
    pointer    operator->()            const { return  (const S*)_ptr;}

    Self& operator++() {
        _ptr = ((S*)_ptr)->next;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
};


template < class  S>
class Bidirectional_circulator_over_struct
  : public Bidirectional_circulator_ptrbase<S,std::ptrdiff_t,std::size_t>{
public:

    typedef Bidirectional_circulator_over_struct<S> Self;
    typedef Bidirectional_circulator_ptrbase<S,std::ptrdiff_t,
                                             std::size_t> Base1;
    typedef typename Base1::reference reference;
    typedef typename Base1::pointer   pointer;

// CREATION
//
// New creation variable is: `circ'

    Bidirectional_circulator_over_struct() {}
        // a circulator `circ' with singular value.

    Bidirectional_circulator_over_struct( S* ptr)
        : Bidirectional_circulator_ptrbase<S,std::ptrdiff_t,
                                           std::size_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c)    const { return _ptr == c._ptr; }
    bool operator!=( const Self& c)    const { return !(*this == c); }
    reference  operator*()             const { return *(S*)_ptr;}
    pointer    operator->()            const { return  (S*)_ptr;}

    Self& operator++() {
        _ptr = ((S*)_ptr)->next;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        _ptr = ((S*)_ptr)->prev;
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
};


template < class  S>
class Bidirectional_const_circulator_over_struct
  : public Bidirectional_circulator_ptrbase<S,std::ptrdiff_t,std::size_t>{
public:

    typedef Bidirectional_const_circulator_over_struct<S> Self;
    typedef const S&  reference;
    typedef const S*  pointer;

// CREATION

    Bidirectional_const_circulator_over_struct() {}
        // a circulator `circ' with singular value.

    Bidirectional_const_circulator_over_struct( const S* ptr)
        : Bidirectional_circulator_ptrbase<S,std::ptrdiff_t,std::size_t>(
            (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c)    const { return _ptr == c._ptr; }
    bool operator!=( const Self& c)    const { return !(*this == c); }
    reference  operator*()             const { return *(const S*)_ptr;}
    pointer    operator->()            const { return  (const S*)_ptr;}

    Self& operator++() {
        _ptr = ((S*)_ptr)->next;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        _ptr = ((S*)_ptr)->prev;
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
};
template < class  C>
class Forward_circulator_over_class
    : public Forward_circulator_ptrbase<C,std::ptrdiff_t,std::size_t>{
public:
    typedef Forward_circulator_over_class<C> Self;

// DEFINITION
//
// Given a class `C' that has a member function `C* next()' that realizes
// a ring like data structure the adaptor
// `Forward_circulator_over_class<C>' provides a forward circulator
// for it. If the class `C' has additionally a second member function `C*
// prev()' that realizes the reverse direction the adaptor
// `Bidirectional_circulator_over_class<C>' provides a bidirectional
// circulator for it. In addition, adaptors for const circulators are
// provided with the names `Forward_const_circulator_over_class<C>'
// and `Bidirectional_const_circulator_over_class<C>'. A circulator
// becomes invalid whenever the object it refers to gets deleted from the
// data structure.

    Forward_circulator_over_class() {}
        // a circulator `circ' with a singular value.

    Forward_circulator_over_class( C* ptr)
        : Forward_circulator_ptrbase<C,std::ptrdiff_t,std::size_t>( ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c)    const { return _ptr == c._ptr; }
    bool operator!=( const Self& c)    const { return !(*this == c); }
    C&   operator*()                   const { return *(C*)_ptr;}
    C*   operator->()                  const { return  (C*)_ptr;}
    Self& operator++() {
        _ptr = ((C*)_ptr)->next();
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
};

template < class  C>
class Forward_const_circulator_over_class
    : public Forward_circulator_ptrbase<C,std::ptrdiff_t,std::size_t>{
public:
    typedef Forward_const_circulator_over_class<C> Self;

    Forward_const_circulator_over_class() {}
        // a circulator `circ' with singular value.

    Forward_const_circulator_over_class( const C* ptr)
        : Forward_circulator_ptrbase<C,std::ptrdiff_t,std::size_t>
            ((void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

//
// OPERATIONS


    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c)    const { return _ptr == c._ptr; }
    bool operator!=( const Self& c)    const { return !(*this == c); }
    const C&  operator*()              const { return *(C*)_ptr;}
    const C*  operator->()             const { return  (C*)_ptr;}
    Self& operator++() {
        _ptr = (void*)(((C*)_ptr)->next());
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
};

template < class  C>
class Bidirectional_circulator_over_class
  : public Bidirectional_circulator_ptrbase<C,std::ptrdiff_t,std::size_t>{
public:
    typedef Bidirectional_circulator_over_class<C> Self;

    Bidirectional_circulator_over_class() {}
        // a circulator `circ' with singular value.

    Bidirectional_circulator_over_class( C* ptr)
        : Bidirectional_circulator_ptrbase<C,std::ptrdiff_t,std::size_t>
            (ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c)    const { return _ptr == c._ptr; }
    bool operator!=( const Self& c)    const { return !(*this == c); }
    C&   operator*()                   const { return *(C*)_ptr;}
    C*   operator->()                  const { return  (C*)_ptr;}

    Self& operator++() {
        _ptr = ((C*)_ptr)->next();
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        _ptr = ((C*)_ptr)->prev();
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
};

template < class  C>
class Bidirectional_const_circulator_over_class
  : public Bidirectional_circulator_ptrbase<C,std::ptrdiff_t,std::size_t>{
public:
    typedef Bidirectional_const_circulator_over_class<C> Self;
//
// CREATION

    Bidirectional_const_circulator_over_class() {}
        // a circulator `circ' with singular value.

    Bidirectional_const_circulator_over_class( const C* ptr)
        : Bidirectional_circulator_ptrbase<C,std::ptrdiff_t,std::size_t>(
            (void*)ptr) {}
        // a circulator `circ' initialized to point to the element `*ptr'.

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _ptr == NULL;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c)    const { return _ptr == c._ptr; }
    bool operator!=( const Self& c)    const { return !(*this == c); }
    const C&  operator*()              const { return *(C*)_ptr;}
    const C*  operator->()             const { return  (C*)_ptr;}

    Self& operator++() {
        _ptr = (void*)(((C*)_ptr)->next());
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        _ptr = (void*)(((C*)_ptr)->prev());
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
};
template < class A, class T, class U, class I>
class Circulator_over_array
    : public Random_access_circulator_ptrbase<T,I,U>{
    U _size;
    U _i;
public:

// DEFINITION
//
// Given a data structure `A' that provides random access with an index of
// type `U' to its sequence of stored elements of type `T' with the member
// function `operator[]' the adaptor `Circulator_over_array< A, T, U,
// I>' provides a random access circulator for `A'. The corresponding
// const circulator is `Const_circulator_over_array< A, T, U, I>'. All
// circulators for an array `a' become invalid whenever `a' changes its
// size (due to deletions or insertions).
//
// `A' is a random access data structure and `T' its value type. `U' is
// the unsigned integral type carrying the size of the array and the
// actual index within the container. `I' is the signed integral type used
// as distance type and as index type in the random access circulator.

// TYPES

    typedef A                              Array;
    typedef Circulator_over_array<A,T,U,I> Self;

// CREATION

    Circulator_over_array() : _size(0), _i(0) {}
        // a circulator `circ' with singular value.

    Circulator_over_array( A& array, U size, U start = 0)
        : Random_access_circulator_ptrbase<T,I,U>( &array),
          _size( size), _i(start) {}
        // a circulator `circ' initialized to refer to the element
        // `(array.*access)(start)'. The circulator `circ' contains a
        // singular value if `start >= size'. Precondition: The
        // expressions `(array.*access)(i)' are valid in the range
        // 0 <= i < `size' .

// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _i >= _size;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c) const {
        CGAL_assertion( _ptr  == c._ptr);  // belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i == c._i;
    }
    bool operator!=( const Self& c) const { return !(*this == c); }
    T&  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        return ((A*)_ptr)->operator[](_i);
    }
    T*  operator->() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        return &(((A*)_ptr)->operator[](_i));
    }
    Self& operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        ++ _i;
        if ( _i >= _size)
            _i = 0;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        if ( _i <= 0)
            _i = _size - 1;
        else
            -- _i;
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
    Self& operator+=( I n);
    Self  operator+( I n) const {
        Self tmp = *this;
        return tmp += n;
    }
    Self& operator-=( I n) { return operator+=( -n); }
    Self  operator-( I n) const {
        Self tmp = *this;
        return tmp += -n;
    }
    I     operator-( const Self& c) const {
        CGAL_assertion( _ptr  == c._ptr);  // belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i - c._i;
    }
    T&    operator[](I n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    Self  min_circulator() {
        return Self( *((A*)_ptr), _size);
    }
    // no relational ordering
};

template < class Dist, class  A, class  T, class U, class  I>
inline
Circulator_over_array< A, T, U, I>
operator+( Dist n, const Circulator_over_array< A, T, U, I>& circ) {
    Circulator_over_array< A, T, U, I> tmp = circ;
    return tmp += I(n);
}

template < class A, class T, class U, class I>
Circulator_over_array< A, T, U, I>&
Circulator_over_array< A, T, U, I>::
operator+=( I n) {
    CGAL_assertion( _ptr != NULL);
    CGAL_assertion( _i < _size);
    _i = non_negative_mod( (I)(_i) + n, _size);
    CGAL_assertion( _i < _size);
    return *this;
}

template < class  A, class  T, class U, class  I>
class Const_circulator_over_array
    : public Random_access_circulator_ptrbase<T,I,U> {
    U _size;
    U _i;
public:

// TYPES

    typedef A                                    Array;
    typedef Const_circulator_over_array<A,T,U,I> Self;

// New creation variable is: `circ'
//
// CREATION

    Const_circulator_over_array() : _size(0), _i(0) {}
        // a const circulator `circ' with singular value.

    Const_circulator_over_array( const A& array, U size, U start = 0)
        : Random_access_circulator_ptrbase<T,I,U>(
              (void*)(&array)), _size( size), _i(start) {}
        // a const circulator `circ' initialized to refer to the element
        // `(array.*access)(start)'. The circulator `circ' contains a
        // singular value if `start >= size'. Precondition: The
        // expressions `(array.*access)(i)' are valid in the range
        // 0 <= i < `size' .

//
// OPERATIONS

    bool operator==( CGAL_NULL_TYPE p) const {
        CGAL_assertion( p == CGAL_CIRC_NULL);
        return _i >= _size;
    }
    bool operator!=( CGAL_NULL_TYPE p) const { return !(*this == p); }
    bool operator==( const Self& c) const {
        CGAL_assertion( _ptr  == c._ptr);  // belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i == c._i;
    }
    bool operator!=( const Self& c) const { return !(*this == c); }
    const T&  operator*() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        return ((const A*)_ptr)->operator[](_i);
    }
    const T*  operator->() const {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        return &(((const A*)_ptr)->operator[](_i));
    }
    Self& operator++() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        ++ _i;
        if ( _i >= _size)
            _i = 0;
        return *this;
    }
    Self  operator++(int) {
        Self tmp = *this;
        ++*this;
        return tmp;
    }
    Self& operator--() {
        CGAL_assertion( _ptr != NULL);
        CGAL_assertion( _i < _size);
        if ( _i <= 0)
            _i = _size - 1;
        else
            -- _i;
        return *this;
    }
    Self  operator--(int) {
        Self tmp = *this;
        --*this;
        return tmp;
    }
    Self& operator+=( I n);

    Self  operator+( I n) const {
        Self tmp = *this;
        return tmp += n;
    }
    Self& operator-=( I n) {
        return operator+=( -n);
    }
    Self  operator-( I n) const {
        Self  tmp = *this;
        return tmp += -n;
    }
    I
    operator-( const Self& c)  const {
        CGAL_assertion( _ptr  == c._ptr);  // belong to the same array?
        CGAL_assertion( _size == c._size); // same size when instantiated ?
        return _i - c._i;
    }
    const T&  operator[](I n) const {
        Self tmp = *this;
        tmp += n;
        return tmp.operator*();
    }
    Self  min_circulator() {
        return Self( *((const A*)_ptr), _size);
    }
    // no relational ordering
};

template < class Dist, class  A, class  T, class U, class  I>
inline
Const_circulator_over_array< A, T, U, I>
operator+( Dist n, const Const_circulator_over_array<A,T,U,I>& circ) {
    Const_circulator_over_array< A, T, U, I> tmp = circ;
    return tmp += I(n);
}

template < class A, class T, class U, class I>
Const_circulator_over_array< A, T, U, I>&
Const_circulator_over_array< A, T, U, I>::
operator+=( I n) {
    CGAL_assertion( _ptr != NULL);
    CGAL_assertion( _i < _size);
    _i = non_negative_mod( (I)(_i) + n, _size);
    CGAL_assertion( _i < _size);
    return *this;
}

CGAL_END_NAMESPACE

#endif // CGAL_CIRCULATOR_IMPL_H //
// EOF //
