/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 19:08:33 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/21 16:15:37 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"

void	init_struct(t_commands *cmds)
{
	cmds->args = 0;
	cmds->cmd = 0;
	cmds->next = 0;
	cmds->prev = 0;
	cmds->fd_input = -1;
	cmds->fd_output = 0;
}

t_commands	*input_parse(char *input)
{
	char		**array;
	t_commands	*cmds;

	array = ft_split(input, '|');
	cmds = malloc(sizeof(t_commands) + 1);
	lexer(array, cmds);
	return (cmds);
}
