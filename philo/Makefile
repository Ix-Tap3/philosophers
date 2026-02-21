#==================================== MAKEFILE ====================================#

NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRCS_DIR = srcs
SRCS = main.c
OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

#==================================== COLORS ====================================#

ESC		= \033
RESET   = $(ESC)[0m
BOLD    = $(ESC)[1m

PRIMARY = $(ESC)[38;2;120;80;200m
INFO    = $(ESC)[38;2;160;120;220m
ACCENT  = $(ESC)[38;2;200;160;255m
WARN    = $(ESC)[38;2;220;120;160m
ERROR   = $(ESC)[38;2;200;60;120m

#==================================== HEADER ====================================#

define HEADER
@printf "$(ESC)[38;2;214;188;250m ██████╗ ██╗  ██╗██╗██╗      ██████╗$(RESET)\n"
@printf "$(ESC)[38;2;178;140;230m ██╔══██╗██║  ██║██║██║     ██╔═══██╗$(RESET)\n"
@printf "$(ESC)[38;2;142;102;200m ██████╔╝███████║██║██║     ██║   ██║$(RESET)\n"
@printf "$(ESC)[38;2;110;70;170m ██╔═══╝ ██╔══██║██║██║     ██║   ██║$(RESET)\n"
@printf "$(ESC)[38;2;85;45;130m ██║     ██║  ██║██║███████╗╚██████╔╝$(RESET)\n"
@printf "$(ESC)[38;2;80;34;116m ╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝$(RESET)\n"
endef

#==================================== PHONY ====================================#

.PHONY: all bonus clean fclean re

#==================================== RULES ====================================#

all: header $(NAME)
	@printf "$(PRIMARY)Build Finished !$(RESET)\n"

header:
	$(HEADER)
	@printf "\n";

$(NAME): $(OBJS)
	@printf "\n"
	@printf "$(INFO)Linking %s...$(RESET)\n" "$(NAME)"
	@$(CC) $(OBJS) -o $(NAME)
	@printf "$(PRIMARY)%s Ready !$(RESET)\n" "$(NAME)"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "\r$(ACCENT)Compiling object: %s$(RESET)$(ESC)[K" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean: header
	@printf "$(INFO)Cleaning $(NAME) objects...$(RESET)\n"
	@if [ -d "$(OBJS_DIR)" ]; then \
		for file in $(OBJS); do \
			printf "\r$(ACCENT)Cleaning $$file$(RESET)$(ESC)[K"; \
			rm -f $$file 2>/dev/null; \
		done; \
		printf "\n"; \
		rm -rf $(OBJS_DIR); \
	fi
	@printf "\r$(PRIMARY)$(NAME) objects cleaned!$(RESET)$(ESC)[K\n"

fclean: header clean
	@printf "$(ERROR)Cleanning %s...$(RESET)\n" "$(NAME)"
	@rm -rf $(NAME)

re: header fclean all
