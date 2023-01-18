# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2023/01/18 18:07:49 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philosophers

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

SRCS	=\
./main.c\
./src/utils/memory/ft_memcpy.c\
./src/utils/memory/ft_calloc.c\
./src/utils/atoi.c\
./src/parser/parser.c\
./src/fork.c\
./src/philosopher.c\
./src/pool/pool_data.c\
./src/pool/pool.c\

INCS	=\
./inc\
./inc/utils\
./inc/utils/memory\
./inc/parser\
./inc\

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

valgrind:	fclean
			@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -g3"
			@valgrind														\
			-s																\
			--tool=helgrind													\
			./$(NAME) 5 100 10 10											\

valgrind_leaks:	fclean
			@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -g3"
			@valgrind														\
			-s																\
			--leak-check=full												\
			--show-leak-kinds=all											\
			--track-origins=yes												\
			--track-fds=yes													\
			./$(NAME) 10 10 10 10											\

.PHONY:		all clean fclean re
