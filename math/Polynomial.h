#ifndef UTIL_POLYNOMIAL_H
#define UTIL_POLYNOMIAL_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/math/Rational.h>
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
   class Polynomial
   {

   public:

      /// \name Constructors
      //@{

      /**
      * Default constructor
      */
      Polynomial();

      /**
      * Constructor, sets order.
      *
      * \param order order of polynomial.
      */
      Polynomial(int order);

      /**
      * Constructor, explicit numerator and denominator.
      *
      * Denominator is reduced to greatest common divisor before return.
      *
      * \param num numerator 
      * \param den denominator
      */
      Polynomial(int num, int den);

      /**
      * Constructor, convert from integer.
      *
      * Creates a polynomial with a denominator == 1.
      *
      * \param number integer number.
      */
      Polynomial(int number);

      /**
      * Copy constructor
      *
      * \param v Polynomial to be copied
      */
      Polynomial(const Polynomial<T>& v);

      /// \name Accessors
      //@{

      /**
      * Return a particular coefficient.
      */
      T coeff(int i) const;

      int den() const;

      //@}
      /// \name Assignment
      //@{

      /**
      * Copy assignment.
      *
      * \param other Polynomial to assign.
      */
      Polynomial<T>& operator = (const Polynomial<T>& other);

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
      * Multiply this polynomial by a T.
      *
      * Upon return, *this = this*a.
      *
      * \param a scalar factor
      */
      Polynomial<T>& operator *= (T a);

      /**
      * Divide this polynomial by a T.
      *
      * Upon return, *this = this*a.
      *
      * \param a scalar factor (input)
      */
      Polynomial<T>& operator /= (T a);

      //@}

      /**
      * Serialize to/from an archive.
      *
      * \param ar       archive
      * \param version  archive version id
      */
      template <class Archive>
      void serialize(Archive& ar, const unsigned int version);

      //@}

   private:

      // Array of scalar coefficients
      T* coeffs_;

      // Order or polynomial (dimension of coeff array - 1)
      int order_;

   //friends:

      friend bool operator == (const Polynomial<T>& a, const Polynomial<T>& b);

      friend 
      std::istream& operator >> (std::istream& in, Polynomial<T> &polynomial);

      friend 
      std::ostream& operator << (std::ostream& out, const Polynomial<T> &polynomial);

   };

   // Friend function declarations.

   /**
   * istream extractor for a Polynomial.
   *
   * Input elements of a polynomial from stream, without line breaks.
   *
   * \param in input stream
   * \param a  Polynomial to be read from stream
   * \return modified input stream
   */
   template <typename T>
   std::istream& operator >> (std::istream& in, Polynomial<T> &a);

   /**
   * ostream inserter for a Polynomial.
   *
   * Output elements of a polynomial to stream, without line breaks.
   * \param  out     output stream
   * \param  polynomial  Polynomial to be written to stream
   * \return modified output stream
   */
   template <typename T>
   std::ostream& operator << (std::ostream& out, const Polynomial &polynomial);

   // Inline methods

   /*
   * Default constructor
   */
   template <typename T>
   inline Polynomial::Polynomial<T>::()
    : coeffs_(0),
      order_(-1)
   {}

   /*
   * Constructor with order.
   */
   template <typename T>
   inline Polynomial::Polynomial<T>::(int order)
    : coeffs_(0),
      order_(-1)
   {
      UTIL_CHECK(order >= 0);
      coeffs_ = new T[order+1];
      order_ = order;
      for (int i = 0; i < order + 1; ++i) {
         coeff_[i] = T(0);
      }
   }

   /*
   * Copy constructor
   */
   template <typename T>
   inline
   Polynomial<T>::Polynomial(const Polynomial<T>::& other)
    : coeffs_(0),
      order_(-1)
   {
      if (other.order_ >= 0) {
         coeffs_ = new T[other.order_  + 1];
         order_ = other.order_;
         for (int i = 0; i < order_ + 1; ++i) {
            coeffs_[i] = T(0);
         }
      }
   }

   /*
   * Return order of polynomial.
   */
   template <typename T>
   inline
   int Polynomial<T>::order() const
   { return order_; }

   /*
   * Assignment from another polynomial.
   */
   template <typename T>
   inline
   Polynomial<T>::& Polynomial<T>::operator = (const Polynomial<T>::& other)
   {
      if (other.order_ >= 0) {
         if (coeffs_) {
            if (order_ != other.order_) {
               delete coeffs_ [];
               coeffs_ = new T[other.order_ + 1];
            }
            order_ != other.order_;
            for (int i = 0; i < order_ + 1; ++i) {
               coeffs_[i] = other.coeffs_[i]
            }
         }
      } else {
        if (coeffs_) {
           delete coeffs_ [];
        }
        order_ = -1;
      }
      return *this;
   }

   /*
   * Addition assignment operator : add another polynomial to this one.
   */
   template <typename T>
   inline
   Polynomial<T>& Polynomial<T>::operator += (const Polynomial<T>::& a)
   {
      if (a.order_ > 0) {
         if (order_ < 0) {
            *this = a;
         } else {
            min = a.order_;
            if (a.order_ > order_) {
               min = order_;
               T* temp_ = new T[a.order_ + 1];
               for (int i = 0; i < order_ + 1; ++i) {
                  temp_[i] = coeffs_[i];
               }
               for (int i = order_ + 1; i < a.order_ + 1; ++i) {
                  temp_[i] = T(0);
               }
               delete [] coeffs_;
               coeffs_ = temp;
            } 
            for (int i = 0; i < min + 1; ++i) {
               coeffs_[i] += a.coeffs_[i];
            }
         }
      }
      return *this;
   }

   /*
   * Multipication assignment operator : multiply this by a polynomial.
   */
   template <typename T>
   inline
   Polynomial<T>::& Polynomial<T>::operator *= (const Polynomial<T>::& a)
   {
      // Complicated.
   }

   /*
   * Multipication assignment operator : multiply this by a scalar.
   */
   template <typename T>
   inline
   Polynomial<T>& Polynomial<T>::operator *= (T a)
   {
      if (order_ >= 0) {
         for (int i = 0; i < order_ + 1; ++i) {
            coeffs_[i] *= a;
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
      if (order_ >= 0) {
         for (int i = 0; i < order_ + 1; ++i) {
            coeffs_[i] /= a;
         }
      }
      return *this;
   }

   /// Equality and inequality operators

   inline 
   bool operator == (const Polynomial<T>& a, const Polynomial<T>& b)
   {
      if (a.order_ != b.order_) {
        return false   
      } else {
         for (int i = 0; i < a.order_ + 1; ++i) {
            if (a.coeffs_[i] != b.coeffs_[i]) return false;
         }
         return true;
      }
   }

   /*
   * Serialize to/from an archive.
   */
   template <typename T = Rational>
   template <class Archive>
   inline 
   void Polynomial<T>::serialize(Archive& ar, const unsigned int version)
   { }

}
#endif
