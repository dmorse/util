util_tests_format_ = util/tests/format/Test.cc

util_tests_format_OBJS=\
     $(addprefix $(BLD_DIR)/, $(util_tests_format_:.cc=.o))

