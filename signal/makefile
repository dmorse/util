
include ../../config.mk
include $(SRC_DIR)/util/signal/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_signal_OBJS)

clean:
	rm -f $(util_signal_OBJS) $(util_signal_OBJS:.o=.d)

clean-deps:
	rm -f $(util_signal_OBJS:.o=.d)

-include $(util_signal_OBJS:.o=.d)

