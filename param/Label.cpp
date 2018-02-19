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
   std::string  Label::input_;

   // Static member functions

   /*
   * Clear static input buffer (static member function).
   *
   * Sets isClear = true and isMatched = false.
   */
   void Label::clear()
   {
      input_.clear(); 
      isClear_ = true;
      isMatched_ = false;
   }

   /*
   * Is the input buffer clear? (static member function).
   */
   bool Label::isClear() 
   {  return isClear_; }

   // Non-static member functions

   /*
   * Constructor.
   */
   Label::Label(bool isRequired)
    : isRequired_(isRequired),
      string_()
   {}

   /*
   * Constructor.
   */
   Label::Label(const char* string, bool isRequired)
    : isRequired_(isRequired),
      string_(string)
   {}

   /*
   * Copy constructor.
   */
   Label::Label(const Label& other)
    : isRequired_(other.isRequired_),
      string_(other.string_)
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

      // If previous input value matched, try to read a new one.
      if (label.isClear_) {
         if (!in.eof()) {
            if (in.fail()) {
               UTIL_THROW("istream::fail() before reading Label");
            } 
            skipws(in);
            in >> label.input_;
            if (label.input_.size() != 0) {
               label.isClear_ = false;
            } else {
               if (label.isRequired()) {
                  Log::file() << "Empty required label" << std::endl;
                  UTIL_THROW("Empty required label after read");
               }
            }
         } else { // if is eof
            if (label.isRequired()) {
               Log::file() << "End-of-file before reading required Label" 
                           << std::endl;
               Log::file() << "Expected: " << label.string_ << std::endl;
               UTIL_THROW("EOF before reading required label");
            } else {
               Label::input_.clear();
               Label::isClear_ = true;
               Label::isMatched_ = false;
               return in;
            }
         }
      }
      if (label.input_ == label.string_) {
         Label::input_.clear();;
         Label::isClear_ = true;
         Label::isMatched_ = true;
      } else {
         Label::isMatched_ = false;
         if (label.isRequired_) {
            Log::file() << "Error reading label"         << std::endl;
            Log::file() << "Expected: " << label.string_ << std::endl;
            Log::file() << "Scanned:  " << label.input_  << std::endl;
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
