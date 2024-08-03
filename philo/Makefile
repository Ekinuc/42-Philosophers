SRCS	= main.c utils.c launch.c rnt_fork.c
OBJS	= $(SRCS:.c=.o)
NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

all: $(NAME)
	clear

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean re
