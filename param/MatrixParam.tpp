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
      m_(n),
      n_(n),
      isRequired_(isRequired),
      hasBrackets_(false)
   {
      if (BracketPolicy::get() != BracketPolicy::Forbidden) {
         std::string name = name_;
         name += "(";
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
   * Read the array label.
   */
   template <typename Type>
   void MatrixParam<Type>::readLabel(std::istream &in)
   {
      isActive_ = false;

      if (BracketPolicy::get() == BracketPolicy::Optional) {

         // First try to match array name with an appended ( bracket
         std::string string = name_;
         string += "(";
         label_.setString(string);    // Tentatively reset label string
         label_.setIsRequired(false); // Temporarily set isRequired false
         hasBrackets_ = true;
         in >> label_;
         // This will not throw an exception, because isRequired is false
   
         // Restore isRequired value of label
         label_.setIsRequired(isRequired_);
   
         if (Label::isMatched()) {
            hasBrackets_ = true;
         } else {
            // Try to match array name without appended ( bracket
            label_.setString(name_);
            hasBrackets_ = false;
            in >> label_;
         }

      } else 
      if (BracketPolicy::get() == BracketPolicy::Required) {

         std::string string = name_;
         string += "(";
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
   void MatrixParam<Type>::readEndBracket(std::istream &in)
   {  
      if (hasBrackets_) {
         in >> Label(")");
      } else 
      if (BracketPolicy::get() != BracketPolicy::Forbidden) {
         std::string string = name_;
         string += "(";
         label_.setString(string);  
         hasBrackets_ = true;
      }
   }

   #if 0 
   /*
   * Read array of values from isteam.
   */
   template <class Type>
   void MatrixParam<Type>::readValue(std::istream &in)
   {  
      for (int i = 0; i < m_; ++i) {
         for (int j = 0; j < n_; ++j) {
            in >> element(i, j);
         }
      }
      if (hasBrackets_) {
         in >> Label(")");
      } else 
      if (BracketPolicy::get() != BracketPolicy::Forbidden) {
         std::string string = name_;
         string += "(";
         label_.setString(string);  
         hasBrackets_ = true;
      }
   }
   #endif

   #if 0 
   /*
   * Write an array parameter.
   */
   template <class Type>
   void MatrixParam<Type>::writeParam(std::ostream &out) 
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
            out << indent() << ")" << std::endl;
         }

      } // if isActive
   }
   #endif

} 
