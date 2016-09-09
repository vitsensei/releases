// Copyright (c) 2006 Fernando Luis Cacciola Carballal. All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Straight_skeleton_2/include/CGAL/compute_outer_frame_margin.h $
// $Id: compute_outer_frame_margin.h 33023 2006-08-04 19:11:49Z fcacciola $
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_COMPUTE_OUTER_FRAME_MARGIN_H
#define CGAL_COMPUTE_OUTER_FRAME_MARGIN_H

#include <vector>
#include <algorithm>

#include <boost/shared_ptr.hpp>
#include <boost/optional/optional.hpp>

#include <CGAL/algorithm.h>
#include <CGAL/Polygon_offset_builder_traits_2.h>

CGAL_BEGIN_NAMESPACE

template<class ForwardPointIterator, class Traits>
boost::optional< typename Traits::FT > compute_outer_frame_margin ( ForwardPointIterator aBegin
                                                                  , ForwardPointIterator aEnd
                                                                  , typename Traits::FT  aOffset
                                                                  , Traits const&        aTraits
                                                                  )
{
  typedef typename Traits::Kernel              Kernel ;
  typedef typename Traits::FT                  FT ;
  typedef typename Traits::Point_2             Point_2 ;
  typedef typename Traits::Segment_2           Segment_2 ;
  typedef typename Traits::Seeded_trisegment_2 Seeded_trisegment_2 ;
  
  Kernel kernel ;
  
  typename Kernel::Equal_2                    equal             = kernel.equal_2_object();
  typename Kernel::Collinear_2                collinear         = kernel.collinear_2_object();
  typename Kernel::Compute_squared_distance_2 squared_distance  = kernel.compute_squared_distance_2_object();
  typename Kernel::Construct_segment_2        construct_segment = kernel.construct_segment_2_object();
  
  typedef boost::optional<Point_2> OptionalPoint_2 ;
  
  FT lMaxSDist(0.0) ;
  
  ForwardPointIterator lLast = CGAL::predecessor(aEnd) ;
  
  bool lOverflow = false ;

  Seeded_trisegment_2 nullst = Construct_ss_seeded_trisegment_2(aTraits)();
  
  for ( ForwardPointIterator lCurr = aBegin ; lCurr < aEnd ; ++ lCurr )
  {
    ForwardPointIterator lPrev = ( lCurr == aBegin ? lLast  : CGAL::predecessor(lCurr) ) ;
    ForwardPointIterator lNext = ( lCurr == lLast  ? aBegin : CGAL::successor  (lCurr) ) ;
    
    if ( !equal(*lPrev,*lCurr) && !equal(*lCurr,*lNext) && !collinear(*lPrev,*lCurr,*lNext) )
    {
      Segment_2 lLEdge = construct_segment(*lPrev,*lCurr);
      Segment_2 lREdge = construct_segment(*lCurr,*lNext);
      
      OptionalPoint_2 lP = Construct_offset_point_2(aTraits)(aOffset,lLEdge,lREdge,nullst);
     
      if ( !lP )
      {
        lOverflow = true ;
        break ;
      }
       
      FT lSDist = CGAL::squared_distance(*lCurr,*lP);
 
      if ( ! CGAL_NTS is_finite(lSDist) ) 
      {
        lOverflow = true ;
        break ;
      }  
               
      if ( lSDist > lMaxSDist )
        lMaxSDist = lSDist ;
    }
  }
  
  if ( ! lOverflow )
  {
    FT lDist = CGAL_NTS sqrt(lMaxSDist) ;
  
    return boost::optional<FT>( lDist + ( aOffset * FT(1.05) ) ) ; // Add a %5 gap
  }
  else
    return boost::optional<FT>();
  
}                              

template<class ForwardPointIterator, class FT>
boost::optional<FT> compute_outer_frame_margin ( ForwardPointIterator aBegin, ForwardPointIterator aEnd, FT aOffset )
{
  typedef typename std::iterator_traits<ForwardPointIterator>::value_type Point_2 ;
  
  typedef typename Kernel_traits<Point_2>::Kernel K; 
  
  Polygon_offset_builder_traits_2<K> traits ;
  
  return compute_outer_frame_margin(aBegin,aEnd,aOffset,traits);
}                                                                 

CGAL_END_NAMESPACE

#endif // CGAL_COMPUTE_OUTER_FRAME_MARGIN_H //
// EOF //

 