/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:38:52 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/10 16:11:56 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "minishell.h"
#include "signals.h"
#include "input.h"

void	free_c_data(t_comm_data *c_data)
{
	int	i;

	if (!c_data)
		return ;
	i = 0;
	if (c_data->next)
		free_c_data(c_data->next);
	while (c_data->cmd[i])
	{
		free (c_data->cmd[i]);
		i++;
	}
	if (c_data->fd_input)
		close (c_data->fd_input);
	free (c_data);
}

static void	print_c_data(t_comm_data *c_data)
{
	int	i;
	int	j;

	j = 0;
	while (c_data)
	{
		i = 0;
		printf("arg %i: ", j);
		while (c_data->cmd[i] != NULL)
		{
			printf("%s ", c_data->cmd[i]);
			i++;
		}
		printf("\n");
		if (c_data->fd_input != 0)
			printf("FD infile: %i\n", c_data->fd_input);
		j++;
		c_data = c_data->next;
	}
}

int	manage_input(t_dllist *env)
{
	char		*input;
	t_comm_data	*c_data;

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
	c_data = input_parse(input, env);
	print_c_data(c_data);
	if (c_data || env)
	{
		// executor(c_data, env);
		// free_c_data_memory(c_data);
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
