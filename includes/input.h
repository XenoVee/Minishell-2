/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:58:05 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 14:24:27 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "structs.h"

// input_parse
t_comm_data	*input_parse(char *input);
// void		parser(char **array, t_comm_data *cmds);

// input_utils
int			ms_isspace(char c);
void		*num(int i);

// lexer
t_dllist	*lexer(char *command);

#endif