SRC_DIR_REL =../../..

include $(SRC_DIR_REL)/config.mk
include $(SRC_DIR_REL)/util/config.mk
include $(SRC_DIR_REL)/util/patterns.mk
include $(SRC_DIR_REL)/util/mpi/cxx/sources.mk

all: $(util_mpi_cxx_OBJS)

clean:
	rm -f $(util_mpi_cxx_OBJS) $(util_mpi_cxx_OBJS:.o=.d)

clean-deps:
	rm -f $(util_mpi_cxx_OBJS:.o=.d)

-include $(util_mpi_cxx_OBJS:.o=.d)

