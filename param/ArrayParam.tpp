/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "ArrayParam.h"
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
   ArrayParam<Type>::ArrayParam(const char *label, int n, bool isRequired)
    : Parameter(label, isRequired),
      name_(label),
      n_(n),
      isRequired_(isRequired),
      hasBrackets_(false)
   {
      if (BracketPolicy::get() != BracketPolicy::Forbidden) {
         std::string name = name_;
         name += "[";
         label_.setString(name);
         hasBrackets_ = true;
      }
   }

   /*
   * Destructor.
   */
   template <typename Type>
   ArrayParam<Type>::~ArrayParam()
   {}

   /*
   * Read the array label.
   */
   template <typename Type>
   void ArrayParam<Type>::readLabel(std::istream &in)
   {
      isActive_ = false;

      if (BracketPolicy::get() == BracketPolicy::Optional) {

         // First try to match array name with an appended [ bracket
         std::string string = name_;
         string += "[";
         label_.setString(string);    // Tentatively reset label string
         label_.setIsRequired(false); // Temporarily set isRequired false
         hasBrackets_ = true;
         in >> label_;
         // This will not throw an exception, because isRequired is false
   
         // Restore isRequired value of label
         label_.setIsRequired(isRequired_);
   
         if (Label::isMatched()) {
            //isActive_ = true;
            hasBrackets_ = true;
         } else {
            // Try to match array name without appended [ bracket
            label_.setString(name_);
            hasBrackets_ = false;
            in >> label_;
         }

      } else 
      if (BracketPolicy::get() == BracketPolicy::Required) {

         std::string string = name_;
         string += "[";
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
   * Read array of values from isteam.
   */
   template <class Type>
   void ArrayParam<Type>::readValue(std::istream &in)
   {  
      for (int i = 0; i < n_; ++i) {
         in >> element(i);
      }
      readEndBracket(in);

      #if 0
      if (hasBrackets_) {
         in >> Label("]");
      } else 
      if (BracketPolicy::get() != BracketPolicy::Forbidden) {
         std::string string = name_;
         string += "[";
         label_.setString(string);  
         hasBrackets_ = true;
      }
      #endif
   }
 
   /*
   * Read closing bracket delimiter, if any.
   */
   template <class Type>
   void ArrayParam<Type>::readEndBracket(std::istream& in)
   { 
      // If necessary, attempt to read closing bracket 
      if (hasBrackets_) {
         UTIL_CHECK(BracketPolicy::get() != BracketPolicy::Forbidden);
         in >> Label("]");
         // Operator >> throws an Exception if "]" is not matched
      }
 
      // Reset label_ and hasBrackets_ to default values for output
      std::string string = name_;
      if (BracketPolicy::get() == BracketPolicy::Forbidden) {
         hasBrackets_ = false;
      } else {
         string += "[";
         hasBrackets_ = true;
      }
      label_.setString(string);
   }

   /*
   * Write an array-valued parameter.
   */
   template <class Type>
   void ArrayParam<Type>::writeParam(std::ostream &out) 
   {
      if (isActive()) {

         Label space("");
         int i;
         if (hasBrackets_) {
            out << indent() << Parameter::label_ << std::endl;
         }
         for (i = 0; i < n_; ++i) {
            if (i == 0 && !hasBrackets_) {
               out << indent() << Parameter::label_;
            } else {
               out << indent() << space;
            }
            out << std::right << std::scientific 
                << std::setprecision(Parameter::Precision) 
                << std::setw(Parameter::Width)
                << element(i)
                << std::endl;
         }
         if (hasBrackets_) {
            out << indent() << "]" << std::endl;
         }

      } // if isActive
   }

} 
