/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:38:52 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/09 18:04:07 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "minishell.h"
#include "signals.h"
#include "input.h"

void	free_cmds_memory(t_commands *cmds)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = 0;
	while (1)
	{
		j = 0;
		while (cmds[i].args[j])
		{
			free(cmds[i].args[j]);
			j++;
		}
		free(cmds[i].args);
		free(cmds[i].str);
		free(cmds[i].fd_output);
		if (!cmds[i].next)
			break ;
		i++;
	}
	free(cmds);
}

int	manage_input(t_dllist *env)
{
	char		*input;
	t_commands	*cmds;

	toggle_intercept(OFF);
	input = readline("[Minishell] ~$ ");
	if (!input || !ft_strcmp(input, "exit"))
	{
		free (input);
		return (1);
	}
	if (input[0] == '\0')
	{
		free (input);
		return (0);
	}
	add_history(input);
	cmds = input_parse(input);
	if (cmds)
	{
		executor(cmds, env);
		free_cmds_memory(cmds);
	}
	free (input);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_dllist	*env;

	++argc;
	++argv;
	env = envcpy(envp);
	while (1)
	{
		if (manage_input(env))
			break ;
	}
	cdl_listclear(env);
}
