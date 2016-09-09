// ======================================================================
//
// Copyright (c) 2000,2001 The CGAL Consortium

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
// file          : include/CGAL/Kernel_d/HyperplaneHd.h
// package       : Kernel_d (0.9.47)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/06/11 08:43:18 $
// author(s)     : Michael Seel
// coordinator   : MPI Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_HYPERPLANEHD_H
#define CGAL_HYPERPLANEHD_H

#ifndef NOCGALINCL
#include <CGAL/basic.h>
#include <CGAL/Quotient.h>
#endif
#include <CGAL/Kernel_d/PointHd.h> 
#include <CGAL/Kernel_d/VectorHd.h> 
#include <CGAL/Kernel_d/Aff_transformationHd.h>

CGAL_BEGIN_NAMESPACE

template <class RT, class LA>
std::istream& operator>>(std::istream&, HyperplaneHd<RT,LA>&);
template <class RT, class LA>
std::ostream& operator<<(std::ostream&, const HyperplaneHd<RT,LA>&); 

/*{\Manpage{Hyperplane_d}{R}{Hyperplanes in d-space}{h}}*/
/*{\Msubst 
Hd<RT,LA>#_d<R>
HyperplaneHd#Hyperplane_d
Quotient<RT>#FT
}*/

template <class _RT, class _LA>
class HyperplaneHd : public Handle_for< Tuple_d<_RT,_LA> > { 
  typedef Tuple_d<_RT,_LA> Tuple;
  typedef Handle_for<Tuple> Base;
  typedef HyperplaneHd<_RT,_LA> Self;

/*{\Mdefinition An instance of data type |HyperplaneHd| is an
oriented hyperplane in $d$ - dimensional space. A hyperplane $h$ is
represented by coefficients $(c_0,c_1,\ldots,c_d)$ of type |RT|. At
least one of $c_0$ to $c_{ d - 1 }$ must be non-zero.  The plane
equation is $\sum_{ 0 \le i < d } c_i x_i + c_d = 0$, where $x_0$ to
$x_{d-1}$ are Cartesian point coordinates.  
For a particular $x$ the sign of $\sum_{ 0 \le i < d } c_i x_i +
c_d$ determines the position of a point $x$ with respect to the
hyperplane (on the hyperplane, on the negative side, or on the
positive side).

There are two equality predicates for hyperplanes. The (weak)
equality predicate (|weak_equality|) declares two hyperplanes equal if
they consist of the same set of points, the strong equality predicate
(|operator==|) requires in addition that the negative halfspaces
agree. In other words, two hyperplanes are strongly equal if their
coefficient vectors are positive multiples of each other and they are
(weakly) equal if their coefficient vectors are multiples of each
other.}*/

const typename _LA::Vector& vector_rep() const { return ptr->v; }
_RT& entry(int i) const { return ptr->v[i]; }
void invert_rep() { ptr->invert(); }

public: 
/*{\Mtypes 4}*/

typedef _RT RT;
/*{\Mtypemember the ring type.}*/
typedef Quotient<_RT> FT;
/*{\Mtypemember the field type.}*/
typedef _LA LA;
/*{\Mtypemember the linear algebra layer.}*/
typedef typename Tuple::const_iterator Coefficient_const_iterator;
/*{\Mtypemember a read-only iterator for the coefficients.}*/

/*{\Mcreation h 4}*/

/*{\Moptions nextwarning=no}*/
HyperplaneHd(int d = 0) : Base( Tuple(d+1) ) {}
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname|
initialized to some hyperplane in $d$ - dimensional space. }*/

#ifndef CGAL_SIMPLE_INTERFACE

template <class InputIterator>
HyperplaneHd(int d, InputIterator first, InputIterator last) 
  : Base( Tuple(d+1,first,last) ) {}
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname|
initialized to the hyperplane with coefficients |set [first,last)|.
\precond |size [first,last) == d+1| and the value type of
InputIterator is |RT|.}*/

template <class InputIterator>
HyperplaneHd(int d, InputIterator first, InputIterator last, const RT& D)
  : Base( Tuple(d+1,first,last,D) ) {}
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname|
initialized to the hyperplane with coefficients |set [first,last)| and
|D|. \precond |size [first,last) == d| and the value type of
InputIterator is |RT|.}*/

