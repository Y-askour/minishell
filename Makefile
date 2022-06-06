RED=$'\x1b[31m
GREEN=$'\x1b[32m
PURPLE=$'\x1b[35m

NAME = minishell

HEADER = ./include/minishell.h \

CC = gcc
FLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

FILES = minishell.c\
		signal_handler.c\
		parcer/lexer.c\

OBJ = $(FILES:%.c=%.o)

all : $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB) $(HEADER)
	@$(CC) $(FLAGS) $(LIBFT_LIB) $(OBJ) -o $(NAME) -L ./readline/lib -lreadline

%.o : %.c $(HEADER)
	@$(CC) -I./readline/include -I./include $(FLAGS) -o $@ -c $<
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
