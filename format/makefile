
include ../../config.mk
include $(SRC_DIR)/util/format/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_format_OBJS)

clean:
	rm -f $(util_format_OBJS) $(util_format_OBJS:.o=.d)

clean-deps:
	rm -f $(util_format_OBJS:.o=.d)

-include $(util_format_OBJS:.o=.d)

