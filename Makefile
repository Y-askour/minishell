RED=$'\x1b[31m
GREEN=$'\x1b[32m
PURPLE=$'\x1b[35m

NAME = minishell

HEADER = ./include/minishell.h \

CC = gcc
FLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

FILES = minishell.c\
		prompt.c\
		./tokenizer/lexer.c\
		./tokenizer/tokens_list_utils.c\
		./tokenizer/tokenizer.c\
		./tokenizer/tokenizer_functions.c\
		./tokenizer/tokenizer_functions2.c\
		./print/print_tokens.c\
		./syntax_/check_syntax.c\
		./syntax_/expand.c\
		./error_handler/error_handler.c\
		./parser/parse_cmd.c\
		./parser/parse_cmd_utils.c\
		./print/print_cmd.c\
		./free/free_cmd.c\
		./free/free_tokens.c\
		./executor/get_paths.c\
		./executor/pipe.c\
		./executor/one_cmd.c\
		./executor/builtin/builtins.c\
		./executor/builtin/cd.c\
		./executor/builtin/pwd.c\
		./executor/builtin/export.c\
		./executor/builtin/helpers.c\
		./executor/redirections.c\
		./executor/one_cmd_helper.c\
		./executor/pipe_helper.c\
		./executor/helper_pipe.c
	
OBJ = $(FILES:%.c=%.o)


all : $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB) $(HEADER)
	@$(CC) $(FLAGS) $(LIBFT_LIB) $(OBJ) -o $(NAME) -L ./readline/lib -lreadline -g

%.o : %.c $(HEADER)
	@$(CC) -I ./readline/include -I./include $(FLAGS) -o $@ -c $< -g
	@echo "$(GREEN)" "compiling $<"

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)
	
clean:
	@rm -rf $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "$(RED)" "cleaning ..."

fclean : clean
	@rm -rf $(NAME) *.gch
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo "$(RED)" "full cleaning..."

re : fclean all
	@echo "$(PURPLE)" "remaking"

.PHONY: all clean fclean re bonus