#else
#define FIXHYPHD(I)\
HyperplaneHd(int d, I first, I last) : Base( Tuple(d+1,first,last) ) {}\
HyperplaneHd(int d, I first, I last, const RT& D) \
  : Base(Tuple(d+1,first,last,D)) {}
FIXHYPHD(int*)
FIXHYPHD(const int*)
FIXHYPHD(RT*)
FIXHYPHD(const RT*)
#undef FIXHYPHD
#endif

/* We want to construct a hyperplane that passes through a set |P =
set [first,last)| of points in $d$-dimensional space and has a
specified point $o$ on a specified side.  We simply have to find a
vector $x$ such that $P^T \cdot x = 0$ for every point in $P$. This
amounts to solving a homogeneous linear system. If the system has only
a trivial solution the task at hand is unsolvable and we report an
error.  So assume that the system has a non-trivial solution. Let
vectors $s_1, \ldots, s_k$ span the solution space. if |side == ZERO|
we may take any $s_j$ as the normal vector of our hyperplane. if
$|side| \neq 0$ and the task at hand is solvable there must be a $j$
such that $o^T \cdot s_j \neq 0$.  We take $s_j$ as the normal vector
of our hyperplane and use |o| to normalize the hyperplane equation. */

template <class ForwardIterator> 
void
construct_from_points(ForwardIterator first, ForwardIterator last, 
		      const PointHd<RT,LA>& o, Oriented_side side)
{ 
  TUPLE_DIM_CHECK(first,last,hyperplane::construction);
  CGAL_assertion_msg((first->dimension()==o.dimension()), 
  "hyperplane::construction: dimensions disagree.");

  int d = first->dimension();   // we are in $d$ - dimensional space
  int m = std::distance(first,last); // |P| has $m$ points
  typename LA::Matrix A(m,d + 1); 

  for (int i = 0; i < m; i++) {  /* define $i$-th equation */
    for (int j = 0; j <= d; j++) 
      A(i,j) = first->homogeneous(j); // $j$ - th coord of $i$-th point
    ++first;
  }
  typename LA::Matrix  spanning_vecs; // columns span solution
  int dim = LA::homogeneous_linear_solver(A,spanning_vecs); 

  if (dim == 0)
    CGAL_assertion_msg(0,"HyperplaneHd::constructor: \
    set P is full dimensional."); 

  if (side == ON_ORIENTED_BOUNDARY) { 
    ptr->v = spanning_vecs.column(0); 
    return; 
  }

  RT sum = 0; 
  int j;
  for (j = 0; j < dim; j++) { 
    for (int i = 0; i <= d; i++) 
      sum += spanning_vecs(i,j)*o.homogeneous(i); 
    if (sum != 0) break; 
  }

  if (j == dim)  
    CGAL_assertion_msg(0,"HyperplaneHd::constructor: \
    cannot use o to determine side.");

  ptr->v = spanning_vecs.column(j);
  if ( CGAL_NTS sign(sum) > 0 && side == ON_NEGATIVE_SIDE || 
       CGAL_NTS sign(sum) < 0 && side == ON_POSITIVE_SIDE)   
    invert_rep();
}


#ifndef CGAL_SIMPLE_INTERFACE

template <class ForwardIterator>
HyperplaneHd(ForwardIterator first, ForwardIterator last, 
             const PointHd<RT,LA>& o, 
             Oriented_side side = Oriented_side(0)) 
/*{\Mcreate constructs some hyperplane that passes through the points
in |set [first,last)|. If |side| is |ON_POSITIVE_SIDE| or
|ON_NEGATIVE_SIDE| then |o| is on that side of the constructed
hyperplane.  \precond A hyperplane with the stated properties must
exist.  The value type of |ForwardIterator| is |PointHd<RT,LA>|. }*/
  : Base( Tuple(o.dimension()+1) )
{ construct_from_points(first,last,o,side); }

#else

HyperplaneHd(const PointHd<RT,LA>* first, const PointHd<RT,LA>*  last, 
	     const PointHd<RT,LA>& o, 
	     Oriented_side side = Oriented_side(0)) : 
  Base( Tuple(o.dimension()+1) ) 
{ construct_from_points(first,last,o,side); }

#ifdef _MSC_VER
// necessary as for MSC we have the vector iterators implemented
// as class types and not as pointers 
typedef typename std::vector<PointHd<RT,LA> >::iterator vecpntit;
typedef typename std::vector<PointHd<RT,LA> >::const_iterator vecpntcit;

