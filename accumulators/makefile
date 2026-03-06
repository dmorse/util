
include ../../config.mk
include $(SRC_DIR)/util/accumulators/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_accumulators_OBJS)

clean:
	rm -f $(util_accumulators_OBJS) $(util_accumulators_OBJS:.o=.d)

.PHONY: all clean

-include $(util_accumulators_OBJS:.o=.d)

