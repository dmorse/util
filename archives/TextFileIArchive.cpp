/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, David Morse (morse012@um.edu) 
* Distributed under the terms of the GNU General Public License.
*/

#include "TextFileIArchive.h"

#include <vector>

namespace Util
{

   /*
   * Constructor.
   */
   TextFileIArchive::TextFileIArchive()
    : filePtr_(0),
      version_(0),
      createdFile_(true)
   {  filePtr_ = new std::ifstream(); }

   /*
   * Constructor.
   */
   TextFileIArchive::TextFileIArchive(std::string filename)
    : filePtr_(0),
      version_(0),
      createdFile_(true)
   {  filePtr_ = new std::ifstream(filename.c_str()); }


   /*
   * Constructor.
   */
   TextFileIArchive::TextFileIArchive(std::ifstream& file)
    : filePtr_(&file),
      version_(0),
      createdFile_(false)
   {  
      if (!file.is_open()) {
         UTIL_THROW("File not open");
      }  
   }


   /*
   * Destructor.
   */
   TextFileIArchive::~TextFileIArchive()
   {  
      if (filePtr_ && createdFile_) {  
         delete filePtr_; 
      }
   }

   /*
   * Return underlying file by reference.
   */
   std::ifstream& TextFileIArchive::file()
   {  return *filePtr_; }

   /*
   * Read trailing whitespace and the newline at the end of a record.
   */
   void TextFileIArchive::endRecord()
   {
      if (!filePtr_->good()) return;
      int c = filePtr_->peek();
      while (c == ' ' || c == '\t' || c == '\r') {
         filePtr_->get();
         c = filePtr_->peek();
      }
      if (c == '\n') {
         filePtr_->get();
      }
   }

   /*
   * Load a std::string from TextFileIArchive.
   */
   template <>
   void serialize(TextFileIArchive& ar, std::string& data, 
                  const unsigned int version)
   {
      size_t size;
      ar.unpack(size);
      if (size > 0) {
         // Read size characters, including any whitespace
         data.resize(size);
         ar.file().read(&data[0], size);
         ar.endRecord();
      } else {
         data = "";
      }
   }

}
