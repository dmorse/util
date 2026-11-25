include ../../../config.mk
include $(SRC_DIR)/util/sources.mk
include $(SRC_DIR)/util/patterns.mk

SHORT_DIR=util/tests/containers

TEST_DIR=$(SRC_DIR)/$(SHORT_DIR)
TEST=$(BLD_DIR)/$(SHORT_DIR)/Test
LOG_FILE=$(SHORT_DIR)/log

all: $(TEST)

run: $(TEST)
	@$(TEST) $(TEST_DIR)
	@echo "Finished running $(TEST)"
	@cd $(TEST_DIR); $(MAKE) -s clean-outputs
	
run-quiet: $(TEST)
	@$(TEST) $(TEST_DIR) > log
	@echo `grep failed log` ", "\
              `grep successful log` "in $(SHORT_DIR)" > count
	@cat count
	@cd $(TEST_DIR); $(MAKE) -s clean-outputs

clean:
	rm -f $(TEST).o
	rm -f $(TEST).d
	rm -f $(TEST)
	rm -f log
	$(MAKE) clean-outputs

clean-outputs:
	@rm -f tmp/*

.PHONY: all run run-quiet clean clean-outputs

-include $(TEST).d
-include $(util_DEPS)

