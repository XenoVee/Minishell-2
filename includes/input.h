/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:58:05 by rmaes         #+#    #+#                 */
/*   Updated: 2024/07/26 14:28:32 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "structs.h"

t_commands	*input_parse(char *input, t_dllist *env);
void		input_parse_pipes(char *input, t_commands *cmds, int count);
void		parse_redirection(t_commands *cmds, int count);
void		remove_char(char *str, int position);
void		remove_white_spaces_and_tabs(char *input, char chr, int before);
void		free_cmds_memory(t_commands *cmds);
void		free_split_result(char **split_result);

#endif