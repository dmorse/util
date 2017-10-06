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
   * A rational is always stored in a standard reduced form in which the
   * denominator is a positive integer and the numerator and denominator
   * have no common divisors other than unity.  All integers, including
   * zero, are stored with a denominator of 1.
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
      * Constructor, construct from integer.
      *
      * Creates a rational with a denominator == 1.
      *
      * \param number integer number.
      */
      Rational(int number);

      /**
      * Copy constructor
      *
      * \param v Rational to be copied
      */
      Rational(Rational const & v);

      /**
      * Destructor.
      */
      ~Rational()
      {}

      /// \name Assignment and Conversion.
      //@{

      /**
      * Copy assignment from another Rational.
      *
      * \param other Rational to assign.
      */
      Rational & operator = (Rational const & other);

      /**
      * Assignment from integer.
      *
      * Creates an integer using a denominator == 1.
      *
      * \param other integer to assign.
      */
      Rational & operator = (int other);

      //@}
      /// \name Arithmetic Assignment Operators
      //@{

      /**
      * Add another rational to this one.
      *
      * Upon return, *this = this + a.
      *
      * \param a increment (input)
      */
      Rational & operator += (Rational const & a);

      /**
      * Add an integer to this rational.
      *
      * Upon return, *this = this + a.
      *
      * \param a increment (input)
      */
      Rational & operator += (int a);

      /**
      * Subtract another rational from this one.
      *
      * Upon return, *this = this + a.
      *
      * \param a decrement (input)
      */
      Rational & operator -= (Rational const & a);

      /**
      * Subtract an integer from this rational.
      *
      * Upon return, *this = this + a.
      *
      * \param a decrement (input)
      */
      Rational & operator -= (int);

      /**
      * Multiply this rational by another.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Rational & operator *= (Rational const & a);

      /**
      * Multiply this rational by an integer.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Rational & operator *= (int a);

      /**
      * Divide this rational by another.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Rational & operator /= (Rational const & a);

      /**
      * Divide this rational by an integer.
      *
      * Upon return, *this = this*a.
      *
      * \param a increment (input)
      */
      Rational & operator /= (int a);

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

      /**
      * Cast (convert) to double precision floating point.
      *
      * \return double precision floating point representation of this.
      */
      operator double () const;

      //@}

      /**
      * Serialize to/from an archive.
      *
      * \param ar       archive
      * \param version  archive version id
      */
      template <class Archive>
      void serialize(Archive & ar, const unsigned int version);

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

      /**
      * Convert to standard form, in which denominator is greatest divisor.
      */ 
      void reduce();

   //friends:

      friend Rational operator + (Rational const & a, Rational const & b);
      friend Rational operator + (Rational const & a, int b);

      friend Rational operator - (Rational const & a, Rational const & b);
      friend Rational operator - (Rational const & a, int b);
      friend Rational operator - (int b, Rational const & a);

      friend Rational operator * (Rational const & a, Rational const & b);
      friend Rational operator * (Rational const & a, int b);

      friend Rational operator / (Rational const & a, Rational const & b);
      friend Rational operator / (Rational const & a, int b);
      friend Rational operator / (int b, Rational const & a);

      friend bool operator == (Rational const & a, Rational const & b);
      friend bool operator == (Rational const & a, int b);

      // Unary negation operation
      friend Rational operator - (Rational const & a);

      #if 0
      friend 
      std::istream & operator >> (std::istream & in, Rational & rational);
      #endif

      friend 
      std::ostream & operator << (std::ostream& out, Rational const & rational);

   };



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
   Rational::Rational(Rational const & other)
    : num_(other.num_),
      den_(other.den_)
   {}

   /*
   * Assignment from another rational.
   */
   inline
   Rational & Rational::operator = (Rational const & other)
   {
      num_ = other.num_;
      den_ = other.den_;
      return *this;
   }

   /*
   * Assignment from integer.
   */
   inline
   Rational & Rational::operator = (int other)
   {
      num_ = other;
      den_ = 1;
      return *this;
   }

   // Inline arithmetic assignment operators

   /*
   * Addition assignment operator : add b to this.
   */
   inline
   Rational & Rational::operator += (Rational const & a)
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
   Rational & Rational::operator += (int a)
   {
      num_ += a*den_;
      reduce();
      return *this;
   }

   /*
   * Subtraction assignment operator : subtract a from this.
   */
   inline
   Rational & Rational::operator -= (Rational const & a)
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
   Rational & Rational::operator -= (int a)
   {
      num_ -= a*den_;
      reduce();
      return *this;
   }

   /*
   * Multipication assignment operator : multiply this by a.
   */
   inline
   Rational & Rational::operator *= (Rational const & a)
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
   Rational & Rational::operator *= (int a)
   {
      num_ *= a;
      reduce();
      return *this;
   }

   /*
   * Division assignment operator : divide this by rational.
   */
   inline
   Rational & Rational::operator /= (Rational const & a)
   {
      if (a.num_ == 0) {
         UTIL_THROW("Attempt to divide by zero Rational"); 
      }
      num_ = num_*a.den_;
      den_ = den_*a.num_;
      reduce();
      return *this;
   }

   /*
   * Division assignment operator : divide this by rational.
   */
   inline
   Rational & Rational::operator /= (int a)
   {
      if (a == 0) {
         UTIL_THROW("Attempt to divide Rational by zero integer"); 
      }
      den_ *= a;
      reduce();
      return *this;
   }

   // Accessors

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
   * Cast to double operator.
   */
   inline
   Rational::operator double () const
   {  return double(num_)/double(den_); }

   // Miscellaneous member functions

   /*
   * Serialize to/from an archive.
   */
   template <class Archive>
   inline void Rational::serialize(Archive & ar, const unsigned int version)
   {
      ar & den_;
      ar & num_;
   }

   /*
   * Reduce rational number to standard reduced form (private).
   */
   inline
   void Rational::reduce ()
   {
      UTIL_CHECK(den_ != 0);
      if (num_ == 0) {
         den_ = 1;
      } else {
         if (den_ < 0) {
            den_ *= -1;
            num_ *= -1;
         }
         int c = gcd(num_, den_);
         num_ /= c;
         den_ /= c;
      }
   }

   // Friend functions for binary arithmetic operations

   /**
   * Compute sum of two rationals.
   *
   * \param a 1st argument
   * \param b 2st argument
   * \return sum a + b
   */
   inline
   Rational operator + (Rational const & a, Rational const & b)
   {
     int num = a.num_*b.den_ + b.num_*a.den_;
     int den = a.den_*b.den_;
     return Rational(num, den);
   }

   /**
   * Compute sum of rational and integer.
   *
   * \param a Rational argument
   * \param b integer argument
   * \return sum a + b
   */
   inline
   Rational operator + (Rational const & a, int b)
   {
     int num = a.num_ + b*a.den_;
     return Rational(num, a.den_);
   }

   /**
   * Compute sum of integer and integer.
   *
   * \param b integer argument
   * \param a Rational argument
   * \return sum a + b
   */
   inline
   Rational operator + (int b, Rational const & a)
   { return (a + b); }

   /**
   * Compute difference of rationals.
   *
   * \param a 1st argument
   * \param b 2st argument
   * \return difference a - b
   */
   inline
   Rational operator - (Rational const & a, Rational const & b)
   {
     int num = a.num_*b.den_ - b.num_*a.den_;
     int den = a.den_*b.den_;
     return Rational(num, den);
   }

   /**
   * Compute difference of rational and integer.
   *
   * \param a Rational argument
   * \param b integer argument
   * \return difference a - b
   */
   inline
   Rational operator - (Rational const & a, int b)
   {
     int num = a.num_ - b*a.den_;
     return Rational(num, a.den_);
   }

   /**
   * Compute difference of integer and rational.
   *
   * \param b integer argument
   * \param a Rational argument
   * \return difference b - a 
   */
   inline
   Rational operator - (int b, Rational const & a)
   {
     int num = b*a.den_ - a.num_;
     return Rational(num, a.den_);
   }

   /**
   * Compute product of rationals.
   *
   * \param a 1st argument
   * \param b 2st argument
   * \return product a*b
   */
   inline
   Rational operator * (Rational const & a, Rational const & b)
   {
      int num = a.num_*b.num_;
      int den = a.den_*b.den_;
      return Rational(num, den);
   }

   /**
   * Compute product of rational and integer.
   *
   * \param a Rational argument
   * \param b integer argument
   * \return product a*b
   */
   inline
   Rational operator * (Rational const & a, int b)
   { return Rational(b*a.num_, a.den_); }

   /**
   * Compute product of integer and rational.
   *
   * \param b integer argument
   * \param a Rational argument
   * \return product a*b
   */
   inline
   Rational operator * (int b, Rational const & a)
   { return a*b; }

   /**
   * Compute quotient of two rationals.
   *
   * \param a 1st argument
   * \param b 2st argument
   * \return ratio a/b
   */
   inline
   Rational operator / (Rational const & a, Rational const & b)
   {
      if (b.num_ == 0) {
         UTIL_THROW("Attempt to divide by zero Rational"); 
      }
      int num = a.num_*b.den_;
      int den = a.den_*b.num_;
      return Rational(num, den);
   }

   /**
   * Compute quotient Rational divided by integer.
   *
   * \param a Rational argument
   * \param b integer argument
   * \return ratio a/b
   */
   inline
   Rational operator / (Rational const & a, int b)
   {
      if (b == 0) {
         UTIL_THROW("Attempt to divide Rational by zero integer"); 
      }
      return Rational(a.num_, a.den_*b);
   }

   /**
   * Compute quotient integer divided by Rational.
   *
   * \param b integer argument
   * \param a Rational argument
   * \return ratio b/a
   */
   inline
   Rational operator / (int b, Rational const & a)
   {
      if (a.num_ == 0) {
         UTIL_THROW("Attempt to divide integer by zero Rational"); 
      }
      return Rational(b*a.den_, a.num_);
   }

   // Unary arithmetic operators

   /**
   * Unary negation of Rational.
   *
   * \param a Rational number
   * \return negation -a
   */
   inline
   Rational operator - ( Rational const & a)
   {  return Rational(-a.num_, a.den_); }

   /// Equality operators

   /**
   * Equality operator for two Rational numbers.
   *
   * \param a 1st Rational
   * \param b 2nd Rational
   * \return true if equal, false otherwise
   */
   inline 
   bool operator == (Rational const & a, Rational const & b)
   {  return ((a.num_ == b.num_) && (a.den_ == b.den_)); }

   /**
   * Equality operator for a Rational and an integer.
   *
   * \param a Rational number
   * \param b integer number
   * \return true if equal, false otherwise
   */
   inline bool operator == (Rational const & a, int b)
   {  return ((a.num_ == b) && (a.den_ == 1)); }

   /**
   * Equality operator for an integer and a Rational.
   *
   * \param b integer number
   * \param a Rational number
   * \return true if equal, false otherwise
   */
   inline bool operator == (int b, Rational const & a)
   {  return (a == b); }

   /// Inequality operators

   /**
   * Inequality operator for two Rational numbers.
   *
   * \param a 1st Rational
   * \param b 2nd Rational
   * \return true if unequal, false if equal
   */
   inline bool operator != (Rational const & a, Rational const & b)
   {  return !(a == b); }

   /**
   * Inequality operator for a Rational and an integer.
   *
   * \param a Rational number
   * \param b integer number
   * \return true if unequal, false if equal
   */
   inline bool operator != (Rational const & a, int b)
   {  return !(a == b); }

   /**
   * Inequality operator for an integer and a Rational.
   *
   * \param b integer number
   * \param a Rational number
   * \return true if unequal, false if equal
   */
   inline bool operator != (int b, Rational const & a)
   {  return !(a == b); }

   //  Miscellaneous global functions.

   /**
   * Output stream inserter for a Rational.
   *
   * Output elements of a rational to stream, without line breaks.
   * \param  out     output stream
   * \param  rational  Rational to be written to stream
   * \return modified output stream
   */
   std::ostream& operator << (std::ostream& out, Rational const & rational);

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

}
#endif
