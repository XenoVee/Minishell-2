/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 19:08:33 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 16:49:25 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"

void	init_struct(t_comm_data *c_data)
{
	c_data->cmd = 0;
	c_data->next = 0;
	c_data->prev = 0;
	c_data->fd_input = -1;
	c_data->fd_output = 0;
}

void	parse_cmd(t_comm_data *c_data, t_dllist *lex)
{
	int	i;

	i = 0;
	c_data->cmd = malloc ((sizeof(char *) * lex->arg_l) + 1);
	while (lex->head && *(int *)lex->head->value == COMMAND)
	{
		// check_expansion
		c_data->cmd[i] = lex->head->name;
		lex->head->name = NULL;
		cdl_listdelnode(lex, 0);
		printf("\n%s\n\n", c_data->cmd[i]);
		i++;
	}
}

void	parser(char **array, t_comm_data *c_data)
{
	t_dllist	*lex;

	if (array[1] != NULL)
	{
		c_data->next = malloc(sizeof(t_comm_data) + 1);
		c_data->next->prev = c_data;
		parser(&array[1], c_data->next);
	}
	else
		c_data->next = NULL;
	lex = lexer(array[0]);
	parse_cmd(c_data, lex);
	// func_infiles;
	// func_outfiles;
	cdl_listclear(lex);
}

t_comm_data	*input_parse(char *input)
{
	char		**array;
	t_comm_data	*c_data;

	array = ft_split(input, '|');
	c_data = malloc(sizeof(t_comm_data) + 1);
	parser(array, c_data);
	return (c_data);
}
