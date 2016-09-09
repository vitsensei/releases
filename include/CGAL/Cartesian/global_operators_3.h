// ======================================================================
//
// Copyright (c) 2000 The CGAL Consortium

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
// file          : include/CGAL/Cartesian/global_operators_3.h
// package       : Cartesian_kernel (6.24)
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2000/11/16 21:31:08 $
// author(s)     : Andreas Fabri, Herve Bronnimann
// coordinator   : INRIA Sophia-Antipolis
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CARTESIAN_GLOBAL_OPERATORS_3_H
#define CGAL_CARTESIAN_GLOBAL_OPERATORS_3_H

#include <CGAL/Cartesian/redefine_names_3.h>

CGAL_BEGIN_NAMESPACE

template < class R >
inline
PointC3<R CGAL_CTAG>
operator+(const PointC3<R CGAL_CTAG> &p, const VectorC3<R CGAL_CTAG> &v)
{ // FIXME : construction
  return PointC3<R CGAL_CTAG>(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
}

template < class R >
inline
PointC3<R CGAL_CTAG>
operator-(const PointC3<R CGAL_CTAG> &p, const VectorC3<R CGAL_CTAG> &v)
{ // FIXME : construction
  return PointC3<R CGAL_CTAG>(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
}

template < class R >
inline
PointC3<R CGAL_CTAG>
operator+(const Origin &, const VectorC3<R CGAL_CTAG> &v)
{
  return PointC3<R CGAL_CTAG>(v);
}

template < class R >
inline
PointC3<R CGAL_CTAG>
operator-(const Origin &, const VectorC3<R CGAL_CTAG> &v)
{
  return PointC3<R CGAL_CTAG>(-v);
}

template < class R >
inline
VectorC3<R CGAL_CTAG>
operator-(const PointC3<R CGAL_CTAG> &p, const PointC3<R CGAL_CTAG> &q)
{ // FIXME : construction
  return VectorC3<R CGAL_CTAG>(p.x() - q.x(), p.y() - q.y(), p.z() - q.z());
}

template < class R >
inline
VectorC3<R CGAL_CTAG>
operator-(const PointC3<R CGAL_CTAG> &p, const Origin &)
{
  return VectorC3<R CGAL_CTAG>(p);
}

template < class R >
inline
VectorC3<R CGAL_CTAG>
operator-(const Origin &, const PointC3<R CGAL_CTAG> &p)
{ // FIXME : construction
  return VectorC3<R CGAL_CTAG>(-p.x(), -p.y(), -p.z());
}

template < class R >
CGAL_KERNEL_INLINE
VectorC3<R CGAL_CTAG>
operator*(const typename R::FT &c, const VectorC3<R CGAL_CTAG> &w)
{ // FIXME : construction
   return VectorC3<R CGAL_CTAG>(c * w.x(), c * w.y(), c * w.z());
}

template < class R >
CGAL_KERNEL_INLINE
VectorC3<R CGAL_CTAG>
operator*(const VectorC3<R CGAL_CTAG> &w, const typename R::FT &c)
{ // FIXME : construction
   return VectorC3<R CGAL_CTAG>(c * w.x(), c * w.y(), c * w.z());
}

CGAL_END_NAMESPACE

#endif // CGAL_CARTESIAN_GLOBAL_OPERATORS_3_H
