NAME = philo
NAME_BONUS = philo_bonus
CC = cc
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address
RM = rm -rf
INCLUDES = -I./includes -I./libft
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[38;5;153m
NC = \033[0m
PURPLE = \033[0;35m
PINK = \033[38;5;205m
SRCS =	utils.c\
		free.c\
		routines.c\
		main.c

SRCS_BONUS = \

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

TARGET = $(NAME)

$(NAME): $(OBJS)
	@echo "$(PURPLE)\e[1m┌─────$(NAME)──────────────────────────────────────┐\e"
	@echo "││$(NC)\e[1m		Compiling $(NAME) ⏳		 $(PURPLE)│"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDES)
	@echo "$(PURPLE)\e[1m┌─────$(NAME)──────────────────────────────────────┐\e"
	@echo "││$(BLUE)		\e[1mCompilation finished ✅\e		 $(PURPLE) │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"

.c.o:
	@if [ "$(TARGET)" = "$(NAME)" ] && [ ! -f .mandatory ]; then \
		touch .mandatory; \
	fi
	@cc $(FLAGS) -c -o $@ $<

all: $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

bonus: clean $(OBJS_BONUS)
	@echo "$(PURPLE)\e[1m┌─────$(NAME_BONUS)──────────────────────────────┐\e"
	@echo "││$(PINK)\e[1m	  Compiling $(NAME_BONUS)'s Bonus ⏳     $(PURPLE)│\e"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"
	@$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(INCLUDES)
	@echo "$(PURPLE)\e[1m┌─────$(NAME_BONUS)──────────────────────────────┐\e"
	@echo "││$(BLUE)	      \e[1mCompilation finished ✅\e		 $(PURPLE) │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"

.PHONY: all clean fclean re bonus
