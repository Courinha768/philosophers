NAME		=	philosophers

SRCS		=	$(shell find srcs/ -name '*.c')
OBJS		=	${SRCS:.c=.o}
BOBJS		=	${BSRCS:.c=.o}

FLAGS		=	-pthread
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address

.c.o		:
	@${CC} ${CFLAGS} ${HEAD} -c $< -o ${<:.c=.o}

$(NAME)		:	credit ${OBJS} compile
	@${CC} ${CFLAGS} ${FLAGS} ${OBJS} -o ${NAME}

all			: ${NAME}

clean		:
	@rm -rf ${OBJS}
	@echo "\e[1mObject files deleted\033[0m"

fclean		:	clean
	@rm -rf ${NAME}
	@echo "\e[1mExecutable file deleted\033[0m"

re			:	fclean all

# val			:	${NAME}
# 	@valgrind \
# 	--leak-check=full --tool=memcheck \
# 	--show-reachable=yes \
# 	--track-fds=yes \
# 	--errors-for-leak-kinds=all \
# 	--show-leak-kinds=all

credit:
	@echo "▀██▀▀█▄  ▀██       ██  ▀██                                  ▀██"
	@echo " ██   ██  ██ ▄▄   ▄▄▄   ██    ▄▄▄    ▄▄▄▄▄   ▄▄▄   ▄▄▄ ▄▄▄   ██ ▄▄     ▄▄▄▄  ▄▄▄ ▄▄   ▄▄▄▄▄"
	@echo " ██▄▄▄█▀  ██▀ ██   ██   ██  ▄█  ▀█▄ ██▄  ▀ ▄█  ▀█▄  ██▀  ██  ██▀ ██  ▄█▄▄▄██  ██▀ ▀▀ ██▄  ▀"
	@echo " ██       ██  ██   ██   ██  ██   ██ ▄ ▀█▄▄ ██   ██  ██    █  ██  ██  ██       ██     ▄ ▀█▄▄"
	@echo "▄██▄     ▄██▄ ██▄ ▄██▄ ▄██▄  ▀█▄▄█▀ █▀▄▄█▀  ▀█▄▄█▀  ██▄▄▄▀  ▄██▄ ██▄  ▀█▄▄▄▀ ▄██▄    █▀▄▄█▀"
	@echo "                                                    ██"
	@echo "         Made by : \033[1;91mCourinha\033[m 		           ▀▀▀▀"

compile		:
	@echo "\e[1m\nCompiling\033[0m : putmsg.c				\e[1mDone\033[0m"
	@echo "\e[1mCompiling\033[0m : philosophers.c			\e[1mDone\033[0m"
	@echo "\e[1mCompiling\033[0m : philosophers_utils.c		\e[1mDone\033[0m"
	@echo "\e[1mCompiling\033[0m : error_handler.c			\e[1mDone\033[0m"
	@echo "\e[1mCompiling\033[0m : routine.c				\e[1mDone\033[0m"
	@echo "\nCompiling is \e[1mcomplete\033[0m"
.PHONY		:	all clean fclean re