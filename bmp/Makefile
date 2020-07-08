GREEN = $(shell printf "\e[38;5;10m")
WHITE = $(shell printf "\e[39m")
RED = $(shell printf "\033[0;31m")

NAME = lib_bmp.a
CFILES = read utilities
OFILES = $(CFILES:%=.objects/%.o)

all: .objects $(NAME)

$(NAME): $(OFILES)
	@echo "$(GREEN)[+]$(WHITE) compiling $@..."
	@ar rc $@ $^
	@echo "$@ compiled successfully!"

.objects/%.o: srcs/%.c srcs/bmp.h
	@$(CC) -o $@ -c $<

.objects:
	@mkdir .objects

clean:
	@rm -rf .objects
	@echo "cleaned $(NAME) object files"

fclean: clean
	@rm -f $(NAME)
	@echo "removed $(NAME)"

re: fclean all
