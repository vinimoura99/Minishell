# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      ::::::::    #
#                                                     +:+ +:+         +:+      #
#    By: vmoura-d <vmoura-d@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/18 12:37:19 by vmoura-d          #+#    #+#              #
#    Updated: 2025/10/18 18:44:33 by vmoura-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = Libft

# Directory paths
MAIN_DIR = $(SRC_DIR)/main
LEXER_DIR = $(SRC_DIR)/lexer
AUX_DIR = $(SRC_DIR)/aux
INPUT_VALIDATOR_DIR = $(SRC_DIR)/input_validator
CMD_DIR = $(SRC_DIR)/cmd
BUILTINS_DIR = $(SRC_DIR)/builtins
BINARY_TREE_DIR = $(SRC_DIR)/binary_tree
EXECUTOR_DIR = $(SRC_DIR)/executor
REDIRECTIONS_DIR = $(SRC_DIR)/redirections
HEREDOC_DIR = $(SRC_DIR)/heredoc
ENV_DIR = $(SRC_DIR)/env
SIGNAL_DIR = $(SRC_DIR)/signal

# Source files by module
MAIN_SRC = $(MAIN_DIR)/main.c

LEXER_SRC = $(LEXER_DIR)/lexer_1.c \
            $(LEXER_DIR)/lexer_2.c \
            $(LEXER_DIR)/ft_split_quotes_1.c \
            $(LEXER_DIR)/ft_split_quotes_2.c

AUX_SRC = $(AUX_DIR)/aux_1.c \
          $(AUX_DIR)/aux_2.c \
          $(AUX_DIR)/aux_3.c \
          $(AUX_DIR)/aux_4.c \
          $(AUX_DIR)/aux_5.c \
          $(AUX_DIR)/free_1.c \
          $(AUX_DIR)/free_2.c

INPUT_VALIDATOR_SRC = $(INPUT_VALIDATOR_DIR)/input_validator_1.c \
                      $(INPUT_VALIDATOR_DIR)/input_validator_2.c \
                      $(INPUT_VALIDATOR_DIR)/input_validator_3.c

CMD_SRC = $(CMD_DIR)/cmd_1.c \
          $(CMD_DIR)/cmd_2.c \
          $(CMD_DIR)/cmd_3.c \
          $(CMD_DIR)/cmd_4.c

BUILTINS_SRC = $(BUILTINS_DIR)/builtin_cd_1.c \
               $(BUILTINS_DIR)/builtin_cd_2.c \
               $(BUILTINS_DIR)/builtin_echo.c \
               $(BUILTINS_DIR)/builtin_env.c \
               $(BUILTINS_DIR)/builtin_exit.c \
               $(BUILTINS_DIR)/builtin_export_1.c \
               $(BUILTINS_DIR)/builtin_export_2.c \
               $(BUILTINS_DIR)/builtin_export_3.c \
               $(BUILTINS_DIR)/builtin_export_4.c \
               $(BUILTINS_DIR)/builtin_pwd.c \
               $(BUILTINS_DIR)/builtin_unset.c

BINARY_TREE_SRC = $(BINARY_TREE_DIR)/binary_tree_1.c \
                  $(BINARY_TREE_DIR)/binary_tree_2.c

EXECUTOR_SRC = $(EXECUTOR_DIR)/executor_1.c \
               $(EXECUTOR_DIR)/executor_2.c \
               $(EXECUTOR_DIR)/executor_3.c \
               $(EXECUTOR_DIR)/executor_4.c

REDIRECTIONS_SRC = $(REDIRECTIONS_DIR)/redirections.c

HEREDOC_SRC = $(HEREDOC_DIR)/heredoc_1.c \
              $(HEREDOC_DIR)/heredoc_2.c

ENV_SRC = $(ENV_DIR)/env_1.c \
          $(ENV_DIR)/env_2.c \
          $(ENV_DIR)/env_3.c \
          $(ENV_DIR)/get_user_1.c \
          $(ENV_DIR)/get_user_2.c

SIGNAL_SRC = $(SIGNAL_DIR)/signal.c

# Combine all sources
SRCS = $(MAIN_SRC) $(LEXER_SRC) $(AUX_SRC) $(INPUT_VALIDATOR_SRC) \
       $(CMD_SRC) $(BUILTINS_SRC) $(BINARY_TREE_SRC) $(EXECUTOR_SRC) \
       $(REDIRECTIONS_SRC) $(HEREDOC_SRC) $(ENV_SRC) $(SIGNAL_SRC)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJ_DIRS = $(sort $(dir $(OBJ)))

LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -Iinclude -I$(LIBFT_DIR)
RLFLAG = -Lvendor/readline/lib -lreadline

LPURPLE = \033[1;35m
LGREEN = \033[1;32m
LBLUE = \033[1;34m
YELLOW = \033[0;33m
RESET = \033[0m
CLEAR_LINE = \r\033[K
ASCII_LINES = \
" ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓    "\
"▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    "\
"▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    "\
"▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    "\
"▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒ "\
"░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░ "\
"░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░ "\
"░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   "\
"       ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░ "


all: $(OBJ_DIRS) $(LIBFT) $(NAME)

startup:
	@clear
	@printf "\033[2J\033[H"
	@for line in $(ASCII_LINES); do \
		printf "$(LPURPLE)%s$(RESET)\n" "$$line"; \
		sleep 0.05; \
	done
	@printf "\n$(LPURPLE)🚀 Building Minishell...$(RESET)\n\n"

$(OBJ_DIRS):
	@mkdir -p $@

$(NAME): $(OBJ) $(LIBFT)
	@$(MAKE) startup --no-print-directory
	@printf "$(YELLOW)⚙️  Linking $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) $(RLFLAG) -o $(NAME)
	@printf "$(LGREEN)✅ $(NAME) compiled successfully!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT):
	@make -C $(LIBFT_DIR) -s --no-print-directory
	
clean:
	@printf "$(YELLOW)🧹 Cleaning objects...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@rm -rf readline.supp
	@make -C $(LIBFT_DIR) clean -s --no-print-directory
	@printf "$(LGREEN)✅ Clean done!$(RESET)\n"

fclean: clean
	@printf "$(YELLOW)🗑️  Removing $(NAME) and libs...$(RESET)\n"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean -s --no-print-directory
	@printf "$(LGREEN)✅ Full clean done!$(RESET)\n"

re: fclean all

val:
	echo "{\n   leak readline\n   Memcheck:Leak\n...\n   fun:readline\n}\n{\n   leak add_history\n   Memcheck:Leak\n...\n   fun:add_history\n}" > readline.supp
	valgrind --suppressions=readline.supp --leak-check=full -s --show-leak-kinds=all --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re startup val