#ifdef UTIL_MPI

#include "MpiStructBuilder.h"
#include <util/global.h>

namespace Util
{

   /// Default constructor.
   MpiStructBuilder::MpiStructBuilder() 
    : base_(0),
      nMember_(0)
   {}
   
   /* 
   * Record address of a pointer to an instance of the class.
   */
   void MpiStructBuilder::setBase(void* objectAddress) 
   {  MPI_Get_address(objectAddress, &base_); }

   /* 
   * Add a member variable to the struct definition
   */
   void MpiStructBuilder::addMember(void* memberAddress, MPI_Datatype type, int count)
   {
      MPI_Get_address(memberAddress, &addresses_[nMember_]);
      types_[nMember_] = type;
      counts_[nMember_] = count;
      ++nMember_;
   }

   /*
   * Build and commit a user-defined MPI Struct datatype.
   *
   * \param mpiType new MPI datatype (on output).
   */
   void MpiStructBuilder::commit(MPI_Datatype& mpiType) 
   {
      for (int i = 0; i < nMember_; ++i) {
         addresses_[i] = addresses_[i] - base_;
      }
      MPI_Type_create_struct(nMember_, counts_, addresses_, types_, &mpiType);
      MPI_Type_commit(&mpiType);
   }

}
#endif
