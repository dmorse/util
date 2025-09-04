
include ../../config.mk
include $(SRC_DIR)/util/config.mk
include $(SRC_DIR)/util/patterns.mk
include $(SRC_DIR)/util/mpi/sources.mk

all: $(util_mpi_OBJS)

clean:
	rm -f $(util_mpi_OBJS) $(util_mpi_OBJS:.o=.d)

.PHONY: all clean

-include $(util_mpi_OBJS:.o=.d)

