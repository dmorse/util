#include $(SRC_DIR)/util/tests/param/serial/sources.mk
#include $(SRC_DIR)/util/tests/param/mpi/sources.mk

#util_tests_param_=\
#    $(util_tests_param_serial_) \
#    $(util_tests_param_mpi_) \
#    util/tests/param/Test.cc 

util_tests_param_=util/tests/param/Test.cc 

util_tests_param_SRCS=\
     $(addprefix $(SRC_DIR)/, $(util_tests_param_))
util_tests_param_OBJS=\
     $(addprefix $(BLD_DIR)/, $(util_tests_param_:.cc=.o))
util_tests_param_EXES=\
     $(addprefix $(BLD_DIR)/, $(util_tests_param_:.cc=))

