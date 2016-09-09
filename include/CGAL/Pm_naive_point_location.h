// ======================================================================
//
// Copyright (c) 1999 The GALIA Consortium
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
//   the GALIA Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the GALIA Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The GALIA Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.0
// release_date  : 1999, June 03
//
// file          : include/CGAL/Pm_naive_point_location.h
// package       : pm (3.07)
// source        : 
// revision      : 
// revision_date : 
// author(s)     : Iddo Hanniel
//                 Oren Nechushtan
//
//
// coordinator   : Tel-Aviv University (Dan Halperin)
//
// Chapter       : 
// email         : cgal@cs.uu.nl
//
// ======================================================================
#ifndef CGAL_PM_NAIVE_POINT_LOCATION_H
#define CGAL_PM_NAIVE_POINT_LOCATION_H

#ifndef CGAL_PM_CONFIG_H
#include <CGAL/Pm_config.h>
#endif

#ifndef CGAL_PM_POINT_LOCATION_BASE_H
#include <CGAL/Pm_point_location_base.h>
#endif

#ifndef CGAL_PLANAR_MAP_MISC_H
#include <CGAL/Planar_map_misc.h>
#endif


CGAL_BEGIN_NAMESPACE

////////////////////////////////////////////////////////
//NAIVE STRATEGY
////////////////////////////////////////////////////////

template <class Planar_map>
class Pm_naive_point_location : public Pm_point_location_base<Planar_map> {
public:
  typedef typename Planar_map::Traits_wrap Traits_wrap;
private:
  Planar_map* pm;
  Traits_wrap* traits;

public:

  Pm_naive_point_location() : Pm_point_location_base<Planar_map>(),traits(0) {}
  
  void init(Planar_map& pmp, Traits& tr) {
    pm = &pmp;
    traits = (Traits_wrap*)(&tr);
  }

  void insert(Halfedge_handle h
              //additions by iddo for arrangement
              ,const X_curve& cv
              //end additions
              ) {}

  Halfedge_handle locate(const Point& p, Locate_type& lt);

  Halfedge_handle vertical_ray_shoot(const Point& p, Locate_type& lt, bool up);

  void split_edge(const X_curve &cv,
                  Halfedge_handle e1,
                  Halfedge_handle e2
                  //additions by iddo for arrangement
                  ,const X_curve& cv1, const X_curve& cv2
                  //end additions
                  ) {}

  void merge_edge(const X_curve &cv1,
                  const X_curve &cv2,
                  Halfedge_handle e
                  //additions by iddo for arrangement
                  ,const X_curve& cv
                  //end additions
                  ) {}

  void remove_edge(Halfedge_handle e) {}

private:
  //find the first halfedge pointing at v, when going clockwise
  //if highest==true - start from 12 oclock, else start from 6 oclock
  Halfedge_handle find_lowest(typename Planar_map::Vertex_handle v,
                              Traits_wrap *traits, bool highest){

  Halfedge_handle lowest_left = pm->halfedges_end();
  Halfedge_handle lowest_right = pm->halfedges_end();
  Halfedge_handle vertical_up = pm->halfedges_end();
  Halfedge_handle vertical_down = pm->halfedges_end();
  

  typename Planar_map::Halfedge_around_vertex_circulator first = v->incident_halfedges();
  typename Planar_map::Halfedge_around_vertex_circulator curr = first;
  
  do {
    if ( traits->point_is_left(curr->source()->point(), v->point())) 
      {
        if (lowest_left == pm->halfedges_end())
          lowest_left = curr;
        
        if (traits->curve_compare_at_x_left(curr->curve(),
                                            lowest_left->curve(), 
                                            v->point())==SMALLER)
          lowest_left = curr;
      }
    
    if ( traits->point_is_right(curr->source()->point(), 
                             v->point()) ) 
      {
        if (lowest_right == pm->halfedges_end())
          lowest_right = curr;
        
        if (traits->curve_compare_at_x_right(curr->curve(),
                                             lowest_right->curve(), 
                                             v->point())==LARGER
            )
          lowest_right = curr;
      }

    
    
    if (traits->curve_is_vertical(curr->curve())) {
        if (traits->compare_y(v->point(),
                               curr->source()->point())==LARGER)
          //debug
          //{ std::cout << "vertical up = " << curr->curve() << std::endl;

          vertical_up=curr; 

        //}//enddebug

        if (traits->compare_y(v->point(),
                               curr->source()->point())==SMALLER)
          //debug
          //{ std::cout << "vertical down = " << curr->curve() << std::endl;

           vertical_down=curr;
        //}//enddebug

    }        
        
  } while (++curr != first);
  

  /*
               vertical_down  
                    |
                    v   <- lowest_right      
                   'v'  
     lowest_left->  ^ 
                    |
                vertical_up
  */

  if (!highest) {
    if (lowest_left!= pm->halfedges_end()) 
      return lowest_left;
    else 
      if (vertical_down!= pm->halfedges_end()) 
        return vertical_down;
    else
      return lowest_right;
  }
  else { //down
    if (lowest_right!=pm->halfedges_end()) 
      return lowest_right;
    else 
      if (vertical_up!= pm->halfedges_end()) 
        return vertical_up; 
    else
      return lowest_left;
  }

}

};

