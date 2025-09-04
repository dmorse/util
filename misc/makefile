BLD_DIR_REL =../..

include ../../config.mk
include $(SRC_DIR)/util/misc/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_misc_OBJS)

clean:
	rm -f $(util_misc_OBJS) $(util_misc_OBJS:.o=.d)

.PHONY: all clean

-include $(util_misc_OBJS:.o=.d)

