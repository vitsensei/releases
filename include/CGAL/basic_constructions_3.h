// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// 
// release       : CGAL-1.1
// release_date  : 1998, July 24
// 
// source        : basic_constructions_3.fw
// file          : include/CGAL/basic_constructions_3.h
// package       : _3 (1.3)
// revision      : 1.3
// revision_date : 15 May 1998 
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : cgal@cs.uu.nl
//
// ======================================================================


#ifndef CGAL_BASIC_CONSTRUCTIONS_3_H
#define CGAL_BASIC_CONSTRUCTIONS_3_H

#ifdef CGAL_HOMOGENEOUS_H
#include <CGAL/basic_constructionsH3.h>
#endif // CGAL_HOMOGENEOUS_H

#ifdef CGAL_CARTESIAN_H
#include <CGAL/basic_constructionsC3.h>
#endif // CGAL_CARTESIAN_H

template < class R >
inline
CGAL_Point_3<R>
CGAL_midpoint( const CGAL_Point_3<R>& p,
               const CGAL_Point_3<R>& q )
{
    typedef typename R::Point_3  Point_3;
    return( CGAL_midpoint( CGAL_static_cast( const Point_3&, p),
                           CGAL_static_cast( const Point_3&, q)));
}
template < class R >
inline
CGAL_Point_3<R>
CGAL_circumcenter( const CGAL_Point_3<R>& p,
                   const CGAL_Point_3<R>& q,
                   const CGAL_Point_3<R>& r,
                   const CGAL_Point_3<R>& s)
{
    typedef typename R::Point_3  Point_3;
    return( CGAL_circumcenter( CGAL_static_cast( const Point_3&, p),
                               CGAL_static_cast( const Point_3&, q),
                               CGAL_static_cast( const Point_3&, r),
                               CGAL_static_cast( const Point_3&, s)));
}

#endif // CGAL_BASIC_CONSTRUCTIONS_3_H