#ifndef UTIL_RATIONAL_H
#define UTIL_RATIONAL_H

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
   * A Rational number (a ratio of integers).
   *
   * \ingroup Math_Module
   */
   class Rational
   {

   public:

      /// \name Constructors
      //@{

      /**
      * Default constructor
      */
      Rational();

      /**
      * Constructor, explicit numerator and denominator.
      *
      * Denominator is reduced to greatest common divisor before return.
      *
      * \param num numerator 
      * \param den denominator
      */
      Rational(int num, int den);

      /**
      * Constructor, convert from integer.
      *
      * Creates an integer using a denominator == 1.
      *
      * \param number integer number.
      */
      Rational(int number);

      /**
      * Copy constructor
      *
      * \param v Rational to be copied
      */
      Rational(const Rational& v);

      /**
      * Serialize to/from an archive.
      *
      * \param ar       archive
      * \param version  archive version id
      */
      template <class Archive>
      void serialize(Archive& ar, const unsigned int version);

      /// \name Assignment
      //@{

      /**
      * Copy assignment.
      *
      * \param other Rational to assign.
      */
      Rational& operator = (const Rational& other);

      /**
      * Assignment from integer.
      *
      * Creates an integer using a denominator == 1.
      *
      * \param other integer to assign.
      */
      Rational& operator = (int other);

      //@}
      /// \name Accessors
      //@{

      /**
      * Return numerator.
      */
      int num() const;

      /**
      * Return denominator.
      */
      int den() const;

      //@}

      /// \name Arithmetic Assignment
      //@{

      /**
      * Add another rational to this one.
      *
      * Upon return, *this = this + a.
      *
      * \param a increment (input)
      */
      Rational& operator += (const Rational& a);

      /**
      * Add another rational to this one.
      *
      * Upon return, *this = this + a.
      *
      * \param a increment (input)
      */
      Rational& operator -= (const Rational& a);

      /**
      * Multiply this rational by another.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Rational& operator *= (const Rational& a);

      /**
      * Divide this rational by another.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Rational& operator /= (const Rational& a);

      //@}

      #ifdef UTIL_MPI
      /**
      * Commit MPI datatype MpiTraits<Rational>::type.
      */
      static void commitMpiType();
      #endif

      //@}

   private:

      int num_;

      int den_;

      void reduce();

   //friends:

      friend 
      Rational operator + (const Rational& a, const Rational& b);

      friend 
      Rational operator - (const Rational& a, const Rational& b);

      friend 
      Rational operator * (const Rational& a, const Rational& b);

      friend 
      Rational operator / (const Rational& a, const Rational& b);

      friend 
      bool operator == (const Rational& a, const Rational& b);

      friend 
      bool operator == (const Rational& a, const double* b);

      friend 
      std::istream& operator >> (std::istream& in, Rational &rational);

      friend 
      std::ostream& operator << (std::ostream& out, const Rational &rational);

   };

   // Friend function declarations.

   /**
   * istream extractor for a Rational.
   *
   * Input elements of a rational from stream, without line breaks.
   *
   * \param in input stream
   * \param a  Rational to be read from stream
   * \return modified input stream
   */
   std::istream& operator >> (std::istream& in, Rational &a);

   /**
   * ostream inserter for a Rational.
   *
   * Output elements of a rational to stream, without line breaks.
   * \param  out     output stream
   * \param  rational  Rational to be written to stream
   * \return modified output stream
   */
   std::ostream& operator << (std::ostream& out, const Rational &rational);

   #ifdef UTIL_MPI
   /**
   * Explicit specialization MpiTraits<Rational>.
   */
   template <>
   class MpiTraits<Rational>
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
   Rational::Rational()
    : num_(0),
      den_(1)
   { reduce(); }

   /*
   * Constructor from numerator and denominator.
   */
   inline
   Rational::Rational(int num, int den)
    : num_(num),
      den_(den)
   { reduce(); }

   /*
   * Constructor from integer.
   */
   inline
   Rational::Rational(int number)
    : num_(number),
      den_(1)
   {}

   /*
   * Copy constructor
   */
   inline
   Rational::Rational(const Rational& other)
    : num_(other.num_),
      den_(other.den_)
   {}

   /*
   * Return numerator.
   */
   inline
   int Rational::num() const
   { return num_; }

   /*
   * Return denominator.
   */
   inline
   int Rational::den() const
   {  return den_; }

   /*
   * Assignment from another rational.
   */
   inline
   Rational& Rational::operator = (const Rational& other)
   {
      num_ = other.num_;
      den_ = other.den_;
      return *this;
   }

   /*
   * Assignment from integer.
   */
   inline
   Rational& Rational::operator = (int other)
   {
      num_ = other;
      den_ = 1;
      return *this;
   }

   /*
   * Addition assignment operator : add b to this.
   */
   inline
   Rational& Rational::operator += (const Rational& a)
   {
      num_ = num_*a.den_ + a.num_*den_;
      den_ = den_*a.den_;
      reduce();
      return *this;
   }

   /*
   * Subtraction assignment operator : subtract a from this.
   */
   inline
   Rational& Rational::operator -= (const Rational& a)
   {
      num_ = num_*a.den_ - a.num_*den_;
      den_ = den_*a.den_;
      reduce();
      return *this;
   }

   /*
   * Multipication assignment operator : multiply this by a.
   */
   inline
   Rational& Rational::operator *= (const Rational& a)
   {
      num_ = num_*a.num_;
      den_ = den_*a.den_;
      reduce();
      return *this;
   }

   /*
   * Division assignment operator : divide this by a.
   */
   inline
   Rational& Rational::operator /= (const Rational& a)
   {
      if (a.num_ == 0) {
         UTIL_THROW("Attempt to divide by zero Rational"); 
      }
      num_ = num_*a.den_;
      den_ = den_*a.num_;
      reduce();
      return *this;
   }

   /**
   * Compute sum of rationals a and b.
   *
   * \param a 1st argument
   * \param a 2st argument
   * \return sum a + b
   */
   inline
   Rational operator + (const Rational& a, const Rational& b)
   {
     int num = a.num_*b.den_ + b.num_*a.den_;
     int den = a.den_*b.den_;
     return Rational(num, den);
   }

   /**
   * Compute difference of rationals.
   *
   * \param a 1st argument
   * \param b 2st argument
   * \return difference a - b
   */
   inline
   Rational operator - (const Rational& a, const Rational& b)
   {
     int num = a.num_*b.den_ - b.num_*a.den_;
     int den = a.den_*b.den_;
     return Rational(num, den);
   }

   /**
   * Compute product of rationals.
   *
   * \param a 1st argument
   * \param b 2st argument
   * \return product a*b
   */
   inline
   Rational operator * (const Rational& a, const Rational& b)
   {
      int num = a.num_*b.num_;
      int den = a.den_*b.den_;
      return Rational(num, den);
   }

   /**
   * Compute quotient of two rationals.
   *
   * \param a 1st argument
   * \param b 2st argument
   * \return ratio a/b
   */
   inline
   Rational operator / (const Rational& a, const Rational& b)
   {
      if (b.num_ == 0) {
         UTIL_THROW("Attempt to divide by zero Rational"); 
      }
      int num = a.num_*b.den_;
      int den = a.den_*b.num_;
      return Rational(num, den);
   }

   /// Equality for Rationals.
   inline
   bool operator == (const Rational& a, const Rational& b)
   {  return ((a.num_ == b.num_) && (a.den_ == b.den_)); }

   /// Inequality of two Rationals.
   inline
   bool operator != (const Rational& a, const Rational& b)
   {  return !(a == b); }

   /*
   * Serialize to/from an archive.
   */
   template <class Archive>
   inline void Rational::serialize(Archive& ar, const unsigned int version)
   {
      ar & den_;
      ar & num_;
   }

   /*
   * Reduce denominator to greatest common divisor (private function).
   */
   inline
   void Rational::reduce ()
   {
      if (den_ < 0) {
         den_ *= -1;
         num_ *= -1;
      }
      int c = gcd(num_, den_);
      num_ /= c;
      den_ /= c;
   }

}
#endif
