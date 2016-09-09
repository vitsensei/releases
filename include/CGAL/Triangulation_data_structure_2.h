// Copyright (c) 1997  INRIA Sophia-Antipolis (France).
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
// $Source: /CVSROOT/CGAL/Packages/Triangulation_2/include/CGAL/Triangulation_data_structure_2.h,v $
// $Revision: 1.42 $ $Date: 2004/09/07 13:22:35 $
// $Name:  $
//
// Author(s)     : Mariette Yvinec

#ifndef CGAL_TRIANGULATION_DATA_STRUCTURE_2_H
#define CGAL_TRIANGULATION_DATA_STRUCTURE_2_H

#include <CGAL/basic.h>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>
#include <boost/tuple/tuple.hpp>

#if (!defined _MSC_VER || defined __INTEL_COMPILER) && !defined __sgi
#  define CGAL_T2_USE_ITERATOR_AS_HANDLE
#endif

#include <CGAL/triangulation_assertions.h>
#include <CGAL/Triangulation_short_names_2.h>
#include <CGAL/Triangulation_utils_2.h>
 
#include <CGAL/Compact_container.h>

#include <CGAL/Triangulation_ds_face_base_2.h>
#include <CGAL/Triangulation_ds_vertex_base_2.h>
#include <CGAL/Triangulation_ds_face_2.h>
#include <CGAL/Triangulation_ds_vertex_2.h>
#include <CGAL/Triangulation_ds_iterators_2.h>
#include <CGAL/Triangulation_ds_circulators_2.h>

#include <CGAL/IO/File_header_OFF.h>
#include <CGAL/IO/File_scanner_OFF.h>

CGAL_BEGIN_NAMESPACE 

template < class Vb = Triangulation_ds_vertex_base_2<>, 
           class Fb = Triangulation_ds_face_base_2<> >
