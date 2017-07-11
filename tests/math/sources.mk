util_tests_math_=util/tests/math/Test.cc

util_tests_math_SRCS=\
     $(addprefix $(SRC_DIR)/, $(util_tests_math_))
util_tests_math_OBJS=\
     $(addprefix $(BLD_DIR)/, $(util_tests_math_:.cc=.o))

