
include ../../config.mk
include $(SRC_DIR)/util/space/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_space_OBJS)

clean:
	rm -f $(util_space_OBJS) $(util_space_OBJS:.o=.d)

.PHONY: all clean

-include $(util_space_OBJS:.o=.d)

