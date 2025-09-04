
include ../../config.mk
include $(SRC_DIR)/util/math/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_math_OBJS)

clean:
	rm -f $(util_math_OBJS) $(util_math_OBJS:.o=.d)

.PHONY: all clean

-include $(util_math_OBJS:.o=.d)

