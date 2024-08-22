/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:38:52 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 14:55:59 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "minishell.h"
#include "signals.h"
#include "input.h"

// void	free_c_data_memory(t_comm_data *c_data)
// {
// 	int	i;
// 	int	j;

// 	if (!c_data)
// 		return ;
// 	i = 0;
// 	while (1)
// 	{
// 		j = 0;
// 		while (c_data[i].args[j])
// 		{
// 			free(c_data[i].args[j]);
// 			j++;
// 		}
// 		free(c_data[i].args);
// 		free(c_data[i].str);
// 		free(c_data[i].fd_output);
// 		if (!c_data[i].next)
// 			break ;
// 		i++;
// 	}
// 	free(c_data);
// }

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
	c_data = input_parse(input);
	if (c_data || env)
	{
	// 	executor(c_data, env);
	// 	free_c_data_memory(c_data);
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
