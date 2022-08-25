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


PARSER = $(addprefix parser/, parse_cmd_utils2 parse_cmd_utils parse_cmd)
FREE = $(addprefix free/, free_cmd free_tokens)
SYNTAX = $(addprefix syntax_/, check_syntax expand)
TOKENIZER = $(addprefix tokenizer/, lexer1 lexer2 tokenizer tokens_list_utils)
ERROR = $(addprefix error_handler,/ error_handler)
BUILTIN = $(addprefix builtin/, builtins cd echo export helpers pwd unset)
EXECUTION = $(addprefix executor/, get_paths helper_pipe one_cmd one_cmd_helper pipe pipe_helper redirections $(BUILTIN))
FILES =  $(addprefix src/, minishell prompt.c heredoc.c $(FREE) $(PARSER) $(SYNTAX) $(TOKENIZER) $(ERROR) $(EXECUTION))

OBJ = $(addprefix $(OFILES)/, $(FILES:=.o))

all : $(NAME)

$(OFILES)/src/%.o: src/%.c $(HEADER)
	mkdir $(@D)
	@$(CC) -I ./readline1/include -I$(INCLUDE) $(FLAGS) -o $@ -c $<
	@echo "$(GREEN)" "compiling $<"

$(NAME): $(OBJ) $(LIBFT_LIB) $(HEADER)
	@$(CC) $(FLAGS) $(LIBFT_LIB) $(OBJ) -o $(NAME) -L ./readline1/lib -lreadline


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
