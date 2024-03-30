
CC := cc

SRCDIR := srcs
OBJDIR := objs
INCDIR := includes
GNL_DIR := get_next_line

SRCS := $(wildcard $(SRCDIR)/*.c) $(wildcard $(GNL_DIR)/*.c)
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))


TARGET := minishell

CFLAGS := -Wall -Wextra -Werror -g -I$(INCDIR)
LDFLAGS := -lreadline

.PHONY: all clean fclean re

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

pipex:
	@$(MAKE) -C pipex

libft:
	@$(MAKE) -C libft

get_next_line:
	@$(MAKE) -C $(GNL_DIR)
