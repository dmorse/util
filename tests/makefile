include ../../config.mk
include $(SRC_DIR)/util/sources.mk
include $(SRC_DIR)/util/patterns.mk

SHORT_DIR=util/tests
TEST_DIR=$(SRC_DIR)/$(SHORT_DIR)
TEST=$(BLD_DIR)/$(SHORT_DIR)/Test

.PHONY: all run run-quiet clean clean-outputs

all: $(TEST)

$(TEST): $(TEST).o $(LIBS)
	$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

run: $(TEST)
	@echo "BLD_DIR is $(BLD_DIR)"
	@echo "SRC_DIR is $(SRC_DIR)"
	$(TEST) $(TEST_DIR)/ 
	@echo "Finished running $(TEST)"
	@cd $(TEST_DIR); $(MAKE) -s clean-outputs
	
run-quiet: $(TEST)
	@$(TEST) $(TEST_DIR)/ > log
	@echo `grep failed log` ", "\
              `grep successful log` "in $(SHORT_DIR)/log" > count
	@cat count
	@cd $(TEST_DIR); $(MAKE) -s clean-outputs
	

clean:
	rm -f $(TEST)
	rm -f $(TEST).o
	rm -f $(TEST).d
	rm -f log count
ifeq ($(BLD_DIR),$(SRC_DIR))
	cd accumulators/unit; $(MAKE) clean
	cd archives; $(MAKE) clean
	cd containers; $(MAKE) clean
	cd format; $(MAKE) clean
	cd math; $(MAKE) clean
	cd misc; $(MAKE) clean
	cd param; $(MAKE) clean
	cd random; $(MAKE) clean
	cd signal; $(MAKE) clean
	cd space; $(MAKE) clean
	rm -f */*.o */*/*.o 
	rm -f */*.d */*/*.d
endif

clean-outputs:
	rm -f log count
	@cd accumulators/unit; $(MAKE) clean-outputs
	@cd archives; $(MAKE) clean-outputs
	@cd containers; $(MAKE) clean-outputs
	@cd param/serial; $(MAKE) clean-outputs
	@cd random; $(MAKE) clean-outputs


-include $(TEST).d
-include $(util_DEPS)
