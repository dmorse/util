
include ../../config.mk
include $(SRC_DIR)/util/containers/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_containers_OBJS)

clean:
	rm -f $(util_containers_OBJS) $(util_containers_OBJS:.o=.d)

clean-deps:
	rm -f $(util_containers_OBJS:.o=.d)

-include $(util_containers_OBJS:.o=.d)

