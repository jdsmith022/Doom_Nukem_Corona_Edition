# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: efrank <efrank@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/10 13:52:34 by efrank        #+#    #+#                  #
#    Updated: 2020/08/28 22:23:12 by elkanfrank    ########   odam.nl          #
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
	ft_islower ft_isupper ft_strndup get_next_line \
	ft_itoa_base ft_put_unsigned ft_intlen
OFILES_LIBFT = $(CFILES_LIBFT:%=.objects_libft/%.o)

all: $(NAME)

$(NAME): $(OFILES_LIBFT)
	@ar rc $(NAME) $^
	@echo "$(NAME) compiled successfully!"

.objects_libft/%.o: src/%.c src/libft.h
	@mkdir -p .objects_libft
	@$(CC) -o $@ -c $<

clean:
	@rm -rf .objects_libft .objects_printf

fclean: clean
	@rm -f $(NAME)

re: fclean all
