#ifndef UTIL_LABEL_H
#define UTIL_LABEL_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>
#include <iostream>
#include <string>

namespace Util
{

   /**
   * A label string in a file format.
   *
   * The operator >> for a label checks if the expected label was found.
   * The operator << outputs the expected label.
   *
   * Every Label constructor takes an optional parameter isRequired that 
   * determines whether the label must be matched (isRequired == true), 
   * or if it is optional (isRequired == false). The isRequired parameter
   * is true by default. If the input value read by the >> operator does
   * not match the expected value and isRequired is true, the >> operator 
   * will print an error message to the Log::file() and then throw an 
   * Exception. If the input value does not match and isRequired is false,
   * the >> operator stores the input value in a buffer string for later
   * use. If the >> operator is invoked when the buffer is not clear (e.g.,
   * after a failed match to an optional label), the operator does not 
   * read from file and compares the expected label to the string in the
   * buffer.
   * 
   * The class is designed to allow either of two methods to be used to 
   * read and check a label, referred to below as cases A and B:
   * 
   * Case A (the usual case, and concise) : The user constructs a Label 
   * object using a constructor that takes an expected label string as
   * as argument, then uses the >> operator to attempt to read a string 
   * from file into the Label. For example, to read a required label that
   * must match the expected label string "thing", one might use the line
   * \code
   *    in >> Label("thing");
   * \endcode
   * where "in" is a symbol for an input stream. The overloaded ">>"
   * operator reads a string from input stream into a buffer if and
   * only if the buffer is empty. It then compares the string in the 
   * buffer to the label string (e.g., "thing"). If the strings match, 
   * the buffer is cleared and isMatch is set true. If the strings do 
   * not match and is isRequired is true, an Exception is thrown. If 
   * the strings do not match but isRequired is false, the buffer is 
   * left unchanged and isMatched is set false.
   * 
   * Case B (less common, and more verbose) : A user can use several
   * static functions to perform a sequence of operations similar to
   * those peformed by the >> operator.  In this case, the user must
   * call the static Label::read function to read a string from an 
   * input stream iff the buffer is empty, then call Label::buffer to 
   * retrieve the buffer string, and explicitly check if that string
   * matches one or more allowed possible labels. If a match is found, 
   * call Label::clear to clear the buffer and call Label::setIsMatched
   * to set isMatched false. This more verbose sequence of operations 
   * is used in the readObject function of the Factory class template, 
   * in which a single input string is * compared to a list of several 
   * possible valid labels. 
   *
   * \ingroup Param_Module
   */
   class Label
   {

   public:

      // Static public members

      /// Width of label field in file output format.
      static const int LabelWidth  = 20;

      /**
      * Read a string without checking its value.
      *
      * This function reads a string from input stream in if and only
      * if the buffer is empty. It does not compare the string to an
      * expected value. If matching is desired, use >> operator.
      * 
      * \param in input stream
      */
      static void read(std::istream& in);

      /**
      * Clear the input buffer.
      */
      static void clear();

      /**
      * Explicitly set the isMatched flag.
      *
      * \param isMatched boolean value to store in isMatched_.
      */
      static void setIsMatched(bool isMatched);

      /** 
      * Get the string that is currently in the input buffer.
      */ 
      static std::string buffer();

      /**
      * Is the input buffer clear?
      */
      static bool isClear();

      /**
      * Did the most recent attempt to match a Label succeed?
      *
      * Returns true after a successful match by operator >> or the
      * match() function. Returns false before any attempt to match 
      * any Label, or after a failed attempt to match either a
      * required or optional label.
      */
      static bool isMatched();

      // Non-static Public Members

      /**
      * Constructor.
      *
      * \param isRequired Is this label a required entry? (true by default)
      */
      explicit Label(bool isRequired = true);

      /**
      * Constructor.
      *
      * \param string  label string that precedes value in file format
      * \param isRequired Is this label a required entry? (true by default)
      */
      Label(std::string string, bool isRequired = true);

      /**
      * Constructor.
      *
      * \param string  label string that precedes value in file format
      * \param isRequired Is this label a required entry? (true by default)
      */
      Label(const char* string, bool isRequired = true);

      /**
      * Copy constructor.
      *
      * \param other Label object being copied.
      */
      Label(const Label& other);

      /**
      * Destructor.
      */
      virtual ~Label();

      /**
      * Set the label string.
      *
      * \param string label string that precedes value in file format
      */
      void setString(std::string string);

      /**
      * Set the isRequired boolean flag.
      *
      * \param isRequired  boolean that is true iff the label is required.
      */
      void setIsRequired(bool isRequired);

      /**
      * Read and attempt to match next word in an input stream.
      *
      * This is a convenience function that invokes operator >> to
      * read a word and then returns the value of Label::isMatched().
      * For an optional Label, this returns true upon a successful
      * match and false otherwise. For a required label, returns
      * true upon a successful match or throws an Exception. 
      */
      bool match(std::istream& in);

      /**
      * Return label string.
      */
      std::string string() const;

      /**
      * Is this the label for a required component?
      */
      bool isRequired() const;

   private:

      /**
      * Expected label string.
      */
      std::string string_;

      /**
      * Is this label a required entry ? 
      *
      * This is passed to the constructor, and constant thereafter.
      */
      bool isRequired_;

   // Static members:

      /**
      * Is Label::buffer_ clear? (initialized true).
      */
      static bool isClear_;

      /**
      * Did the most recent attempt to match this label succeed?
      *
      * This is used for optional labels to check whether the most
      * recent attempt to match the string succeeded. The variable
      * is set false in the constructor, and can be set true by the
      * extraction operator (operator >>) or the match function.
      */
      static bool isMatched_;

      /// Most recent input value from istream (initialized empty).
      static std::string buffer_;

   // friends:

      friend std::istream& operator >> (std::istream& in, Label label);
      friend std::ostream& operator << (std::ostream& out, Label label);

   };

   // Friend function declarations

   /**
   * Extractor for Label.
   *
   * \param in  input stream
   * \param label  Label to be read from file
   */ 
   std::istream& operator >> (std::istream& in, Label label);

   /**
   * Inserter for Label.
   *
   * \param out   output stream
   * \param label Label to be written to file
   */ 
   std::ostream& operator << (std::ostream& out, Label label);

   // Inline functions

   /*
   * Is this label a required component of the file format?
   */
   inline bool Label::isRequired() const
   {  return isRequired_; }

   /*
   * Is the input buffer clear? (static member function).
   */
   inline bool Label::isClear()
   {  return isClear_; }

   /*
   * Did the most recent attempt to read match? 
   * (static member function)
   */
   inline bool Label::isMatched()
   {  return isMatched_; }

   /*
   * Manually set isMatched. 
   */
   inline void Label::setIsMatched(bool isMatched)
   {  isMatched_ = isMatched; }

   /*
   * Get the string that is currently stored in the buffer.
   */ 
   inline std::string Label::buffer()
   {  return buffer_; }

} 
#endif
