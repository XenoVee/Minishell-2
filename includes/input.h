/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/23 15:58:05 by rmaes         #+#    #+#                 */
/*   Updated: 2024/02/23 15:58:25 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define input_H
#include "structs.h"

void input_loop(void);
t_commands *input_parse(char *input);
void free_cmds_memory(t_commands *cmds);

#endif