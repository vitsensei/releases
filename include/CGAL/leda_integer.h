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
// source        : Integer.fw
// file          : include/CGAL/leda_integer.h
// package       : Number_types (1.2.8)
// revision      : 1.2.8
// revision_date : 01 Jul 1998 
// author(s)     : Andreas Fabri
//
// coordinator   : MPI, Saarbruecken  (<Stefan.Schirra>)
// email         : cgal@cs.uu.nl
//
// ======================================================================
 

#ifndef CGAL_INTEGER_H
#define CGAL_INTEGER_H

#ifndef CGAL_IO_IO_TAGS_H
#include <CGAL/IO/io_tags.h>
#endif // CGAL_IO_IO_TAGS_H
#ifndef CGAL_NUMBER_TYPE_TAGS_H
#include <CGAL/number_type_tags.h>
#endif // CGAL_NUMBER_TYPE_TAGS_H

/*
#if !defined(LEDA_ROOT_INCL_ID)
#define LEDA_ROOT_INCL_ID 349063
#include <LEDA/REDEFINE_NAMES.h>
#endif
*/

#ifndef CGAL_PROTECT_LEDA_INTEGER_H
#include <LEDA/integer.h>
#define CGAL_PROTECT_LEDA_INTEGER_H
#endif // CGAL_PROTECT_LEDA_INTEGER_H

inline
double
CGAL_to_double(const leda_integer & i)
{ return i.todouble(); }

inline
CGAL_Number_tag
CGAL_number_type_tag(const leda_integer& )
{ return CGAL_Number_tag(); }

inline
bool
CGAL_is_finite(const leda_integer &)
{ return true; }

inline
bool
CGAL_is_valid(const leda_integer &)
{ return true; }

inline
CGAL_io_Operator
CGAL_io_tag(const leda_integer &)
{ return CGAL_io_Operator(); }

/*
#if LEDA_ROOT_INCL_ID == 349063
#undef LEDA_ROOT_INCL_ID
#include <LEDA/UNDEFINE_NAMES.h>
#endif
*/

#endif // CGAL_INTEGER_H