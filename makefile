#-----------------------------------------------------------------------
# The copy of this namespace-level makefile in the src/util directory is 
# copied to the bld directory during initial package setup. Only the copy 
# in the src/ directory is stored in the repository.
#-----------------------------------------------------------------------
# Include *.mk makefile fragments

include ../config.mk
include $(SRC_DIR)/util/sources.mk
include $(SRC_DIR)/util/patterns.mk

#-----------------------------------------------------------------------
# Main targets 

all: $(util_OBJS) $(util_LIB)

clean:
	rm -f $(util_OBJS) $(util_OBJS:.o=.d) $(util_LIB)
	rm -f */*.o */*/*.o */*/*/*.o
	rm -f */*.d */*/*.d */*/*/*.d
	rm -f lib*.a
	cd tests; $(MAKE) clean

veryclean:
	$(MAKE) clean

test:
	@cd tests; $(MAKE) run

#-----------------------------------------------------------------------
# Include dependency files

-include $(util_OBJS:.o=.d)
