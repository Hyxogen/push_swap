CHECKER_NAME		:= checker
PUSH_SWAP_NAME		:= push_swap
NAME				:= $(PUSH_SWAP_NAME)

DEPEND_DIR			:= ./Dependencies
LIBFT_DIR			:= $(DEPEND_DIR)/Libft
LIBFT_LIB			:= $(LIBFT_DIR)/libft.a

SRC_DIR				:= ./src
INT_DIR				:= ./obj
# SRCS				:= push_swap.c stack.c dlinked_list.c ps_object.c

CHECKER_SRCS		:= checker.c argument_parser.c ps_object.c stack.c dlinked_list.c \
						evaluator.c distance.c generator.c instruction.c
CHECKER_OBJS		:= $(addprefix $(INT_DIR)/,$(CHECKER_SRCS:%.c=%.o))

PUSH_SWAP_SRCS		:= push_swap.c argument_parser.c ps_object.c \
						evaluator.c instruction.c sorter.c quick_solver.c \
						evaluation.c malloc_utils.c vector2.c array_utils.c \
						generator.c int_deque.c bruteforcer.c distance.c
PUSH_SWAP_OBJS		:= $(addprefix $(INT_DIR)/,$(PUSH_SWAP_SRCS:%.c=%.o))

ALL_OBJS			:= $(CHECKER_OBJS) $(PUSH_SWAP_OBJS)

VPATH				:= $(SRC_DIR) $(SRC_DIR)/utils $(SRC_DIR)/checker $(SRC_DIR)/parser $(SRC_DIR)/solver \
						$(SRC_DIR)/solver/quick_solver
DEFINES				:=
INCLUDE_DIRS		:= -I $(LIBFT_DIR)/include

CC					:= cc
LINK_CMD			:= cc

ALL_CFLAGS			:= -std=c89 -Wall -Wextra -Werror -pedantic $(INCLUDE_DIRS)
ALL_LINKFLAGS		:=

DEBUG_CFLAGS		:= -g -O0 -fsanitize=address
DEBUG_LINKFLAGS		:= -fsanitize=address -fsanitize=undefined
DEBUG_DEFINES		:= -DPS_DEBUG

RELEASE_CFLAGS		:= -g -O2 -fsanitize=address
RELEASE_LINKFLAGS	:= -fsanitize=address -fsanitize=undefined
RELEASE_DEFINES		:= -DPS_RELEASE

# TODO test if -O2 might be better than -O3, also try unroll loops (probably does nothing though)
DISTR_CFLAGS		:= -Ofast -g0
DISTR_LINKFLAGS		:=
DISTR_DEFINES		:= -DPS_DISTRIBUTION

SILENT		:= @
ifdef verbose
	SILENT	:=
endif

ifndef config
	config := release
endif

ifeq ($(config), debug)
ALL_CFLAGS += $(DEBUG_CFLAGS)
ALL_LINKFLAGS += $(DEBUG_LINKFLAGS)
DEFINES += $(DEBUG_DEFINES)
else ifeq ($(config), release)
ALL_CFLAGS += $(RELEASE_CFLAGS)
ALL_LINKFLAGS += $(RELEASE_LINKFLAGS)
DEFINES += $(RELEASE_DEFINES)
else ifeq ($(config), distribution)
ALL_CFLAGS += $(DISTR_CFLAGS)
ALL_CFLAGS += $(DISTR_DEFINES)
ALL_LINKFLAGS += $(DISTR_LINKFLAGS)
endif

all: $(PUSH_SWAP_NAME)

$(CHECKER_NAME): $(CHECKER_OBJS) $(LIBFT_LIB)
	$(SILENT)echo Linking $@
	$(SILENT)$(LINK_CMD) $(ALL_LINKFLAGS) $(CHECKER_OBJS) $(LIBFT_LIB) -o $@

$(PUSH_SWAP_NAME): $(PUSH_SWAP_OBJS) $(LIBFT_LIB)
	$(SILENT)echo Linking $@
	$(SILENT)$(LINK_CMD) $(ALL_LINKFLAGS) $(PUSH_SWAP_OBJS) $(LIBFT_LIB) -o $@

#$(NAME): $(OBJS) $(LIBFT_LIB)
#	$(SILENT)echo Linking $(NAME)
#	$(SILENT)$(LINK_CMD) $(ALL_LINKFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(INT_DIR)/%.o: %.c
	$(SILENT)echo $(notdir $<)
	$(SILENT)mkdir -p $(INT_DIR)
	$(SILENT)$(CC) $(ALL_CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	$(SILENT) make -C $(LIBFT_DIR)

clean:
	$(SILENT)echo Cleaning object files
	$(SILENT)rm -f $(ALL_OBJS)

fclean: clean
	$(SILENT)echo Cleaning $(PUSH_SWAP_NAME)
	$(SILENT)rm -f $(PUSH_SWAP_NAME)
	$(SILENT)echo Cleaning $(CHECKER_NAME)
	$(SILENT)rm -f $(CHECKER_NAME)

re: fclean all