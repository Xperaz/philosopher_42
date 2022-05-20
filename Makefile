HEADER=philosophers.h

SRC_FILE = main.c errors.c utils.c ft_atoi.c

NAME = philo
OBJ_FILE = $(SRC_FILE:.c=.o)
all: $(NAME)

$(NAME):	$(OBJ_FILE) $(HEADER)
		gcc -Wall -Wextra -Werror $(OBJ_FILE) -o $(NAME)

%.o: %.c ${HEADER}
		gcc -Wall -Wextra -Werror  -c $<

clean:
	rm -f $(OBJ_FILE)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
.PHONY : all clean fclean re