class Triangulation_data_structure_2 
  :public Triangulation_cw_ccw_2
{
  typedef Triangulation_data_structure_2<Vb,Fb>  Tds;

  typedef typename Vb::template Rebind_TDS<Tds>::Other  Vertex_base;
  typedef typename Fb::template Rebind_TDS<Tds>::Other  Face_base;

  friend class Triangulation_ds_edge_iterator_2<Tds>;
  friend class Triangulation_ds_face_circulator_2<Tds>;
  friend class Triangulation_ds_edge_circulator_2<Tds>;
  friend class Triangulation_ds_vertex_circulator_2<Tds>;
                
public:
  typedef Triangulation_ds_vertex_2<Vertex_base>     Vertex;
  typedef Triangulation_ds_face_2<Face_base>         Face;
  
private:
  typedef Compact_container<Face>                    Face_container;
  typedef Compact_container<Vertex>                  Vertex_container;

public:
  typedef typename Face_container::size_type         size_type;
  typedef typename Face_container::difference_type   difference_type;

  typedef typename Face_container::iterator          Face_iterator;
  typedef typename Vertex_container::iterator        Vertex_iterator;

  typedef Triangulation_ds_edge_iterator_2<Tds>      Edge_iterator;

  typedef Triangulation_ds_face_circulator_2<Tds>    Face_circulator;
  typedef Triangulation_ds_vertex_circulator_2<Tds>  Vertex_circulator;
  typedef Triangulation_ds_edge_circulator_2<Tds>    Edge_circulator;

#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE 
  typedef Vertex_iterator Vertex_handle;
  typedef Face_iterator Face_handle;
#else
  // Defining nested classes for the handles instead of typedefs
  // considerably shortens the symbol names (and compile times).
  // It makes error messages more readable as well.
  class Vertex_handle {
    Vertex_iterator _v;
  public:
    typedef Vertex                                 value_type;
    typedef value_type *                           pointer;
    typedef value_type &                           reference;
    typedef std::size_t                            size_type;
    typedef std::ptrdiff_t                         difference_type;
    typedef void                                   iterator_category;

    Vertex_handle() : _v() {}
    Vertex_handle(const Vertex_iterator& v) : _v(v) {}
    Vertex_handle(const Vertex_circulator& v) : _v(v.base()._v) {}
    Vertex_handle(void * CGAL_triangulation_precondition_code(n)) : _v()
    { CGAL_triangulation_precondition(n == NULL); }

    Vertex* operator->() const { return &*_v; }
    Vertex& operator*()  const { return *_v; }

    bool operator==(Vertex_handle v) const { return _v == v._v; }
    bool operator!=(Vertex_handle v) const { return _v != v._v; }

    // For std::set and co.
    bool operator<(Vertex_handle v) const { return &*_v < &*v._v; }

    // Should be private to the TDS :
    const Vertex_iterator & base() const { return _v; }
    Vertex_iterator & base() { return _v; }

    void * for_compact_container() const { return _v.for_compact_container(); }
    void * & for_compact_container()     { return _v.for_compact_container(); }
   };
  
  class Face_handle {
    Face_iterator _f;
  public:
    typedef Face                                   value_type;
    typedef value_type *                           pointer;
    typedef value_type &                           reference;
    typedef std::size_t                            size_type;
    typedef std::ptrdiff_t                         difference_type;
    typedef void                                   iterator_category;

    Face_handle() : _f() {}
    Face_handle(const Face_iterator& f) : _f(f) {}
    Face_handle(const Face_circulator& f) : _f(f.base()._f) {}
    //Face_handle(Face_circulator f) : _f(f.base()._f) {}
    Face_handle(void * CGAL_triangulation_precondition_code(n)) : _f()
    { CGAL_triangulation_precondition(n == NULL); }

    Face* operator->() const { return &*_f; }
    Face& operator*()  const { return *_f; }

    bool operator==(Face_handle f) const { return _f == f._f; }
    bool operator!=(Face_handle f) const { return _f != f._f; }

    // For std::set and co.
    bool operator<(Face_handle f) const { return &*_f < &*f._f; }

    // These should be private to the TDS :
    const Face_iterator & base() const { return _f; }
    Face_iterator & base() { return _f; }

    void * for_compact_container() const { return _f.for_compact_container(); }
    void * & for_compact_container()     { return _f.for_compact_container(); }
   };
#endif
  typedef std::pair<Face_handle, int>                Edge;
  typedef std::list<Edge> List_edges;

protected:
  int _dimension;
  Face_container   _face_container;
  Vertex_container _vertex_container;

  //CREATORS - DESTRUCTORS
public:
  Triangulation_data_structure_2(); 
  Triangulation_data_structure_2(const Tds &tds);
  ~Triangulation_data_structure_2();
  Tds& operator= (const Tds &tds);
  void swap(Tds &tds);

  //ACCESS FUNCTIONS
private:
  // We need the const_cast<>s because TDS is not const-correct.
  Face_container& face_container()             { return _face_container;}
  Face_container& face_container() const 
    { return  const_cast<Tds*>(this)->_face_container;}
  Vertex_container& vertex_container()         {return _vertex_container;}
  Vertex_container& vertex_container() const
    {return  const_cast<Tds*>(this)->_vertex_container;}

public:
  int  dimension() const { return _dimension;  }
  size_type number_of_vertices() const {return vertex_container().size();}
  size_type number_of_faces() const ;
  size_type number_of_edges() const;
  size_type number_of_full_dim_faces() const; //number of faces stored by tds
  
  // TEST FEATURES
  bool is_vertex(Vertex_handle v) const;
  bool is_edge(Face_handle fh, int i) const;
  bool is_edge(Vertex_handle va, Vertex_handle vb) const;
  bool is_edge(Vertex_handle va, Vertex_handle vb, 
	       Face_handle& fr,  int& i) const;
  bool is_face(Face_handle fh) const;
  bool is_face(Vertex_handle v1, 
	       Vertex_handle v2, 
	       Vertex_handle v3) const;
  bool is_face(Vertex_handle v1, 
	       Vertex_handle v2, 
	       Vertex_handle v3,
	       Face_handle& fr) const;

  // ITERATORS AND CIRCULATORS
public:
// The face_iterator_base_begin  gives the possibility to iterate over all
// faces in the container  independently of the dimension.
  // public for the need of file_ouput() of Constrained triangulation
  // should be made private later

  Face_iterator face_iterator_base_begin() const    {
    return face_container().begin();
  }
  Face_iterator face_iterator_base_end() const    {
    return face_container().end();
  }

public:
  Face_iterator faces_begin() const {
    if (dimension() < 2) return faces_end();
    return face_container().begin();
  }
    
  Face_iterator faces_end() const {
    return face_container().end();
  }

  Vertex_iterator vertices_begin() const  {
    return vertex_container().begin();
  }

  Vertex_iterator vertices_end() const {
    return vertex_container().end();
  }
  
  Edge_iterator edges_begin() const {
    return Edge_iterator(this);
  }

  Edge_iterator edges_end() const {
    return Edge_iterator(this,1);
  }
  
  Face_circulator incident_faces(Vertex_handle v, 
				 Face_handle f =  Face_handle()) const{
    return Face_circulator(v,f);
  }
  Vertex_circulator incident_vertices(Vertex_handle v, 
				      Face_handle f = Face_handle()) const
  {    
    return Vertex_circulator(v,f);  
  }

  Edge_circulator incident_edges(Vertex_handle v, 
				 Face_handle f = Face_handle()) const{
    return Edge_circulator(v,f);
  }

  // MODIFY
  void flip(Face_handle f, int i);
 
  Vertex_handle insert_first();
  Vertex_handle insert_second();
  Vertex_handle insert_in_face(Face_handle f);
  Vertex_handle insert_in_edge(Face_handle f, int i);
  Vertex_handle insert_dim_up(Vertex_handle w = Vertex_handle(), 
			      bool orient=true);

  void remove_degree_3(Vertex_handle v, Face_handle f = Face_handle());
  void remove_1D(Vertex_handle v); 
   
  void remove_second(Vertex_handle v);
  void remove_first(Vertex_handle v);
  void remove_dim_down(Vertex_handle v);

  Vertex_handle star_hole(List_edges& hole);
  void    star_hole(Vertex_handle v, List_edges& hole);
  void    make_hole(Vertex_handle v, List_edges& hole);

//   template< class EdgeIt>
//   Vertex_handle star_hole(EdgeIt edge_begin,EdgeIt edge_end);
 
//   template< class EdgeIt>
//   void  star_hole(Vertex_handle v, EdgeIt edge_begin,  EdgeIt edge_end);

//   template< class EdgeIt, class FaceIt>
//   Vertex_handle star_hole(EdgeIt edge_begin, 
// 		    EdgeIt edge_end,
// 		    FaceIt face_begin,
// 		    FaceIt face_end);
 
//   template< class EdgeIt, class FaceIt>
//   void  star_hole(Vertex_handle v,
// 		  EdgeIt edge_begin, 
// 		  EdgeIt edge_end,
// 		  FaceIt face_begin,
// 		  FaceIt face_end);
  
  Vertex_handle create_vertex(const Vertex &v = Vertex());
  Vertex_handle create_vertex(Vertex_handle v); //calls copy constructor 
  Face_handle create_face(const Face& f = Face());
  Face_handle create_face(Face_handle f); //calls copy constructor 

 Face_handle create_face(Face_handle f1, int i1, 
			  Face_handle f2, int i2, 
			  Face_handle f3, int i3);
  Face_handle create_face(Face_handle f1, int i1, 
			  Face_handle f2, int i2);
  Face_handle create_face(Face_handle f1, int i1, Vertex_handle v);
  Face_handle create_face(Vertex_handle v1, 
			  Vertex_handle v2, 
			  Vertex_handle v3);
  Face_handle create_face(Vertex_handle v1, 
			  Vertex_handle v2, 
			  Vertex_handle v3,
			  Face_handle f1, 
			  Face_handle f2, 
			  Face_handle f3);
    void set_adjacency(Face_handle f0, int i0, Face_handle f1, int i1) const;
  void delete_face(Face_handle);
  void delete_vertex(Vertex_handle);

  // split and join operations
 protected:
  Vertex_handle join_vertices(Face_handle f, int i, Vertex_handle v);

  typedef
  boost::tuples::tuple<Vertex_handle,Vertex_handle,Face_handle,Face_handle>
  Fourtuple;

 public:
  Fourtuple split_vertex(Vertex_handle v, Face_handle f1, Face_handle g1);

  inline Vertex_handle join_vertices(Face_handle f, int i) {
    return join_vertices(f, i, f->vertex( ccw(i) ));
  }

  inline Vertex_handle join_vertices(Edge e) {
    return join_vertices(e.first, e.second);
  }

  inline Vertex_handle join_vertices(Edge_iterator eit) {
    return join_vertices(*eit);
  }

  inline Vertex_handle join_vertices(Edge_circulator ec) {
    return join_vertices(*ec);
  }

  // insert_degree_2 and remove_degree_2 operations
  Vertex_handle insert_degree_2(Face_handle f, int i);
  void remove_degree_2(Vertex_handle v);

  // CHECKING
  bool is_valid(bool verbose = false, int level = 0) const;
  
  // HELPING
private:
  typedef std::pair<Vertex_handle,Vertex_handle> Vh_pair;
  void  set_adjacency(Face_handle fh, 
		      int ih, 
		      std::map< Vh_pair, Edge>& edge_map);
  void reorient_faces();

public:
  void clear();
  Vertex_handle copy_tds(const Tds &tds, Vertex_handle = Vertex_handle());
  
  // I/O
  Vertex_handle file_input(std::istream& is, bool skip_first=false);
  void file_output(std::ostream& os,
		   Vertex_handle v = Vertex_handle(),
		   bool skip_first=false) const;
  Vertex_handle off_file_input(std::istream& is, bool verbose=false);
  void  vrml_output(std::ostream& os,
		    Vertex_handle v = Vertex_handle(),
		    bool skip_first=false) const;

  // SETTING (had to make them public for use in remove from Triangulations)
  void set_dimension (int n) {_dimension = n ;}

  // template members definition
public:
  template< class EdgeIt>
  Vertex_handle star_hole(EdgeIt edge_begin, EdgeIt edge_end)
  // creates a new vertex 
  // and stars from it
  // the hole described by the range [edge_begin,edge_end[
  // the triangulation is assumed to have dim=2
  // hole is supposed to be ccw oriented
  {
     Vertex_handle newv = create_vertex();
     star_hole(newv, edge_begin, edge_end);
     return newv;
  }
 
  template< class EdgeIt>
  void  star_hole(Vertex_handle v, EdgeIt edge_begin,  EdgeIt edge_end)
  // uses vertex v
  // to star the hole described by the range [edge_begin,edge_end[
  // the triangulation is assumed to have dim=2
  // the hole is supposed to be ccw oriented
  { 
    std::list<Face_handle> empty_list;
    star_hole(v, 
	      edge_begin, 
	      edge_end, 
	      empty_list.begin(),
	      empty_list.end());
    return;    
  }


  template< class EdgeIt, class FaceIt>
  Vertex_handle star_hole(EdgeIt edge_begin, 
		    EdgeIt edge_end,
		    FaceIt face_begin,
		    FaceIt face_end)
  // creates a new vertex 
  // and stars from it
  // the hole described by the range [edge_begin,edge_end[
    // reusing the faces in the range [face_begin,face_end[
  // the triangulation is assumed to have dim=2
  // the hole is supposed to be ccw oriented
  {
    Vertex_handle newv = create_vertex();
    star_hole(newv, edge_begin, edge_end, face_begin, face_end);
    return newv;
  }
 
  template< class EdgeIt, class FaceIt>
  void  star_hole(Vertex_handle newv,
		  EdgeIt edge_begin, 
		  EdgeIt edge_end,
		  FaceIt face_begin,
		  FaceIt face_end)
    // uses vertex v
    // to star the hole described by the range [edge_begin,edge_end[
    // reusing the faces in the range [face_begin,face_end[
    // the triangulation is assumed to have dim=2
    // hole is supposed to be ccw oriented
  {
    CGAL_triangulation_precondition(dimension() == 2);
    EdgeIt eit = edge_begin;
    FaceIt fit = face_begin;

    Face_handle fn = (*eit).first;
    int in = (*eit).second;
    fn->vertex(cw(in))->set_face(fn);
    Face_handle first_f =  reset_or_create_face(fn, in , newv, fit, face_end);
    Face_handle previous_f=first_f, next_f;
    ++eit; 

    for( ; eit != edge_end ; eit++) {
      fn = (*eit).first;
      in = (*eit).second;
      fn->vertex(cw(in))->set_face(fn);
      next_f = reset_or_create_face(fn, in , newv, fit, face_end);
      next_f->set_neighbor(1, previous_f);
      previous_f->set_neighbor(0, next_f);
      previous_f=next_f;
    }
    
    next_f->set_neighbor(0, first_f);
    first_f->set_neighbor(1, next_f);
    newv->set_face(first_f);
    return;    
  }

private:
  template< class FaceIt>
  Face_handle  reset_or_create_face(Face_handle fn, 
			      int in, 
			      Vertex_handle v,
			      FaceIt& fit,
			      const FaceIt& face_end)
  {
    if (fit == face_end) return create_face(fn, in, v);
    (*fit)->set_vertices(fn->vertex(cw(in)), fn->vertex(ccw(in)), v);
    (*fit)->set_neighbors(Face_handle(),Face_handle(),fn);
    fn->set_neighbor(in, *fit);
    return *fit++;    
  }

};

