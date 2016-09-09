// Copyright (c) 2004  Max-Planck-Institute Saarbruecken (Germany).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Box_intersection_d/include/CGAL/Box_intersection_d/Box_traits_d.h $
// $Id: Box_traits_d.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>
//                 Andreas Meyer <ameyer@mpi-sb.mpg.de>

#ifndef CGAL_BOX_INTERSECTION_D_BOX_TRAITS_D_H
#define CGAL_BOX_INTERSECTION_D_BOX_TRAITS_D_H

#include <CGAL/basic.h>
#include <functional>

namespace CGAL {

namespace Box_intersection_d {


enum Setting  { COMPLETE, BIPARTITE };
enum Topology { HALF_OPEN, CLOSED };


template<class BoxHandle>
struct Box_traits_d {
    typedef const BoxHandle&        Box_parameter;
    typedef typename BoxHandle::NT  NT;
    typedef typename BoxHandle::ID  ID;

    static NT  min_coord(Box_parameter b, int dim) { return b.min_coord( dim);}
    static NT  max_coord(Box_parameter b, int dim) { return b.max_coord( dim);}
    static ID  id(Box_parameter b)                 { return b.id();}
    static int dimension()                         { return BoxHandle::dimension();}
};

// box pointer traits
template<class Box_>
struct Box_traits_d<Box_*> {
    typedef const Box_*       Box_parameter;
    typedef typename Box_::NT NT;
    typedef typename Box_::ID ID;

    static NT  min_coord(Box_parameter b, int dim) { return b->min_coord(dim);}
    static NT  max_coord(Box_parameter b, int dim) { return b->max_coord(dim);}
    static ID  id(Box_parameter b)                 { return b->id();}
    static int dimension()                         { return Box_::dimension();}
};

// box pointer traits
template<class Box_>
struct Box_traits_d<const Box_*> {
    typedef const Box_*       Box_parameter;
    typedef typename Box_::NT NT;
    typedef typename Box_::ID ID;

    static NT  min_coord(Box_parameter b, int dim) { return b->min_coord(dim);}
    static NT  max_coord(Box_parameter b, int dim) { return b->max_coord(dim);}
    static ID  id(Box_parameter b)                 { return b->id();}
    static int dimension()                         { return Box_::dimension();}
};


template< class BoxTraits, bool closed >
struct Predicate_traits_d : public BoxTraits {
    typedef typename BoxTraits::Box_parameter Box_parameter;
    typedef typename BoxTraits::NT         NT;

    template<bool b> struct Bool_t {};

    static bool hi_greater(NT hi, NT val, Bool_t<true> ) { return hi >= val;}
    static bool hi_greater(NT hi, NT val, Bool_t<false> ){ return hi >  val;}
    static bool hi_greater (NT hi, NT val) {
        return hi_greater(hi,val, Bool_t<closed>()); 
    }

    // compare dim a b = islolesslo a b dim
    class Compare : 
        public std::binary_function<Box_parameter,Box_parameter,bool>
    {
        int dim;
    public:
        Compare(int dim) : dim(dim) {}
        bool operator()(Box_parameter a, Box_parameter b) const { 
            return is_lo_less_lo(a,b,dim); 
        }
    };

    // loless val dim box = getlo box dim < val
    class Lo_less : public std::unary_function<Box_parameter,bool> {
        NT value;
        int dim;
    public:
        Lo_less(NT value, int dim) : value(value), dim(dim) {}
        bool operator() (Box_parameter box) const { 
            return BoxTraits::min_coord(box, dim) < value;
        }
    };

    class Hi_greater : public std::unary_function<Box_parameter,bool> {
        NT value;
        int dim;
    public:
        Hi_greater(NT value, int dim) : value(value), dim(dim) {}
        bool operator() (Box_parameter box) const {
            return hi_greater( BoxTraits::max_coord(box, dim), value);
        }
    };

    // spanning lo hi dim box = getlo box dim < lo && gethi box dim > hi
    class Spanning : public std::unary_function<Box_parameter,bool> {
        NT lo, hi;
        int dim;
    public:
        Spanning(NT lo, NT hi, int dim) : lo(lo), hi(hi), dim(dim) {}
        // returns true <=> box spans [lo,hi) in dimension dim
        bool operator() (Box_parameter box) const {
            return BoxTraits::min_coord(box,dim) < lo 
                && BoxTraits::max_coord(box,dim) > hi;
        }
    };

    static Compare    compare_object(int dim) { return Compare(dim); }

    static Lo_less    lo_less_object(NT value, int dim) {
                          return Lo_less(value, dim);
    }
    static Hi_greater hi_greater_object(NT value, int dim) {
                          return Hi_greater( value, dim );
    }
    static Spanning   spanning_object(NT lo, NT hi, int dim) {
                          return Spanning( lo, hi, dim );
    }
    static bool is_lo_less_lo(Box_parameter a, Box_parameter b, int dim) {
        return BoxTraits::min_coord(a,dim)  < BoxTraits::min_coord(b,dim) ||
               ( BoxTraits::min_coord(a,dim) == BoxTraits::min_coord(b,dim) && 
                 BoxTraits::id(a) < BoxTraits::id(b) );
    }

    static bool is_lo_less_hi(Box_parameter a, Box_parameter b, int dim) {
        return hi_greater( BoxTraits::max_coord(b,dim), 
                           BoxTraits::min_coord(a,dim));
    }
    static bool does_intersect (Box_parameter a, Box_parameter b, int dim) {
        return is_lo_less_hi(a,b,dim) && is_lo_less_hi(b,a,dim);
    }
    static bool contains_lo_point(Box_parameter a, Box_parameter b, int dim) {
        return is_lo_less_lo(a,b,dim) && is_lo_less_hi(b,a,dim);
    }
};

} // end namespace Box_intersection_d


} //namespace CGAL

#endif
