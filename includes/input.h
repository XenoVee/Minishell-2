/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:58:05 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/05 16:46:44 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "structs.h"
# include "minishell.h"

// input_parse
t_comm_data	*input_parse(char *input, t_dllist *env);
// void		parser(char **array, t_comm_data *cmds);

char		**input_split(char const *s);

// input_utils
int			ms_isspace(char c);
void		*num(int i);
int			skipover_quotes(char const *s, int *i, int j);
char		*find_var(char	*str, t_dllist *env);

// Expansion
void		check_expansion(t_comm_data *c_data, t_dlnode *node, t_dllist *env);

// lexer
t_dllist	*lexer(char *command);

#endif