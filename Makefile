NAME = minishell
LIBFT = $(LIBFT_PATH)libft.a
LIBFT_PATH = ./libft/
INCDIR = ./includes/
GNLDIR = ./get_next_line/
SRCSDIR = ./srcs/
OBJDIR = ./objs/

# Find all source files, keeping their relative paths
SOURCES = $(wildcard $(SRCSDIR)**/*.c)
SOURCES += $(wildcard $(SRCSDIR)*.c)
SOURCES += $(wildcard $(GNLDIR)*.c)

# Create a list of object files with their relative paths preserved
OBJECTS = $(patsubst $(SRCSDIR)%.c, $(OBJDIR)%.o, $(SOURCES))
OBJECTS := $(patsubst $(GNLDIR)%.c, $(OBJDIR)%.o, $(OBJECTS))

CC = cc
LDFLAGS := -lreadline
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -I$(GNLDIR) -g3

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@echo "Linking $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) -L$(LIBFT_PATH) -lft
	@echo "$@ has been successfully built!"

$(LIBFT):
	@echo "Building $(LIBFT) library"
	@make -C $(LIBFT_PATH) >/dev/null 2>&1

# Rule to compile .c files to .o files, preserving the directory structure
$(OBJDIR)%.o: $(SRCSDIR)%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)%.o: $(GNLDIR)%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
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
