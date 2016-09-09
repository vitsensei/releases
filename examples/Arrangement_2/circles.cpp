//! \file examples/Arrangement_2/ex_circles.cpp
// Constructing an arrangement of circles using the conic-arc traits.

#include "arr_rational_nt.h"
#include <CGAL/Cartesian.h>
#include <CGAL/Arr_circle_segment_traits_2.h>
#include <CGAL/Arrangement_2.h>

typedef CGAL::Cartesian<Number_type>                  Kernel;
typedef Kernel::Circle_2                              Circle_2;
typedef CGAL::Arr_circle_segment_traits_2<Kernel>     Traits_2;
typedef Traits_2::CoordNT                             CoordNT;
typedef Traits_2::Point_2                             Point_2;
typedef Traits_2::Curve_2                             Curve_2;
typedef CGAL::Arrangement_2<Traits_2>                 Arrangement_2;

int main ()
{
  // Create a circle centered at the origin with radius 5.
  Kernel::Point_2  c1 = Kernel::Point_2 (0, 0);
  Number_type      sqr_r1 = Number_type (25);       // = 5^2
  Circle_2         circ1 = Circle_2 (c1, sqr_r1, CGAL::CLOCKWISE);
  Curve_2          cv1 = Curve_2 (circ1);

  // Create a circle centered at (7,7) with radius 5.
  Kernel::Point_2  c2 = Kernel::Point_2 (7, 7);
  Number_type      sqr_r2 = Number_type (25);       // = 5^2
  Circle_2         circ2 = Circle_2 (c2, sqr_r2, CGAL::CLOCKWISE);
  Curve_2          cv2 = Curve_2 (circ2);

  // Create a circle centered at (4,-0.5) with radius 3.5 (= 7/2).
  Kernel::Point_2  c3 = Kernel::Point_2 (4, Number_type (-1,2));
  Number_type      sqr_r3 = Number_type (49, 4);    // = 3.5^2
  Circle_2         circ3 = Circle_2 (c3, sqr_r3, CGAL::CLOCKWISE);
  Curve_2          cv3 = Curve_2 (circ3);

  // Construct the arrangement of the three circles.
  Arrangement_2    arr;

  insert_curve (arr, cv1);
  insert_curve (arr, cv2);
  insert_curve (arr, cv3);

  // Locate the vertex with maximal degree.
  Arrangement_2::Vertex_const_iterator  vit;
  Arrangement_2::Vertex_const_handle    v_max;
  unsigned int                          max_degree = 0;

  for (vit = arr.vertices_begin(); vit != arr.vertices_end(); ++vit)
  {
    if (vit->degree() > max_degree)
    {
      v_max = vit;
      max_degree = vit->degree();
    }
  }

  std::cout << "The vertex with maximal degree in the arrangement is: "
            << "v_max = (" << v_max->point() << ") "
            << "with degree " << max_degree << "." << std::endl;

  return (0);
}
