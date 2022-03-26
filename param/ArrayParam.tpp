/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "ArrayParam.h"

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
      n_(n),
      name_(label),
      isRequired_(isRequired),
      hasBrackets_(false)
   {
      if (Parameter::bracketPolicy() != Parameter::Forbidden) {
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
      hasBrackets_ = false;

      if (Parameter::bracketPolicy() == Parameter::Optional) {

         // First try to match array name with an appended [ bracket
         std::string string = name_;
         string += "[";
         label_.setString(string);    // Tentatively reset label string
         label_.setIsRequired(false); // Temporarily set isRequired false
         in >> label_;
         // This will not throw an exception, because isRequired is false
   
         // Restore isRequired value of label
         label_.setIsRequired(isRequired_);
   
         if (Label::isMatched()) {
            isActive_ = true;
            hasBrackets_ = true;
         } else {
            // Try to match array name without appended [ bracket
            label_.setString(name_);
            in >> label_;
            // Will throw exception if not matched and isRequired = true
            if (Label::isMatched()) {
               isActive_ = true;
               hasBrackets_ = false;
            }
         }

      } else 
      if (Parameter::bracketPolicy() == Parameter::Required) {

         hasBrackets_ = true;
         std::string string = name_;
         string += "[";
         label_.setString(string);    
         in >> label_;
         if (Label::isMatched()) {
            isActive_ = true;
         } else {
            isActive_ = false;
         }

      } else
      if (Parameter::bracketPolicy() == Parameter::Forbidden) {

         hasBrackets_ = false;
         std::string string = name_;
         label_.setString(string);    
         in >> label_;
         if (Label::isMatched()) {
            isActive_ = true;
         } else {
            isActive_ = false;
         }

      } 
      
   }

   /*
   * Read array of values from isteam.
   */
   template <class Type>
   void ArrayParam<Type>::readValue(std::istream &in)
   {  
      #if 0
      if (!(arrayPtr_->isAllocated())) {
         UTIL_THROW("Cannot read unallocated DArray");
      }
      if (arrayPtr_->capacity() != n_) {
         UTIL_THROW("Error: DArray capacity < n");
      }
      #endif
      for (int i = 0; i < n_; ++i) {
         in >> element(i);
      }
      if (hasBrackets()) {
         in >> Label("]");
      }
   }

 
   /*
   * Write a array parameter.
   */
   template <class Type>
   void ArrayParam<Type>::writeParam(std::ostream &out) 
   {
      if (isActive()) {

         #if 0
         if (!(arrayPtr_->isAllocated())) {
            UTIL_THROW("Cannot write unallocated DArray");
         }
         if (arrayPtr_->capacity() != n_) {
            UTIL_THROW("Error: DArray capacity != n in writeParam");
         }
         #endif
   
         Label space("");
         int i;
         if (hasBrackets()) {
            out << indent() << Parameter::label_ << std::endl;
         }
         for (i = 0; i < n_; ++i) {
            if (i == 0 && !hasBrackets()) {
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
         if (hasBrackets()) {
            out << indent() << "]" << std::endl;
         }

      } // if isActive
   }

} 
