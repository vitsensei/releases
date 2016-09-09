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
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/ch_utils.h
// package       : Convex_hull_2 (3.21)
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/06/25 12:26:20 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CH_UTILS_H
#define CGAL_CH_UTILS_H

#include <CGAL/config.h>
#include <CGAL/ch_assertions.h>

#define CGAL_CH_USE_ARGUMENT(arg)  (void)(arg)


CGAL_BEGIN_NAMESPACE
template <class Point, class BinaryPredicate>
class ch_Binary_predicate_reversor
{
public:
  ch_Binary_predicate_reversor() {}
  ch_Binary_predicate_reversor( const BinaryPredicate& p) : bp(p) {}

  bool operator() (const Point& p1, const Point& p2) const
       { return bp(p2,p1); }

private:
  BinaryPredicate  bp;
};
CGAL_END_NAMESPACE

#endif // CGAL_CH_UTILS_H

