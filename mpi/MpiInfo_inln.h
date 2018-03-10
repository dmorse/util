/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

/*
* The code in this file and related files implements a variant of t
* the MPI 1.2 C++ bindings. Development of this version of the MPI C++ 
* bindings was motivated by the fact that the C++ bindings were 
* officially deprecated in MPI 2.2, and slated for removal in MPI 3.
*
* The code in this and other files in the same directory that implement
* a variant of the MPI C++ bindings was derived from the implementation 
* provided in the Open MPI (ompi) package, starting from corresponding 
* files in the ompi/ompi/mpi/cxx directory of an ompi source code 
* repository that was cloned from the github server in March 2018. A 
* list of copyright holders for the ompi source code is given in the 
* file named ompiCopyright in the same directory as this file. 
*/
   
   inline Info
   Info::Create()
   {
      MPI_Info newinfo;
      MPI_Info_create(&newinfo);
      return newinfo;
   }
   
   inline void
   Info::Delete(const char* key)
   {
       MPI_Info_delete(mpiInfo_, const_cast<char *>(key));
   }
   
   inline Info
   Info::Dup() const
   {
      MPI_Info newinfo;
      MPI_Info_dup(mpiInfo_, &newinfo);
      return newinfo;
   }
   
   inline void
   Info::Free()
   {
      MPI_Info_free(&mpiInfo_);
   }
   
   inline bool
   Info::Get(const char* key, int valuelen, char* value) const
   {
      int flag;
      MPI_Info_get(mpiInfo_, const_cast<char *>(key), valuelen, 
                   value, &flag);
      return bool(flag);
   }
   
   inline int
   Info::Get_nkeys() const
   {
      int nkeys;
      MPI_Info_get_nkeys(mpiInfo_, &nkeys);
      return nkeys;
   }
   
   inline void
   Info::Get_nthkey(int n, char* key) const
   {
      MPI_Info_get_nthkey(mpiInfo_, n, key);
   }
   
   inline bool
   Info::Get_valuelen(const char* key, int& valuelen) const
   {
      int flag;
      MPI_Info_get_valuelen(mpiInfo_, const_cast<char *>(key), 
                            &valuelen, &flag);
      return bool(flag);
   }
   
   inline void
   Info::Set(const char* key, const char* value)
   {
      MPI_Info_set(mpiInfo_, const_cast<char *>(key), 
                   const_cast<char *>(value));
   }
