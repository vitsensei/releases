// Copyright (c) 2001, 2002, 2003, 2004  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Alpha_shapes_3/demo/Alpha_shapes_3/weighted_alpha_shapes_3.cpp $
// $Id: weighted_alpha_shapes_3.cpp 37003 2007-03-10 16:55:12Z spion $
//
//
// Author(s)     : Tran Kai Frank DA <Frank.Da@sophia.inria.fr>

/***********************************************************************

Takes a list of points and returns a list of segments corresponding
to the Alpha Shape.

************************************************************************/

#include <CGAL/Cartesian.h>

#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include <CGAL/Alpha_shape_vertex_base_3.h>
#include <CGAL/Alpha_shape_cell_base_3.h>
#include <CGAL/Triangulation_data_structure_3.h>
#include <CGAL/Weighted_alpha_shape_euclidean_traits_3.h>
#include <CGAL/Regular_triangulation_3.h>
#include <CGAL/Alpha_shape_3.h>

#ifdef CGAL_USE_GEOMVIEW
#include <CGAL/IO/Geomview_stream.h>
#endif



typedef double coord_type;


typedef CGAL::Cartesian<coord_type>  K;

typedef K::Point_3    Point;
typedef K::Segment_3  Segment;
typedef K::Ray_3      Ray;
typedef K::Line_3     Line;
typedef K::Triangle_3 Triangle;

typedef CGAL::Weighted_alpha_shape_euclidean_traits_3<K> Gt;
typedef Gt::Point Wpoint;

typedef CGAL::Alpha_shape_vertex_base_3<Gt> Vb;
typedef CGAL::Alpha_shape_cell_base_3<Gt>   Fb;

typedef CGAL::Triangulation_data_structure_3<Vb,Fb> Tds;
typedef CGAL::Regular_triangulation_3<Gt,Tds> Triangulation_3;

typedef CGAL::Alpha_shape_3<Triangulation_3>  Alpha_shape_3;

typedef Alpha_shape_3::Cell  Cell;
typedef Alpha_shape_3::Vertex Vertex;
typedef Alpha_shape_3::Edge Edge;
typedef Alpha_shape_3::Cell_handle  Cell_handle;
typedef Alpha_shape_3::Vertex_handle Vertex_handle;

typedef Alpha_shape_3::Cell_circulator  Cell_circulator;

typedef Alpha_shape_3::Locate_type Locate_type;

typedef Alpha_shape_3::Cell_iterator  Cell_iterator;
typedef Alpha_shape_3::Vertex_iterator  Vertex_iterator;
typedef Alpha_shape_3::Edge_iterator  Edge_iterator;


typedef Alpha_shape_3::Coord_type Coord_type;
typedef Alpha_shape_3::Alpha_iterator Alpha_iterator;

//---------------------------------------------------------------------

void
construct_alpha_shape(const std::list<Wpoint> &V_p,
		      Alpha_shape_3::Mode mode,
		      Alpha_shape_3& A)
  // Generate Alpha Shape
{
  std::vector<Gt::Segment_3> V_seg;

  int  n = A.make_alpha_shape(V_p.begin(), V_p.end());
  std::cout << "Inserted " << n  << " points" << std::endl;

  A.set_mode(mode);
}

bool
file_input(std::list<Wpoint>& L, const coord_type& weight)
{

  std::ifstream is("./finput", std::ios::in);

  if(is.fail())
    {
      std::cerr << "unable to open file for input" << std::endl;
      return false;
    }

  CGAL::set_ascii_mode(is);

  int n;
  is >> n;
  std::cout << "Reading " << n << " points" << std::endl;
  Point p;
  for( ; n>0 ; n--)
    {
      is >> p;
      L.push_back(Wpoint(p, weight));
    }
  std::cout << "Points inserted" << std::endl;
  return true;
}

void set_alpha(Alpha_shape_3& A, int alpha_index)
{
  // alpha corresponds to an index
  if (A.number_of_alphas() > 0)
  {
    if (alpha_index < 100)
      {
	int n = (alpha_index * A.number_of_alphas())/ 100;
	A.set_alpha(A.get_nth_alpha(n));
      }
    else
      {
	Alpha_shape_3::Alpha_iterator alpha_end_it = A.alpha_end();
	A.set_alpha((*(--alpha_end_it))+1);
      }
  }
  else
    A.set_alpha(0);
}

//------------------ main -------------------------------------------

int main()
{
#ifdef CGAL_USE_GEOMVIEW
  CGAL::Geomview_stream gv(CGAL::Bbox_3(0,0,0, 2, 2, 2));
  gv.set_line_width(4);
  gv.set_trace(false);
  gv.set_bg_color(CGAL::Color(0, 200, 200));
#endif

  Alpha_shape_3 A;
  std::list<Wpoint> L;
  std::cout << "Enter a common weight for all points: ";
  coord_type w;
  std::cin >> w;
  file_input(L, w);
  construct_alpha_shape(L,Alpha_shape_3::GENERAL,A);

  std::cout << "Alpha Shape computed" << std::endl;

  int n(50);

    while(n >= 0){
     std::cout <<  "number of alpha values : "
	       << A.number_of_alphas() << std::endl;
     std::cout << "Enter an alpha index "
	       << "(negative index -> quit, if 0 -> optimal alpha_shape): ";
      std::cin >> n;

#ifdef CGAL_USE_GEOMVIEW
      gv.clear();
#endif
      //gv << (Triangulation_3) A;
      if (n < 0)  break;
      if (n == 0)   A.set_alpha(*A.find_optimal_alpha(1));
      if (n > 0)    A.set_alpha(A.get_nth_alpha(n));

#ifdef CGAL_USE_GEOMVIEW
      gv << A;
#else
      std::cout << A << std::endl;
#endif
    }

  return 0;
}