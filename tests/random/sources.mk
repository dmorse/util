util_tests_random_=util/tests/random/Test.cc

util_tests_random_OBJS=\
     $(addprefix $(BLD_DIR)/, $(util_tests_random_:.cc=.o))

