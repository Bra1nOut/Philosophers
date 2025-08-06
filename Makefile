NAME = philo
NAME_BONUS = philo_bonus
CC = cc
FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address #-fsanitize=thread
RM = rm -rf
INCLUDES = -I./includes -I./libft
GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[38;5;153m
NC = \033[0m
PURPLE = \033[0;35m
PINK = \033[38;5;205m

SRCS =	main.c init.c utils.c time.c routine.c monitor.c free.c

SRCS_BONUS = \

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
TARGET = $(NAME)

.PHONY: all clean fclean re bonus compile_with_progress

compile_with_progress:
	@echo "$(PURPLE)\e[1m┌─────$(NAME)──────────────────────────────────────┐\e"
	@echo "││$(NC)\e[1m		Compiling $(NAME) ⏳		 $(PURPLE)│"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"
	@echo ""

	@total=$(words $(SRCS)); \
	count=0; \
	bar_width=30; \
	for src in $(SRCS); do \
		count=$$((count + 1)); \
		obj=$$(echo $$src | sed 's/\.c$$/.o/'); \
		$(CC) $(FLAGS) -c -o $$obj $$src $(INCLUDES); \
		percent=$$(( 100 * count / total )); \
		done=$$(( (bar_width * count) / total )); \
		todo=$$(( bar_width - done )); \
		done_bar=$$(printf "%0.s#" $$(seq 1 $$done)); \
		todo_bar=$$(printf "%0.s-" $$(seq 1 $$todo)); \
		color=$$([ $$percent -eq 100 ] && echo "$(PURPLE)" || echo "$(RED)"); \
		printf "\r%s[%s%s] %3d%%$(NC)\033[K" "$$color" "$$done_bar" "$$todo_bar" "$$percent"; \
		done; \
		printf "\n"
		@echo ""

	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDES)

	@echo "$(PURPLE)\e[1m┌─────$(NAME)──────────────────────────────────────┐\e"
	@echo "││$(BLUE)		\e[1mCompilation finished ✅\e		 $(PURPLE) │"
	@echo "\e[1m└────────────────────────────────────────────────┘\e"


all: compile_with_progress

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
