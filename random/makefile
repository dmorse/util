
include ../../config.mk
include $(SRC_DIR)/util/random/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_random_OBJS)

clean:
	rm -f $(util_random_OBJS) $(util_random_OBJS:.o=.d)

.PHONY: all clean

-include $(util_random_OBJS:.o=.d)