HyperplaneHd(vecpntit first, vecpntit last, 
	     const PointHd<RT,LA>& o, 
	     Oriented_side side = Oriented_side(0)) : 
  Base( Tuple(o.dimension()+1) ) 
{ construct_from_points(first,last,o,side); }

HyperplaneHd(vecpntcit first, vecpntcit last, 
	     const PointHd<RT,LA>& o, 
	     Oriented_side side = Oriented_side(0)) : 
  Base( Tuple(o.dimension()+1) ) 
{ construct_from_points(first,last,o,side); }

#endif // MSC
#endif // CGAL_SIMPLE_INTERFACE


HyperplaneHd(const PointHd<RT,LA>& p, const DirectionHd<RT,LA>& dir) 
/*{\Mcreate constructs the hyperplane with normal direction |dir|
that passes through $p$. The direction |dir| points into the positive
side.  \precond |dir| is not the trivial direction.}*/
  : Base( Tuple(p.dimension()+1) ) { 
  int d = p.dimension(); 
  CGAL_assertion_msg((dir.dimension() == d), "HyperplaneHd::constructor: \
  parameter dimensions disagree.");
  CGAL_assertion_msg((dir.dimension() == d), "HyperplaneHd::constructor: \
  parameter dimensions disagree.");

  RT sum = 0; 
  for (int i = 0; i < d; i++) { 
    sum += dir.delta(i)*p.homogeneous(i); 
    entry(i) = dir.delta(i)*p.homogeneous(d); 
  }
  entry(d) = -sum; 
}

HyperplaneHd(const RT& a, const RT& b, const RT& c) : 
  Base( Tuple(a,b,c) ) {} 
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in 
$2$-dimensional space with equation $ax+by+c=0$. }*/

HyperplaneHd(int a, int b, int c) : 
  Base( Tuple(RT(a),RT(b),RT(c)) ) {} 

HyperplaneHd(const RT& a, const RT& b, const RT& c, const RT& d) :
  Base( Tuple(a,b,c,d) ) {} 
/*{\Mcreate introduces a variable |\Mvar| of type |\Mname| in 
$3$-dimensional space with equation $ax+by+cz+d=0$. }*/

HyperplaneHd(int a, int b, int c, int d) : 
  Base( Tuple(RT(a),RT(b),RT(c),RT(d)) ) {} 

HyperplaneHd(const HyperplaneHd<RT,LA>& h) : Base(h) {}
~HyperplaneHd()  {}    

/*{\Moperations 4 2}*/

int dimension() const { return ptr->size()-1; }
/*{\Mop returns the dimension of |\Mvar|. }*/

RT operator[](int i) const
/*{\Marrop returns the $i$-th coefficient of |\Mvar|. 
   \precond $0 \leq i \leq d$.}*/
{ CGAL_assertion_msg((0<=i && i<=(dimension())), "HyperplaneHd::op[]:\
  index out of range."); return entry(i); }

RT coefficient(int i) const { return entry(i); }
/*{\Mop returns the $i$-th coefficient of |\Mvar|. 
   \precond $0 \leq i \leq d$.}*/

const typename LA::Vector& coefficient_vector() const
/*{\Xop returns the coefficient vector $(c_0,\ldots,c_d)$ of |\Mvar|. }*/
{ return vector_rep(); }

Coefficient_const_iterator coefficients_begin() const 
/*{\Mop returns an iterator pointing to the first coefficient.}*/
{ return ptr->begin(); }

Coefficient_const_iterator coefficients_end() const 
/*{\Mop returns an iterator pointing beyond the last coefficient.}*/
{ return ptr->end(); }

VectorHd<RT,LA> orthogonal_vector() const; 
/*{\Mop returns the orthogonal vector of |\Mvar|. It points from the 
negative halfspace into the positive halfspace and its 
homogeneous coordinates are $(c_0, \ldots, c_{d - 1},1)$. }*/
DirectionHd<RT,LA> orthogonal_direction() const 
/*{\Mop returns the orthogonal direction of |\Mvar|. It points from the 
negative halfspace into the positive halfspace. }*/
{ return orthogonal_vector().direction(); }

