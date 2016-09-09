// ======================================================================
//
// Copyright (c) 1997,1998,1999,2000,2001 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - A commercial license is available through Algorithmic Solutions, who also
//   markets LEDA (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3
// release_date  : 2001, August 13
//
// file          : include/CGAL/IO/Geomview_stream.h
// package       : Geomview (3.19)
// revision      : $Revision: 1.37 $
// revision_date : $Date: 2001/06/19 18:36:10 $
// author(s)     : Andreas Fabri, Sylvain Pion
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_GEOMVIEW_STREAM_H
#define CGAL_GEOMVIEW_STREAM_H

#include <CGAL/Bbox_2.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/IO/Color.h>

// #include <CGAL/Iso_rectangle_2.h>
// #include <CGAL/intersections.h>

#include <map>
#include <string>
#include <strstream> // deprecated
// #include <sstream>

CGAL_BEGIN_NAMESPACE

class Geomview_stream {
public:
    Geomview_stream(const Bbox_3 &bbox = Bbox_3(0,0,0, 1,1,1),
		    const char *machine = NULL,
		    const char *login = NULL);

    ~Geomview_stream();

    Geomview_stream &operator<<(const Color &c);
    Geomview_stream &operator<<(std::string s);
    Geomview_stream &operator<<(int i);
    Geomview_stream &operator<<(double d);

    Geomview_stream &operator>>(char *expr);

    void clear();
    void look_recenter();

    void set_bg_color(const Color &c);

    Color get_vertex_color() const;
    Color get_edge_color() const;
    Color get_face_color() const;

    Color set_vertex_color(const Color&);
    Color set_edge_color(const Color&);
    Color set_face_color(const Color&);

    double vcr() const;
    double vcg() const;
    double vcb() const;

    double ecr() const;
    double ecg() const;
    double ecb() const;

    double fcr() const;
    double fcg() const;
    double fcb() const;

    double get_vertex_radius() const
    {
	return radius;
    }
    double set_vertex_radius(double r)
    {
	std::swap(r, radius);
	return r;
    }

    int get_line_width() const
    {
	return line_width;
    }
    int set_line_width(int w)
    {
	std::swap(w, line_width);
        return w;
    }

    bool set_wired(bool b)
    {
	std::swap(b, wired_flag);
	return b;
    }
    bool get_wired() const
    {
	return wired_flag;
    }

    bool set_echo(bool b)
    {
	std::swap(b, echo_flag);
	return b;
    }
    bool get_echo() const
    {
	return echo_flag;
    }

    bool set_raw(bool b)
    {
	std::swap(b, raw_flag);
	return b;
    }
    bool get_raw() const
    {
	return raw_flag;
    }

    bool set_trace(bool b)
    {
	std::swap(b, trace_flag);
	return b;
    }
    bool get_trace() const
    {
	return trace_flag;
    }

    void trace(const std::string s) const
    {
        if (get_trace())
            std::cerr << s;
    }
    void trace(double d) const
    {
        if (get_trace())
            std::cerr << d << ' ';
    }
    void trace(int i) const
    {
        if (get_trace())
            std::cerr << i << ' ';
    }

    bool set_binary_mode(bool b = true)
    {
	std::swap(b, binary_flag);
	return b;
    }
    bool set_ascii_mode(bool b = true)
    {
	return !set_binary_mode(!b);
    }
    bool get_binary_mode() const
    {
	return binary_flag;
    }
    bool get_ascii_mode() const
    {
	return !binary_flag;
    }

    std::string get_new_id(const std::string & s)
    {
	std::ostrstream str;
	str << s << id[s]++ << std::ends;
	return str.str();
    }

    const Bbox_3 & get_bbox()
    {
	return bb;
    }

    void pickplane()
    {
        pickplane(get_bbox());
    }

private:
    void setup_geomview(const char *machine, const char *login);
    void frame(const Bbox_3 &bbox);
    void pickplane(const Bbox_3 &bbox);

    Bbox_3 bb;
    Color vertex_color, edge_color, face_color;
    bool wired_flag;  // decides if we draw surfaces or edges.
    bool echo_flag;   // decides if we echo the point we get back to Geomview.
    bool raw_flag;    // decides if we output footers and headers.
    bool trace_flag;  // makes operator<<() write a trace on cerr.
    bool binary_flag; // makes operator<<() write binary format
    int line_width;   // width of edges
    double radius;    // radius of vertices
    int in, out;      // file descriptors for input and output pipes
    int pid;          // the geomview process identification
    std::map<const std::string, int> id; // used to get a unique ID per type.
};

// Factorize code for Point_2 and Point_3.
template < class FT >
void
output_point(Geomview_stream &gv, const FT &x, const FT &y, const FT &z)
{
    bool ascii_bak = true; // the initialization value shuts up the compiler.
    if (!gv.get_raw()) {
    	ascii_bak = gv.set_ascii_mode();
    	gv << "(geometry " << gv.get_new_id("P")
       	   << " {appearance {linewidth 5 material {edgecolor "
           << gv.vcr() << gv.vcg() << gv.vcb() << "}}{SKEL 1 1 ";
    }

    gv << CGAL::to_double(x) << CGAL::to_double(y) << CGAL::to_double(z);

    if (!gv.get_raw()) {
        gv << "1 0\n}})";
    	gv.set_ascii_mode(ascii_bak);
    }
}

