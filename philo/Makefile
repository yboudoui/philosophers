# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2023/01/26 19:21:04 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

SRCS	=\
./main.c\
./ft_memcpy.c\
./ft_calloc.c\
./fork.c\
./pool_data.c\
./is_eating.c\
./pool.c\
./routine.c\
./routine_utils.c\
./parser.c\
./philosopher.c\
./atoi.c

INCS	=.

OBJS				=	$(SRCS:.c=.o)

# **************************************************************************** #


all:		$(NAME)

$(OBJS): %.o : %.c
		@$(CC) $(CFLAGS) $(addprefix -I , $(INCS)) -c $< -o $@
		@echo $(CC) $(CFLAGS) $@

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
			@echo $(CC) $(CFLAGS) $(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

fsanitize:	fclean
			@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -fsanitize=address"

ARG					= 200 410 200 200 10
#5 400 200 200
#4 400 200 200
#1 800 200 200
#5 800 200 200
#4 410 200 200
#4 310 200 100
#1 800 200 200
#5 800 200 200
#5 800 90 60

valgrind:	fclean
			@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -g3"
			@valgrind														\
			--tool=helgrind													\
			./$(NAME) $(ARG)												\

valgrind_leaks:	fclean
			@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -g3"
			@valgrind														\
			-s																\
			--leak-check=full												\
			--show-leak-kinds=all											\
			--track-origins=yes												\
			--track-fds=yes													\
			./$(NAME) $(ARG)												\

.PHONY:		all clean fclean re


