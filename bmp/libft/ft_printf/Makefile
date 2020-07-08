# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: efrank <efrank@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/09 15:24:52 by fhignett       #+#    #+#                 #
#    Updated: 2019/04/16 18:17:10 by efrank        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =  libftprintf.a
EXECUTABLE = ft_printf
FILESC = get_flags.c print_float.c print_string.c print_hex.c \
print_unsigned.c flags.c number_length.c print_oct.c print_width.c \
ft_printf.c print_binary.c print_output.c print_width_extra.c \
print_char.c print_pointer.c put_data.c \
get_data_list.c print_decimal.c print_precision.c
FILESO = $(FILESC:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@echo "compiling..."
	@make -C libft
	@gcc $(FLAGS) -c $(FILESC)
	@mv libft/libft.a $(NAME)
	@ar rc $(NAME) $(FILESO)
	@ranlib $(NAME)
	@echo "done"

clean:
	@echo "cleaning..."
	@make clean -C libft
	@rm -f $(FILESO)

fclean: clean
	@echo "fcleaning..."
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all
