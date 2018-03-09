   // Groups, Contexts, and Communicators

   inline int
   Group::Get_size() const
   {
      int size;
      MPI_Group_size(mpiGroup_, &size);
      return size;
   }

   inline 
   int Group::Get_rank() const
   {
      int myrank;
      MPI_Group_rank(mpiGroup_, &myrank);
      return myrank;
   }

   inline void
   Group::Translate_ranks (const Group& group1, int n,
                           const int ranks1[],
                           const Group& group2, int ranks2[])
   {
      MPI_Group_translate_ranks(group1, n, const_cast<int *>(ranks1),
                                group2, const_cast<int *>(ranks2));
   }

   inline int
   Group::Compare(const Group& group1, const Group& group2)
   {
      int result;
      MPI_Group_compare(group1, group2, &result);
      return result;
   }

   inline 
   Group Group::Union(const Group &group1, const Group &group2)
   {
      MPI_Group newgroup;
      MPI_Group_union(group1, group2, &newgroup);
      return newgroup;
   }

   inline Group
   Group::Intersect(const Group &group1, const Group &group2)
   {
      MPI_Group newgroup;
      MPI_Group_intersection( group1,  group2, &newgroup);
      return newgroup;
   }

   inline 
   Group Group::Difference(const Group &group1, const Group &group2)
   {
      MPI_Group newgroup;
      (void)MPI_Group_difference(group1, group2, &newgroup);
      return newgroup;
   }

   inline 
   Group Group::Incl(int n, const int ranks[]) const
   {
      MPI_Group newgroup;
      MPI_Group_incl(mpiGroup_, n, const_cast<int *>(ranks), &newgroup);
      return newgroup;
   }

   inline 
   Group Group::Excl(int n, const int ranks[]) const
   {
      MPI_Group newgroup;
      MPI_Group_excl(mpiGroup_, n, const_cast<int *>(ranks), &newgroup);
      return newgroup;
   }

   inline 
   void Group::Free()
   {  MPI_Group_free(&mpiGroup_); }
