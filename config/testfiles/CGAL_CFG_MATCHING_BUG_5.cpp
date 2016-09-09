// Copyright (c) 2005  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.3-branch/Installation/config/testfiles/CGAL_CFG_MATCHING_BUG_5.cpp $
// $Id: CGAL_CFG_MATCHING_BUG_5.cpp 37704 2007-03-30 08:39:31Z spion $
// 
//
// Author(s)     : Sylvain Pion

// ---------------------------------------------------------------------
// This program is used by install_cgal.
// The following documentation will be pasted in the generated configfile.
// ---------------------------------------------------------------------

//| This flag is set, if a compiler cannot distinguish the signature
//| of overloaded function templates, which have one template parameter
//| to be passed explicitely when being called.
//| This bug appears for example on g++ 3.3 and 3.4.

template < typename T >
struct A {};

template < typename T, typename U >
T enum_cast(const U&) { return T(); }

template < typename T, typename U >
T enum_cast(const A<U>&) { return T(); }

int main()
{
  A<double> a;
  int i = enum_cast<int>(a);
  (void) i;
  return 0;
}