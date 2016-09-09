// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium

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
// file          : include/CGAL/squared_distance_utils.h
// package       : Distance_2 (2.4.2)
// source        : sqdistance_2.fw
// author(s)     : Geert-Jan Giezeman
//
// coordinator   : Saarbruecken
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_SQUARED_DISTANCE_UTILS_H
#define CGAL_SQUARED_DISTANCE_UTILS_H

#include <CGAL/determinant.h>
#include <CGAL/wmult.h>

CGAL_BEGIN_NAMESPACE


template <class R>
bool is_null(const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return v.hx()==RT(0) && v.hy()==RT(0);
}


template <class R>
typename R::RT
wdot(const Vector_2<R> &u, const Vector_2<R> &v)
{
    return  (u.hx()*v.hx() + u.hy()*v.hy());
}



template <class R>
typename R::RT wdot(const Point_2< R > &p,
    const Point_2< R > &q,
    const Point_2< R > &r)
{
    R* pR = 0;
    return  (wmult(pR, p.hx(),q.hw()) - wmult(pR, q.hx(),p.hw()))
          * (wmult(pR, r.hx(),q.hw()) - wmult(pR, q.hx(),r.hw()))
          + (wmult(pR, p.hy(),q.hw()) - wmult(pR, q.hy(),p.hw()))
          * (wmult(pR, r.hy(),q.hw()) - wmult(pR, q.hy(),r.hw()));
}



template <class R>
typename R::RT
wcross(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    return (typename R::RT)(u.hx()*v.hy() - u.hy()*v.hx());
}

#if defined CGAL_HOMOGENEOUS_H
template <class RT>
inline
RT wcross_impl(const Homogeneous<RT>*,const Point_2< Homogeneous<RT> > &p,
    const Point_2< Homogeneous<RT> > &q,
    const Point_2< Homogeneous<RT> > &r)
{
    return   p.hx() * (q.hy()*r.hw() - q.hw()*r.hy() )
           + p.hy() * (q.hw()*r.hx() - q.hx()*r.hw() )
           + p.hw() * (q.hx()*r.hy() - q.hy()*r.hx() );
}
#endif // CGAL_HOMOGENEOUS_H

#if defined CGAL_SIMPLE_HOMOGENEOUS_H
template <class RT>
inline
RT wcross_impl(const Simple_homogeneous<RT>*,
    const Point_2< Simple_homogeneous<RT> > &p,
    const Point_2< Simple_homogeneous<RT> > &q,
    const Point_2< Simple_homogeneous<RT> > &r)
{
    return det3x3_by_formula(
        p.hx(), q.hx(), r.hx(),
        p.hy(), q.hy(), r.hy(),
        p.hw(), q.hw(), r.hw());
}
#endif // CGAL_SIMPLE_HOMOGENEOUS_H

#if defined CGAL_CARTESIAN_H
template <class FT>
inline
FT wcross_impl(const Cartesian<FT> *, const Point_2< Cartesian<FT> > &p,
    const Point_2< Cartesian<FT> > &q,
    const Point_2< Cartesian<FT> > &r)
{
    return (q.x()-p.x())*(r.y()-q.y()) - (q.y()-p.y())*(r.x()-q.x());
}
#endif // CGAL_CARTESIAN_H

#if defined CGAL_SIMPLE_CARTESIAN_H
template <class FT>
inline
FT wcross_impl(const Simple_cartesian<FT> *,
    const Point_2< Simple_cartesian<FT> > &p,
    const Point_2< Simple_cartesian<FT> > &q,
    const Point_2< Simple_cartesian<FT> > &r)
{
    return (q.x()-p.x())*(r.y()-q.y()) - (q.y()-p.y())*(r.x()-q.x());
}
#endif // CGAL_SIMPLE_CARTESIAN_H

template <class R>
typename R::RT wcross(const Point_2< R > &p,
    const Point_2< R > &q,
    const Point_2< R > &r)
{
   return wcross_impl(static_cast<R*>(0), p, q, r);
}



template <class R>
inline bool is_acute_angle(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) > RT(0) ;
}

template <class R>
inline bool is_straight_angle(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) == RT(0) ;
}

template <class R>
inline bool is_obtuse_angle(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wdot(u, v)) < RT(0) ;
}

template <class R>
inline bool is_acute_angle(const Point_2<R> &p,
    const Point_2<R> &q, const Point_2<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) > RT(0) ;
}

template <class R>
inline bool is_straight_angle(const Point_2<R> &p,
    const Point_2<R> &q, const Point_2<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) == RT(0) ;
}

template <class R>
inline bool is_obtuse_angle(const Point_2<R> &p,
    const Point_2<R> &q, const Point_2<R> &r)
{
    typedef typename R::RT RT;
    return RT(wdot(p, q, r)) < RT(0) ;
}


template <class R>
Orientation orientation(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    RT wcr = wcross(u,v);
    return (wcr > RT(0)) ? COUNTERCLOCKWISE :
           (wcr < RT(0)) ? CLOCKWISE
                            : COLLINEAR;
}

template <class R>
inline bool counterclockwise(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) > RT(0);
}

template <class R>
inline bool leftturn(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) > RT(0);
}

template <class R>
inline bool clockwise(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) < RT(0);
}

template <class R>
inline bool rightturn(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) < RT(0);
}

template <class R>
inline bool collinear(const Vector_2<R> &u,
    const Vector_2<R> &v)
{
    typedef typename R::RT RT;
    return RT(wcross(u,v)) == RT(0);
}

/*
the ordertype, rightturn, leftturn and collinear routines for points are
defined elsewhere.
*/


CGAL_END_NAMESPACE

#endif // CGAL_SQUARED_DISTANCE_UTILS_H
