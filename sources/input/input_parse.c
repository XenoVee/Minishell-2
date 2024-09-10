/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 19:08:33 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/10 16:17:16 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include <fcntl.h>
#include <sys/types.h>

void	init_struct(t_comm_data *c_data)
{
	c_data->cmd = 0;
	c_data->next = 0;
	c_data->prev = 0;
	c_data->fd_input = -1;
	c_data->fd_output = 0;
}

static void	parse_cmd(t_comm_data *c_data, t_dllist *lex, t_dllist *env)
{
	int	i;
	int	do_while;

	i = 0;
	c_data->cmd = malloc ((sizeof(char *) * lex->arg_l) + 1);
	lex->current = lex->head;
	do_while = 0;
	while ((do_while == 0) || lex->current != lex->head)
	{
		if (*(int *)lex->current->value == COMMAND)
		{
			check_expansion(c_data, lex->current, env);
			c_data->cmd[i] = lex->current->name;
			lex->current->name = NULL;
			i++;
		}
		do_while = 1;
		lex->current = lex->current->next;
	}
	c_data->cmd[i] = NULL;
}

int	func_infiles(t_comm_data *c_data, t_dllist *lex, t_dllist *env)
{
	int		do_while;
	int		fd;
	char	*file;

	do_while = 0;
	fd = 0;
	while ((do_while == 0) || lex->current != lex->head)
	{
		if (*(int *)lex->current->value == INFILE)
		{
			if (fd != 0)
				close (fd);
			file = pathfinder(lex->current->name, env);
			fd = open(file, O_RDONLY);
			free (file);
			if (fd == -1)
			{
				return (-1);
			}
		}
		c_data->fd_input = fd;
		do_while = 1;
		lex->current = lex->current->next;
	}
	return (0);
}

static t_comm_data	*parser(char **array, t_comm_data *c_data, t_dllist *env)
{
	t_dllist	*lex;

	if (array[1] != NULL)
	{
		c_data->next = malloc(sizeof(t_comm_data) + 1);
		c_data->next->prev = c_data;
		parser(&array[1], c_data->next, env);
	}
	else
		c_data->next = NULL;
	lex = lexer(array[0]);
	parse_cmd(c_data, lex, env);
	if (func_infiles(c_data, lex, env) == -1)
	{
		free_c_data(c_data);
		return (NULL);
	}
	cdl_listclear(lex);
	return (c_data);
}
	// func_outfiles;

t_comm_data	*input_parse(char *input, t_dllist *env)
{
	char		**array;
	t_comm_data	*c_data;

	array = input_split(input);
	if (array == NULL)
	{
		return (NULL);
	}
	c_data = malloc(sizeof(t_comm_data) + 1);
	c_data = parser(array, c_data, env);
	return (c_data);
}
