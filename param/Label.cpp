/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Label.h"

#include <iomanip>

namespace Util
{

   /// Define static variables.
   bool  Label::isClear_ = true;
   bool  Label::isMatched_ = false;
   std::string  Label::buffer_;

   // Static member functions

   /*
   * Clear static input buffer (static member function), and
   * set isClear = true.
   */
   void Label::clear()
   {
      buffer_.clear(); 
      isClear_ = true;
   }

   /*
   * Extract string from input stream and store in the buffer without 
   * attempting to match.
   */
   void Label::read(std::istream& in)
   {
      if (isClear_) {
         if (!in.eof()) {
            if (in.fail()) {
               UTIL_THROW("istream::fail() before reading Label");
            } 
            skipws(in);
            in >> buffer_;
            if (buffer_.size() != 0) {
               isClear_ = false;
            }
         } else { // if is eof
            Label::isMatched_ = false;
         }
      }
   }

   // Non-static member functions

   /*
   * Constructor.
   */
   Label::Label(bool isRequired)
    : string_(),
      isRequired_(isRequired)
   {}

   /*
   * Constructor.
   */
   Label::Label(std::string string, bool isRequired)
    : string_(string),
      isRequired_(isRequired)
   {}

   /*
   * Constructor.
   */
   Label::Label(const char* string, bool isRequired)
    : string_(string),
      isRequired_(isRequired)
   {}

   /*
   * Copy constructor.
   */
   Label::Label(const Label& other)
    : string_(other.string_),
      isRequired_(other.isRequired_)
   {}

   /*
   * Destructor.
   */
   Label::~Label()
   {}

   /*
   * Set the label string.
   */
   void Label::setString(std::string string) 
   {  string_ = string; }

   /*
   * Set the isRequired flag.
   */
   void Label::setIsRequired(bool isRequired) 
   {  isRequired_ = isRequired; }

   /*
   * Return label string.
   */
   std::string Label::string() const
   {  return string_; }

   /*
   * Attempt to match label and return true iff matched.
   */
   bool Label::match(std::istream& in)
   {  
      in >> *this;
      return isMatched_;
   }

   /*
   * Extract a label from an input stream.
   */
   std::istream& operator >> (std::istream& in, Label label)
   {
      UTIL_CHECK(label.string_.size() > 0);

      if (in.eof()) {
         if (label.isRequired()) {
            Log::file() << "End-of-file before reading required Label" 
                        << std::endl;
            Log::file() << "Expected: " << label.string_ << std::endl;
            UTIL_THROW("EOF before reading required label");
         }
      } else {
         // If previous input value matched, try to read a new one.
         Label::read(in);

         if (label.isRequired() && label.isClear()) {
            Log::file() << "Empty required label" << std::endl;
            Log::file() << "Expected: " << label.string_ << std::endl;
            UTIL_THROW("Empty required label after read");
         }
      }

      // Attempt to match input string to expected string.
      if (label.buffer_ == label.string_) {
         Label::clear();
         Label::isMatched_ = true;
      } else {
         Label::isMatched_ = false;
         if (label.isRequired_) {
            Log::file() << "Error reading label"         << std::endl;
            Log::file() << "Expected: " << label.string_ << std::endl;
            Log::file() << "Scanned:  " << label.buffer_  << std::endl;
            UTIL_THROW("Incorrect label");
         }
      };
      return in;
   }

   /*
   * Insert a Label into an output stream.
   */
   std::ostream& operator << (std::ostream& out, Label label)
   {
      out << std::left << std::setw(Label::LabelWidth) 
          << label.string_; 
      out << std::right;
      return out;
   }

} 
