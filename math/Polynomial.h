#ifndef UTIL_POLYNOMIAL_H
#define UTIL_POLYNOMIAL_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "gcd.h"
#include <util/global.h>

#ifdef UTIL_MPI
#include <util/mpi/MpiTraits.h>
#endif

#include <iostream>

namespace Util
{

   /**
   * A Polynomial (i.e,. a list of coefficents).
   *
   * \ingroup Math_Module
   */
   template <typename Scalar>
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
      Polynomial(const Polynomial& v);

      /// \name Accessors
      //@{

      /**
      * Return a particular coefficient.
      */
      Scalar coeff(int i) const;

      int den() const;

      //@}
      /// \name Assignment
      //@{

      /**
      * Copy assignment.
      *
      * \param other Polynomial to assign.
      */
      Polynomial& operator = (const Polynomial& other);

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
      Polynomial& operator += (const Polynomial& a);

      /**
      * Subtract another polynomial from this one.
      *
      * Upon return, *this = this + a.
      *
      * \param a decrement (input)
      */
      Polynomial& operator -= (const Polynomial& a);

      /**
      * Multiply this polynomial by another.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Polynomial& operator *= (const Polynomial& a);

      /**
      * Multiply this polynomial by a Scalar.
      *
      * Upon return, *this = this*a.
      *
      * \param a scalar factor
      */
      Polynomial& operator *= (Scalar a);

      /**
      * Divide this polynomial by a Scalar.
      *
      * Upon return, *this = this*a.
      *
      * \param a scalar factor (input)
      */
      Polynomial& operator /= (Scalar a);

      //@}

      /**
      * Serialize to/from an archive.
      *
      * \param ar       archive
      * \param version  archive version id
      */
      template <class Archive>
      void serialize(Archive& ar, const unsigned int version);

      #ifdef UTIL_MPI
      /**
      * Commit MPI datatype MpiTraits<Polynomial>::type.
      */
      static void commitMpiType();
      #endif

      //@}

   private:

      DArray<Scalar> coeffs_;

      int order_;

   //friends:

      friend Polynomial operator + (const Polynomial& a, const Polynomial& b);
      friend Polynomial operator - (const Polynomial& a, const Polynomial& b);
      friend Polynomial operator * (const Polynomial& a, const Polynomial& b);
      friend Polynomial operator * (const Polynomial& a, int b);
      friend Polynomial operator / (const Polynomial& a, int b);

      friend bool operator == (const Polynomial& a, const Polynomial& b);

      friend 
      std::istream& operator >> (std::istream& in, Polynomial &polynomial);

      friend 
      std::ostream& operator << (std::ostream& out, const Polynomial &polynomial);

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
   std::istream& operator >> (std::istream& in, Polynomial &a);

   /**
   * ostream inserter for a Polynomial.
   *
   * Output elements of a polynomial to stream, without line breaks.
   * \param  out     output stream
   * \param  polynomial  Polynomial to be written to stream
   * \return modified output stream
   */
   std::ostream& operator << (std::ostream& out, const Polynomial &polynomial);

   #ifdef UTIL_MPI
   /**
   * Explicit specialization MpiTraits<Polynomial>.
   */
   template <>
   class MpiTraits<Polynomial>
   {
   public:
      static MPI::Datatype type;   ///< MPI Datatype
      static bool hasType;         ///< Is the MPI type initialized?
   };
   #endif

   // Inline methods

   /*
   * Default constructor
   */
   inline
   Polynomial::Polynomial()
    : num_(0),
      den_(1)
   { reduce(); }

   /*
   * Constructor from numerator and denominator.
   */
   inline
   Polynomial::Polynomial(int num, int den)
    : num_(num),
      den_(den)
   { reduce(); }

   /*
   * Constructor from integer.
   */
   inline
   Polynomial::Polynomial(int number)
    : num_(number),
      den_(1)
   {}

   /*
   * Copy constructor
   */
   inline
   Polynomial::Polynomial(const Polynomial& other)
    : num_(other.num_),
      den_(other.den_)
   {}

   /*
   * Return numerator.
   */
   inline
   int Polynomial::num() const
   { return num_; }

   /*
   * Return denominator.
   */
   inline
   int Polynomial::den() const
   {  return den_; }

