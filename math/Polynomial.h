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
      * Creates a zero polynomial f(x) = 0, with no stored coefficients.
      * The capacity parameter specifies how much physical space to
      * allocate for subsqequent growth in the array of coefficients.
      *
      * \param capacity initial capacity of coefficient array.
      */
      Polynomial(int capacity = 10);

      /**
      * Construct a constant polynomial.
      *
      * Creates a polynomial f(x) = c, with degree() = 0.
      *
      * \param c constant coefficient value
      */
      explicit Polynomial(T c);

      /**
      * Construct a polynomial from array of coefficients.
      *
      * Constructs a polynomial in which the coefficient of x^{i} 
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
      template <typename U>
      Polynomial<T>& operator = (Polynomial<U> const & other);

      /**
      * Assign this polynomial a value of zero.
      *
      * Equivalent to GArray::clear(): Clears all coefficients, setting 
      * size = 0 and degree = -1.
      */
      void setToZero();

      //@}
      /// \name Simple Accessors
      //@{

      // Get a specific coefficient by index.
      using GArray<T>::operator [];

      /**
      * Return degree of polynomial.
      *
      * Returns size() - 1, number of coefficients - 1.
      * By convention, a zero polynomial has degree = -1.
      */
      int degree() const;

      // Logical size of the coefficient array.
      using GArray<T>::size;

      // Physical capacity of the coefficient array.
      using GArray<T>::capacity;

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
      * Add a constant to this polynomial.
      *
      * Upon return, *this = this + a.
      *
      * \param a increment (input)
      */
      Polynomial<T>& operator += (T a);

      /**
      * Subtract another polynomial from this one.
      *
      * Upon return, *this = this + a.
      *
      * \param a decrement (input)
      */
      Polynomial<T>& operator -= (const Polynomial<T>& a);

      /**
      * Subtract a constant from this polynomial.
      *
      * Upon return, *this = this + a.
      *
      * \param a increment (input)
      */
      Polynomial<T>& operator -= (T a);

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
      /// \name Mathematical Functions (return polynomials)
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
      * Compute and return derivative of this polynomial.
      *
      * Returns a polynomial of one smaller degree.
      *
      * \return derivative polynomial
      */
      Polynomial<T> differentiate() const;

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
      /// \name Polynomial Evaluation Functions
      //@{ 

      /**
      * Evaluate polynomial at specific argument of type T.
      *
      * \param x value of argument 
      * \return Value f(x) of this polynomial at specified x
      */
      T operator () (T x) const;

      /**
      * Evaluate polynomial at specific floating point argument.
      *
      * \param x value of argument x
      * \return Value f(x) of polynomial at specified x
      */
      double evaluate (double x) const;

      //@}

      // Static public member functions
      
      /**
      * Return a monomial f(x) = x^{n}.
      *
      * \param n power of x in monomial.
      */ 
      static Polynomial<T> monomial(int n);

   };

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
   template <typename U>
   inline
   Polynomial<T>& Polynomial<T>::operator = (const Polynomial<U>& other)
   {
      setToZero();
      if (other.size() >= 0) {
         if (other.size() > capacity()) {
            GArray<T>::reserve(other.capacity());
         }
         T element;
         for (int i = 0; i < other.size(); ++i) {
            element = other[i];
            GArray<T>::append(element);
         }
      }
      return *this;
   }

   /*
   * Set this polynomial to zero.
   */
   template <typename T>
   inline 
   void Polynomial<T>::setToZero()
   {  GArray<T>::clear(); }

   /*
   * Return degree of polynomial (size of coeff. array - 1).
   */
   template <typename T>
   inline
   int Polynomial<T>::degree() const
   {  return GArray<T>::size() - 1; }

   /*
   * Addition assignment operator : add another polynomial to this one.
   */
   template <typename T>
   Polynomial<T>& Polynomial<T>::operator += (const Polynomial<T>& a)
   {
      if (a.size() > 0) {
         int min = a.size() > size() ? size() : a.size();
         if (min > 0) {
            for (int i = 0; i < min; ++i) {
               (*this)[i] += a[i];
            }
         }
         if (a.size() > size()) {
            UTIL_CHECK(min == size());
            for (int i = size(); i < a.size(); ++i) {
               GArray<T>::append(a[i]);
            }
         }
      }
      return *this;
   }

   /*
   * Add a constant to this polynomial.
   */
   template <typename T>
   Polynomial<T>& Polynomial<T>::operator += (T a)
   {
      if (size() == 0) {
         (*this).append(a);
      } else {
         (*this)[0] += a;
      }
      return *this;
   }

   /*
   * Subtract assignment operator : subtract another polynomial from this.
   */
   template <typename T>
   Polynomial<T>& Polynomial<T>::operator -= (const Polynomial<T>& a)
   {
      if (a.size() > 0) {
         int min = a.size() > size() ? size() : a.size();
         if (min > 0) {
            for (int i = 0; i < min; ++i) {
               (*this)[i] -= a[i];
            }
         }
         if (a.size() > size()) {
            UTIL_CHECK(min == size());
            for (int i = size(); i < a.size(); ++i) {
               GArray<T>::append(-a[i]);
            }
         }
      }
      return *this;
   }

   /*
   * Subtract a constant from this polynomial.
   */
   template <typename T>
   Polynomial<T>& Polynomial<T>::operator -= (T a)
   {
      if (size() == 0) {
         (*this).append(-a);
      } else {
         (*this)[0] -= a;
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
            setToZero();
         } else {

            // Compute size of new array of coefficients (degree + 1)
            int n = size() + a.size() - 1;

            // Make a copy of coefficients of this polynomial
            GArray<T> b(*this);

            // Clear this array of coefficients and reserve enough space
            setToZero();
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
      if (size() == 0) {
         Polynomial<T> b;
         b.setToZero();
         return b;
      } else {
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
   }

   /*
   * Compute and return the derivatvie of this polynomial.
   */
   template <typename T>
   Polynomial<T> Polynomial<T>::differentiate() const
   {
      if (size() <= 1) {

         // If this polynomial is null or constant, return null
         Polynomial<T> b;
         b.setToZero();
         return b;

      } else {

         // Construct coefficient array for derivative polynomial
         DArray<T> coeffs;
         coeffs.allocate(size()-1);
         for (int i = 1; i < size(); ++i) {
            coeffs[i-1] = (*this)[i];
            coeffs[i-1] *= T(i);
         }

         // Construct and return associated Polynomial
         Polynomial<T> b(coeffs);
         return b;
      }
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

      int degree = size() - 1;
      if (degree > 0) {
         Binomial::setup(degree);
         int n, m;
         T p;
         for (n = 1; n <= degree; ++n) {
            p = b[n]*a;
            for (m = 1; m <= n; ++m) {
               b[n -m] += Binomial::coeff(n, m)*p;
               p *= a;
            }
         }
      }

      return b;
   }

   /*
   * Evaluate polynomial at specific argument.
   */
   template <typename T>
   inline T Polynomial<T>::operator () (T x) const
   { 
      if (size() > 0) {
         int degree = size() - 1;
         T value = (*this)[degree];
         if (degree > 0) {
            for (int i = degree-1; i >= 0; --i) {
              value *= x;
              value += (*this)[i];
            }
         }
         return value;
      } else {
         return T(0);
      }
   }

   /*
   * Evaluate polynomial at specific floating point argument.
   */
   template <typename T>
   inline double Polynomial<T>::evaluate (double x) const
   {
      if (size() > 0) {
         int degree = size()-1;
         double value = (double)(*this)[degree];
         if (degree > 0) {
            for (int i = degree-1; i >= 0; --i) {
              value *= x;
              value += (double)(*this)[i];
            }
         }
         return value;
      } else {
         return 0.0;
      }
   }

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
   * Two polynomials are equal iff they have the same degree and the
   * the same values for all coefficients.
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

   template <typename T>
   std::ostream& operator << (std::ostream& out, Polynomial<T> const & p)
   {
      out << "(";
      if (p.size() > 0) {
         for (int i = 0; i < p.size(); ++i) {
            out << p[i] << " ";
         }
      }
      out << ")";
      return out;
   }
}
#endif
