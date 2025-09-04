include ../../../config.mk
include $(SRC_DIR)/util/sources.mk
include $(SRC_DIR)/util/tests/containers/sources.mk
include $(SRC_DIR)/util/patterns.mk

TEST=util/tests/containers/Test

all: $(util_tests_containers_OBJS) $(BLD_DIR)/$(TEST)

clean:
	rm -f $(util_tests_containers_OBJS) $(util_tests_containers_OBJS:.o=.d)
	rm -f $(BLD_DIR)/$(TEST)
	$(MAKE) clean-outputs

clean-outputs:
	@rm -f tmp/*

.PHONY: all clean clean-outputs

-include $(util_tests_containers_OBJS:.o=.d)
-include $(util_OBJS:.o=.d)

