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

# Dependencies on build configuration files
UTIL_CFGS= -A$(BLD_DIR)/config.mk
UTIL_CFGS+= -A$(BLD_DIR)/util/config.mk

# All libraries needed in src/util
LIBS=$(util_LIB)

#-----------------------------------------------------------------------
# Pattern rules

# Rule to compile *.cpp class source files in src/util
$(BLD_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(CXX) $(INCLUDES) $(UTIL_DEFS) $(CXXFLAGS) -c -o $@ $<
ifdef MAKEDEP
	$(MAKEDEP) $(INCLUDES) $(UTIL_DEFS) $(CXXFLAGS) $(UTIL_CFGS) -S$(SRC_DIR) -B$(BLD_DIR) $<
endif

# Rule to compile *.cc test programs in src/util/tests
$(BLD_DIR)/util/tests/%.o: $(SRC_DIR)/util/tests/%.cc 
	$(CXX) $(INCLUDES) $(UTIL_DEFS) $(TESTFLAGS) -c -o $@ $<
ifdef MAKEDEP
	$(MAKEDEP) $(INCLUDES) $(UTIL_DEFS) $(CXXFLAGS) $(UTIL_CFGS) -S$(SRC_DIR) -B$(BLD_DIR) $<
endif

# Rule to link *.cc test programs in src/util/tests
$(BLD_DIR)/util/tests/%: $(BLD_DIR)/util/tests/%.o $(LIBS)
	$(CXX) -o $@ $@.o $(LIBS) $(LDFLAGS)

