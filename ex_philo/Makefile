SRCS = philo/philo.c \
	   philo/ft_atoi.c \
	   philo/ft_isdigit.c \

OBJS = $(SRCS:.c=.o)

NAME = philos
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all