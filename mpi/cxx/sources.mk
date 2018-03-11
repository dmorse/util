
util_mpi_cxx_=

ifdef UTIL_MPI
util_mpi_cxx_+=\
    util/mpi/cxx/MpiDatatype.cpp \
    util/mpi/cxx/MpiGroup.cpp \
    util/mpi/cxx/MpiOp.cpp \
    util/mpi/cxx/MpiStatus.cpp \
    util/mpi/cxx/MpiRequest.cpp \
    util/mpi/cxx/MpiPrequest.cpp \
    util/mpi/cxx/MpiComm.cpp \
    util/mpi/cxx/MpiIntracomm.cpp \
    util/mpi/cxx/MpiCartcomm.cpp \
    util/mpi/cxx/MpiGraphcomm.cpp \
    util/mpi/cxx/MpiIntercomm.cpp \
    util/mpi/cxx/MpiConstants.cpp \
    util/mpi/cxx/MpiFunctions.cpp 
endif

util_mpi_cxx_SRCS=$(addprefix $(SRC_DIR)/, $(util_mpi_cxx_))
util_mpi_cxx_OBJS=$(addprefix $(BLD_DIR)/, $(util_mpi_cxx_:.cpp=.o))

