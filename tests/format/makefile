include ../../../config.mk
include $(SRC_DIR)/util/sources.mk
include $(SRC_DIR)/util/tests/format/sources.mk
include $(SRC_DIR)/util/patterns.mk

TEST=util/tests/format/Test

all: $(util_tests_format_OBJS) $(BLD_DIR)/$(TEST)

clean:
	rm -f $(util_tests_format_OBJS) $(util_tests_format_OBJS:.o=.d)
	rm -f $(BLD_DIR)/$(TEST) 

.PHONY: all clean

-include $(util_tests_format_OBJS:.o=.d)
