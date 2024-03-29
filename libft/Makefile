NAME = libft.a
SOURCES = $(wildcard $(shell find . -name "*.c"))
OBJECTS = $(SOURCES:.c=.o)
OBJ_PATH = ../objs

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJECTS)
	@echo "Archiving $@"
	@$(AR) -r $@ $?
	@mkdir -p $(OBJ_PATH)
	@mv $(OBJECTS) $(OBJ_PATH)

bonus: $(OBJECTS)
	@echo "Creating bonus archive"
	@$(AR) -r $(NAME) $@

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@ >/dev/null 2>&1  # Redirect compilation output to /dev/null

clean:
	@echo "Cleaning objects"
	@rm -f *.o

fclean: clean
	@echo "Cleaning $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
