# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmaes <rmaes@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/13 17:19:52 by rmaes         #+#    #+#                  #
#    Updated: 2024/02/20 15:33:30 by rmaes         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


#Colors

DEFAULT = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m

#main files
MAIN_FILES = main.c 
MAIN_DIR = main/
MAIN_DF = $(addprefix $(MAIN_DIR), $(MAIN_FILES))

#utils files
UTILS_FILES = error.c
UTILS_DIR = utils/
UTILS_DF = $(addprefix $(UTILS_DIR), $(UTILS_FILES))

#environment variables files
ENVP_FILES = envp.c ft_getenv.c
ENVP_DIR = envp/
ENVP_DF = $(addprefix $(ENVP_DIR), $(ENVP_FILES))

#executor files
EXECUTOR_FILES = $(BUILTIN_DF) executor.c executor_utils.c redirect.c
EXECUTOR_DIR = executor/
EXECUTOR_DF = $(addprefix $(EXECUTOR_DIR), $(EXECUTOR_FILES))

OBJECTS_DIR = objects/
OBJECTS = $(addprefix $(OBJECTS_DIR), $(FILES:.c=.o))

CFLAGS = -Wall -Wextra -Werror
CC = gcc -g
NAME = minishell

LIBFT_FOLDER = libraries/libftprintf/
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_FOLDER), $(LIBFT_NAME))

LIST_FOLDER = libraries/cdl_list/
LIST_NAME = cdl_list.a
LIST = $(addprefix $(LIST_FOLDER), $(LIST_NAME))

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(LIST)
	@echo "compiling: $(YELLOW)creating executable$(DEFAULT)"
#	 @$(CC) -o $@ $^ -lreadline -L/opt/homebrew/opt/readline/lib
	@$(CC) -o $@ $^ -lreadline -L/Users/rmaes/.brew/opt/readline/lib
	@echo "$(GREEN)$@ successfully compiled!$(DEFAULT)"

$(OBJECTS_DIR):
	@mkdir objects

$(LIBFT):
	@make -C $(LIBFT_FOLDER)

$(LIST):
	@make -C $(LIST_FOLDER)

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.c 
	@mkdir -p $(@D)
	@echo "compiling: $(YELLOW)$@$(DEFAULT)"
	@$(CC) -c $(CFLAGS) -I $(INCLUDES) -o $@ $^

clean:
	@echo "cleaning:  $(RED)removing object files$(DEFAULT)"
	@rm -f $(OBJECTS)
	@rm -rf $(OBJECTS_DIR)
	@make -C $(LIBFT_FOLDER) clean
	@make -C $(LIST_FOLDER) clean

fclean: clean
	@echo "cleaning:  $(RED)removing $(NAME)$(DEFAULT)"
	@rm -f $(NAME)
	@make -C $(LIBFT_FOLDER) rmlib
	@make -C $(LIST_FOLDER) rmlib

re: fclean all

.PHONY: all clean fclean re