include ../../../config.mk
include $(SRC_DIR)/util/sources.mk
include $(SRC_DIR)/util/tests/param/sources.mk
include $(SRC_DIR)/util/patterns.mk

TEST=$(BLD_DIR)/util/tests/param/Test

.SECONDARY:$(util_tests_param_OBJS)

all: $(util_tests_param_EXES)

run: $(TEST)
	@echo "BLD_DIR is $(BLD_DIR)"
	@echo "SRC_DIR is $(SRC_DIR)"
	$(TEST) $(SRC_DIR)/util/tests/ 
	@echo "Finished running $(TEST)"
	@cd $(SRC_DIR)/util/tests; $(MAKE) -s clean-outputs
	
quiet: $(TEST)
	@$(TEST) $(SRC_DIR)/util/tests/ > log
	@echo `grep failed log` ", "\
              `grep successful log` "in util/tests/log" > count
	@cat count
	@cd $(SRC_DIR)/util/tests; $(MAKE) -s clean-outputs

clean:
	cd mpi; $(MAKE) clean
	cd serial; $(MAKE) clean

clean-outputs:
	@cd serial; $(MAKE) clean-outputs

.PHONY: all run quiet clean clean-outputs

-include $(util_tests_param_OBJS:.o=.d)
-include $(util_OBJS:.o=.d)

