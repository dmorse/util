/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MatrixParam.h"
#include "BracketPolicy.h"

#ifdef UTIL_MPI
#include <util/mpi/MpiSendRecv.h>
#endif

#include <iomanip>

namespace Util
{

   /*
   * Constructor.
   */
   template <typename Type>
   MatrixParam<Type>::MatrixParam(const char *label, int m, int n,
                                  bool isRequired)
    : Parameter(label, isRequired),
      name_(label),
      lBracket_("["),
      rBracket_("]"),
      m_(m),
      n_(n),
      isRequired_(isRequired),
      hasBrackets_(false)
   {
      if (BracketPolicy::get() != BracketPolicy::Forbidden) {
         std::string name = name_;
         name += lBracket_;
         label_.setString(name);
         hasBrackets_ = true;
      }
   }

   /*
   * Destructor.
   */
   template <typename Type>
   MatrixParam<Type>::~MatrixParam()
   {}

   /*
   * Set left and right bracket delimiter strings.
   */
   template <typename Type>
   void MatrixParam<Type>::setBrackets(std::string lBracket,
                                       std::string rBracket)
   {
      // Set bracket string values
      lBracket_ = lBracket;
      rBracket_ = rBracket;

      // Reset label_ and hasBrackets to default for output
      std::string string = name_;
      if (BracketPolicy::get() == BracketPolicy::Forbidden) {
         hasBrackets_ = false;
      } else {
         string += lBracket_;
         hasBrackets_ = true;
      }
      label_.setString(string);
   }

   /*
   * Read the array label.
   */
   template <typename Type>
   void MatrixParam<Type>::readLabel(std::istream &in)
   {
      isActive_ = false;

      if (BracketPolicy::get() == BracketPolicy::Optional) {

         // First try to match array name with an appended left bracket
         std::string string = name_;
         string += lBracket_;
         label_.setString(string);    // Tentatively reset label string
         label_.setIsRequired(false); // Temporarily set isRequired false
         hasBrackets_ = true;
         in >> label_;
         // This will not throw an exception, because isRequired is false

         // Restore original isRequired value of label
         label_.setIsRequired(isRequired_);

         if (!Label::isMatched()) {
            // Try to match array name without appended ( bracket
            label_.setString(name_);
            hasBrackets_ = false;
            in >> label_;
         }

      } else
      if (BracketPolicy::get() == BracketPolicy::Required) {

         std::string string = name_;
         string += lBracket_;
         label_.setString(string);
         hasBrackets_ = true;
         in >> label_;

      } else
      if (BracketPolicy::get() == BracketPolicy::Forbidden) {

         std::string string = name_;
         label_.setString(string);
         hasBrackets_ = false;
         in >> label_;

      }

   }

   /*
   * Read end bracket delimiter, if any.
   */
   template <class Type>
   void MatrixParam<Type>::readEndBracket(std::istream& in)
   {
      // If necessary, attempt to read closing bracket
      if (hasBrackets_) {
         UTIL_CHECK(BracketPolicy::get() != BracketPolicy::Forbidden);
         in >> Label(rBracket_);
         // Operator >> will throw an Exception if bracket is not matched
      }

      // Reset label_ and hasBrackets to default for output
      std::string string = name_;
      if (BracketPolicy::get() == BracketPolicy::Forbidden) {
         hasBrackets_ = false;
      } else {
         string += lBracket_;
         hasBrackets_ = true;
      }
      label_.setString(string);
   }

   /*
   * Write end bracket delimiter, if any.
   */
   template <class Type>
   void MatrixParam<Type>::writeEndBracket(std::ostream& out) const
   {
      if (hasBrackets_) {
         out << indent() << rBracket_ << std::endl;
      }
   }

}
