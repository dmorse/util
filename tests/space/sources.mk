util_tests_space_=util/tests/space/Test.cc

util_tests_space_OBJS=\
     $(addprefix $(BLD_DIR)/, $(util_tests_space_:.cc=.o))

