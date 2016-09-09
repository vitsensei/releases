// Copyright (c) 2002 Utrecht University (The Netherlands).
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
// $Source: /CVSROOT/CGAL/Packages/Spatial_searching/include/CGAL/Search_traits_3.h,v $
// $Revision: 1.8 $ $Date: 2004/09/07 09:16:23 $
// $Name:  $
//
// Author(s)     : Hans Tangelder (<hanst@cs.uu.nl>)


#ifndef CGAL_SEARCH_TRAITS_3_H
#define CGAL_SEARCH_TRAITS_3_H

namespace CGAL {


  template <class K>

  class Search_traits_3 {

  public:
    
    typedef typename K::Cartesian_const_iterator_3 Cartesian_const_iterator_d;
    typedef typename K::Construct_cartesian_const_iterator_3 Construct_cartesian_const_iterator_d;
    typedef typename K::Point_3 Point_d;
    typedef typename K::Iso_cuboid_3 Iso_box_d;
    typedef typename K::Sphere_3 Sphere_d;
    typedef typename K::Construct_iso_cuboid_3 Construct_iso_box_d;

    typedef typename K::Construct_min_vertex_3 Construct_min_vertex_d;
    typedef typename K::Construct_max_vertex_3 Construct_max_vertex_d;
    typedef typename K::Construct_center_3 Construct_center_d;
    typedef typename K::Compute_squared_radius_3 Compute_squared_radius_d;
    typedef typename K::FT FT;
 
  };

  
} // namespace CGAL
#endif // SEARCH_TRAITS_3_H