//for backward compatibility
template < class Gt , class Vb, class Fb>
class Triangulation_default_data_structure_2 
  : public Triangulation_data_structure_2<Vb,Fb>
{
public:
  typedef Triangulation_data_structure_2<Vb,Fb>  Tds;
  typedef Triangulation_default_data_structure_2<Gt,Vb,Fb> Tdds;
  typedef Gt                           Geom_traits; 

  Triangulation_default_data_structure_2(const Geom_traits&
					 gt=Geom_traits())
    : Tds() {}
 
  Triangulation_default_data_structure_2(const Tdds &tdds)
    : Tds(tdds) {}
};

//for backward compatibility
template <class Vb, class Fb>
class Triangulation_data_structure_using_list_2
  :public Triangulation_data_structure_2<Vb, Fb>
{
public:
  typedef Triangulation_data_structure_2<Vb,Fb>  Tds;
  typedef Triangulation_data_structure_using_list_2<Vb,Fb>  Tdsul;

  Triangulation_data_structure_using_list_2(): Tds() {} 
  Triangulation_data_structure_using_list_2(const Tdsul &tdsul)
    : Tds(tdsul) {}
};

 
template < class Vb, class Fb>
Triangulation_data_structure_2<Vb,Fb> ::
Triangulation_data_structure_2() 
  : _dimension(-2)
{ }

template < class Vb, class Fb>
Triangulation_data_structure_2<Vb,Fb> ::
Triangulation_data_structure_2(const Tds &tds)
{
  copy_tds(tds);
}

template < class Vb, class Fb>
Triangulation_data_structure_2<Vb,Fb> ::
~Triangulation_data_structure_2()
{
  clear();
}

//assignement  
template < class Vb, class Fb>
Triangulation_data_structure_2<Vb,Fb>&
Triangulation_data_structure_2<Vb,Fb> ::
operator= (const Tds &tds)
{
  copy_tds(tds);
  return *this;
}  

template <  class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
clear()
{
  face_container().clear();
  vertex_container().clear();
  set_dimension(-2);
  return;
}

template <  class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
swap(Tds &tds)
{
  CGAL_triangulation_expensive_precondition(tds.is_valid() && is_valid());
  std::swap(_dimension, tds._dimension);
  face_container().swap(tds.face_container());
  vertex_container().swap(tds.vertex_container());
  return;
}

//ACCESS FUNCTIONS
template <class Vb, class Fb>
inline 
typename Triangulation_data_structure_2<Vb,Fb>::size_type
Triangulation_data_structure_2<Vb,Fb> ::
number_of_faces() const 
{
  if (dimension() < 2) return 0;
  return face_container().size();
}

template <class Vb, class Fb>
inline 
typename Triangulation_data_structure_2<Vb,Fb>::size_type
Triangulation_data_structure_2<Vb,Fb>::
number_of_edges() const
{
  switch (dimension()) {
  case 1:  return number_of_vertices();
  case 2:  return 3*number_of_faces()/2;
  default: return 0;
  }
}
      
template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::size_type
Triangulation_data_structure_2<Vb,Fb>::
number_of_full_dim_faces() const
{
  return face_container().size();
}

template <class Vb, class Fb>
inline bool
Triangulation_data_structure_2<Vb,Fb>::
is_vertex(Vertex_handle v) const
{
  Vertex_iterator vit = vertices_begin();
  while (vit != vertices_end() && v != vit)
        ++vit;
  return v == vit;
}

template <class Vb, class Fb>
inline bool
Triangulation_data_structure_2<Vb,Fb>::
is_edge(Face_handle fh, int i) const
{
  if ( dimension() == 0 )  return false;
  if ( dimension() == 1 && i != 2) return false;
  if (i > 2) return false;
  Face_iterator fit = face_iterator_base_begin();
  while (fit != face_iterator_base_end() && fh != fit ) ++fit;
  return fh == fit;
}

template <class Vb, class Fb>
bool
Triangulation_data_structure_2<Vb,Fb>::
is_edge(Vertex_handle va, Vertex_handle vb) const
// returns true (false) if the line segment ab is (is not) an edge of t
//It is assumed that va is a vertex of t
{
  Vertex_circulator vc = incident_vertices(va), done(vc);
  if ( vc == 0) return false;
  do {
    if( vb == vc ) {return true;} 
  } while (++vc != done);
  return false;
}
 

template <class Vb, class Fb>
bool
Triangulation_data_structure_2<Vb,Fb>::
is_edge(Vertex_handle va, Vertex_handle vb, 
	Face_handle &fr,  int & i) const
// assume va is a vertex of t
// returns true (false) if the line segment ab is (is not) an edge of t
// if true is returned (fr,i) is the edge ab
// with face fr on the right of a->b
{
  Face_handle fc = va->face(); 
  Face_handle start = fc;
  if (fc == 0) return false;
  int inda, indb;
  do {
    inda=fc->index(va);
    indb = (dimension() == 2 ? cw(inda) : 1-inda);
    if(fc->vertex(indb) == vb) {
      fr=fc;
      i = 3 - inda - indb; //works in dim 1 or 2
      return true;
    }
    fc=fc->neighbor(indb); //turns ccw around va
  } while (fc != start);
  return false;
}

template <class Vb, class Fb>
inline bool 
Triangulation_data_structure_2<Vb,Fb>::
is_face(Face_handle fh) const
{
  if (dimension() < 2)  return false;
  Face_iterator fit = faces_begin();
  while (fit != faces_end() && fh != fit ) ++fit;
  return fh == fit;
}

template <class Vb, class Fb>
inline bool 
Triangulation_data_structure_2<Vb,Fb>::
is_face(Vertex_handle v1, 
	Vertex_handle v2, 
	Vertex_handle v3) const
{
  Face_handle f;
  return is_face(v1,v2,v3,f);
}

template <class Vb, class Fb>
bool 
Triangulation_data_structure_2<Vb,Fb>::
is_face(Vertex_handle v1, 
	Vertex_handle v2, 
	Vertex_handle v3,
	Face_handle &f) const
{
  if (dimension() != 2) return false;
  int i;
  bool b = is_edge(v1,v2,f,i);
  if (!b) return false;
  else if (v3== f->vertex(i)) return true;
  f = f-> neighbor(i);
  int ind1= f->index(v1);
  int ind2= f->index(v2);
  if (v3 == f->vertex(3-ind1-ind2)) { return true;}
  return false;  
}

template <class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
flip(Face_handle f, int i)
{
  CGAL_triangulation_precondition( dimension()==2);
  Face_handle n  = f->neighbor(i);
  int ni = f->mirror_index(i); //ni = n->index(f);
    
  Vertex_handle  v_cw = f->vertex(cw(i));
  Vertex_handle  v_ccw = f->vertex(ccw(i));

  // bl == bottom left, tr == top right
  Face_handle tr = f->neighbor(ccw(i));
  int tri =  f->mirror_index(ccw(i));  
  Face_handle bl = n->neighbor(ccw(ni));
  int bli =  n->mirror_index(ccw(ni)); 
      
  f->set_vertex(cw(i), n->vertex(ni));
  n->set_vertex(cw(ni), f->vertex(i));
    
  // update the neighborhood relations
  f->set_neighbor(i, bl);
  bl->set_neighbor(bli, f);
    
  f->set_neighbor(ccw(i), n);
  n->set_neighbor(ccw(ni), f);
    
  n->set_neighbor(ni, tr);
  tr->set_neighbor(tri, n);
    
  if(v_cw->face() == f) {
    v_cw->set_face(n);
  }
    
  if(v_ccw->face() == n) {
    v_ccw->set_face(f);
  }
}
  
template < class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
insert_first( )
{
  CGAL_triangulation_precondition( number_of_vertices() == 0 &&
				   dimension()==-2 );
  return insert_dim_up();
}

template < class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle 
Triangulation_data_structure_2<Vb,Fb>::
insert_second()
{
  CGAL_triangulation_precondition( number_of_vertices() == 1 &&
				   dimension()==-1 );
  return insert_dim_up();

}


