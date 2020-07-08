# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: efrank <efrank@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/10 13:52:34 by efrank         #+#    #+#                 #
#    Updated: 2019/11/14 12:30:34 by efrank        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFILES_LIBFT = ft_putnbr ft_putchar ft_putstr ft_putendl ft_putnbr_fd \
	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_bzero ft_memdel \
	ft_strdel ft_strclr ft_striter ft_striteri ft_memset ft_memcpy \
	ft_memccpy ft_memmove ft_memchr ft_memalloc ft_strdup ft_strchr \
	ft_strrchr ft_strstr ft_strnstr ft_strcpy ft_strncpy ft_strcat \
	ft_strncat ft_strnew ft_strmap ft_strmapi ft_strsub ft_strjoin \
	ft_strtrim ft_itoa ft_strsplit ft_isalpha ft_isdigit ft_isalnum \
	ft_isascii ft_isprint ft_toupper ft_tolower ft_atoi ft_strcmp \
	ft_strncmp ft_memcmp ft_strequ ft_strnequ ft_strlen ft_strlcat \
	ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter ft_lstmap \
	ft_islower ft_isupper ft_strndup get_next_line ft_malloc_grid \
	ft_free_arrays ft_itoa_base ft_put_unsigned ft_intlen ft_map
CFILES_PRINTF = get_flags print_float print_string print_hex \
	print_unsigned flags number_length print_oct print_width \
	ft_printf print_binary print_output \
	print_width_extra print_char print_pointer put_data \
	get_data_list print_decimal print_precision
OFILES_LIBFT = $(CFILES_LIBFT:%=.objects_libft/%.o)
OFILES_PRINTF = $(CFILES_PRINTF:%=.objects_printf/%.o)

all: $(NAME)

$(NAME): $(OFILES_LIBFT) $(OFILES_PRINTF)
	@ar rc $(NAME) $^
	@echo "$(NAME) compiled successfully!"

.objects_libft/%.o: src/%.c src/libft.h
	@mkdir -p .objects_libft
	@$(CC) -o $@ -c $<

.objects_printf/%.o: ft_printf/%.c ft_printf/ft_printf.h src/libft.h
	@mkdir -p .objects_printf
	@$(CC) -o $@ -c $<

clean:
	@rm -rf .objects_libft .objects_printf

fclean: clean
	@rm -f $(NAME)

re: fclean all
