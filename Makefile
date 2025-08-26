NAME		:= philo

CC			:= cc
CFLAGS		:= -Wall -Wextra -pthread
STRICT_CFLAGS	:= -Wall -Wextra -Werror -pthread
INCDIR		:= includes
SRC_DIR		:= sources
OBJDIR		:= obj

SRCS		:= \
	philo.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/mini_libft.c \
	$(SRC_DIR)/philo_functions.c \
	$(SRC_DIR)/threads.c \
	$(SRC_DIR)/utils.c

OBJS		:= $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

.PHONY:		all clean fclean re strict

all:		$(NAME)

strict:
	$(MAKE) CFLAGS="$(STRICT_CFLAGS)" all

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCDIR) -MMD -MP -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean:		clean
	rm -f $(NAME)

re:		fclean all

-include $(DEPS)


