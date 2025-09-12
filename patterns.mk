# ---------------------------------------------------------------------
# File: src/util/patterns.mk
#
# This makefile contains the pattern rule used to compile all C++ source
# files in the util/ directory tree, which contains all source code for 
# the Util namespace. 
#
# This file is included by all "makefile" files in the util/ directory 
# tree. This file should be included in other makefiles after inclusion 
# of main config.mk configuration file of the build directory, and the
# util/config.mk namespace level config file. 
#-----------------------------------------------------------------------
# Makefile variable definitions

# All libraries needed in src/util
LIBS=$(util_LIB)

# Arguments for MAKEDEP
MAKEDEP_ARGS=$(CPPFLAGS) $(INCLUDES)
MAKEDEP_ARGS+= -A$(BLD_DIR)/config.mk
MAKEDEP_ARGS+= -S$(SRC_DIR)
MAKEDEP_ARGS+= -B$(BLD_DIR)

#-----------------------------------------------------------------------
# Pattern rules

# Rule to compile *.cpp class source files in src/util
$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@SDIR=$$(dirname "$@"); if [ ! -d "$$SDIR" ]; then mkdir -p "$$SDIR"; fi
	$(CXX) $(CPPFLAGS) $(INCLUDES) $(CXXFLAGS) -c -o $@ $<
ifdef MAKEDEP
	$(MAKEDEP) $(MAKEDEP_CMD) $(MAKEDEP_ARGS) $<
endif

# Rule to compile *.cc test programs in src/util/tests
$(BLD_DIR)/util/tests/%.o: $(SRC_DIR)/util/tests/%.cc 
	$(CXX) $(CPPFLAGS) $(INCLUDES) $(CXXFLAGS) -c -o $@ $<
ifdef MAKEDEP
	$(MAKEDEP) $(MAKEDEP_CMD) $(MAKEDEP_ARGS) $<
endif

# Rule to link *.cc test programs in src/util/tests
$(BLD_DIR)/util/tests/%: $(BLD_DIR)/util/tests/%.o $(LIBS)
	$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

