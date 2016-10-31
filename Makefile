CC = gcc -Werror -Wextra -Wall -g

SRCPATH = ./srcs
OPTION_L = $(SRCPATH)/option_l

INCPATH = ./includes

LIBFTPATH = ./libft

HEADER = -I $(LIBFTPATH)/includes -I $(INCPATH)

LIB = -L$(LIBFTPATH) -lft
LIBNAME = $(LIBFTPATH)/libft.a

SRC = 	$(SRCPATH)/main.c\

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(LIBNAME) $(OBJ)
	@$(CC) -o $@ $(LIB) $^
	@echo "\n\033[39mCompilation done.\033[0m"
	@echo " "
	@echo "   \033[33m                                         \033[043m        \033[0m"
	@echo "   \033[33m                      \033[41m              \033[0m     \033[043m        \033[0m"
	@echo "   \033[33m                    \033[41m                        \033[043m     \033[0m"
	@echo "   \033[33m                    \033[100m        \033[43m     \033[0m\033[100m   \033[0m\033[43m   \033[0m  \033[100m        \033[0m"
	@echo "   \033[33m                  \033[100m  \033[43m   \033[0m\033[100m   \033[0m\033[43m       \033[0m\033[100m   \033[0m\033[43m     \033[0m\033[100m        \033[0m"
	@echo "   \033[33m                  \033[100m  \033[43m░░░\033[0m\033[100m      \033[0m\033[43m       \033[0m\033[100m   \033[0m\033[43m        \033[0m\033[100m  \033[0m"
	@echo "   \033[33m                  \033[100m     \033[43m░░░░░░░░░░\033[0m\033[100m              \033[0m"
	@echo "   \033[33m                       \033[43m░░░░░░░░░░░░░░░░░░\033[0m\033[100m   \033[0m"
	@echo "   \033[33m             \033[100m             \033[41m   \033[0m\033[100m       \033[0m\033[41m   \033[0m\033[100m  \033[0m"
	@echo "   \033[33m           \033[100m                  \033[41m   \033[0m\033[100m       \033[0m\033[41m  \033[0m     \033[100m  \033[0m"
	@echo "   \033[33m         \033[043m    \033[0m\033[100m                \033[41m            \033[0m     \033[100m  \033[0m"
	@echo "   \033[33m         \033[043m      \033[0m   \033[041m     \033[0m\033[100m   \033[41m      \033[0m\033[043m  \033[0m\033[041m     \033[0m\033[043m  \033[0m\033[041m   \033[0m\033[100m    \033[0m"
	@echo "   \033[33m           \033[043m░░\033[0m  \033[100m   \033[0m\033[041m                          \033[0m\033[100m    \033[0m"
	@echo "   \033[33m             \033[100m       \033[0m\033[041m                        \033[0m\033[100m    \033[0m"
	@echo "   \033[33m           \033[100m       \033[0m\033[041m                  \033[0m"
	@echo "   \033[33m           \033[100m  \033[0m     \033[041m          \033[0m"
	@echo " "
	@echo " "
	@echo " \033[043m                                                             \033[0m"
	@echo "\033[043m                         \033[030mMINISHELL                             \033[0m"
	@echo "\033[043m                    \033[030m     nle-bret                              \033[0m"
	@echo " \033[043m                                                             \033[0m"
	@echo " "

$(LIBNAME):
	@make -C $(LIBFTPATH)

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