template <  class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
insert_in_face(Face_handle f)
  // New vertex will replace f->vertex(0) in face f
{
  CGAL_triangulation_precondition( f != Face_handle() && dimension()== 2);
  Vertex_handle  v = create_vertex();

  Vertex_handle v0 = f->vertex(0);
  Vertex_handle v2 = f->vertex(2);
  Vertex_handle v1 = f->vertex(1);
    
  Face_handle n1 = f->neighbor(1);
  Face_handle n2 = f->neighbor(2);
    
  Face_handle f1 = create_face(v0, v, v2, f, n1, Face_handle());
  Face_handle f2 = create_face(v0, v1, v, f, Face_handle(), n2);

  f1->set_neighbor(2, f2);
  f2->set_neighbor(1, f1);
  if (n1 != Face_handle()) {
    int i1 = f->mirror_index(1); //int i1 = n1->index(f);
    n1->set_neighbor(i1,f1);
  }
  if (n2 != Face_handle()) {
    int i2 = f->mirror_index(2);//int i2 = n2->index(f);
    n2->set_neighbor(i2,f2);}

  f->set_vertex(0, v);
  f->set_neighbor(1, f1);
  f->set_neighbor(2, f2);

  if( v0->face() == f  ) {  v0->set_face(f2); }
  v->set_face(f);

  return v;
}


template <  class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
insert_in_edge(Face_handle f, int i)
  //insert in the edge opposite to vertex i of face f
{
  CGAL_triangulation_precondition(f != Face_handle() && dimension() >= 1); 
  if (dimension() == 1) {CGAL_triangulation_precondition(i == 2);}
  if (dimension() == 2) {CGAL_triangulation_precondition(i == 0 || 
							 i == 1 || 
							 i == 2);}
  Vertex_handle v;
  if (dimension() == 1) {
    v = create_vertex();
    Face_handle ff = f->neighbor(0);
    Vertex_handle vv = f->vertex(1);
    Face_handle g = create_face(v,vv,Vertex_handle(),ff, f, Face_handle());
    f->set_vertex(1,v);f->set_neighbor(0,g);
    ff->set_neighbor(1,g);
    v->set_face(g);
    vv->set_face(ff);
  }

    else { //dimension() ==2
    Face_handle n = f->neighbor(i);
    int in = f->mirror_index(i); //n->index(f);
    v = insert_in_face(f);
    flip(n,in); 
    }

  return v;
}


template <  class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
insert_dim_up(Vertex_handle w,  bool orient)
{
  // the following function insert 
  // a vertex  v which is outside the affine  hull of Tds
  // The triangulation will be starred from  v and w 
  // ( geometrically w=  // the infinite vertex )
  // w=NULL for first and second insertions
  // orient governs the orientation of the resulting triangulation

  Vertex_handle v = create_vertex();
  set_dimension( dimension() + 1);
  Face_handle f1;
  Face_handle f2;
    
  switch (dimension()) { //it is the resulting dimension
  case -1:
    f1 = create_face(v,Vertex_handle(),Vertex_handle());
    v->set_face(f1);
    break;
  case 0 :
    f1 = face_iterator_base_begin();
    f2 = create_face(v,Vertex_handle(),Vertex_handle());
    f1->set_neighbor(0,f2);
    f2->set_neighbor(0,f1);
    v->set_face(f2);
    break;
  case 1 :
  case 2 :
    {
      std::list<Face_handle> faces_list;
      Face_iterator ib= face_iterator_base_begin(); 
      Face_iterator ib_end = face_iterator_base_end();
      for (; ib != ib_end ; ++ib){
	faces_list.push_back( ib);
      }
      
      std::list<Face_handle>  to_delete;
      typename std::list<Face_handle>::iterator lfit = faces_list.begin();
      int i = dimension(); // maximun non NULL index in faces 
      Face_handle f, g;

      for ( ; lfit != faces_list.end() ; ++lfit) {
	f = * lfit;
	g = create_face(f); //calls copy constructor of face
	f->set_vertex(i,v); f->set_neighbor(i,g);
	g->set_vertex(i,w); g->set_neighbor(i,f);
	if (f->has_vertex(w)) to_delete.push_back(g); // flat face to delete
      }

      lfit = faces_list.begin();
      for ( ; lfit != faces_list.end() ; ++lfit) {
	f = * lfit;
	g = f->neighbor(i);
	for(int j = 0; j < i ; ++j) {
	  g->set_neighbor(j, f->neighbor(j)->neighbor(i));
	}
      }

      // couldn't unify the code for reorientation mater
      lfit = faces_list.begin() ; 
      if (dimension() == 1){
	if (orient) {
	  (*lfit)->reorient(); ++lfit ;  (*lfit)->neighbor(1)->reorient();
	}
	else {
	  (*lfit)->neighbor(1)->reorient(); ++lfit ; (*lfit)->reorient(); 
	}
      }
      else { // dimension == 2
	for( ;lfit  != faces_list.end(); ++lfit ) {
	  if (orient) {(*lfit)->neighbor(2)->reorient();}
	  else { (*lfit)->reorient();}
	}
      }

      lfit = to_delete.begin();
      int i1, i2;
      for ( ;lfit  != to_delete.end(); ++lfit){
	f = *lfit ;
	int j ;
	if (f->vertex(0) == w) {j=0;}
	else {j=1;}
	f1= f->neighbor(i); i1= f->mirror_index(i); //f1->index(f);
	f2= f->neighbor(j); i2= f->mirror_index(j); //f2->index(f);
	f1->set_neighbor(i1,f2);
	f2->set_neighbor(i2,f1);
	delete_face(f);
      }
    
      v->set_face( *(faces_list.begin()));
    }
    break;
  default:
    CGAL_triangulation_assertion(false);
    break;  }
  return v;
}


template <class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
remove_degree_3(Vertex_handle v, Face_handle f)
// remove a vertex of degree 3
{
  CGAL_triangulation_precondition(v != Vertex_handle());
  CGAL_triangulation_precondition(v->degree() == 3);

  if (f == Face_handle()) {f= v->face();}
  else { CGAL_triangulation_assertion( f->has_vertex(v));}
      
  int i = f->index(v);
  Face_handle left = f->neighbor(cw(i));
  int li = f->mirror_index(cw(i)); 
  Face_handle right = f->neighbor(ccw(i));
  int ri = f->mirror_index(ccw(i)); 

  Face_handle ll, rr;
  Vertex_handle q = left->vertex(li);
  CGAL_triangulation_assertion( left->vertex(li) == right->vertex(ri));
    
  ll = left->neighbor(cw(li));
  if(ll != Face_handle()) {
    int lli = left->mirror_index(cw(li)); 
    ll->set_neighbor(lli, f);
  } 
  f->set_neighbor(cw(i), ll);
  if (f->vertex(ccw(i))->face() == left) f->vertex(ccw(i))->set_face(f);    
        
  rr = right->neighbor(ccw(ri));
  if(rr != Face_handle()) {
    int rri =  right->mirror_index(ccw(ri)); //rr->index(right);
    rr->set_neighbor(rri, f);
  } 
  f->set_neighbor(ccw(i), rr);
  if (f->vertex(cw(i))->face() == right) f->vertex(cw(i))->set_face(f);  
        
  f->set_vertex(i, q);
  if (q->face() == right || q->face() == left) {
    q->set_face(f);
  }
  delete_face(right);
  delete_face(left);
        
  delete_vertex(v);
} 


  
template <class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
remove_dim_down(Vertex_handle v)
{
  Face_handle f;
  switch( dimension()){
  case -1: 
    delete_face(v->face());
    break;
  case 0:
    f = v->face();
    f->neighbor(0)->set_neighbor(0,Face_handle());
    delete_face(v->face());
    break;
  case 1:
  case 2:
    CGAL_triangulation_precondition ( 
	     (dimension() == 1 &&  number_of_vertices() == 3) ||
	     (dimension() == 2 && number_of_vertices() > 3) );
    // the faces incident to v are down graded one dimension
    // the other faces are deleted
    std::list<Face_handle > to_delete;
    std::list<Face_handle > to_downgrade;
    Face_iterator ib = face_iterator_base_begin();
    for( ; ib != face_iterator_base_end(); ++ib ){
      if ( ! ib->has_vertex(v) ) { to_delete.push_back(ib);}
      else { to_downgrade.push_back(ib);}
    }

    typename std::list<Face_handle>::iterator lfit = to_downgrade.begin();
    int j;
    for( ; lfit !=  to_downgrade.end() ; ++lfit) {
      f = *lfit; j = f->index(v);
      if (dimension() == 1) {
	if (j == 0) 	f->reorient();
	f->set_vertex(1,Vertex_handle());
	f->set_neighbor(1, Face_handle());
      }
      else { //dimension() == 2
	if (j == 0) f->cw_permute();
	else if(j == 1) f->ccw_permute();
	f->set_vertex(2, Vertex_handle());
	f->set_neighbor(2, Face_handle());
      }
      f->vertex(0)->set_face(f);
    }

    lfit = to_delete.begin();
    for( ; lfit !=  to_delete.end() ; ++lfit) {
      delete_face(*lfit);
    }
  }  
  delete_vertex(v);
  set_dimension(dimension() -1);
  return;
}

