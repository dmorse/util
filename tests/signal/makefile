include ../../../config.mk
include $(SRC_DIR)/util/sources.mk
include $(SRC_DIR)/util/tests/signal/sources.mk
include $(SRC_DIR)/util/patterns.mk

TEST=util/tests/signal/Test

all: $(util_tests_signal_OBJS) $(BLD_DIR)/$(TEST)

clean:
	rm -f $(util_tests_signal_OBJS) $(util_tests_signal_OBJS:.o=.d)
	rm -f $(BLD_DIR)/$(TEST) 

.PHONY: all clean

-include $(util_tests_signal_OBJS:.o=.d)
-include $(util_OBJS:.o=.d)

