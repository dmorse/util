
include ../../config.mk
include $(SRC_DIR)/util/param/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_param_OBJS)

clean:
	rm -f $(util_param_OBJS) $(util_param_OBJS:.o=.d)

.PHONY: all clean

-include $(util_param_OBJS:.o=.d)