template <  class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::  
remove_1D(Vertex_handle v)
{
  CGAL_triangulation_precondition( dimension() == 1 &&
				   number_of_vertices() > 3);
  Face_handle f = v->face();
  int i = f->index(v);
  if (i==0) {f = f->neighbor(1);}
  CGAL_triangulation_assertion( f->index(v) == 1);
  Face_handle g= f->neighbor(0);
  f->set_vertex(1, g->vertex(1));
  f->set_neighbor(0,g->neighbor(0));
  g->neighbor(0)->set_neighbor(1,f);
  g->vertex(1)->set_face(f);
  delete_face(g);
  delete_vertex(v);
  return;
}



template <class Vb, class Fb>
inline void
Triangulation_data_structure_2<Vb,Fb>::
remove_second(Vertex_handle v)
{
  CGAL_triangulation_precondition(number_of_vertices()== 2 &&
 				  dimension() == 0);
  remove_dim_down(v);
  return;
}

    
template <class Vb, class Fb>
inline void
Triangulation_data_structure_2<Vb,Fb>::
remove_first(Vertex_handle v)
{
  CGAL_triangulation_precondition(number_of_vertices()== 1 && 
 				  dimension() == -1);
  remove_dim_down(v);
  return; 
}

template <class Vb, class Fb>
inline
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
star_hole(List_edges& hole)
{
  Vertex_handle newv = create_vertex();
  star_hole(newv, hole);
  return newv;
}

template <class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
star_hole(Vertex_handle newv, List_edges& hole)
  // star the hole represented by hole around newv
  // the triangulation is assumed to have dim=2
  // hole is supposed to be ccw oriented
{
   
  star_hole(newv, hole.begin(), hole.end());
  return;	    
}

template <class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
make_hole(Vertex_handle v, List_edges& hole)
  // delete the faces incident to v and v
  // and return the dscription of the hole in hole
{
 CGAL_triangulation_precondition(dimension() == 2);
 std::list<Face_handle> to_delete;  

 Face_handle  f, fn;
 int i =0, in =0;
 Vertex_handle  vv;

 Face_circulator fc = incident_faces(v);
 Face_circulator done(fc);
 do {
   f = fc ;
   i = f->index(v);
   fn = f->neighbor(i);
   in = f->mirror_index(i); //fn->index(f);
   vv = f->vertex(cw(i));
   if( vv->face()==  f) vv->set_face(fn);
   vv = fc->vertex(ccw(i));
   if( vv->face()== f) vv->set_face(fn);
   fn->set_neighbor(in, Face_handle());
   hole.push_back(Edge(fn,in));
   to_delete.push_back(f);
 }
  while(++fc != done);

  while (! to_delete.empty()){
    delete_face(to_delete.front());
    to_delete.pop_front();
  }
  delete_vertex(v);
  return;
}


template <class Vb, class Fb>
inline
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
create_vertex(const Vertex &v)
{
  return vertex_container().insert(v);
}

template <class Vb, class Fb>
inline
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
create_vertex(Vertex_handle vh)
{
  return vertex_container().insert(*vh);
}

template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Face_handle
Triangulation_data_structure_2<Vb,Fb>::
create_face(const Face& f)
{
  return face_container().insert(f);
}

template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Face_handle
Triangulation_data_structure_2<Vb,Fb>::
create_face( Face_handle fh)
{
  return create_face(*fh);
}


template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Face_handle
Triangulation_data_structure_2<Vb,Fb>::
create_face(Face_handle f1, int i1, 
	    Face_handle f2, int i2, 
	    Face_handle f3, int i3)
{
  Face_handle newf = face_container().construct_insert(f1->vertex(cw(i1)),
						       f2->vertex(cw(i2)),
						       f3->vertex(cw(i3)),
						       f2, f3, f1);
  f1->set_neighbor(i1,newf);
  f2->set_neighbor(i2,newf);
  f3->set_neighbor(i3,newf);
  return newf;
}

template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Face_handle
Triangulation_data_structure_2<Vb,Fb>::
create_face(Face_handle f1, int i1, Face_handle f2, int i2)
{
  Face_handle newf = face_container().construct_insert(f1->vertex(cw(i1)),
						       f2->vertex(cw(i2)),
						       f2->vertex(ccw(i2)),
						       f2, Face_handle(), f1);
  f1->set_neighbor(i1,newf);
  f2->set_neighbor(i2,newf);
  return newf;
}

template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Face_handle
Triangulation_data_structure_2<Vb,Fb>::
create_face(Face_handle f1, int i1, Vertex_handle v)
{
  Face_handle newf = create_face();
  newf->set_vertices(f1->vertex(cw(i1)), f1->vertex(ccw(i1)), v);
  newf->set_neighbors(Face_handle(), Face_handle(), f1);
  f1->set_neighbor(i1,newf);
  return newf;
}


template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Face_handle
Triangulation_data_structure_2<Vb,Fb>::
create_face(Vertex_handle v1, Vertex_handle v2, Vertex_handle v3)
{
  Face_handle newf = face_container().construct_insert(v1, v2, v3);
  return newf;
}

template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Face_handle
Triangulation_data_structure_2<Vb,Fb>::
create_face(Vertex_handle v1, Vertex_handle v2, Vertex_handle v3,
	    Face_handle f1, Face_handle f2, Face_handle f3)
{
  Face_handle newf = face_container().construct_insert(v1, v2, v3, f1, f2, f3);

  return(newf);
}

template <class Vb, class Fb>
inline void
Triangulation_data_structure_2<Vb,Fb>::
set_adjacency(Face_handle f0, int i0, Face_handle f1, int i1) const
{
  CGAL_triangulation_assertion(i0 >= 0 && i0 <= dimension());
  CGAL_triangulation_assertion(i1 >= 0 && i1 <= dimension());
  CGAL_triangulation_assertion(f0 != f1);
  f0->set_neighbor(i0,f1);
  f1->set_neighbor(i1,f0);
}

template <class Vb, class Fb>
inline void
Triangulation_data_structure_2<Vb,Fb>::
delete_face(Face_handle f)
{
  CGAL_triangulation_expensive_precondition( dimension() != 2 || is_face(f));
  CGAL_triangulation_expensive_precondition( dimension() != 1 || is_edge(f,2));
  CGAL_triangulation_expensive_precondition( dimension() != 0 ||
					     is_vertex(f->vertex(0)) );
#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE
  face_container().erase(f);
#else
  face_container().erase(f.base());
#endif
}



template <class Vb, class Fb>
inline void
Triangulation_data_structure_2<Vb,Fb>::
delete_vertex(Vertex_handle v)
{
  CGAL_triangulation_expensive_precondition( is_vertex(v) );
#ifdef CGAL_T2_USE_ITERATOR_AS_HANDLE
  vertex_container().erase(v);
#else
  vertex_container().erase(v.base());
#endif
}

// split and join operations

