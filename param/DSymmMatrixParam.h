#ifndef UTIL_D_SYMM_MATRIX_PARAM_H
#define UTIL_D_SYMM_MATRIX_PARAM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/MatrixParam.h>
#include <util/containers/DMatrix.h>
#include <util/format/Int.h>
#include <util/format/Dbl.h>
#ifdef UTIL_MPI
#include <util/mpi/MpiSendRecv.h>
#endif
#include <util/global.h>

#include <iomanip> 
#include <sstream> 

namespace Util
{

   /**
   * A Parameter associated with a square symmetric DMatrix.
   *
   * The parameter file format for a DSymmMatrixParam uses one line per matrix
   * element, in which each line contains the row index, the column index and
   * the value of one matrix element.  Symmetry is imposed on reading by 
   * assigning value to both the (i,j) and (j,i) elements of the matrix when 
   * the (i, j) element is read. Each distinct element may only appear once.
   *
   * Elements may be omitted. Values of omitted elements are set to zero by
   * default. 
   *
   * The format may input and output in either bracketed or bracket free 
   * format, depending on the value of the bracket policy returned by the
   * function BracketPolicy::get(). See class documentation for MatrixParam
   * for a discussion. When bracketed format is used left and right 
   * parentheses "( ... )" are used as bracketing delimiters, and omitted
   * elements are set to zero by default. 
   * 
   * \ingroup Param_Module
   */
   template <class Type>
   class DSymmMatrixParam : public MatrixParam<Type>
   {
      
   public:
  
      /** 
      * Constructor.
      *
      * \param label  parameter label (a literal C-string)
      * \param matrix  DMatrix<Type> object
      * \param n  number of rows or columns of a square matrix
      * \param isRequired  Is this a required array-valued parameter?
      */
      DSymmMatrixParam(const char *label, DMatrix<Type>& matrix, int n, 
                       bool isRequired = true);
 
      /**
      * Write symmetric DMatrix to file.
      *
      * \param out  output stream to which to write
      */ 
      void writeParam(std::ostream &out);

   protected:
  
      /**
      * Read parameter value from an input stream.
      * 
      * \param in input stream from which to read
      */
      virtual void readValue(std::istream& in);

      /**
      * Load bare parameter value from an archive.
      *
      * \param ar input archive from which to load
      */
      virtual void loadValue(Serializable::IArchive& ar);

      /**
      * Save parameter value to an archive.
      *
      * \param ar output archive to which to save
      */
      virtual void saveValue(Serializable::OArchive& ar);

      #ifdef UTIL_MPI
      /**
      * Broadcast parameter value within the ioCommunicator.
      */
      virtual void bcastValue();
      #endif

      using ParamComponent::indent;
      using Parameter::isActive;
      using MatrixParam<Type>::m;
      using MatrixParam<Type>::n;

   protected:

      using Parameter::label_;
      using MatrixParam<Type>::hasBrackets;
      using MatrixParam<Type>::setBrackets;
      using MatrixParam<Type>::readEndBracket;
      using MatrixParam<Type>::writeEndBracket;

   private:
   
      /// Pointer to associated DMatrix.
      DMatrix<Type>* matrixPtr_;
   
      /// Should we allow default zero value for elements
      bool defaultZero_;
   
   };

   /*
   * Constructor.
   */
   template <class Type>
   DSymmMatrixParam<Type>::DSymmMatrixParam(const char* label, 
                                            DMatrix<Type>& matrix, 
                                            int n, bool isRequired)
    : MatrixParam<Type>(label, n, n, isRequired),
      matrixPtr_(&matrix),
      defaultZero_(true)
   {
      // Set left and right brackets to parentheses 
      setBrackets("(",")"); 
   }

