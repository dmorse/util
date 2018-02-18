BLD_DIR_REL =../../../..
include $(BLD_DIR_REL)/config.mk
include $(BLD_DIR)/util/config.mk
include $(SRC_DIR)/util/patterns.mk
include $(SRC_DIR)/util/sources.mk

TEST_DIR=$(BLD_DIR)/util/tests/param/serial
include $(TEST_DIR)/sources.mk

TEST=$(TEST_DIR)/Test
.SECONDARY: $(TEST).o

all: $(TEST)

run: $(TEST)
	$(TEST)

clean:
	rm -f $(TEST)
	rm -f $(util_tests_param_serial_OBJS) 
	rm -f $(util_tests_param_serial_OBJS:.o=.d)
	rm -f $(util_tests_param_serial_OBJS:.o=)
	$(MAKE) clean-outputs

clean-outputs:
	@rm -f $(TEST_DIR)/out/*

-include $(util_tests_param_serial_OBJS:.o=.d)
-include $(util_OBJS:.o=.d)