RT value_at(const PointHd<RT,LA>& p) const
/*{\Xop returns the value of |\Mvar| at the point |p|, i.e., 
$\sum_{ 0 \le i \le d } h_i p_i$.\\
Warning: this value depends on the particular representation 
of |\Mvar| and |p|. }*/
{ CGAL_assertion_msg((dimension()==p.dimension()),"HyperplaneHd::value_at:\
  dimensions disagree.");
  return vector_rep()*p.vector_rep();
}

Oriented_side  oriented_side(const PointHd<RT,LA>& p) const 
/*{\Mop returns the side of the hyperplane |\Mvar| containing $p$. }*/
/*{\Mtext \setopdims{2cm}{2cm}}*/
{ 
  CGAL_assertion_msg((dimension()==p.dimension()), 
  "HyperplaneHd::oriented_side: dimensions do not agree."); 
  return Oriented_side(CGAL_NTS sign(value_at(p)));
}

bool has_on(const PointHd<RT,LA>& p) const 
/*{\Mop returns true iff point |p| lies on the hyperplane |\Mvar|. }*/
{ return (oriented_side(p) == ON_ORIENTED_BOUNDARY); }

bool has_on_boundary(const PointHd<RT,LA>& p) const 
/*{\Mop returns true iff point |p| lies on the boundary of 
hyperplane |\Mvar|. }*/
{ return (oriented_side(p) == ON_ORIENTED_BOUNDARY); }

bool has_on_positive_side(const PointHd<RT,LA>& p) const 
/*{\Mop returns true iff point |p| lies on the positive side of 
hyperplane |\Mvar|. }*/
{ return (oriented_side(p) == ON_POSITIVE_SIDE); }

bool has_on_negative_side(const PointHd<RT,LA>& p) const 
/*{\Mop returns true iff point |p| lies on the negative side of 
hyperplane |\Mvar|. }*/
{ return (oriented_side(p) == ON_NEGATIVE_SIDE); }

/*{\Mtext \restoreopdims }*/

HyperplaneHd<RT,LA> transform(const Aff_transformationHd<RT,LA>& t) const
/*{\Mop returns $t(h)$.}*/
{ Aff_transformationHd<RT,LA> t_inv = t.inverse();
  typename LA::Vector res = LA::transpose(t_inv.matrix())*vector_rep();
  if ( t_inv.is_odd() ) res = -res;
  return HyperplaneHd<RT,LA>(dimension(),res.begin(),res.end()); }

/*{\Mtext \headerline{Non-Member Functions}}*/

static Comparison_result weak_cmp(
  const HyperplaneHd<RT,LA>&, const HyperplaneHd<RT,LA>&);

static Comparison_result strong_cmp(
  const HyperplaneHd<RT,LA>&, const HyperplaneHd<RT,LA>&);

bool operator==(const HyperplaneHd<RT,LA>& h2) const
{ if (identical(h2)) return true;
  if (dimension()!=h2.dimension()) return false;
  return HyperplaneHd<RT,LA>::strong_cmp(*this,h2) == EQUAL; 
}

bool operator!=(const HyperplaneHd<RT,LA>& h2) const
{ return !operator==(h2); }

friend std::istream& operator>> CGAL_NULL_TMPL_ARGS 
  (std::istream&, HyperplaneHd<RT,LA>&);
friend std::ostream& operator<< CGAL_NULL_TMPL_ARGS 
  (std::ostream&, const HyperplaneHd<RT,LA>&);

}; // end of class HyperplaneHd

template <class RT, class LA>
bool weak_equality(const HyperplaneHd<RT,LA>& h1, 
                   const HyperplaneHd<RT,LA>& h2)
/*{\Mfunc test for weak equality. }*/
{ if (h1.identical(h2)) return true;
  if (h1.dimension()!=h2.dimension()) return false;
  return HyperplaneHd<RT,LA>::weak_cmp(h1,h2) == EQUAL; 
}

/*{\Mimplementation
Hyperplanes are implemented by arrays of integers as an item type.
All operations like creation, initialization, tests, vector
arithmetic, input and output on a hyperplane $h$ take time
$O(|h.dimension()|)$. coordinate access and |dimension()| take
constant time.  The space requirement is $O(|h.dimension()|)$.  }*/

CGAL_END_NAMESPACE
#endif // CGAL_HYPERPLANEHD_H

//----------------------- end of file ----------------------------------

