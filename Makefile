# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yboudoui <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 14:53:15 by yboudoui          #+#    #+#              #
#    Updated: 2023/01/22 18:24:49 by yboudoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philosophers

CC					=	cc

CFLAGS				=	-Wall -Wextra -Werror

RM					=	rm -f

# **************************************************************************** #

SOURCES	= \
	main.c\
	utils/memory/ft_memcpy.c\
	utils/memory/ft_calloc.c\
	utils/atoi.c\
	parser/parser.c\
	fork.c\
	routine.c\
	routine_utils.c\
	philosopher.c\
	pool/pool_data.c\
	pool/pool.c\

INCLUDES = \
	. \
	utils \
	utils/memory \
	parser \

PROJECT_DIR = .
SRCS_DIR = $(PROJECT_DIR)/srcs
INCS_DIR = $(PROJECT_DIR)/incs
OBJS_DIR = $(PROJECT_DIR)/objs

SRCS = $(addprefix $(SRCS_DIR)/, $(SOURCES))
INCS = $(addprefix $(INCS_DIR)/, $(INCLUDES))
OBJS = $(patsubst $(SRCS_DIR)/%.c,$(OBJS_DIR)/%.o,$(patsubst $(SRCS_DIR)/%.s,$(OBJS_DIR)/%.o,$(SRCS)))

# **************************************************************************** #

all: $(NAME)

$(OBJS_DIR)/%.o : $(SRCS_DIR)/%.c
	@echo "Compiling $(notdir $<)..."
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(addprefix -I , $(INCS)) -c $< -o $@

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)
		@echo "\033[1;32mCompilation successful!\033[0m"
		@echo ""
		@echo "\033[1;34mUsage:\033[0m ./$(NAME) \033[1;33m<number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\033[0m"
		@echo ""
		@echo "\033[1;36mArguments:\033[0m"
		@echo "  \033[1;33m<number_of_philosophers>\033[0m – Number of philosophers (and forks)."
		@echo "  \033[1;33m<time_to_die> (ms)\033[0m – Time before a philosopher dies if they haven't eaten."
		@echo "  \033[1;33m<time_to_eat> (ms)\033[0m – Time required for a philosopher to eat."
		@echo "  \033[1;33m<time_to_sleep> (ms)\033[0m – Time a philosopher spends sleeping after eating."
		@echo "  \033[1;33m[number_of_times_each_philosopher_must_eat]\033[0m *(optional)* – If specified, the simulation ends once each philosopher has eaten this many times."

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

fsanitize: fclean
	@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -fsanitize=address"

valgrind: fclean
	@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -g3"
	@valgrind														\
	--tool=helgrind													\
	./$(NAME) 4 410 200 200										\

valgrind_leaks:	fclean
			@$(MAKE) all -C . CFLAGS="-Wall -Wextra -Werror -g3"
			@valgrind														\
			-s																\
			--leak-check=full												\
			--show-leak-kinds=all											\
			--track-origins=yes												\
			--track-fds=yes													\
			./$(NAME) 10 10 10 10

.PHONY:		all clean fclean re