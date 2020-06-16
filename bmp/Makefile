NAME = lib_bmp.a
CFILES = read utilities
OFILES = $(CFILES:%=.objects/%.o)

all: $(NAME)

$(NAME): $(OFILES)
	@ar rc $(NAME) $^
	@echo "compiled successfully!"

.objects/%.o: srcs/%.c srcs/bmp.h
	@mkdir -p .objects
	@$(CC) -o $@ -c $<

clean:
	@rm -rf .objects
	@echo "removed ofiles"

fclean: clean
	@rm -f $(NAME)
	@echo "removed binary"

re: fclean all 