   /*
   * Assignment from another polynomial.
   */
   inline
   Polynomial& Polynomial::operator = (const Polynomial& other)
   {
      num_ = other.num_;
      den_ = other.den_;
      return *this;
   }

   /*
   * Assignment from integer.
   */
   inline
   Polynomial& Polynomial::operator = (int other)
   {
      num_ = other;
      den_ = 1;
      return *this;
   }

   /*
   * Addition assignment operator : add b to this.
   */
   inline
   Polynomial& Polynomial::operator += (const Polynomial& a)
   {
      num_ = num_*a.den_ + a.num_*den_;
      den_ = den_*a.den_;
      reduce();
      return *this;
   }

   /*
   * Addition assignment operator : add integer to this.
   */
   inline
   Polynomial& Polynomial::operator += (int a)
   {
      num_ += a*den_;
      reduce();
      return *this;
   }

   /*
   * Subtraction assignment operator : subtract a from this.
   */
   inline
   Polynomial& Polynomial::operator -= (const Polynomial& a)
   {
      num_ = num_*a.den_ - a.num_*den_;
      den_ = den_*a.den_;
      reduce();
      return *this;
   }

   /*
   * Subtraction assignment operator : subtract integer from this.
   */
   inline
   Polynomial& Polynomial::operator -= (int a)
   {
      num_ -= a*den_;
      reduce();
      return *this;
   }

   /*
   * Multipication assignment operator : multiply this by a.
   */
   inline
   Polynomial& Polynomial::operator *= (const Polynomial& a)
   {
      num_ *= a.num_;
      den_ *= a.den_;
      reduce();
      return *this;
   }

   /*
   * Multipication assignment operator : multiply this by a.
   */
   inline
   Polynomial& Polynomial::operator *= (int a)
   {
      num_ *= a;
      reduce();
      return *this;
   }

   /*
   * Division assignment operator : divide this by polynomial.
   */
   inline
   Polynomial& Polynomial::operator /= (const Polynomial& a)
   {
      if (a.num_ == 0) {
         UTIL_THROW("Attempt to divide by zero Polynomial"); 
      }
      num_ = num_*a.den_;
      den_ = den_*a.num_;
      reduce();
      return *this;
   }

   /*
   * Division assignment operator : divide this by polynomial.
   */
   inline
   Polynomial& Polynomial::operator /= (int a)
   {
      if (a == 0) {
         UTIL_THROW("Attempt to divide Polynomial by zero integer"); 
      }
      den_ *= a;
      reduce();
      return *this;
   }

   // Friend functions for binary arithmetic operations

   /**
   * Compute sum of two polynomials.
   *
   * \param a 1st polynomials.
   * \param a 2st polynomials.
   * \return sum a + b
   */
   inline
   Polynomial operator + (const Polynomial& a, const Polynomial& b)
   {
   }

   /**
   * Compute difference of polynomials.
   *
   * \param a 1st polynomial
   * \param b 2st polynomial
   * \return difference a - b
   */
   inline
   Polynomial operator - (const Polynomial& a, const Polynomial& b)
   {
   }

   /**
   * Compute product of polynomials.
   *
   * \param a 1st argument
   * \param b 2st argument
   * \return product a*b
   */
   inline
   Polynomial operator * (const Polynomial& a, const Polynomial& b)
   {
   }

   /**
   * Compute product of polynomial and scalar.
   *
   * \param a Polynomial argument
   * \param b scalar argument
   * \return product a*b
   */
   inline
   Polynomial operator * (const Polynomial& a, Scalar b)
   {
   }

   /**
   * Compute product of scalar and a polynomial.
   *
   * \param b scalar argument
   * \param a Polynomial argument
   * \return product b*a
   */
   inline
   Polynomial operator * (Scalar b, const Polynomial& a)
   { return a*b; }

   /**
   * Compute quotient Polynomial divided by integer.
   *
   * \param a Polynomial argument
   * \param b scalar argument
   * \return ratio a/b
   */
   inline
   Polynomial operator / (const Polynomial& a, Scalar b)
   {}

   /// Equality and inequality operators

   inline 
   bool operator == (const Polynomial& a, const Polynomial& b)
   {}

   inline bool operator != (const Polynomial& a, const Polynomial& b)
   {  return !(a == b); }

   /*
   * Serialize to/from an archive.
   */
   template <class Archive>
   inline void Polynomial::serialize(Archive& ar, const unsigned int version)
   { }

}
#endif
