NAME		=	philosophers

SRCS		=	$(shell find srcs/ -name '*.c')
OBJS		=	${SRCS:.c=.o}
BOBJS		=	${BSRCS:.c=.o}

FLAGS		=	-pthread
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address

.c.o		:
	@${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)		:	${OBJS}
	@${CC} ${CFLAGS} ${FLAGS} ${OBJS} -o ${NAME}

all			:	${NAME}

clean		:
	@rm -rf ${OBJS}

fclean		:	clean
	@rm -rf ${NAME}

re			:	fclean all

# val			:	${NAME}
# 	@valgrind \
# 	--leak-check=full --tool=memcheck \
# 	--show-reachable=yes \
# 	--track-fds=yes \
# 	--errors-for-leak-kinds=all \
# 	--show-leak-kinds=all ./so_long	maps/map1.ber

.PHONY		:	all clean fclean re