template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Fourtuple
Triangulation_data_structure_2<Vb,Fb>::
split_vertex(Vertex_handle v, Face_handle f1, Face_handle g1)
{
  /*
  // The following method preforms a split operation of the vertex v
  // using the faces f1 and g1. The split operation is shown
  // below.
  // The names of the variables in the method correspond to the
  // quantities in the drawings below
  //
  // The configuration before the split:
  //
  //                  cw(i1)   v3   ccw(i2)
  //                     *-----*-----*
  //                    / \    |    / \
  //                   /   \ f1|f2 /   \
  //                  /     \  |  /     \
  //                 /       \ | /       \
  //                /         \|/v        \
  //               *-----------*-----------*
  //                \         /|\         /
  //                 \       / | \       /
  //                  \     /  |  \     /
  //                   \   / g2|g1 \   /
  //                    \ /    |    \ /
  //                     *-----*-----*
  //                 ccw(j2)   v4   cw(j1)
  //
  //
  // The configuration after the split:
  //
  //
  //               cw(i1)      v3     ccw(i2)
  //                 *---------*---------*
  //                / \       / \       / \
  //               /   \  f1 /   \  f2 /   \
  //              /     \   /  f  \   /     \
  //             /       \ /     v2\ /       \
  //            *---------*---------*---------*
  //             \       / \v1     / \       /
  //              \     /   \  g  /   \     /
  //               \   /  g2 \   /  g1 \   /
  //                \ /       \ /       \ /
  //                 *---------*---------*
  //              ccw(j2)      v4      cw(j1)
  //
  */

  CGAL_triangulation_expensive_precondition( is_valid() );

  CGAL_triangulation_precondition( dimension() == 2 );
  CGAL_triangulation_precondition( f1 != Face_handle() && f1->has_vertex(v) );
  CGAL_triangulation_precondition( g1 != Face_handle() && g1->has_vertex(v) );

  // 1. first we read some information that we will need
  int i1 = f1->index(v);
  int j1 = g1->index(v);
  Face_handle f2 = f1->neighbor( cw(i1) );
  Face_handle g2 = g1->neighbor( cw(j1) );

  int i2 = f2->index(v);
  int j2 = g2->index(v);

  Vertex_handle v3 = f1->vertex( ccw(i1) );
  Vertex_handle v4 = g1->vertex( ccw(j1) );

  // lst is the list of faces adjecent to v stored in
  // counterclockwise order from g2 to f1) inclusive.
  // the list idx contains the indices of v in the
  // faces in lst.
  std::list<Face_handle> lst;
  std::list<int>         idx;

  Face_circulator fc(v, g1);
  Face_handle ff(fc);
  while ( ff != f2 ) {
    lst.push_back( ff );
    idx.push_back( ff->index(v) );
    fc++;
    ff = Face_handle(fc);
  }
  lst.push_back( ff );
  idx.push_back( ff->index(v) );

  // 2. we create the new vertices and the two new faces
  Vertex_handle v1 = v;
  Vertex_handle v2 = create_vertex();
  Face_handle f = create_face(v1, v2, v3);
  Face_handle g = create_face(v2, v1, v4);

  // 3. we update the adjacency information for the new vertices and
  //    the new faces
  f->set_neighbor(0, f2);
  f->set_neighbor(1, f1);
  f->set_neighbor(2, g);
  g->set_neighbor(0, g2);
  g->set_neighbor(1, g1);
  g->set_neighbor(2, g);
  v1->set_face(f);
  v2->set_face(g);

  // 4. update the vertex for the faces f2 through g1 in
  //    counterclockwise order
  typename std::list<Face_handle>::iterator fit = lst.begin();
  typename std::list<int>::iterator         iit = idx.begin();
  for (; fit != lst.end(); ++fit, ++iit) {
    (*fit)->set_vertex(*iit, v2);
  }

  lst.clear();
  idx.clear();

  // 5. make f and g the new neighbors of f1, f2 and g1, g2
  //    respectively.
  f1->set_neighbor(  cw(i1), f );
  f2->set_neighbor( ccw(i2), f );
  g1->set_neighbor(  cw(j1), g );
  g2->set_neighbor( ccw(j2), g );

  CGAL_triangulation_expensive_postcondition( is_valid() );

  // 6. return the new stuff
  return Fourtuple(v1, v2, f, g);
}

template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
join_vertices(Face_handle f, int i, Vertex_handle v)
{
  CGAL_triangulation_expensive_precondition( is_valid() );
  CGAL_triangulation_precondition( f != Face_handle() );
  CGAL_triangulation_precondition( i >= 0 && i <= 2 );

  // this methods does the "join"-operation and preserves
  // the vertex v among the two vertices that define the edge (f, i) 

  Vertex_handle v1 = f->vertex( ccw(i) );
  Vertex_handle v2 = f->vertex( cw(i)  );

  CGAL_triangulation_precondition( v == v1 || v == v2 );

  if ( v == v2 ) {
    return join_vertices(f->neighbor(i), f->mirror_index(i), v);
  }

  int deg2 = v2->degree();

  CGAL_triangulation_precondition( deg2 >= 3 );

  if ( deg2 == 3 ) {
    remove_degree_3(v2, f);
    return v1;
  }
  
  if ( deg2 == 2 ) {
    remove_degree_2(v2);
    return v1;
  }

  /*
  // The following drawing corrsponds to the variables
  // used in this part...
  // The vertex v1 is returned...
  //
  //      itl       i=v3      itr
  //       *---------*---------*
  //        \       / \       /
  //         \  tl /   \  tr /
  //          \   /  f  \   /
  //           \ /       \ /
  //  v1=ccw(i) *---------*  cw(i)=v2
  //           / \       / \
  //          /   \  g  /   \
  //         /  bl \   /  br \
  //        /       \ /	      \
  //       *---------*---------*
  //      ibl       j=v4      ibr
  //                                                           
  // The situation after the "join"-operation is as follows:
  //
  //                 i
  //           *-----*-----*
  //            \    |    /
  //             \ tl|tr /
  //              \  |  /
  //               \ | /
  //                \|/
  //                 *  v1
  //                /|\
  //               / | \
  //              /  |	\
  //             / bl|br \
  //            /    |	  \
  //           *-----*-----*
  //
  */

  // first we register all the needed info
  Face_handle g = f->neighbor(i);
  int j = f->mirror_index(i);

  Face_handle tl = f->neighbor( cw(i)  );
  Face_handle tr = f->neighbor( ccw(i) );

  int itl = f->mirror_index( cw(i)  );
  int itr = f->mirror_index( ccw(i) );

  Face_handle bl = g->neighbor( ccw(j) );
  Face_handle br = g->neighbor( cw(j)  );

  int ibl = g->mirror_index( ccw(j) );
  int ibr = g->mirror_index( cw(j)  );

  // we need to store the faces adjacent to v2 as well as the
  // indices of v2 w.r.t. these faces, so that afterwards we can set 
  // v1 to be the vertex for these faces
  std::vector<Face_handle> star_faces_of_v2;
  std::vector<int> star_indices_of_v2;
  Face_circulator fc_start(v2);
  Face_circulator fc = fc_start;

  do {
    Face_handle ff(fc);
    star_faces_of_v2.push_back(ff);
    star_indices_of_v2.push_back(ff->index(v2));
    ++fc;
  } while ( fc != fc_start );

  CGAL_triangulation_assertion( int(star_faces_of_v2.size()) == deg2 );

  // from this point and on we modify the values

  // first set the neighbors
  tl->set_neighbor(itl, tr);
  tr->set_neighbor(itr, tl);

  bl->set_neighbor(ibl, br);
  br->set_neighbor(ibr, bl);

  // make sure that all the faces containing v2 as a vertex, now
  // contain v1
  for (unsigned int k = 0; k < star_faces_of_v2.size(); k++) {
    int id = star_indices_of_v2[k];
    CGAL_triangulation_assertion( star_faces_of_v2[k]->vertex(id) == v2 );
    star_faces_of_v2[k]->set_vertex( id, v1 );
  }

  // then make sure that all the vertices have correct pointers to 
  // faces
  Vertex_handle v3 = f->vertex(i);
  Vertex_handle v4 = g->vertex(j);
  if ( v3->face() == f )  v3->set_face(tr);
  if ( v4->face() == g )  v4->set_face(br);
  if ( v1->face() == f || v1->face() == g ) v1->set_face(tl);


#ifndef CGAL_NO_ASSERTIONS
  for (Face_iterator fit = faces_begin(); fit != faces_end(); ++fit) {
    int id;
    CGAL_triangulation_assertion( !fit->has_vertex(v2, id) );
  }
#endif

  // memory management
  star_faces_of_v2.clear();
  star_indices_of_v2.clear();

  delete_face(f);
  delete_face(g);

  delete_vertex(v2);

  CGAL_triangulation_expensive_postcondition( is_valid() );

  return v1;
}

// insert_degree_2 and remove_degree_2 operations
template <class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
insert_degree_2(Face_handle f, int i)
{
  /*
  // This method basically does the following transformation
  // The remove_degree_2 method performs the same operation in the
  // opposite direction
  //
  //
  //                                                *
  //                 i                             / \
  //                 *                            /   \
  //                / \                          /  f  \
  //               /   \                        / _____	\
  //              /  f  \                      / /  f1 \ \
  //             /       \                     |/   v   \|
  //  v0=ccw(i) *---------* v1=cw(i)  ===>  v0 *----*----* v1
  //             \       /                     |\   f2  /|
  //              \  g  /                      \ \_____/ /
  //               \   /                        \       /
  //                \ /                          \  g  /
  //                 *                            \   /
  //                 j                             \ /
  //                                                *
  //
  */

  Face_handle g = f->neighbor(i);
  int j = f->mirror_index(i);

  Vertex_handle  v = create_vertex();

  Vertex_handle v0 = f->vertex( ccw(i) );
  Vertex_handle v1 = f->vertex( cw(i)  );

  Face_handle f_undef;

  Face_handle f1 = create_face(v0, v, v1, f_undef, f, f_undef);
  Face_handle f2 = create_face(v0, v1, v, f_undef, f_undef, g);

  f1->set_neighbor(0, f2);
  f1->set_neighbor(2, f2);

  f2->set_neighbor(0, f1);
  f2->set_neighbor(1, f1);

  f->set_neighbor(i, f1);
  g->set_neighbor(j, f2);

  v->set_face(f1);

  return v;
}

