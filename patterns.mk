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

# All libraries needed in src/util
LIBS=$(util_LIB)

# Preprocessor macro definitions needed in src/util
DEFINES=$(UTIL_DEFS)

# Dependencies on build configuration files
MAKE_DEPS= -A$(BLD_DIR)/config.mk
MAKE_DEPS+= -A$(BLD_DIR)/util/config.mk

# Pattern rule to compile *.cpp class source files in src/util
$(BLD_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(CXX) $(INCLUDES) $(DEFINES) $(CXXFLAGS) -c -o $@ $<
ifdef MAKEDEP
	$(MAKEDEP) $(INCLUDES) $(DEFINES) $(MAKE_DEPS) -S$(SRC_DIR) -B$(BLD_DIR) $<
endif

# Pattern rule to compile *.cc test programs in src/util/tests
$(BLD_DIR)/util/tests/%.o: $(SRC_DIR)/util/tests/%.cc 
	$(CXX) $(INCLUDES) $(DEFINES) $(TESTFLAGS) -c -o $@ $<
ifdef MAKEDEP
	$(MAKEDEP) $(INCLUDES) $(DEFINES) $(MAKE_DEPS) -S$(SRC_DIR) -B$(BLD_DIR) $<
endif

# Pattern rule to link *.cc test programs in src/util/tests
$(BLD_DIR)/util/tests/%: $(BLD_DIR)/util/tests/%.o $(LIBS)
	$(CXX) $(INCLUDES) $(DEFINES) -o $@ $@.o $(LIBS) $(LDFLAGS)

