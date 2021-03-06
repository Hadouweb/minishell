CC = gcc -Werror -Wextra -Wall -g

SRCPATH = ./srcs
OPTION_L = $(SRCPATH)/option_l

INCPATH = ./includes

LIBFTPATH = ./libft

HEADER = -I $(LIBFTPATH)/includes -I $(INCPATH)

LIB = -L$(LIBFTPATH) -lft
LIBNAME = $(LIBFTPATH)/libft.a

SRC = 	$(SRCPATH)/main.c\
        $(SRCPATH)/m_set_data.c\
        $(SRCPATH)/m_free_memory.c\
        $(SRCPATH)/m_error.c\
        $(SRCPATH)/m_run_cmd.c\
        $(SRCPATH)/m_util.c\
        $(SRCPATH)/m_util2.c\
        $(SRCPATH)/m_check_builtin.c\
        $(SRCPATH)/m_echo.c\
        $(SRCPATH)/m_set_env_var.c\
        $(SRCPATH)/m_env.c\
        $(SRCPATH)/m_setenv.c\
        $(SRCPATH)/m_unsetenv.c\
        $(SRCPATH)/m_cd.c\
        $(SRCPATH)/m_exit.c\
        $(SRCPATH)/m_util_cd.c\
        $(SRCPATH)/m_util_echo.c\
        $(SRCPATH)/m_special_character.c\

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(LIBNAME) $(OBJ)
	@$(CC) -o $@ $(LIB) $^
	@echo "\n\033[39mCompilation done.\033[0m"

$(LIBNAME):
	@make -C $(LIBFTPATH) -j 8

%.o: %.c
	@$(CC) -o $@ -c $< $(HEADER)
	@echo "\033[34m█\033[0m\c"

clean:
	@make -C $(LIBFTPATH) clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C $(LIBFTPATH) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