#if defined CGAL_POINT_2_H && \
   !defined CGAL_GV_OUT_POINT_2_H
#define CGAL_GV_OUT_POINT_2_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Point_2<R> &p)
{
    output_point(gv, p.x(), p.y(), typename R::FT(0));
    return gv;
}
#endif

#if defined CGAL_POINT_3_H && \
   !defined CGAL_GV_OUT_POINT_3_H
#define CGAL_GV_OUT_POINT_3_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Point_3<R> &p)
{
    output_point(gv, p.x(), p.y(), p.z());
    return gv;
}
#endif

// The following code is the same for Segment_2 and Segment_3.
template < class Segment >
void
output_segment(Geomview_stream &gv, const Segment &segment)
{
    bool ascii_bak = gv.set_ascii_mode();
    gv << "(geometry " << gv.get_new_id("Seg")
       << " {appearance {linewidth "
       << gv.get_line_width() << "}{VECT "
       << 1 <<  2 << 1    // 1 polyline, two vertices, 1 color
       << 2               // the first polyline contains 2 vertices
       << 1;              // and it has 1 color

    // here are start and end points
    bool raw_bak = gv.set_raw(true);
    gv << segment.source() << segment.target();
    gv.set_raw(raw_bak);

    // and the color of the segment and its opaqueness
    gv << gv.ecr() << gv.ecg() << gv.ecb() << 1.0 << "}})";
    gv.set_ascii_mode(ascii_bak);
}

#if defined CGAL_SEGMENT_2_H && \
   !defined CGAL_GV_OUT_SEGMENT_2_H
#define CGAL_GV_OUT_SEGMENT_2_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Segment_2<R> &segment)
{
    output_segment(gv, segment);
    return gv;
}
#endif

#if defined CGAL_SEGMENT_3_H && \
   !defined CGAL_GV_OUT_SEGMENT_3_H
#define CGAL_GV_OUT_SEGMENT_3_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Segment_3<R> &segment)
{
    output_segment(gv, segment);
    return gv;
}
#endif

// The following code is the same for Triangle_2 and Triangle_3.
template < class Triangle >
void
output_triangle(Geomview_stream &gv, const Triangle &triangle)
{
    bool ascii_bak = gv.set_ascii_mode();
    gv << "(geometry " << gv.get_new_id("Tr")
       << " {appearance {+edge material {edgecolor "
       << gv.ecr()  << gv.ecg()  << gv.ecb() <<  " } shading constant}{ ";
    gv.set_binary_mode();
    // it's a planar polygon
    gv << "OFF BINARY\n"

    // it has 3 vertices, 1 face and 3 edges
       << 3 << 1 << 3;

    bool raw_bak = gv.set_raw(true);
    for(int i=0; i<3; i++)
        gv << triangle[i];
    gv.set_raw(raw_bak);

    // the face
    gv << 3 << 0 << 1 << 2 << 4 << gv.fcr() << gv.fcg() << gv.fcb() << 1.0
       << "}})";
    gv.set_ascii_mode(ascii_bak);
}

#if defined CGAL_TRIANGLE_2_H && \
   !defined CGAL_GV_OUT_TRIANGLE_2_H
#define CGAL_GV_OUT_TRIANGLE_2_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Triangle_2<R> &triangle)
{
    output_triangle(gv, triangle);
    return gv;
}
#endif

#if defined CGAL_TRIANGLE_3_H && \
   !defined CGAL_GV_OUT_TRIANGLE_3_H
#define CGAL_GV_OUT_TRIANGLE_3_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Triangle_3<R> &triangle)
{
    output_triangle(gv, triangle);
    return gv;
}
#endif

#if defined CGAL_TETRAHEDRON_3_H && \
   !defined CGAL_GV_OUT_TETRAHEDRON_3_H
#define CGAL_GV_OUT_TETRAHEDRON_3_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Tetrahedron_3<R> &t)
{
    bool ascii_bak = gv.set_ascii_mode();
    gv << "(geometry " << gv.get_new_id("Tetra")
       << " {appearance {}{ ";
    gv.set_binary_mode();
    gv << "OFF BINARY\n"

    // it has 4 vertices, 4 face and 6 edges
       << 4 << 4 << 6 ;

    // the vertices
    bool raw_bak = gv.set_raw(true);
    for(int i=0; i<4; i++)
        gv << t[i];
    gv.set_raw(raw_bak);

    // the faces
    double r = gv.fcr(),
           g = gv.fcg(),
           b = gv.fcb();
    gv << 3 << 0 << 1 << 2 << 4 << r << g << b << 1.0
       << 3 << 3 << 0 << 1 << 4 << r << g << b << 1.0
       << 3 << 3 << 1 << 2 << 4 << r << g << b << 1.0
       << 3 << 3 << 0 << 2 << 4 << r << g << b << 1.0
       << "}})";
    gv.set_ascii_mode(ascii_bak);
    return gv;
}
#endif

