util_tests_signal_=util/tests/signal/Test.cc

util_tests_signal_OBJS=\
     $(addprefix $(BLD_DIR)/, $(util_tests_signal_:.cc=.o))

