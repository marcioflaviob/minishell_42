NAME = pipex
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_PATH = ../libft/
INCDIR = ./includes/
SRCSDIR = ./srcs/
OBJDIR = ./objs/

SOURCES = $(wildcard $(SRCSDIR)*.c)
OBJECTS = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) -L$(LIBFT_PATH) -lft
	@echo "$@ has been successfully built!"

$(LIBFT):
	@echo "Building $(LIBFT) library"
	@make -C $(LIBFT_PATH) >/dev/null 2>&1

$(OBJDIR)%.o: $(SRCSDIR)%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@echo "Cleaning objects"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT_PATH) clean >/dev/null 2>&1

fclean: clean
	@echo "Cleaning $(NAME)"
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean >/dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re bonus
