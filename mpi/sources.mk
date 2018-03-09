
util_mpi_=util/mpi/MpiFileIo.cpp 

ifdef UTIL_MPI
util_mpi_+=\
    util/mpi/MpiDatatype.cpp \
    util/mpi/MpiGroup.cpp \
    util/mpi/MpiOp.cpp \
    util/mpi/MpiStatus.cpp \
    util/mpi/MpiRequest.cpp \
    util/mpi/MpiPrequest.cpp \
    util/mpi/MpiComm.cpp \
    util/mpi/MpiIntracomm.cpp \
    util/mpi/MpiIntercomm.cpp \
    util/mpi/MpiTraits.cpp \
    util/mpi/MpiLogger.cpp \
    util/mpi/MpiSendRecv.cpp \
    util/mpi/MpiStructBuilder.cpp
endif

util_mpi_SRCS=$(addprefix $(SRC_DIR)/, $(util_mpi_))
util_mpi_OBJS=$(addprefix $(BLD_DIR)/, $(util_mpi_:.cpp=.o))

