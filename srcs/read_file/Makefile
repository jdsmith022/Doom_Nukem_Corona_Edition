# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: nde-wild <nde-wild@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/03/19 15:43:30 by nde-wild       #+#    #+#                 #
#    Updated: 2020/03/08 14:21:25 by rsteigen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = doom_nukem

# FLAGS = -Wall -Werror -Wextra

LIBFT = libft

FILES = main.c error.c read_file.c add_info_to_lib.c

HEADER = doom_nukem.h

OBJ = $(FILES: .c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
		@gcc $(FLAGS) -o $@ $<

$(NAME): $(OBJ)
		@make -C $(LIBFT)
		@gcc -o $(NAME) $(FLAGS) $(OBJ) -L $(LIBFT) -lft

clean:
		@make -C $(LIBFT) clean

fclean: clean
		rm -rf $(NAME)
		@make -C $(LIBFT) fclean

re: fclean all
		@make -C $(LIBFT) re
