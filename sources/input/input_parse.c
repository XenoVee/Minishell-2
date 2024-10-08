/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 19:08:33 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/24 15:40:01 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include <stdio.h>

static void	func_cmd(t_comm_data *c_data, t_dllist *lex, t_dllist *env)
{
	int	i;
	int	do_while;

	i = 0;
	c_data->cmd = malloc ((sizeof(char *) * lex->arg_l) + 1);
	lex->current = lex->head;
	do_while = 0;
	while ((do_while == 0) || lex->current != lex->head)
	{
		if (*(int *)lex->current->value != HEREDOC)
			check_expansion(c_data, lex->current, env);
		if (*(int *)lex->current->value == COMMAND)
		{
			c_data->cmd[i] = lex->current->name;
			lex->current->name = NULL;
			i++;
		}
		do_while = 1;
		lex->current = lex->current->next;
	}
	c_data->cmd[i] = NULL;
}

static t_comm_data	*run_lexer(char **array, t_comm_data *c_data, t_dllist *env)
{
	t_dllist	*lex;

	lex = lexer(array[0]);
	func_cmd(c_data, lex, env);
	if (func_infiles(c_data, lex, env) || func_outfiles(c_data, lex, env))
	{
		perror("Minishell");
		free (c_data->cmd);
		if (c_data->next)
			free (c_data->next);
		cdl_listclear(lex);
		return (NULL);
	}
	cdl_listclear(lex);
	return (c_data);
}

static t_comm_data	*parser(char **array, t_comm_data *c_data, t_dllist *env)
{
	c_data->fd_input = 0;
	c_data->fd_output = 0;
	if (array[1] != NULL)
	{
		c_data->next = malloc(sizeof(t_comm_data) + 1);
		if (c_data->next == NULL)
			return (NULL);
		c_data->next->prev = c_data;
		if (parser(&array[1], c_data->next, env) == NULL)
		{
			free (c_data->next);
			return (NULL);
		}
	}
	else
		c_data->next = NULL;
	return (run_lexer(array, c_data, env));
}

t_comm_data	*input_parse(char *input, t_dllist *env)
{
	char		**array;
	t_comm_data	*c_data;

	array = input_split(input);
	if (array == NULL)
		return (NULL);
	c_data = malloc(sizeof(t_comm_data) + 1);
	c_data->prev = NULL;
	c_data = parser(array, c_data, env);
	return (c_data);
}
