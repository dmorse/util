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
   ArrayParam::ArrayParam(const char *label, bool isRequired)
    : Parameter(label, isRequired),
      name_(label),
      isRequired_(isRequired),
      hasBrackets_(false)
   {}

   /*
   * Destructor.
   */
   ArrayParam::~ArrayParam()
   {}

   /*
   * Read the array label.
   */
   void ArrayParam::readLabel(std::istream &in)
   {
      isActive_ = false;
      hasBrackets_ = false;

      // Try to match array name with an appended [ bracket
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
   }

   #if 0
   /*
   * Read a parameter.
   */
   void ArrayParam::readParam(std::istream &in)
   {
      if (isIoProcessor()) {

         // Attempt to read array label
         readLabel(in);

         // If this array parameter is required and the label does 
         // not match, an Exception will be thrown from within the 
         // readLabel function, terminating execution.

         if (Label::isMatched()) {

            // If the label string matched
            readValue(in);
            isActive_ = true;
            if (ParamComponent::echo()) {
               writeParam(Log::file());
            }

         } else {

            // If label does not match.
            // Note: Label must be optional or an
            // Exception should have been thrown.
            assert(!isRequired());
            isActive_ = false;
            if (ParamComponent::echo()) {
               Log::file() << indent() 
                           << label_ << std::right
                           << std::setw(Parameter::Width)
                           << "[ absent ]" << std::endl;
            }

         }
      } else {
         #ifdef UTIL_MPI
         if (!hasIoCommunicator()) {
            UTIL_THROW("Error: not isIoProcessor & not hasIoCommunicator");
         }
         #else
         UTIL_THROW("Error: not isIoProcessor and no MPI");
         #endif
      }
      #ifdef UTIL_MPI
      if (hasIoCommunicator()) {
         if (isRequired()) {
            bcastValue();
            isActive_ = true;
         } else {
            bcast<bool>(ioCommunicator(), isActive_, 0); 
            if (isActive_) {
               bcastValue();
            }
         }
      }
      #endif
   }
   #endif

} 
