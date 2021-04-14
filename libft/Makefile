NAME = libft.a

all: $(NAME)

$(NAME):
	gcc -c *.c -Wall -Wextra -Werror
	ar cr $(NAME) *.o

clean:
	rm -rf *.o

fclean: clean 
	rm -rf $(NAME)

re: fclean all

