// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

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
// file          : include/CGAL/predicates_on_linesH2.h
// package       : H2 (2.37)
// revision      : $Revision: 1.6 $
// revision_date : $Date: 2001/06/20 14:53:36 $
// author(s)     : Stefan Schirra
//
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================
 
#ifndef CGAL_PREDICATES_ON_LINESH2_H
#define CGAL_PREDICATES_ON_LINESH2_H

#include <CGAL/PointH2.h>
#include <CGAL/LineH2.h>
#include <CGAL/predicates_on_pointsH2.h>
#include <CGAL/basic_constructionsH2.h>

CGAL_BEGIN_NAMESPACE

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x(const PointH2<R>& p,
          const LineH2<R>& l1,
          const LineH2<R>& l2)
{
  PointH2<R> ip = gp_linear_intersection( l1, l2 );
  return compare_x( p, ip );
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x(const LineH2<R>& l1,
          const LineH2<R>& l2,
          const LineH2<R>& h1,
          const LineH2<R>& h2)
{
  PointH2<R> lip = gp_linear_intersection( l1, l2 );
  PointH2<R> hip = gp_linear_intersection( h1, h2 );
  return compare_x( lip, hip );
}

template < class R >
inline
Comparison_result
compare_x(const Line_2<R> &l,
	  const Line_2<R> &h1,
	  const Line_2<R> &h2)
{
    return compare_x(l, h1, l, h2);
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y(const PointH2<R>& p,
          const LineH2<R>& l1,
          const LineH2<R>& l2)
{
  PointH2<R> ip = gp_linear_intersection( l1, l2 );
  return compare_y( p, ip );
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y(const LineH2<R>& l1,
          const LineH2<R>& l2,
          const LineH2<R>& h1,
          const LineH2<R>& h2)
{
  PointH2<R> lip = gp_linear_intersection( l1, l2 );
  PointH2<R> hip = gp_linear_intersection( h1, h2 );
  return compare_y( lip, hip );
}

template < class R >
inline
Comparison_result
compare_y(const Line_2<R> &l,
	  const Line_2<R> &h1,
	  const Line_2<R> &h2)
{
    return compare_y(l, h1, l, h2);
}

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_y_at_x(const PointH2<R>& p,
               const LineH2<R>& h)
{
  typedef typename R::RT RT;
  CGAL_kernel_precondition( ! h.is_vertical() );
  Oriented_side ors = h.oriented_side( p );
  if ( h.b() < RT(0) )
  {
      ors = opposite( ors );
  }
  if ( ors == ON_POSITIVE_SIDE )
  {
      return LARGER;
  }
  return ( ors == ON_NEGATIVE_SIDE ) ? SMALLER : EQUAL;
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const PointH2<R>& p,
               const LineH2<R>& h1,
               const LineH2<R>& h2)
{ return CGAL_NTS compare(h1.y_at_x( p.x() ), h2.y_at_x( p.x() )); }

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const LineH2<R>& l1,
               const LineH2<R>& l2,
               const LineH2<R>& h)
{ return compare_y_at_x( gp_linear_intersection( l1, l2 ), h); }

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_y_at_x(const LineH2<R>& l1,
               const LineH2<R>& l2,
               const LineH2<R>& h1,
               const LineH2<R>& h2)
{ return compare_y_at_x( gp_linear_intersection( l1, l2 ), h1, h2 ); }

template <class R>
CGAL_KERNEL_MEDIUM_INLINE
Comparison_result
compare_x_at_y(const PointH2<R>& p,
               const LineH2<R>& h)
{
  typedef typename R::RT RT;
  CGAL_kernel_precondition( ! h.is_horizontal() );
  Oriented_side ors = h.oriented_side( p );
  if ( h.a() < RT(0) )
  {
      ors = opposite( ors );
  }
  if ( ors == ON_POSITIVE_SIDE )
  {
      return LARGER;
  }
  return ( ors == ON_NEGATIVE_SIDE ) ? SMALLER : EQUAL;
}

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x_at_y(const PointH2<R>& p,
               const LineH2<R>& h1,
               const LineH2<R>& h2)
{ return CGAL_NTS compare(h1.x_at_y( p.y() ), h2.x_at_y( p.y() )); }


template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x_at_y(const LineH2<R>& l1,
               const LineH2<R>& l2,
               const LineH2<R>& h)
{ return compare_x_at_y( gp_linear_intersection( l1, l2 ), h); }

template <class R>
CGAL_KERNEL_INLINE
Comparison_result
compare_x_at_y(const LineH2<R>& l1,
               const LineH2<R>& l2,
               const LineH2<R>& h1,
               const LineH2<R>& h2)
{ return compare_x_at_y( gp_linear_intersection( l1, l2 ), h1, h2 ); }

CGAL_END_NAMESPACE

#endif  // CGAL_PREDICATES_ON_LINESH2_H
