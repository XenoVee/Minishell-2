# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: rmaes <rmaes@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/06/13 17:19:52 by rmaes         #+#    #+#                  #
#    Updated: 2024/08/21 16:09:54 by rmaes         ########   odam.nl          #
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

#input parser files
INPUT_PARSER_FILES = input_parse.c lexer.c input_utils.c
INPUT_PARSER_DIR = input/
INPUT_PARSER_DF = $(addprefix $(INPUT_PARSER_DIR), $(INPUT_PARSER_FILES))

#signals files
SIGNALS_FILES = signals.c 
SIGNALS_DIR = signals/
SIGNALS_DF = $(addprefix $(SIGNALS_DIR), $(SIGNALS_FILES))

#utils files
UTILS_FILES = error.c
UTILS_DIR = utils/
UTILS_DF = $(addprefix $(UTILS_DIR), $(UTILS_FILES))

#environment variables files
ENVP_FILES = envp.c ft_getenv.c
ENVP_DIR = envp/
ENVP_DF = $(addprefix $(ENVP_DIR), $(ENVP_FILES))

#builtins
BUILTIN_FILES = echo.c env.c unset.c export.c pwd.c cd.c exit.c
BUILTIN_DIR = builtins/
BUILTIN_DF = $(addprefix $(BUILTIN_DIR), $(BUILTIN_FILES))

#executor files
EXECUTOR_FILES = $(BUILTIN_DF) executor.c executor_utils.c redirect.c
EXECUTOR_DIR = executor/
EXECUTOR_DF = $(addprefix $(EXECUTOR_DIR), $(EXECUTOR_FILES))

SOURCES_DIR = sources/
FILES =	$(MAIN_DF) $(EXECUTOR_DF) $(UTILS_DF) $(ENVP_DF) $(SIGNALS_DF) $(INPUT_PARSER_DF)
SOURCES = $(addprefix $(SOURCES_DIR), $(FILES))

INCLUDES = includes -I/Users/rmaes/.brew/opt/readline/include -Ilibraries/libftprintf


OBJECTS_DIR = objects/
OBJECTS = $(addprefix $(OBJECTS_DIR), $(FILES:.c=.o))

CFLAGS = -g -Wall -Wextra -Werror
CC = gcc
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
	@$(CC) -o $@ $^ -lreadline
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

test: 
	@$(CC) test/test_input.c \
	sources/input/input_parse.c \
	sources/input/input_parse_util.c \
	sources/input/input_parse_pipes.c \
	sources/input/input_parse_redirection.c \
	sources/input/ft_split.c \
	-Iincludes/ \
	-Ilibraries/libftprintf \
	-Wall -Wextra -Werror -g

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