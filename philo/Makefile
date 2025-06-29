NAME = philosophers
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC = philosophers.c tools.c simulation.c simulation_tools.c initializer.c

OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${OBJ}
	@echo "building the project..."
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean:
	@echo "cleaning ..."
	@${RM} ${OBJ}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all fclean clean re
.SECONDARY:
