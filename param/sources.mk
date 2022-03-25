
util_param_= \
    util/param/Label.cpp \
    util/param/OptionalLabel.cpp \
    util/param/Begin.cpp \
    util/param/Blank.cpp \
    util/param/End.cpp \
    util/param/ParamComponent.cpp \
    util/param/ParamComposite.cpp \
    util/param/Parameter.cpp \
    util/param/ArrayParam.cpp 

util_param_SRCS=$(addprefix $(SRC_DIR)/, $(util_param_))
util_param_OBJS=$(addprefix $(BLD_DIR)/, $(util_param_:.cpp=.o))

