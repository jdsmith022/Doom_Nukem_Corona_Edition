# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: JessicaSmith <JessicaSmith@student.coda      +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/11 00:04:23 by JessicaSmit   #+#    #+#                  #
#    Updated: 2020/09/11 00:04:25 by JessicaSmit   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

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
	@rm -f libft/libft.a
	@echo "removed $(NAME)"

re: fclean all
