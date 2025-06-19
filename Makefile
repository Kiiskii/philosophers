CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
HDRS = -Iincludes/
HDR_PATH = includes/
OBJS_DIR = obj

SRCS =	srcs/main.c srcs/utils.c srcs/ph_exit.c srcs/parse_input.c \
		srcs/init_philos.c srcs/create_threads.c srcs/routine.c \
		srcs/init_mutexes.c srcs/monitor.c
NAME = philo
OBJS = $(patsubst srcs/%.c, $(OBJS_DIR)/%.o, $(SRCS))

GREEN = \033[32m
ORANGE = \033[38;5;214m
RESET = \033[0m

all: $(NAME)

debug: CFLAGS:=$(CFLAGS) -g
debug: re

sanitize: CFLAGS:=$(CFLAGS) -g -fsanitize=thread
sanitize: re

$(NAME): $(OBJS)
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)Compiling executable...$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(HDRS) -o $(NAME)
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)COMPILATION COMPLETE!$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"

$(OBJS_DIR)/%.o: srcs/%.c $(HDR_PATH)philos.h $(HDR_PATH)error_msgs.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HDRS) -c $< -o $@

clean:
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)Cleaning object files$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"
	rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(GREEN)----------------------------------------$(RESET)"
	@echo "$(ORANGE)Removing executable$(RESET)"
	@echo "$(GREEN)----------------------------------------$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug
