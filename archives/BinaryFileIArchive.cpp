/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, David Morse (morse012@um.edu) 
* Distributed under the terms of the GNU General Public License.
*/

#include "BinaryFileIArchive.h"

#include <vector>

namespace Util
{

   /*
   * Constructor.
   */
   BinaryFileIArchive::BinaryFileIArchive()
    : filePtr_(0),
      version_(0),
      createdFile_(true)
   {  filePtr_ = new std::ifstream(); }

   /*
   * Constructor.
   */
   BinaryFileIArchive::BinaryFileIArchive(std::string filename)
    : filePtr_(0),
      version_(0),
      createdFile_(true)
   {  filePtr_ = new std::ifstream(filename.c_str()); }

   /*
   * Constructor.
   */
   BinaryFileIArchive::BinaryFileIArchive(std::ifstream& file)
    : filePtr_(&file),
      version_(0),
      createdFile_(false)
   {}

   /*
   * Destructor.
   */
   BinaryFileIArchive::~BinaryFileIArchive()
   {
      if (filePtr_ && createdFile_) {  
         delete filePtr_; 
      }
   }

   /*
   * Return underlying file by reference.
   */
   std::ifstream& BinaryFileIArchive::file()
   {  return *filePtr_; }

   /*
   * Load a std::string from BinaryFileIArchive.
   */
   template <>
   void serialize(BinaryFileIArchive& ar, std::string& data, 
                  const unsigned int version)
   {
      size_t size;
      ar.unpack(size);
      // The saved size includes the terminating null character
      UTIL_CHECK(size > 0);
      std::vector<char> charvec(size);
      ar.unpack(&charvec[0], size);
      UTIL_CHECK(charvec[size - 1] == '\0');
      data.assign(&charvec[0], size - 1);
   }


}
