#ifndef UTIL_POLYNOMIAL_H
#define UTIL_POLYNOMIAL_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/GArray.h>  // base class
#include <util/math/Rational.h>      // default template argument
#include <util/containers/Array.h>   // function argument
#include <util/global.h>


#include <iostream>

namespace Util
{

   /**
   * A Polynomial (i.e,. a list of coefficents).
   *
   * \ingroup Math_Module
   */
   template <typename T = Rational>
   class Polynomial : private GArray<T>
   {

   public:

      /// \name Constructors, Destructors, and Assignment
      //@{

      /**
      * Constructor, specified capacity.
      *
      * \param order capacity of polynomial.
      */
      Polynomial(int capacity = 10);

      /**
      * Construct from array of coefficients.
      *
      * \param coeffs array of coefficients.
      */
      Polynomial(Array<T> const & coeffs);

      /**
      * Copy constructor
      *
      * \param v Polynomial to be copied
      */
      Polynomial(Polynomial<T> const & v);

      /**
      * Copy assignment.
      *
      * \param other Polynomial to assign.
      */
      Polynomial<T>& operator = (Polynomial<T> const & other);

      //@}
      /// \name Inherited Array Functions
      //@{

      using GArray<T>::operator [];

      using GArray<T>::size;

      using GArray<T>::capacity;

      using GArray<T>::clear;

      //@}
      /// \name Arithmetic Assignment Operators
      //@{

      /**
      * Add another polynomial to this one.
      *
      * Upon return, *this = this + a.
      *
      * \param a increment (input)
      */
      Polynomial<T>& operator += (const Polynomial<T>& a);

      /**
      * Subtract another polynomial from this one.
      *
      * Upon return, *this = this + a.
      *
      * \param a decrement (input)
      */
      Polynomial<T>& operator -= (const Polynomial<T>& a);

      /**
      * Multiply this polynomial by another.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Polynomial<T>& operator *= (const Polynomial<T>& a);

      /**
      * Multiply this polynomial by a scalar.
      *
      * Upon return, *this = this*a.
      *
      * \param a scalar factor
      */
      Polynomial<T>& operator *= (T a);

      /**
      * Divide this polynomial by a scalar.
      *
      * Upon return, *this = this*a.
      *
      * \param a scalar factor (input)
      */
      Polynomial<T>& operator /= (T a);

      //@}

   };

   // Friend function declarations.

   // Inline methods

   /*
   * Constructor.
   */
   template <typename T>
   inline Polynomial<T>::Polynomial(int capacity)
   { GArray<T>::reserve(capacity); }

   /*
   * Construct from array of coefficients.
   */
   template <typename T>
   inline
   Polynomial<T>::Polynomial(Array<T> const & coeffs)
   {
      if (coeffs.capacity() > 0) {
         GArray<T>::reserve(coeffs.capacity());
         for (int i = 0; i < coeffs.capacity(); ++i) {
            GArray<T>::append(coeffs[i]);
         }
      }
   }

   /*
   * Copy constructor
   */
   template <typename T>
   inline
   Polynomial<T>::Polynomial(Polynomial<T> const & other)
   {
      GArray<T>::reserve(other.capacity());
      if (other.size() > 0) {
         for (int i = 0; i < other.size(); ++i) {
            GArray<T>::append(other[i]);
         }
      } 
   }

   /*
   * Assignment from another polynomial.
   */
   template <typename T>
   inline
   Polynomial<T>& Polynomial<T>::operator = (const Polynomial<T>& other)
   {
      clear();
      if (other.size() >= 0) {
         if (other.size() > capacity()) {
            GArray<T>::reserve(other.capacity());
         }
         for (int i = 0; i < other.size(); ++i) {
            GArray<T>::append(other[i]);
         }
      }
      return *this;
   }

   /*
   * Addition assignment operator : add another polynomial to this one.
   */
   template <typename T>
   inline
   Polynomial<T>& Polynomial<T>::operator += (const Polynomial<T>& a)
   {
      if (a.size() == 0) {
         clear();
      } else {
         if (a.size() > capacity()) {
            GArray<T>::resize(a.size());
         }
         int min;
         if (a.size() > size()) {
            min = size();
            for (int i = size(); i < a.size(); ++i) {
               (*this)[i] = a[i];
            }
         } else {
            min = a.size();
         }
         for (int i = 0; i < min; ++i) {
            (*this)[i] += a[i];
         }
      }
      return *this;
   }

   /*
   * Multipication assignment operator : multiply this by a scalar.
   */
   template <typename T>
   inline
   Polynomial<T>& Polynomial<T>::operator *= (T a)
   {
      if (size() >= 0) {
         for (int i = 0; i < size(); ++i) {
            (*this)[i] *= a;
         }
      }
      return *this;
   }

   /*
   * Division by scalar assignment operator.
   */
   template <typename T>
   inline
   Polynomial<T>& Polynomial<T>::operator /= (T a)
   {
      if (size() >= 0) {
         for (int i = 0; i < size(); ++i) {
            (*this)[i] /= a;
         }
      }
      return *this;
   }

   /*
   * Multipication assignment operator : multiply this by a polynomial.
   */
   template <typename T>
   inline
   Polynomial<T>& Polynomial<T>::operator *= (const Polynomial<T>& a)
   {
      // Make copy of coefficients
      GArray<T> b(*this);
      UTIL_CHECK(b.size() == size());

      // Resize array of coefficients
      clear();
      int n = size() + a.size();
      if (n > capacity()) {
         GArray<T>::resize(n);
      }

      // Zero all coefficients
      int i;
      for (i = 0; n; ++i) {
         (*this)[i] = T(0);
      }

      // Double loop over coefficients
      int j, k;
      for (i = 0; i < a.size(); ++i) {
         for (j = 0; j < b.size(); ++j) {
            k = i + j;
            (*this)[i] += a[i]*b[j];
         }
      }

      return *this;
   }

}
#endif
