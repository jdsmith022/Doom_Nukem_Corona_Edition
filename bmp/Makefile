NAME = lib_bmp.a
CFILES = read utilities
OFILES = $(CFILES:%=.objects/%.o)

all: .objects $(NAME)

$(NAME): $(OFILES)
	@ar rc $@ $^
	@echo "$@ compiled successfully!"

.objects/%.o: srcs/%.c srcs/bmp.h
	@$(CC) -o $@ -c $<
	@echo "[+] $@"

.objects:
	@mkdir .objects

clean:
	@rm -rf .objects
	@echo "cleaned $(OFILES)"

fclean: clean
	@rm -f $(NAME)
	@echo "removed $(NAME)"

re: fclean all
