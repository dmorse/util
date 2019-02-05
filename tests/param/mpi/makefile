BLD_DIR_REL =../../../..
include $(BLD_DIR_REL)/config.mk
include $(BLD_DIR)/util/config.mk
include $(SRC_DIR)/util/patterns.mk
include $(SRC_DIR)/util/sources.mk

TEST_DIR=$(BLD_DIR)/util/tests/param/mpi
include $(TEST_DIR)/sources.mk

all: $(util_tests_param_mpi_EXES)

clean:
	rm -f $(util_tests_param_mpi_EXES) 
	rm -f $(util_tests_param_mpi_OBJS) 
	rm -f $(util_tests_param_mpi_OBJS:.o=.d)

clean-outputs:
	@rm -f $(TEST_DIR)/out/*

-include $(util_tests_param_mpi_OBJS:.o=.d)
-include $(util_OBJS:.o=.d)
