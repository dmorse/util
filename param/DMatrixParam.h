#ifndef UTIL_DMATRIX_PARAM_H
#define UTIL_DMATRIX_PARAM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/MatrixParam.h>
#include <util/containers/DMatrix.h>
#ifdef UTIL_MPI
#include <util/mpi/MpiSendRecv.h>
#endif
#include <util/global.h>

#include <iomanip> 

namespace Util
{

   /**
   * A Parameter associated with a 2D built-in C array.
   *
   * \ingroup Param_Module
   */
   template <class Type>
   class DMatrixParam : public MatrixParam<Type>
   {
      
   public:
  
      /** 
      * Constructor.
      *
      * \param label  parameter label (a literal C-string)
      * \param matrix  DMatrix<Type> object
      * \param m  number of rows
      * \param n  number of columns
      * \param isRequired  Is this a required parameter?
      */
      DMatrixParam(const char *label, DMatrix<Type>& matrix, int m, int n, 
                   bool isRequired = true);
 
      /**
      * Write DMatrix to file.
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
      using MatrixParam<Type>::readEndBracket;

   protected:

      using Parameter::label_;
      using MatrixParam<Type>::hasBrackets;

   private:
   
      /// Pointer to associated DMatrix.
      DMatrix<Type>* matrixPtr_;
   
   };

   /*
   * DMatrix constructor.
   */
   template <class Type>
   DMatrixParam<Type>::DMatrixParam(const char* label, DMatrix<Type>& matrix, 
                                    int m, int n, bool isRequired)
    : MatrixParam<Type>(label, m, n, isRequired),
      matrixPtr_(&matrix)
   {}

   /*
   * Read a DMatrix from isteam.
   */
   template <class Type>
   void DMatrixParam<Type>::readValue(std::istream &in)
   {  
      // Preconditions
      if (!(matrixPtr_->isAllocated())) {
         UTIL_THROW("Cannot read unallocated DMatrix");
      }
      if (m() != matrixPtr_->capacity1()) {
         UTIL_THROW("Error: Logical size m() != DMatrix<Type>::capacity1()");
      }
      if (n() != matrixPtr_->capacity2()) {
         UTIL_THROW("Error: Logical size n() != DMatrix<Type>::capacity2()");
      }

      int i, j;
      for (i = 0; i < m(); ++i) {
         for (j = 0; j < n(); ++j) {
            in >> (*matrixPtr_)(i, j);
         }
      }

      readEndBracket(in);
   }

   /*
   * Load a DMatrix from input archive.
   */
   template <class Type>
   void DMatrixParam<Type>::loadValue(Serializable::IArchive& ar)
   {  
      if (!(matrixPtr_->isAllocated())) {
         matrixPtr_->allocate(m(), n());
      } else {
         if (m() != matrixPtr_->capacity1()) {
            UTIL_THROW("Error: Logical size m() != DMatrix<Type>::capacity1()");
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
   void DMatrixParam<Type>::saveValue(Serializable::OArchive& ar)
   {
      if (m() != matrixPtr_->capacity1()) {
         UTIL_THROW("Error: Logical size m() != DMatrix<Type>::capacity1()");
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
   void DMatrixParam<Type>::bcastValue()
   {  
      if (!(matrixPtr_->isAllocated())) {
         matrixPtr_->allocate(m(), n());
      } else {
         if (m() != matrixPtr_->capacity1()) {
            UTIL_THROW("Error: Logical size m() > DMatrix<Type>::capacity1()");
         }
         if (n() != matrixPtr_->capacity2()) {
            UTIL_THROW("Error: Logical size n() > DMatrix<Type>::capacity2()");
         }
      }
      bcast<Type>(ioCommunicator(), *matrixPtr_, m(), n(), 0); 
   }
   #endif

   /*
   * Write a DMatrixParam.
   */
   template <class Type>
   void DMatrixParam<Type>::writeParam(std::ostream &out)
   {
      if (isActive()) {
         // Preconditions
         if (!(matrixPtr_->isAllocated())) {
            UTIL_THROW("Cannot read unallocated DMatrix");
         }
         if (m() > matrixPtr_->capacity1()) {
            UTIL_THROW("Error: Logical size m() > DMatrix<Type>::capacity1()");
         }
         if (n() > matrixPtr_->capacity2()) {
            UTIL_THROW("Error: Logical size n() > DMatrix<Type>::capacity2()");
         }
  
         if (hasBrackets()) {
            out << indent() << label_ << std::endl;
         } 
         Label space("");
         int i, j;
         for (i = 0; i < m(); ++i) {
            if (i == 0 && !hasBrackets()) {
               out << indent() << label_;
            } else {
               out << indent() << space;
            }
            for (j = 0; j < n(); ++j) {
               out << std::right << std::scientific 
                   << std::setprecision(Parameter::Precision) 
                   << std::setw(Parameter::Width)
                   << (*matrixPtr_)(i, j);
            }
            out << std::endl;
         }
         if (hasBrackets()) {
            out << indent() << ")" << std::endl;
         } 
      }
   }

} 
#endif