template <class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
remove_degree_2(Vertex_handle v)
{
  CGAL_precondition( v->degree() == 2 );

  Face_handle f1 = v->face();
  int i = f1->index(v);

  Face_handle f2 = f1->neighbor( ccw(i) );
  int j = f2->index(v);

  Face_handle ff1 = f1->neighbor( i );
  Face_handle ff2 = f2->neighbor( j );

  int id1 = f1->mirror_index(i);
  int id2 = f2->mirror_index(j);

  ff1->set_neighbor(id1, ff2);
  ff2->set_neighbor(id2, ff1);

  Vertex_handle v1 = f1->vertex( ccw(i) );
  //    if ( v1->face() == f1 || v1->face() == f2 ) {
  v1->set_face(ff1);
  //    }

  Vertex_handle v2 = f1->vertex( cw(i) );
  //    if ( v2->face() == f1 || v2->face() == f2 ) {
  v2->set_face(ff2);
  //    }

  delete_face(f1);
  delete_face(f2);

  delete_vertex(v);
}

// CHECKING
template <  class Vb, class Fb>
bool
Triangulation_data_structure_2<Vb,Fb>::
is_valid(bool verbose, int level) const
{
  if(number_of_vertices() == 0){ 
    return (dimension() == -2);
  }

      
  bool result = (dimension()>= -1);
  CGAL_triangulation_assertion(result);

  //count and test the validity of the faces (for positive dimensions)
  Face_iterator ib = face_iterator_base_begin(); 
  Face_iterator ib_end = face_iterator_base_end();
  size_type count_stored_faces =0;
  for ( ; ib != ib_end ; ++ib){
    count_stored_faces += 1;
    if (dimension()>= 0) {
      result = result && ib->is_valid(verbose,level);
      CGAL_triangulation_assertion(result);
    }
  }
  
  result = result && (count_stored_faces == number_of_full_dim_faces());
  CGAL_triangulation_assertion(
		 count_stored_faces == number_of_full_dim_faces());
 
  // vertex count
  size_type vertex_count = 0;
  for(Vertex_iterator vit = vertices_begin(); vit != vertices_end();
      ++vit) {
    CGAL_triangulation_assertion( vit->face() != Face_handle());
    result = result && vit->is_valid(verbose,level);
    CGAL_triangulation_assertion( result );
    ++vertex_count;
  }
  result = result && (number_of_vertices() == vertex_count);
  CGAL_triangulation_assertion( number_of_vertices() == vertex_count );
    
  //edge count
  size_type edge_count = 0;
  for(Edge_iterator eit = edges_begin(); eit != edges_end(); ++eit) { 
    ++edge_count;
  }

  // face count
  size_type face_count = 0;
  for(Face_iterator fit = faces_begin(); fit != faces_end(); ++fit) {
    ++face_count;
  }
        
  switch(dimension()) {
  case -1: 
    result = result && vertex_count == 1 && face_count == 0
      && edge_count == 0;
    CGAL_triangulation_assertion(result);
    break;
  case 0:
    result = result && vertex_count == 2 && face_count == 0
      && edge_count == 0;
    CGAL_triangulation_assertion(result);
    break;
  case 1:
    result = result &&  edge_count == vertex_count;
    CGAL_triangulation_assertion(result);
    result = result &&  face_count == 0;
    CGAL_triangulation_assertion(result);
    break;
  case 2:
    result = result &&  edge_count == 3*face_count/2 ;
    CGAL_triangulation_assertion(edge_count == 3*face_count/2);
    break;
  default:
    result = false;
    CGAL_triangulation_assertion(result);
  }
  return result;
}

template <  class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
copy_tds(const Tds &tds, Vertex_handle vh)
  // return the vertex corresponding to vh in the new tds
{
  if (this == &tds) return Vertex_handle();
  if (vh != Vertex_handle()) 
    CGAL_triangulation_precondition( tds.is_vertex(vh));

  clear();
  size_type n = tds.number_of_vertices();
  set_dimension(tds.dimension());

  // Number of pointers to cell/vertex to copy per cell.
  int dim = std::max(1, dimension() + 1);
 
  if(n == 0) {return Vertex_handle();}
  
  //initializes maps
  std::map<Vertex_handle,Vertex_handle> vmap;
  std::map<Face_handle,Face_handle> fmap;

  // create vertices
  Vertex_iterator vit1 = tds.vertices_begin();
  for( ; vit1 != tds.vertices_end(); ++vit1) {
    vmap[vit1] = create_vertex(vit1);
  }

  //create faces 
  Face_iterator fit1 = tds.face_container().begin();
  for( ; fit1 != tds.faces_end(); ++fit1) {
    fmap[fit1] = create_face(fit1);
  }

  //link vertices to a cell 
  vit1 = tds.vertices_begin();
  for ( ; vit1 != tds.vertices_end(); vit1++) {
    vmap[vit1]->set_face(fmap[vit1->face()]);
  }

  //update vertices and neighbor pointers
  fit1 = tds.face_container().begin();
  for ( ; fit1 != tds.faces_end(); ++fit1) {
      for (int j = 0; j < dim ; ++j) {
	fmap[fit1]->set_vertex(j, vmap[fit1->vertex(j)] );
	fmap[fit1]->set_neighbor(j, fmap[fit1->neighbor(j)]);
      }
    }
   
  // remove the post condition because it is false when copying the
  // TDS of a regular triangulation because of hidden vertices
  // CGAL_triangulation_postcondition( is_valid() );
  return (vh == Vertex_handle())  ? Vertex_handle() : vmap[vh];
}
 

template < class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
file_output( std::ostream& os, Vertex_handle v, bool skip_first) const
{
  // ouput to a file
  // if non NULL, v is the vertex to be output first
  // if skip_first is true, the point in the first vertex is not output
  // (it may be for instance the infinite vertex of the triangulation)
  
  size_type n = number_of_vertices();
  size_type m = number_of_full_dim_faces();
  if(is_ascii(os))  os << n << ' ' << m << ' ' << dimension() << std::endl;
  else     os << n << m << dimension();
  if (n==0) return;

  std::map<Vertex_handle,int> V;
  std::map<Face_handle,int> F;

  // first vertex 
  int inum = 0;
  if ( v != Vertex_handle()) {
    V[v] = inum++;
    if( ! skip_first){
      // os << v->point();
      os << *v ;
    if(is_ascii(os))  os << std::endl;
    }
  }
  
  // other vertices
  for( Vertex_iterator vit= vertices_begin(); vit != vertices_end() ; ++vit) {
    if ( v != vit ) {
	V[vit] = inum++;
	// os << vit->point();
	os << *vit;
	if(is_ascii(os)) os << "\n";
    }
  }
  if(is_ascii(os)) os << "\n";

  // vertices of the faces
  inum = 0;
  int dim = (dimension() == -1 ? 1 :  dimension() + 1);
  for( Face_iterator ib = face_iterator_base_begin();
       ib != face_iterator_base_end(); ++ib) {
    F[ib] = inum++;
    for(int j = 0; j < dim ; ++j) {
      os << V[ib->vertex(j)];
      if(is_ascii(os)) os << " ";
    }
    os << *ib ;
    if(is_ascii(os)) os << "\n";
  }
  if(is_ascii(os)) os << "\n";
    
  // neighbor pointers of the  faces
  for( Face_iterator it = face_iterator_base_begin();
       it != face_iterator_base_end(); ++it) {
    for(int j = 0; j < dimension()+1; ++j){
      os << F[it->neighbor(j)];
      if(is_ascii(os))  os << " ";
    }
    if(is_ascii(os)) os << "\n";
  }

  return ;
}