   /*
   * Read a DMatrix from isteam.
   */
   template <class Type>
   void DSymmMatrixParam<Type>::readValue(std::istream &in)
   {  
      // Preconditions
      if (!(matrixPtr_->isAllocated())) {
         UTIL_THROW("Cannot read unallocated DMatrix");
      }
      if (n() != matrixPtr_->capacity1()) {
         UTIL_THROW("Error: Logical size n() != DMatrix<Type>::capacity1()");
      }
      if (n() != matrixPtr_->capacity2()) {
         UTIL_THROW("Error: Logical size n() != DMatrix<Type>::capacity2()");
      }

      // Create matrix of int/bool flags for error checking
      // Initialize all elements to zero
      DMatrix<int> flags;
      flags.allocate(n(), n());
      int i, j;
      for (i = 0; i < n(); ++i) {
         for (j = 0; j < n(); ++j) {
            flags(i, j) = 0;
            (*matrixPtr_)(i, j) = 0.0;
         }
      }

      double value;
      int k = 0;
      bool open = true ;
      while (open) {
         std::string string;
         in >> string;
         std::stringstream stream;
         stream << string;
         if (string == ")") {
            UTIL_CHECK(BracketPolicy::get() != BracketPolicy::Forbidden);
            UTIL_CHECK(hasBrackets());
            open = false;
            readEndBracket(stream);
         } else {
            stream >> i; 
            in >> j >> value;
            UTIL_CHECK(flags(i,j) == 0);
            (*matrixPtr_)(i, j) = value;
            flags(i, j) = 1;
            if (i != j) {
               UTIL_CHECK(flags(j,i) == 0);
               (*matrixPtr_)(j, i) = value;
               flags(j, i) = 1;
            }
            ++k;
            if (k == (n()+1)*n()/2) {
               open = false;
               readEndBracket(in); // Only reads if hasBrackets
            }
         }
      }

   }

   /*
   * Load a DMatrix from input archive.
   */
   template <class Type>
   void DSymmMatrixParam<Type>::loadValue(Serializable::IArchive& ar)
   {  
      if (!(matrixPtr_->isAllocated())) {
         matrixPtr_->allocate(n(), n());
      } else {
         if (n() != matrixPtr_->capacity1()) {
            UTIL_THROW("Error: Logical size n() != DMatrix<Type>::capacity1()");
         }
         if (n() != matrixPtr_->capacity2()) {
            UTIL_THROW("Error: Logical size n() != DMatrix<Type>::capacity2()");
         }
      }
      ar >> *matrixPtr_;
   }

   /*
   * Save a DMatrix to an output archive.
   */
   template <class Type>
   void DSymmMatrixParam<Type>::saveValue(Serializable::OArchive& ar)
   {
      if (n() != matrixPtr_->capacity1()) {
         UTIL_THROW("Error: Logical size n() != DMatrix<Type>::capacity1()");
      }
      if (n() != matrixPtr_->capacity2()) {
         UTIL_THROW("Error: Logical size n() != DMatrix<Type>::capacity2()");
      }
      ar << *matrixPtr_; 
   }

   #ifdef UTIL_MPI
   /*
   * Broadcast a DMatrix.
   */
   template <class Type>
   void DSymmMatrixParam<Type>::bcastValue()
   {  
      if (!(matrixPtr_->isAllocated())) {
         matrixPtr_->allocate(n(), n());
      } else {
         if (n() != matrixPtr_->capacity1()) {
            UTIL_THROW("Error: Logical size n() > DMatrix<Type>::capacity1()");
         }
         if (n() != matrixPtr_->capacity2()) {
            UTIL_THROW("Error: Logical size n() > DMatrix<Type>::capacity2()");
         }
      }
      bcast<Type>(ioCommunicator(), *matrixPtr_, n(), n(), 0); 
   }
   #endif

   /*
   * Write a DSymmMatrixParam.
   */
   template <class Type>
   void DSymmMatrixParam<Type>::writeParam(std::ostream &out)
   {
      if (isActive()) {
         // Preconditions
         if (!(matrixPtr_->isAllocated())) {
            UTIL_THROW("Cannot read unallocated DMatrix");
         }
         if (n() > matrixPtr_->capacity1()) {
            UTIL_THROW("Error: Logical size n() > DMatrix<Type>::capacity1()");
         }
         if (n() > matrixPtr_->capacity2()) {
            UTIL_THROW("Error: Logical size n() > DMatrix<Type>::capacity2()");
         }
  
         if (hasBrackets()) {
            out << indent() << label_ << std::endl;
         }
         Label space("");
         int i, j;
         for (i = 0; i < n(); ++i) {
            for (j = 0; j <= i; ++j) {
               if (i == 0 && j == 0 && !hasBrackets()) {
                  out << indent() << label_;
               } else {
                  out << indent() << space;
               }
               out << Int(i, 4) << " " << Int(j, 4) << " "
                   << std::right << std::scientific 
                   << std::setprecision(Parameter::Precision) 
                   << std::setw(Parameter::Width)
                   << (*matrixPtr_)(i, j)
                   << std::endl;
            }
         }
         writeEndBracket(out);
      }
   }

} 
#endif
