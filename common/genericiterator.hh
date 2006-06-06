// -*- tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// vi: set et ts=4 sw=2 sts=2:
// $Id$
#ifndef DUNE_GENERICITERATOR_HH
#define DUNE_GENERICITERATOR_HH

#include <dune/common/iteratorfacades.hh>
#include <cassert>

namespace Dune {

  /*! \defgroup GenericIterator GenericIterator
     \ingroup IteratorFacades

     \brief Generic Iterator class for writing stl conformant iterators
     for any Container class with operator[]

     Using this template class you can create an iterator and a const_iterator
     for any Container class.

     Imagine you have SimpleContainer and would like to have an iterator.
     All you have to do is provide operator[], begin() and end()
     (for const and for non-const).

     \code
     template<class T>
     class SimpleContainer{
     public:
      typedef GenericIterator<SimpleContainer<T>,T> iterator;

      typedef GenericIterator<const SimpleContainer<T>,const T> const_iterator;

      SimpleContainer(){
        for(int i=0; i < 100; i++)
          values_[i]=i;
      }

      iterator begin(){
        return iterator(*this, 0);
      }

      const_iterator begin() const{
        return const_iterator(*this, 0);
      }

      iterator end(){
        return iterator(*this, 100);
      }

      const_iterator end() const{
        return const_iterator(*this, 100);
      }

      T& operator[](int i){
        return values_[i];
      }


      const T& operator[](int i) const{
        return values_[i];
      }
     private:
      T values_[100];
     };
     \endcode

     See dune/common/test/iteratorfacestest.hh for details or
     Dune::QuadratureDefault in dune/quadrature/quadrature.hh
     for a real example.
   */

  /**
   * @file
   * @brief This file implements a generic iterator classes for writing stl conformant iterators.
   *
   * With using this generic iterator writing iterators for containers
   * with operator[] is only a matter of seconds
   */

  /** @addtogroup GenericIterator
   *
   * @{
   */
  /**
   * @brief Generic class for stl conformant iterators for container classes with operator[].
   *
   * If template parameter C has a const qualifier we are a const iterator, otherwise we
   * are a mutable iterator.
   */
  template<class C, class T, class D = std::ptrdiff_t>
  class GenericIterator :
    public Dune::RandomAccessIteratorFacade<GenericIterator<C,T>,T, T&, D>
  {
    friend class GenericIterator<typename Dune::RemoveConst<C>::Type, typename Dune::RemoveConst<T>::Type >;
    friend class GenericIterator<const typename Dune::RemoveConst<C>::Type, const typename Dune::RemoveConst<T>::Type >;

  public:

    /**
     * @brief The type of container we are an iterator for.
     *
     * The container type must provide a operator[] method.
     *
     * If C has a const qualifier we are a const iterator, otherwise we
     * are a mutable iterator.
     */
    typedef C Container;

    /**
     * @brief The value type of the iterator.
     *
     * This is the return type of the iterator returned when derefencing.
     */
    typedef T Value;

    /**
     *
       /**
     * @brief The type of the difference between two positions.
     */
    typedef D DifferenceType;

    // Constructors needed by the base iterators.
    GenericIterator() : container_(0), position_(0)
    {}

    /**
     * @brief Constructor.
     * @param cont Reference to the container we are an iterator for.
     * @param pos The postion the Iterator will be positioned to.
     * (e. g. 0 for an iterator return by Container::begin() or
     * the sizeof the container for an iterator returned by Container::end()
     */
    GenericIterator(Container& cont, DifferenceType pos)
      : container_(&cont), position_(pos)
    {}

    /**
     * @brief Copy constructor.
     *
     * This is somehow hard to understand, therefore play with the cases:
     * 1. if we are mutable this is the only valid copy constructor, as the arguments is a mutable iterator
     * 2. if we are a const iterator the argument is a mutable iterator => This is the needed conversion to initialize a const iterator form a mutable one.
     */
    GenericIterator(const GenericIterator<typename Dune::RemoveConst<Container>::Type, typename Dune::RemoveConst<T>::Type >& other) : container_(other.container_), position_(other.position_)
    {}

    /**
     * @brief Copy constructor
     *
     * @warning Calling this method results in a compiler error, if this is a mutable iterator.
     *
     * This is somehow hard to understand, therefore play with the cases:
     * 1. if we are mutable the arguments is a const iterator and therefore calling this method is mistake in the users code and results in a (probably not understandable compiler error
     * 2. If we are a const iterator this is the default copy constructor as the argument is a const iterator too.
     */
    GenericIterator(const GenericIterator<const typename Dune::RemoveConst<Container>::Type, const typename Dune::RemoveConst<T>::Type >& other) : container_(other.container_), position_(other.position_)
    {}

    // Methods needed by the forward iterator
    bool equals(const GenericIterator<typename Dune::RemoveConst<Container>::Type,typename Dune::RemoveConst<T>::Type>& other) const
    {
      return position_ == other.position_ && container_ == other.container_;
    }


    bool equals(const GenericIterator<const typename Dune::RemoveConst<Container>::Type,const typename Dune::RemoveConst<T>::Type>& other) const
    {
      return position_ == other.position_ && container_ == other.container_;
    }

    T& dereference() const {
      return container_->operator[](position_);
    }

    void increment(){
      ++position_;
    }

    // Additional function needed by BidirectionalIterator
    void decrement(){
      --position_;
    }

    // Additional function needed by RandomAccessIterator
    T& elementAt(DifferenceType i) const {
      return container_->operator[](position_+i);
    }

    void advance(DifferenceType n){
      position_=position_+n;
    }

    std::ptrdiff_t distanceTo(GenericIterator<const typename Dune::RemoveConst<Container>::Type,const typename Dune::RemoveConst<T>::Type> other) const
    {
      assert(other.container_==container_);
      return other.position_ - position_;
    }

    std::ptrdiff_t distanceTo(GenericIterator<typename Dune::RemoveConst<Container>::Type, typename Dune::RemoveConst<T>::Type> other) const
    {
      assert(other.container_==container_);
      return other.position_ - position_;
    }
  private:
    Container *container_;
    DifferenceType position_;
  };

  /** @} */

} // end namespace Dune

#endif