template < class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
file_input( std::istream& is, bool skip_first)
{
  //input from file
  //return a pointer to the first input vertex
  // if skip_first is true, a first vertex is added (infinite_vertex)
  //set this  first vertex as infinite_Vertex
  if(number_of_vertices() != 0)    clear();
  
  size_type n, m;
  int d;
  is >> n >> m >> d;

  if (n==0){ return Vertex_handle();}

  set_dimension(d);

  std::vector<Vertex_handle > V(n);
  std::vector<Face_handle> F(m);

  // read vertices
  size_type i = 0;
  if(skip_first){
    V[0] = create_vertex();
    ++i;
  }
  for( ; i < n; ++i) {
    V[i] = create_vertex();
    is >> *(V[i]);
  }
  
  // Creation of the faces
  int index;
  int dim = (dimension() == -1 ? 1 :  dimension() + 1);
  {
    for(i = 0; i < m; ++i) {
      F[i] = create_face() ;
      for(int j = 0; j < dim ; ++j){
	is >> index;
	F[i]->set_vertex(j, V[index]);
	// The face pointer of vertices is set too often,
	// but otherwise we had to use a further map
	V[index]->set_face(F[i]);
      }
      // read in non combinatorial info of the face
      is >> *(F[i]) ;
    }
  }

  // Setting the neighbor pointers 
  {
    for(i = 0; i < m; ++i) {
      for(int j = 0; j < dimension()+1; ++j){
	is >> index;
	F[i]->set_neighbor(j, F[index]);
      }
    }
  }
  
  return V[0];
}


template < class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
vrml_output( std::ostream& os, Vertex_handle v, bool skip_infinite) const
{
  // ouput to a vrml file style
  // Point are assumed to be 3d points with a stream oprator <<
  // if non NULL, v is the vertex to be output first
  // if skip_inf is true, the point in the first vertex is not output
  // and the faces incident to v are not output
  // (it may be for instance the infinite vertex of the terrain)
  os << "#VRML V2.0 utf8" << std::endl;
  os << "Shape {" << std::endl;
  os << "\tgeometry IndexedFaceSet {" << std::endl;
  os << "\t\tcoord Coordinate {" << std::endl;
  os << "\t\t\tpoint [" << std::endl;

  std::map<Vertex_handle,int> vmap;
  Vertex_iterator vit;
  Face_iterator fit;

  //first vertex
  int inum = 0;
  if ( v != Vertex_handle()) {
    vmap[v] = inum++;
    if( ! skip_infinite)  os << "\t\t\t\t" << *v << std::endl;
  }

  //other vertices
  for( vit= vertices_begin(); vit != vertices_end() ; ++vit) {
    if ( v != vit) {
      vmap[vit] = inum++;
      os << "\t\t\t\t" << *vit << std::endl;
    }
  }

   os << "\t\t\t]" << std::endl;
   os << "\t\t}" << std::endl;
   os << "\t\tcoordIndex [" << std::endl;

   // faces
   for(fit= faces_begin(); fit != faces_end(); ++fit) {
     if (!skip_infinite || !fit->has_vertex(v)) {
   	os << "\t\t\t";
	os << vmap[(*fit).vertex(0)] << ", ";
	os << vmap[(*fit).vertex(1)] << ", ";
	os << vmap[(*fit).vertex(2)] << ", ";
	os << "-1, " << std::endl;  
     }
   }
   os << "\t\t]" << std::endl;
   os << "\t}" << std::endl;
   os << "}" << std::endl;
   return;
}

template < class Vb, class Fb>
typename Triangulation_data_structure_2<Vb,Fb>::Vertex_handle
Triangulation_data_structure_2<Vb,Fb>::
off_file_input( std::istream& is, bool verbose)
{
  // input from an OFF file
  // assume a dimension 2 triangulation
  // create an infinite-vertex and  infinite faces with the
  // boundary edges if any.
  // return the infinite vertex if created
  Vertex_handle vinf;
  File_scanner_OFF scanner(is, verbose);
  if (! is) {
    if (scanner.verbose()) {
         std::cerr << " " << std::endl;
	 std::cerr << "TDS::off_file_input" << std::endl;
	 std::cerr << " input error: file format is not OFF." << std::endl;
    }
    return vinf;
  }

  if(number_of_vertices() != 0)    clear();
  int dim = 2;
  set_dimension(dim);

  std::vector<Vertex_handle > vvh(scanner.size_of_vertices());
  std::map<Vh_pair, Edge> edge_map;
  typedef typename Vb::Point   Point;

  // read vertices
  int i;
  for ( i = 0; i < scanner.size_of_vertices(); i++) {
    Point p;
    file_scan_vertex( scanner, p);
    vvh[i] = create_vertex();
    vvh[i]->set_point(p);
    scanner.skip_to_next_vertex( i);
  }
  if ( ! is ) {
    is.clear( std::ios::badbit);
    return vinf;
  }
  //vinf = vvh[0];

  // create the facets
  for ( i = 0; i < scanner.size_of_facets(); i++) {
    Face_handle fh = create_face();
    Integer32 no;
    scanner.scan_facet( no, i);
    if( ! is || no != 3) {
      if ( scanner.verbose()) {
	std::cerr << " " << std::endl;
	std::cerr << "TDS::off_file_input" << std::endl;
	std::cerr << "facet " << i << "does not have  3 vertices." 
		  << std::endl;
      }
      is.clear( std::ios::badbit);
      return vinf;
    }

    for ( int j = 0; j < no; ++j) {
      Integer32 index;
      scanner.scan_facet_vertex_index( index, i);
      fh->set_vertex(j, vvh[index]);
      vvh[index]->set_face(fh);
    }

    for (int ih  = 0; ih < no; ++ih) {
	set_adjacency(fh, ih, edge_map);
    }
  }

  // deal with  boundaries
  if ( !edge_map.empty()) {
    vinf = create_vertex();
    std::map<Vh_pair, Edge> inf_edge_map;
   while (!edge_map.empty()) {
     Face_handle fh = edge_map.begin()->second.first;
     int ih = edge_map.begin()->second.second;
     Face_handle fn = create_face( vinf, 
				   fh->vertex(cw(ih)), 
				   fh->vertex(ccw(ih)));
     vinf->set_face(fn);
     set_adjacency(fn, 0, fh, ih);
     set_adjacency(fn, 1, inf_edge_map);
     set_adjacency(fn, 2, inf_edge_map);
     edge_map.erase(edge_map.begin());
   }
   CGAL_triangulation_assertion(inf_edge_map.empty());
  }
  
  
  // coherent orientation
  reorient_faces();
  return vinf;
}


template < class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
set_adjacency(Face_handle fh, 
	      int ih, 
	      std::map< Vh_pair, Edge>& edge_map)
{
  // set adjacency to (fh,ih) using the the map edge_map
  // or insert (fh,ih) in edge map
  Vertex_handle vhcw  =  fh->vertex(cw(ih));
  Vertex_handle vhccw =  fh->vertex(ccw(ih)); 
  Vh_pair  vhp =  vhcw < vhccw ?  
                  std::make_pair(vhcw, vhccw) 
                : std::make_pair(vhccw, vhcw) ;
  typename std::map<Vh_pair, Edge>::iterator emapit = edge_map.find(vhp);
  if (emapit == edge_map.end()) {// not found, insert edge
    edge_map.insert(std::make_pair(vhp, Edge(fh,ih)));
  }
  else { //found set adjacency and erase
    Edge e = emapit->second;
    set_adjacency( fh,ih, e.first, e.second);
    edge_map.erase(emapit);
  } 
}



template < class Vb, class Fb>
void
Triangulation_data_structure_2<Vb,Fb>::
reorient_faces()
{
  // reorient the faces of a triangulation 
  // needed for example in off_file_input
  // because the genus is not known, the number of faces 
  std::set<Face_handle> oriented_set;
  std::stack<Face_handle>  st;
  Face_iterator fit = faces_begin();
  int nf  = std::distance(faces_begin(),faces_end());

  while (static_cast<int>(oriented_set.size()) != nf) {
    while ( oriented_set.find(fit->handle()) != oriented_set.end()){
      ++fit; // find a germ for  non oriented components 
    }
    // orient component
    oriented_set.insert(fit->handle());
    st.push(fit->handle());
    while ( ! st.empty()) {
      Face_handle fh = st.top();
      st.pop();
      for(int ih = 0 ; ih < 3 ; ++ih){
	Face_handle fn = fh->neighbor(ih);
	if (oriented_set.find(fn) == oriented_set.end()){
	  int in = fn->index(fh);
	  if (fn->vertex(cw(in)) != fh->vertex(ccw(ih))) fn->reorient();
	  oriented_set.insert(fn);
	  st.push(fn);
	}
      }
    }

  }
  return;
}
	  

template <  class Vb, class Fb>
std::istream&
operator>>(std::istream& is,  
	   Triangulation_data_structure_2<Vb,Fb>& tds) 
{
  tds.file_input(is);
  return is;
}


template <  class Vb, class Fb>
std::ostream&
operator<<(std::ostream& os, 
	   const Triangulation_data_structure_2<Vb,Fb>  &tds) 
{
   tds.file_output(os);
   return os;
}


CGAL_END_NAMESPACE 

#endif //CGAL_TRIANGULATION_DATA_STRUCTURE_2_H