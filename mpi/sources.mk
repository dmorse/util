
util_mpi_=util/mpi/MpiFileIo.cpp 

ifdef UTIL_MPI
include $(SRC_DIR)/util/mpi/cxx/sources.mk
util_mpi_ += $(util_mpi_cxx_)
util_mpi_+= \
    util/mpi/MpiTraits.cpp \
    util/mpi/MpiLogger.cpp \
    util/mpi/MpiSendRecv.cpp \
    util/mpi/MpiStructBuilder.cpp
endif

util_mpi_SRCS=$(addprefix $(SRC_DIR)/, $(util_mpi_))
util_mpi_OBJS=$(addprefix $(BLD_DIR)/, $(util_mpi_:.cpp=.o))