//IMPLEMENTATION
//if unbounded face - returns NULL or some edge on unbounded face 
//if its a vertex returns a halfedge pointing _at_ it
template <class Planar_map>
Pm_naive_point_location<Planar_map>::Halfedge_handle
Pm_naive_point_location<Planar_map>::locate(const Point& p, Locate_type& lt){
  typename Planar_map::Vertex_iterator vit=pm->vertices_begin();
  for (; vit!=pm->vertices_end(); ++vit) {
    if (traits->point_is_same(p,vit->point()) ) {
      lt = pm->VERTEX; 
      return ( (vit->incident_halfedges()) );
    }
  }
  
  typename Planar_map::Halfedge_iterator hit=pm->halfedges_begin();
  for (; hit!=pm->halfedges_end(); ++hit) {
    if (traits->curve_get_point_status(hit->curve(),p)==Traits::ON_CURVE) {
      lt = pm->EDGE; 
      return hit;
    }
  }
  
  lt=pm->UNBOUNDED_FACE;
  Locate_type temp;
  Halfedge_handle h = vertical_ray_shoot(p,temp,true);
  if( temp!=pm->UNBOUNDED_FACE )       
    {
      if (temp==pm->VERTEX) {  //since h points at the vertex and is the first 
        h=h->twin();        //halfedge after the ray clockwise! then the  face
      }        //is to its _right_ (maybe the specs will change in the future) 

      if ( !(h->face()->is_unbounded()) ) 
          lt=pm->FACE;

      return h;
    }
  else //==the vertical ray shoot returned the halfedges_end() iterator.
    {
      if (pm->unbounded_face()->holes_begin() == pm->unbounded_face()->holes_end() ) //an empty map
        return h; //return halfedges_end()
      else {
        //- returns a halfedge on an inner ccb of the unbounded face
        typename Planar_map::Holes_iterator hot=pm->unbounded_face()->holes_begin();
        return (*hot);
      }
    }
}
  


template <class Planar_map>
Pm_naive_point_location<Planar_map>::Halfedge_handle
Pm_naive_point_location<Planar_map>::vertical_ray_shoot(const Point& p, Locate_type& lt, bool up) {

  typename Planar_map::Halfedge_iterator closest_edge = pm->halfedges_end();
  bool first = false;
  typename Traits::Curve_point_status point_above_under;
  int curve_above_under;

  lt=pm->EDGE;
  
  // set the flags for comparison acording to the ray 
  // direction (up/down)
  if (up) 
    {
      point_above_under = Traits::UNDER_CURVE;
      curve_above_under = LARGER;
    } 
  else 
    {
      point_above_under = Traits::ABOVE_CURVE;
      curve_above_under = SMALLER;
    }
  for (typename Planar_map::Halfedge_iterator it = pm->halfedges_begin(); it != pm->halfedges_end(); ++it) 
    {
      if ( traits->curve_get_point_status(it->curve(), p) 
           == point_above_under ) 
        {
          if (!first) 
            {
              closest_edge = it;
              first = true;
            } 
          else 
            {
              if ( traits->curve_compare_at_x(closest_edge->curve(),
                                              it->curve(), p) == curve_above_under) 
                {
                  closest_edge = it;
                }
            }
        }
    }
  
  // if we didn't find any edge above p then it is the empty face
  if (!first) {
    lt=pm->UNBOUNDED_FACE;
    return pm->halfedges_end(); //==NULL
  }
  // if the closest point is a vertex then find the first clockwise 
  // edge from the vertical segment
  typename Planar_map::Vertex_handle v = pm->vertices_end();
  if ( traits->point_is_same_x(closest_edge->target()->point(), p) ) 
    {
      v = closest_edge->target();
    }
  
  if ( traits->point_is_same_x( closest_edge->source()->point(), p) ) 
    {
      v = closest_edge->source();
    }
  
  //if (closest_is_vertex)
  if (v != pm->vertices_end()) 
    {
      lt=pm->VERTEX;
      if (up)    
        closest_edge = find_lowest(v,traits, false);  
      else
        closest_edge = find_lowest(v,traits, true);
    }

  if (lt==pm->VERTEX)
    return closest_edge;
  //else  

  if (up) 
    {
      // return the edge that is going from right to left
      // such that p is to the left of this edge
      
      if ( traits->point_is_right( closest_edge->source()->point(),
                                closest_edge->target()->point()) )
        return closest_edge;  //source is right of the target
      else
        return closest_edge->twin();
    } 
  else 
    {
      if ( traits->point_is_left( closest_edge->source()->point(),
                                closest_edge->target()->point()) )
        return  closest_edge;
      else
        return  closest_edge->twin();
    }
}



CGAL_END_NAMESPACE

#endif //CGAL_PM_NAIVE_POINT_LOCATION_H











