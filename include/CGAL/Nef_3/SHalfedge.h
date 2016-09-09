// Copyright (c) 1997-2002  Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://hachenb@scm.gforge.inria.fr/svn/cgal/branches/Filtered_Nef/Nef_3/include/CGAL/Nef_3/SHalfedge.h $
// $Id: SHalfedge.h 35450 2006-12-06 10:43:20Z hachenb $
// 
//
// Author(s)     : Michael Seel        <seel@mpi-sb.mpg.de>
//                 Miguel Granados     <granados@mpi-sb.mpg.de>
//                 Susan Hert          <hert@mpi-sb.mpg.de>
//                 Lutz Kettner        <kettner@mpi-sb.mpg.de>
//                 Peter Hachenberger  <hachenberger@mpi-sb.mpg.de>
#ifndef CGAL_NEF_SHALFEDGE_H
#define CGAL_NEF_SHALFEDGE_H

#include <string>
#include <sstream>
#include <CGAL/IO/Verbose_ostream.h>
#include <CGAL/Nef_3/SNC_iteration.h>

#undef CGAL_NEF_DEBUG
#define CGAL_NEF_DEBUG 83
#include <CGAL/Nef_2/debug.h>

CGAL_BEGIN_NAMESPACE

template <typename Refs>
class SHalfedge_base  { 
  typedef void* GenPtr;
  typedef typename Refs::Mark  Mark;
  typedef typename Refs::Sphere_circle  Sphere_circle;

  typedef typename Refs::Halfedge_handle Halfedge_handle;
  typedef typename Refs::Halfedge_const_handle Halfedge_const_handle;
  typedef typename Refs::SVertex_handle SVertex_handle;
  typedef typename Refs::SVertex_const_handle SVertex_const_handle;
  typedef typename Refs::SHalfedge_handle SHalfedge_handle;
  typedef typename Refs::SHalfedge_const_handle SHalfedge_const_handle;
  typedef typename Refs::SFace_handle SFace_handle;
  typedef typename Refs::SFace_const_handle SFace_const_handle;
  typedef typename Refs::Halffacet_handle Halffacet_handle;
  typedef typename Refs::Halffacet_const_handle Halffacet_const_handle;

  // Role within local graph:
  SVertex_handle     source_;
  SHalfedge_handle   sprev_, snext_;
  SFace_handle       incident_sface_;
  SHalfedge_handle   twin_;
  // Topology within global Nef structure:  
  SHalfedge_handle   prev_, next_;
  Halffacet_handle   facet_;
  GenPtr             info_;
  // temporary needed:
  Mark               mark_;
  Sphere_circle      circle_;

 public:

  SHalfedge_base() : source_(), sprev_(), snext_(),
    incident_sface_(), twin_(), 
    prev_(), next_(), facet_(), 
    info_(), mark_(), circle_() {}

    ~SHalfedge_base() {
      CGAL_NEF_TRACEN("  destroying SHalfedge_base item "<<&*this);
    }

    SHalfedge_base(const SHalfedge_base<Refs>& e)
      {
	source_ = e.source_;
	sprev_ = e.sprev_;
	snext_ = e.snext_;
	incident_sface_ = e.incident_sface_;
	twin_ = e.twin_;
	prev_ = e.prev_;
	next_ = e.next_;
	facet_ = e.facet_;
	info_ = 0;
	mark_ = e.mark_;
	circle_ = e.circle_;
      }

    SHalfedge_base<Refs>& operator=(const SHalfedge_base<Refs>& e)
      {
	source_ = e.source_;
	sprev_ = e.sprev_;
	snext_ = e.snext_;
	incident_sface_ = e.incident_sface_;
	twin_ = e.twin_;
	prev_ = e.prev_;
	next_ = e.next_;
	facet_ = e.facet_;
	info_ = 0;
	mark_ = e.mark_;
	circle_ = e.circle_;
	return *this;
      }

    Mark& mark() { return mark_; }
    const Mark& mark() const { return mark_; }

    SHalfedge_handle& twin() { return twin_; }
    SHalfedge_const_handle twin() const { return twin_; }

    SVertex_handle& source() { return source_; }
    SVertex_const_handle source() const { return source_; }

    SVertex_handle& target() { return twin()->source(); }
    SVertex_const_handle target() const { return twin()->source(); }

    SHalfedge_handle& prev() { return prev_; }
    SHalfedge_const_handle prev() const { return prev_; }

    SHalfedge_handle& next() { return next_; }
    SHalfedge_const_handle next() const { return next_; }

    SHalfedge_handle& sprev() { return sprev_; }
    SHalfedge_const_handle sprev() const { return sprev_; }

    SHalfedge_handle& snext() { return snext_; }
    SHalfedge_const_handle snext() const { return snext_; }

    SHalfedge_handle& cyclic_adj_succ()
      { return sprev()->twin(); }
    SHalfedge_const_handle cyclic_adj_succ() const
    { return sprev()->twin(); }

    SHalfedge_handle& cyclic_adj_pred(SHalfedge_const_handle e)
      { return e->twin()->snext(); }
    SHalfedge_const_handle cyclic_adj_pred(SHalfedge_const_handle e) const
    { return e->twin()->snext(); }

    Sphere_circle& circle() { return circle_; }
    const Sphere_circle& circle() const { return circle_; }
    
    SFace_handle& incident_sface() { return incident_sface_; }
    SFace_const_handle incident_sface() const { return incident_sface_; }

    Halffacet_handle& facet() { return facet_; }
    Halffacet_const_handle facet() const { return facet_; }

    GenPtr& info() { return info_; }
    const GenPtr& info() const { return info_; }

 public:
    std::string debug() const
      { std::stringstream os; 
	set_pretty_mode(os); 
	os <<"e[ "<<source_->debug()<<", "
	   <<twin_->source_->debug()<<" "<<info_<<" ] ";
	return os.str();
      }

    bool is_twin() const { return (&*twin_ < this); }

    bool is_valid( bool verb = false, int level = 0) const {
      
      Verbose_ostream verr(verb);
      verr << "begin CGAL::SNC_items<...>::SHalfedge_base::is_valid( verb=true, "
	"level = " << level << "):" << std::endl;

      bool valid = (source_ != SVertex_handle() &&
		    source_ != NULL &&
		    source_ != Halfedge_handle());
      valid = valid && (twin_  != SHalfedge_handle() && twin_  != NULL);
      valid = valid && (sprev_ != SHalfedge_handle() && sprev_ != NULL);
      valid = valid && (snext_ != SHalfedge_handle() && snext_ != NULL);
      valid = valid && (prev_  != SHalfedge_handle() && prev_  != NULL);
      valid = valid && (next_  != SHalfedge_handle() && next_  != NULL);
      
      valid = valid && (incident_sface_ != SFace_handle() && 
			incident_sface_ != NULL);
      valid = valid && (facet_ != Halffacet_handle() &&
			facet_ != NULL);
      valid = valid && (circle_.d() == 0);
      valid = valid && (circle_.a() != 0 || circle_.b() != 0 || circle_.c() !=0);
      
      verr << "end of CGAL::SNC_items<...>::SHalfedge_base::is_valid(): structure is "
	   << ( valid ? "valid." : "NOT VALID.") << std::endl;

      return valid;
    }

}; // SHalfedge_base

CGAL_END_NAMESPACE
#endif //CGAL_NEF_SHALFEDGE_H