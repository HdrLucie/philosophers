SRCS =		srcs/philosophers.c			\
			srcs/utils.c				\
			srcs/init.c					\
			srcs/dining_philosophers.c	\
			srcs/time_utils.c			\
			srcs/print_utils.c			\
			srcs/exit.c					\
			srcs/launch_process.c		\
			srcs/manage_fork.c			\
			srcs/nb_meal.c				\

OBJS = 		${SRCS:.c=.o}

INCLUDE =	-Iinclude

NAME = 		philo

CC		= 	clang

CFLAGS	= 	-Wall -Wextra -Werror -pthread

.c.o:		${SRCS}
			${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${HEAD}
			${CC} ${OBJS} ${CFLAGS} ${INCLUDE} -o ${NAME}
			@echo "\033[33;31mCOMPILED\t\t\tCONGRATS\033[0m"

all: 		${NAME}

clean:
			@rm -f ${OBJS}
			@echo "\033[33;34mCLEAN !\t\t\t\tBUT YOU CAN DO BETTER\033[0m"

fclean:		clean
			rm -f ${NAME}
			@echo "\033[33;32mALL CLEAN !\t\t\tYOU'RE VERY PROPER\033[0m"

re:			fclean all
			@echo "\033[33;36mRECOMPILED !\t\t\tIT'S WORK NOW ?\033[0m"

.PHONY:		all fclean clean re
