
include ../../config.mk
include $(SRC_DIR)/util/archives/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_archives_OBJS)

clean:
	rm -f $(util_archives_OBJS) $(util_archives_OBJS:.o=.d)

-include $(util_archives_OBJS:.o=.d)

