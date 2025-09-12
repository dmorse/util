
include ../../config.mk
include $(SRC_DIR)/util/xmltag/sources.mk
include $(SRC_DIR)/util/patterns.mk

all: $(util_xmltag_OBJS)

clean:
	rm -f $(util_xmltag_OBJS) $(util_xmltag_OBJS:.o=.d)

clean-deps:
	rm -f $(util_xmltag_OBJS:.o=.d)

-include $(util_xmltag_OBJS:.o=.d)

