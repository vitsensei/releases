// Copyright (c) 2011  GeometryFactory Sarl (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/GraphicsView/src/CGALQt4/resources.cpp $
// $Id: resources.cpp 64055 2011-06-10 17:14:27Z lrineau $
// 
//
// Author(s)     : Laurent Rineau <Laurent.Rineau@geometryfactory.com>

#include <QDir>

// cannot use namespaces because of the Q_INIT_RESOURCE macro
void CGAL_Qt4_init_resources() {
  Q_INIT_RESOURCE(File);
  Q_INIT_RESOURCE(Triangulation_2); 
  Q_INIT_RESOURCE(Input);
  Q_INIT_RESOURCE(CGAL);
}