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
    : label_(label, isRequired),
      name_(label),
      isRequired_(isRequired),
      isActive_(false),
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
      label_.setString(string);
      label_.setIsRequired(false);
      in >> label_;
      // This will not throw an exception, because isRequired is temporarily false

      // Reset isRequired value 
      label_.setIsRequired(isRequired_);

      if (Label::isMatched()) {
         isActive_ = true;
         hasBrackets_ = true;
      } else {
         // Try to match array name without appended [ bracket
         label_.setString(name_);
         in >> label_;
         // Will throw exception if not matched and isRequired_ = true
         if (Label::isMatched()) {
            isActive_ = true;
            hasBrackets_ = false;
         }
      }
   }

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
                           << std::setw(ArrayParam::Width)
                           << "[ absent ]" << std::endl;
            }

         }
      } else {
         #ifdef UTIL_MPI
         if (!hasIoCommunicator()) {
            UTIL_THROW("Error: not isIoProcessor and not hasIoCommunicator");
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

   /*
   * Load from an archive.
   */
   void ArrayParam::load(Serializable::IArchive& ar)
   {
      if (isIoProcessor()) {
         if (isRequired()) { 
            isActive_ = true;
         } else {
            ar >> isActive_;
         }
         if (isActive_) {
            loadValue(ar);
            if (ParamComponent::echo()) {
               writeParam(Log::file());
            }
         } else {
            if (ParamComponent::echo() && !isRequired()) {
               Log::file() << indent() 
                           << label_ << std::right
                           << std::setw(ArrayParam::Width)
                           << "[ absent ]" << std::endl;
            }
         }
      } else {
         #ifdef UTIL_MPI
         if (!hasIoCommunicator()) {
            UTIL_THROW("Error: not isIoProcessor and !hasIoCommunicator");
         }
         #else
         UTIL_THROW("Error: not isIoProcessor and no MPI");
         #endif
      }
      #ifdef UTIL_MPI
      if (hasIoCommunicator()) {
         if (isRequired()) {
            isActive_ = true;
         } else {
            bcast<bool>(ioCommunicator(), isActive_, 0); 
         }
         if (isActive_) {
            bcastValue();
         }
      }
      #endif
   }

   /*
   * Save to an archive.
   */
   void ArrayParam::save(Serializable::OArchive& ar)
   {
      if (!isRequired()) {
         ar << isActive_;
      }
      if (isActive_) {
         saveValue(ar);
      }
   }

   /*
   * Return label string.
   */
   std::string ArrayParam::label() const
   {  return name_; }

   /*
   * Is this a required parameter?
   */
   bool ArrayParam::isRequired() const
   {  return isRequired_; }

   /*
   * Is this an active parameter?
   */
   bool ArrayParam::isActive() const
   {  return isActive_; }

} 