#if defined CGAL_SPHERE_3_H && \
   !defined CGAL_GV_OUT_SPHERE_3_H
#define CGAL_GV_OUT_SPHERE_3_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Sphere_3<R> &S)
{
    bool ascii_bak = gv.set_ascii_mode();
    gv << "(geometry " << gv.get_new_id("Sph")
       << " {appearance {+edge material {edgecolor "
       << gv.ecr()  << gv.ecg()  << gv.ecb() <<  "} shading constant}{ "
       << "SPHERE\n"
       << CGAL_CLIB_STD::sqrt(CGAL::to_double(S.squared_radius())) << "\n";

    bool raw_bak = gv.set_raw(true);
    gv << Point_3<R>(S.center()) << "}})";
    gv.set_raw(raw_bak);
    gv.set_ascii_mode(ascii_bak);

    return gv;
}
#endif

#if defined CGAL_RAY_2_H && \
   !defined CGAL_GV_OUT_RAY_2_H
#define CGAL_GV_OUT_RAY_2_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Ray_2<R> &r)
{
    // Note: it won't work if double is not convertible to an RT...
    const Bbox_3 & bb = gv.get_bbox();
    Object result = intersection(Iso_rectangle_2<R>(
		                    Point_2<R>(bb.xmin(), bb.ymin()),
		                    Point_2<R>(bb.xmax(), bb.ymax())), r);
    Point_2<R> ipoint;
    Segment_2<R> iseg;
    if (assign(ipoint, result))
	gv << ipoint;
    else if (assign(iseg, result))
	gv << iseg;
    return gv;
}
#endif

#if defined CGAL_LINE_2_H && \
   !defined CGAL_GV_OUT_LINE_2_H
#define CGAL_GV_OUT_LINE_2_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Line_2<R> &r)
{
    // Note: it won't work if double is not convertible to an RT...
    const Bbox_3 & bb = gv.get_bbox();
    Object result = intersection(Iso_rectangle_2<R>(
		                    Point_2<R>(bb.xmin(), bb.ymin()),
		                    Point_2<R>(bb.xmax(), bb.ymax())), r);
    Point_2<R> ipoint;
    Segment_2<R> iseg;
    if (assign(ipoint, result))
	gv << ipoint;
    else if (assign(iseg, result))
	gv << iseg;
    return gv;
}
#endif

// Ray and Line drawing should be done by intersecting them with the BBox
// of the Geomview_stream.  But for now we take the easy approach.

#if defined CGAL_RAY_3_H && \
   !defined CGAL_GV_OUT_RAY_3_H
#define CGAL_GV_OUT_RAY_3_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Ray_3<R> &r)
{
    typename R::Segment_3 s(r.source(), r.point(1));
    gv << s;
    return gv;
}
#endif

#if defined CGAL_LINE_3_H && \
   !defined CGAL_GV_OUT_LINE_3_H
#define CGAL_GV_OUT_LINE_3_H
template < class R >
Geomview_stream&
operator<<(Geomview_stream &gv, const Line_3<R> &r)
{
    typename R::Segment_3 s(r.point(-1), r.point(1));
    gv << s;
    return gv;
}
#endif

Geomview_stream&
operator<<(Geomview_stream &gv, const Bbox_2 &bbox);

Geomview_stream&
operator<<(Geomview_stream &gv, const Bbox_3 &bbox);

char*
nth(char* s, int count);

#ifdef CGAL_POINT_3_H
template < class R >
void
parse_point(const char* pickpoint, Point_3<R> &point)
{
    // std::stringstream ss;
    std::strstream ss;
    ss << pickpoint << std::ends;

    double x, y, z, w;
    char parenthesis;
    ss >> parenthesis >> x >> y >> z >> w;
    point = Point_3<R>(x, y, z, w);
}
#endif

#if defined CGAL_POINT_3_H && !defined CGAL_GV_IN_POINT_3_H
#define CGAL_GV_IN_POINT_3_H
template < class R >
Geomview_stream&
operator>>(Geomview_stream &gv, Point_3<R> &point)
{
    const char *gclpick =
	"(pick world pickplane * nil nil nil nil nil nil nil)";

    bool ascii_bak = gv.set_ascii_mode();
    gv << "(pickable pickplane yes) (ui-target pickplane yes)"
       << "(interest " << gclpick << ")";

    char sexpr[1024];
    gv >> sexpr;  // this reads a gcl expression

    const char* pickpoint = nth(sexpr, 3);
    // this gives something as: (0.0607123 0.0607125 4.76837e-07 0.529628)
    parse_point(pickpoint, point);

    // we echo the input
    if (gv.get_echo())
	gv << point;

    // we are done and tell geomview to stop sending pick events
    gv << "(uninterest " << gclpick << ") (pickable pickplane no)";
    gv.set_ascii_mode(ascii_bak);

    return gv;
}
#endif

CGAL_END_NAMESPACE

#endif // CGAL_GEOMVIEW_STREAM_H
