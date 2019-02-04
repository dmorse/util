
util_mpi_=util/mpi/MpiFileIo.cpp 

ifdef UTIL_MPI
util_mpi_+=\
    util/mpi/MpiTraits.cpp \
    util/mpi/MpiSendRecv.cpp \
    util/mpi/MpiStructBuilder.cpp
    #util/mpi/MpiLogger.cpp 
endif

util_mpi_SRCS=$(addprefix $(SRC_DIR)/, $(util_mpi_))
util_mpi_OBJS=$(addprefix $(BLD_DIR)/, $(util_mpi_:.cpp=.o))

