##
## Practical aliases
##
CC		= g++
RM		= rm -rf
SRCS_DIR	= ./srcs

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall

##
## Libs
##

CPPFLAGS	+= -fopenmp

LIB		= -lgomp

##
## header location
##
CPPFLAGS 	+= -I./

##
## c++ version
##
CPPFLAGS	+= -std=c++11

##
## compilation options
##
PRGRM	= network

SRCS	= $(SRCS_DIR)/main.cpp \
	$(SRCS_DIR)/Simulation.cpp \
\
	$(SRCS_DIR)/Network.cpp \
	$(SRCS_DIR)/Neuron.cpp \
	$(SRCS_DIR)/Layer.cpp \
	$(SRCS_DIR)/Synapse.cpp \
\
	$(SRCS_DIR)/MNISTReader.cpp

OBJS	= $(SRCS:.cpp=.o)

##
## compilation
##
all:		$(PRGRM)

prgrm:		$(PRGRM)
$(PRGRM):	$(OBJS)
		$(CC) $(OBJS) -o $@ $(LIB)

##
## Clean
##
RM_OBJS	= $(OBJS)

RM_BIN	= $(PRGRM)

clean:
	$(RM) $(RM_OBJS)

fclean:	clean
	$(RM) $(RM_BIN)

re:	fclean all

##
## avoid problems
##
.PHONY:	all clean fclean re rclean prgrm $(PRGRM)
