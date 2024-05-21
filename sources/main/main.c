/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:38:52 by rmaes         #+#    #+#                 */
/*   Updated: 2024/03/21 14:01:06 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "minishell.h"
#include "signals.h"
#include "input.h"

int	manage_input(void)
{
	char		*input;

	toggle_intercept(OFF);
	input = readline("[Minishell] ~$ ");
	if (!input)
	{
		free (input);
		return (1);
	}
	add_history(input);
	toggle_intercept(ON);
	if (!ft_strcmp(input, "exit"))
	{
		free (input);
		return (1);
	}
	t_commands *cmds = input_parse(input);
	if (cmds)
	{
		executor(cmds, 0);
		free_cmds_memory(cmds);
	}
	free (input);
	return (0);
}

int	main(void)
{
	while (1)
	{
		if (manage_input())
			break ;
	}
}
