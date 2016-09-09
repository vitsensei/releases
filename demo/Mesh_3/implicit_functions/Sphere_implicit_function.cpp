// Copyright (c) 2010 INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/demo/Mesh_3/implicit_functions/Sphere_implicit_function.cpp $
// $Id: Sphere_implicit_function.cpp 57336 2010-07-06 07:26:40Z stayeb $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#include <QObject>
#include "Implicit_function_interface.h"


const double radius = 1.;

class Sphere_implicit_function :
  public QObject,
  public Implicit_function_interface
{
  Q_OBJECT
  Q_INTERFACES(Implicit_function_interface)
  
public:
  virtual QString name() const { return "Sphere function"; }
  
  virtual double operator()(double x, double y, double z) const
  {
    return (x*x + y*y + z*z - radius);
  }
  
  virtual Bbox bbox() const
  {
    double r = radius * 1.2;
    return Bbox(-r,-r,-r,r,r,r);
  }
};



#include <QtPlugin>
Q_EXPORT_PLUGIN2(Sphere_implicit_function, Sphere_implicit_function)
#include "Sphere_implicit_function.moc"
