CHECKER_NAME	:= checker
PS_NAME			:= push_swap
NAME			:= $(PS_NAME)

DEPEND_DIR		:= ./Dependencies
LIBFT_DIR		:= $(DEPEND_DIR)/Libft
LIBFT_LIB		:= $(LIBFT_DIR)/libft.a

SRC_DIR			:= ./src
INT_DIR			:= ./obj
SRCS			:= push_swap.c stack.c dlinked_list.c ps_object.c
OBJS			:= $(addprefix $(INT_DIR)/,$(SRCS:%.c=%.o))

VPATH			:= $(SRC_DIR) $(SRC_DIR)/utils

DEFINES			:=
INCLUDE_DIRS	:= -I $(LIBFT_DIR)/include

CC				:= cc
LINK_CMD		:= cc

ALL_CFLAGS		:= -std=c89 -Wall -Wextra -Werror -pedantic
ALL_LINKFLAGS	:= 

DEBUG_FLAGS		:= -g -Og -fsanitize=address
DEBUG_DEFINES	:= -DPS_DEBUG

RELEASE_FLAGS	:= -g -O2 -fsanitize=address
RELEASE_DEFINES	:= -DPS_RELEASE

DISTR_FLAGS		:= -Ofast -g0
DISTR_DEFINES	:= -DPS_DISTRIBUTION

SILENT		:= @
ifdef VERBOSE
	SILENT	:=
endif

all: debug

debug: ALL_CFLAGS += $(DEBUG_FLAGS)
debug: ALL_LINKFLAGS += -fsanitize=address
debug: DEFINES += $(DEBUG_DEFINES)
debug: $(NAME)

release: ALL_CFLAGS += $(RELEASE_FLAGS)
release: ALL_LINKFLAGS += -fsanitize=addresss
release: DEFINES += $(RELEASE_DEFINES)
release: $(NAME)

distribution: ALL_CFLAGS += $(DISTR_FLAGS)
distribution: ALL_CFLAGS += $(DISTR_DEFINES)
distribution: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(SILENT)echo Linking $(NAME)
	$(SILENT)$(LINK_CMD) $(ALL_LINKFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)

$(INT_DIR)/%.o: %.c
	$(SILENT)echo $(notdir $<)
	$(SILENT)mkdir -p $(INT_DIR)
	$(SILENT)$(CC) -c $< -o $@

$(LIBFT_LIB):
	$(SILENT) make -C $(LIBFT_DIR)

clean:
	$(SILENT)echo Cleaning object files
	$(SILENT)rm -f $(OBJS)

fclean: clean
	$(SILENT)echo Cleaning $(NAME)
	$(SILENT)rm -f $(NAME)

re: fclean all