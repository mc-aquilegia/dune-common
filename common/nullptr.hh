// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
#ifndef DUNE_NULLPTR_HH
#define DUNE_NULLPTR_HH

#if ! HAVE_NULLPTR

/**
   \brief Fallback implementation of nullptr

   see C++ proposal
   http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2431.pdf
 */
const                        // this is a const object...
class dune_nullptr_t {            // of type nullptr_t
public:
  template<class T>          // convertible to any type
  operator T*() const        // of null non-member
  { return 0; }              // pointer...
  template<class C, class T> // or any type of null
  operator T C::*() const    // member pointer...
  { return 0; }
private:
  void operator&() const;    // whose address can't be taken
} nullptr = {};              // and whose name is nullptr

typedef dune_nullptr_t nullptr_t;

#endif // HAVE_NULLPTR

#endif // DUNE_NULLPTR_HH