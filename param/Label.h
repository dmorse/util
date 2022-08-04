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
   * The constructor takes a parameter isRequired that determines whether
   * the label must be matched (isRequired == true), or if it is optional
   * (isRequired == false). If the input value read by the >> operator does
   * not match the expected value and isRequired is true, the >> operator 
   * will print an error message to the Log::file() and then throw an 
   * Exception. If the input value does not match and isRequired is false,
   * the >> operator stores the input value in a string buffer, and will 
   * compare it to subsequent values until a match is found.
   * 
   * Generally, the string that is read from the file should not be
   * directly accessed by any outside class; the >> operator should be
   * used to handle the input string. However, several static member 
   * functions are provided to bypass this default behavior if needed
   * (clear, setIsMatched, read, and buffer).
   *
   * \ingroup Param_Module
   */
   class Label
   {

   public:

      // Static Public Members

      /// Width of label field in file output format.
      static const int LabelWidth  = 20;

      /**
      * Clears buffer and sets isClear = true.
      */
      static void clear();

      /**
      * Is the input buffer clear?
      */
      static bool isClear();

      /**
      * Manually set isMatched_.
      * 
      * \param isMatched Boolean to store in isMatched_.
      */
      static void setIsMatched(bool isMatched);

      /**
      * Did the most recent attempt to match a Label succeed?
      *
      * Returns true after a successful match by operator >>
      * or the match() function. Returns false before any 
      * attempt to match any Label, after a failed attempt 
      * with an an optional label.
      */
      static bool isMatched();

      /**
      * Extract string from input stream and store in the buffer without 
      * attempting to match. If matching is desired, use >> operator.
      */
      static void read(std::istream& in);

      /** 
      * Get a copy of the string that is currently stored in the buffer.
      */ 
      static std::string buffer();

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
      * extraction operator (operator >>) and the match function.
      */
      static bool isMatched_;

      /// Most recent input value from istream (initialized empty).
      static std::string buffer_;

   //friends:

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
   * Manually set isMatched. (static member function)
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
