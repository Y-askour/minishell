# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/25 15:54:39 by aboudoun          #+#    #+#              #
#    Updated: 2022/08/28 14:55:15 by yaskour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED=$'\x1b[31m
GREEN=$'\x1b[32m
PURPLE=$'\x1b[35m

NAME = minishell

INCLUDE = ./include
HEADER = $(INCLUDE)/minishell.h

CC = cc
FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
OFILES = ofiles
READLINE = $(shell brew --prefix  readline)


PARSER = $(addprefix parser/, parse_cmd_utils2 parse_cmd_utils parse_cmd)
FREE = $(addprefix free/, free_cmd free_tokens)
SYNTAX = $(addprefix syntax_/, check_syntax expand get_path)
TOKENIZER = $(addprefix tokenizer/, lexer1 lexer2 tokenizer tokens_list_utils)
ERROR = $(addprefix error_handler/, error_handler)
BUILTIN = $(addprefix builtin/, builtins  echo export helpers pwd unset export_helper cd cd_helper)
EXECUTION = $(addprefix executor/, get_env one_cmd one_cmd_helper pipe pipe_helper pipe_helper2 redirections pipe_helper3 redirections_helper $(BUILTIN))
FILES =  $(addprefix src/, minishell prompt heredoc $(FREE) $(PARSER) $(SYNTAX) $(TOKENIZER) $(ERROR) $(EXECUTION))

OBJ = $(addprefix $(OFILES)/, $(FILES:=.o))

all : $(NAME)


$(NAME): $(OBJ) $(LIBFT_LIB) $(HEADER)
	@$(CC) $(FLAGS) $(LIBFT_LIB) $(OBJ) -o $(NAME) -L $(READLINE)/lib -lreadline

$(OFILES)/src/%.o: src/%.c $(HEADER)
	@mkdir -p $(@D)
	@$(CC) -I$(READLINE)/include -I$(INCLUDE) $(FLAGS) -o $@ -c $<
	@echo "$(GREEN)" "compiling $<"

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)
	
clean:
	@rm -rf $(OBJ)
	@rm -rf ofiles
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)" "cleaning ..."

fclean : clean
	@rm -rf $(NAME) *.gch
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)" "full cleaning..."

re : fclean all
	@echo "$(PURPLE)" "remaking"

.PHONY: all clean fclean re bonus
