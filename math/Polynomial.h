#ifndef UTIL_POLYNOMIAL_H
#define UTIL_POLYNOMIAL_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/GArray.h>  // base class
#include <util/containers/DArray.h>  // base class
#include <util/math/Rational.h>      // default template argument
#include <util/math/Binomial.h>      // default in implementation
#include <util/containers/DArray.h>  // used in implementation
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
      * Construct a zero polynomial.
      *
      * Creates a zero polynomial f(x) = 0, with logical size() = 0.
      * The capacity parameter specifies how much physical space to
      * allocate for subsqequent growth in the array of coefficients.
      *
      * \param capacity initial capacity of coefficient array.
      */
      Polynomial(int capacity = 10);

      /**
      * Construct a constant polynomial.
      *
      * Creates a polynomial f(x) = c, with logical size() = 1.
      *
      * \param c constant coefficient value
      */
      Polynomial(T c);

      /**
      * Construct a nonzero polynomial from array of coefficients.
      *
      * Constructs an polynomial in which the coefficient of x^{i} 
      * is given by coeffs[i]. The logical and physical size of the
      * coefficient array are both set to the capacity of coeffs.
      *
      * \param coeffs array of coefficients.
      */
      Polynomial(Array<T> const & coeffs);

      /**
      * Copy constructor
      *
      * \param other Polynomial to be copied
      */
      Polynomial(Polynomial<T> const & other);

      /**
      * Assignment from another polynomial.
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

      /**
      * Multiply this polynomial by another.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Polynomial<T>& operator *= (const Polynomial<T>& a);

      //@}
      /// \name Mathematical Functions (return related polynomials)
      //@{

      /**
      * Compute and return indefinite integral of this polynomial.
      *
      * Returns an indefinite integral with zero constant term.
      *
      * \return indefinite integral polynomial.
      */
      Polynomial<T> integrate() const;

      /**
      * Compute and return reflected polynomial f(-x).
      *
      * If this polynomial is f(x), this returns a polynomial g(x) = f(-x) 
      * created by the reflection operation x-> -x. This yields a
      * polynomial in which the sign is reversed for all coefficients
      * of odd powers of x.
      *
      * \return polynomial created by reflection x -> -x. 
      */
      Polynomial<T> reflect() const;

      /**
      * Compute and return shifted polynomial f(x+a).
      *
      * If this polynomial is f(x), this returns a polynomial g(x) = f(x+a) 
      * created by the shift operation x-> x + a. 
      *
      * \return polynomial created by shift operation x -> x + a.
      */
      Polynomial<T> shift(T a) const;

      //@}

      // Static member functions
      
      /**
      * Return a monomial f(x) = x^{n}.
      *
      * \param n power of x in monomial.
      */ 
      static Polynomial<T> monomial(int n);

   };

   // Friend function declarations.

   // Inline methods

   /*
   * Constructor.
   */
   template <typename T>
   inline 
   Polynomial<T>::Polynomial(int capacity)
   {  GArray<T>::reserve(capacity); }

   /*
   * Construct a constant polynomial f(x) = c.
   */
   template <typename T>
   inline
   Polynomial<T>::Polynomial(T c)
   {
      GArray<T>::reserve(10); 
      GArray<T>::append(c);
   }

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
   Polynomial<T>& Polynomial<T>::operator += (const Polynomial<T>& a)
   {
      if (a.size() == 0) {
         clear();
      } else {
         if (a.size() > capacity()) {
            GArray<T>::resize(a.size());
         }
         int min = a.size() > size() ? size() : a.size();
         if (min > 0) {
            for (int i = 0; i < min; ++i) {
               (*this)[i] += a[i];
            }
         }
         if (a.size() > size()) {
            for (int i = size(); i < a.size(); ++i) {
               (*this)[i] = a[i];
            }
         }
      }
      return *this;
   }

   /*
   * Subtract assignment operator : subtract another polynomial from this.
   */
   template <typename T>
   Polynomial<T>& Polynomial<T>::operator -= (const Polynomial<T>& a)
   {
      if (a.size() == 0) {
         clear();
      } else {
         if (a.size() > capacity()) {
            GArray<T>::resize(a.size());
         }
         int min = a.size() > size() ? size() : a.size();
         for (int i = 0; i < min; ++i) {
            (*this)[i] -= a[i];
         }
         if (a.size() > size()) {
            for (int i = size(); i < a.size(); ++i) {
               (*this)[i] = -a[i];
            }
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
   * Multiplication assignment operator : multiply this by a polynomial.
   */
   template <typename T>
   Polynomial<T>& Polynomial<T>::operator *= (const Polynomial<T>& a)
   {
      // If this polynomial is zero (size == 0), do nothing. Otherwise:
      if (size() > 0) {

         if (a.size() == 0) {
            // If polynomial a is zero, set this one to zero (clear it).
            clear();
         } else {

            // Compute size of new array of coefficients (order + 1)
            int n = size() + a.size() - 1;

            // Make a copy of coefficients of this polynomial
            GArray<T> b(*this);

            // Clear this array of coefficients and reserve enough space
            clear();
            if (n > capacity()) {
               GArray<T>::reserve(n);
            }

            // Set all coefficients of resized array to zero
            int i;
            T zero = 0;
            for (i = 0; i < n; ++i) {
               GArray<T>::append(zero);
            }

            // Compute new coefficients as a double sum
            int j, k;
            for (i = 0; i < a.size(); ++i) {
               for (j = 0; j < b.size(); ++j) {
                  k = i + j;
                  UTIL_ASSERT(k < n);
                  (*this)[k] += a[i]*b[j];
               }
            }

         }
      }
      return *this;
   }

   /*
   * Compute and return indefinite integral of this polynomial.
   */
   template <typename T>
   Polynomial<T> Polynomial<T>::integrate() const
   {
      // Construct and compute coefficient array for integral
      DArray<T> coeffs;
      coeffs.allocate(size()+1);
      coeffs[0] = T(0);
      for (int i = 0; i < size(); ++i) {
         coeffs[i+1] = (*this)[i];
         coeffs[i+1] /= T(i+1);
      }

      // Construct and return associated Polynomial
      Polynomial<T> b(coeffs);
      return b;
   }

   /*
   * Compute and return reflection g(x) = f(-x) this polynomial f(x).
   */
   template <typename T>
   Polynomial<T> Polynomial<T>::reflect() const
   {
      // Make copy
      Polynomial<T> b(*this);

      // Reverse odd power coefficients
      for (int i = 0; i < b.size(); ++i) {
         if (i%2 != 0) {
            b[i] *= -1;
         }
      }

      return b;
   }

   /*
   * Compute and return reflection g(x) = f(-x) this polynomial f(x).
   */
   template <typename T>
   Polynomial<T> Polynomial<T>::shift(T a) const
   {
      // Make copy of this
      Polynomial<T> b(*this);

      int order = size() - 1;
      if (order > 0) {
         Binomial::setup(order);
         int n, m;
         T p;
         for (n = 1; n <= order; ++n) {
            p = b[n]*a;
            for (m = 1; m <= n; ++m) {
               b[n -m] += Binomial::coeff(n, m)*p;
               p *= a;
            }
         }
      }

      return b;
   }
   // Static function

   // Static function

   /**
   * Return a monomial.
   */
   template <typename T>
   Polynomial<T> Polynomial<T>::monomial(int power)
   {
      UTIL_CHECK(power >= 0);
      Polynomial<T> a(power+1);

      // Append zero coefficients.
      T zero(0);
      for (int i = 0; i <= power; ++i) {
         a.GArray<T>::append(zero);
      }

      // Set coefficient of highest power to unity
      a[power] = T(1);

      return a;
   }

   // Related non-member functions

   /**
   * Equality operator for polynomials.
   *
   * Two polynomials are equal iff they have the same order (size)
   * and the same values for all coefficients.
   *
   * \param a 1st polynomial
   * \param b 2nd polynomial
   * \return true if a != b
   */
   template <typename T>
   bool operator == (Polynomial<T>& a, Polynomial<T>& b)
   {
      if (a.size() != b.size()) return false;
      if (a.size() > 0) {
         for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) return false;
         }
      }
      return true;
   }

   /**
   * Inequality operator for polynomials.
   *
   * \param a 1st polynomial
   * \param b 2nd polynomial
   * \return true if a != b
   */
   template <typename T>
   bool operator != (Polynomial<T>& a, Polynomial<T>& b)
   {  return !(a == b); }

   /**
   * Unary negation of polynomial.
   *
   * \param a input polynomial
   * \return negated polynomial -a
   */
   template <typename T>
   inline
   Polynomial<T> operator - (Polynomial<T> const & a)
   {
      Polynomial<T> b(a);
      if (a.size() > 0) {
         for (int i = 0; i < a.size(); ++i) {
           b[i] *= -1;
         }
      }
      return b;
   }

}
#endif
