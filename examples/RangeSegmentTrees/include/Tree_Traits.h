#ifndef __TREE_TRAITS__
#define __TREE_TRAITS__
// ============================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------------
//
// release       : $CGAL_Revision: CGAL-0.9-I-01 $
// release_date  : $CGAL_Date: 1997/08/21 $
//
// file          : src/test/RangeSegmentTrees/include/Tree_Traits.h
// source        : src/test/RangeSegmentTrees/include/Tree_Traits.h
// revision      : $Revision: 1.1 $
// revision_date : $Date: 1997/11/11 08:28:36 $
// author(s)     : Gabriele Neyer (neyer@inf.ethz.ch)
//
// coordinator   : Peter Widmayer, ETH Zurich
//
// ============================================================================

#include <function.h>
#include <pair.h>

class Tree_traits_1{
 public:
  typedef double Key;
  typedef double Key_1;
  typedef pair<Key,Key> Interval;

  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k;}
  };

  class _Compare_1{
  public:
    bool operator()(Key_1 k1, Key_1 k2)
    {
      return less<double>()(k1,k2);
    }
  };

  typedef _Compare_1 compare_1;
  typedef _Low_1 low_1;
  typedef _High_1 high_1;
  typedef _Key_1 key_1;
};



class Tree_traits_2{
 public:
  typedef pair<int, double> Key;
  typedef int Key_1;
  typedef double Key_2;
  typedef pair<Key,Key> Interval;

  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.first;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second.first;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.second;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second.second;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k.first;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k.second;}
  };
  
  class _Compare_1{
  public:
    bool operator()(Key_1 k1, Key_1 k2)
    {
      return less<int>()(k1,k2);
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      return less<double>()(k1,k2);
    }
  };

  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Low_1 low_1;
  typedef _High_1 high_1;
  typedef _Key_1 key_1;
  typedef _Low_2 low_2;
  typedef _High_2 high_2;
  typedef _Key_2 key_2;

};

class tuple_3{
 public:
  int key_1;
  double key_2;
  long key_3;
  tuple_3(){}
  tuple_3(int a, double b, long c) : key_1(a), key_2(b), key_3(c) {}
};

class Tree_traits_3{
 public:
  typedef tuple_3 Key;
  typedef int Key_1;
  typedef double Key_2;
  typedef long Key_3;
  typedef pair<Key,Key> Interval;

  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.key_1;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second.key_1;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.key_2;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second.key_2;}
  };

  class _Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.key_3;}
  };

  class _High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.second.key_3;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k.key_1;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k.key_2;}
  };

  class _Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k.key_3;}
  };
  
  class _Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      return less<int>()(k1,k2);
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      return less<double>()(k1,k2);
    }
  };

  class _Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      return less<long>()(k1,k2);
    }
  };

  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Compare_3 compare_3;
  typedef _Low_1 low_1;
  typedef _Low_2 low_2;
  typedef _Low_3 low_3;
  typedef _High_1 high_1;
  typedef _High_2 high_2;
  typedef _High_3 high_3;
  typedef _Key_1 key_1;
  typedef _Key_2 key_2;
  typedef _Key_3 key_3;
};



class tuple_4{
 public:
  int key_1;
  double key_2;
  long key_3;
  double key_4;
  tuple_4(){}
  tuple_4(int a, double b, long c, double d) : key_1(a), key_2(b), key_3(c), key_4(d) {}
};

class Tree_traits_4{
 public:
  typedef tuple_4 Key;
  typedef int Key_1;
  typedef double Key_2;
  typedef long Key_3;
  typedef double Key_4;
  typedef pair<Key,Key> Interval;

  class _Low_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.first.key_1;}
  };

  class _High_1{
  public:
    Key_1 operator()(const Interval& i)
    { return i.second.key_1;}
  };

  class _Low_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.first.key_2;}
  };

  class _High_2{
  public:
    Key_2 operator()(const Interval& i)
    { return i.second.key_2;}
  };

  class _Low_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.first.key_3;}
  };

  class _High_3{
  public:
    Key_3 operator()(const Interval& i)
    { return i.second.key_3;}
  };

  class _Low_4{
  public:
    Key_4 operator()(const Interval& i)
    { return i.first.key_4;}
  };

  class _High_4{
  public:
    Key_4 operator()(const Interval& i)
    { return i.second.key_4;}
  };

  class _Key_1{
  public:
    Key_1 operator()(const Key& k)
    { return k.key_1;}
  };

  class _Key_2{
  public:
    Key_2 operator()(const Key& k)
    { return k.key_2;}
  };

  class _Key_3{
  public:
    Key_3 operator()(const Key& k)
    { return k.key_3;}
  };

  class _Key_4{
  public:
    Key_4 operator()(const Key& k)
    { return k.key_4;}
  };
  
  class _Compare_1{
  public:
    
    bool operator()(Key_1 k1, Key_1 k2)
    {
      return less<int>()(k1,k2);
    }
  };

  class _Compare_2{
  public:
    
    bool operator()(Key_2 k1, Key_2 k2)
    {
      return less<double>()(k1,k2);
    }
  };

  class _Compare_3{
  public:
    
    bool operator()(Key_3 k1, Key_3 k2)
    {
      return less<long>()(k1,k2);
    }
  };

  class _Compare_4{
  public:
    
    bool operator()(Key_4 k1, Key_4 k2)
    {
      return less<double>()(k1,k2);
    }
  };

  typedef _Compare_1 compare_1;
  typedef _Compare_2 compare_2;
  typedef _Compare_3 compare_3;
  typedef _Compare_4 compare_4;
  typedef _Low_1 low_1;
  typedef _Low_2 low_2;
  typedef _Low_3 low_3;
  typedef _Low_4 low_4;
  typedef _High_1 high_1;
  typedef _High_2 high_2;
  typedef _High_3 high_3;
  typedef _High_4 high_4;
  typedef _Key_1 key_1;
  typedef _Key_2 key_2;
  typedef _Key_3 key_3;
  typedef _Key_4 key_4;
};


#endif