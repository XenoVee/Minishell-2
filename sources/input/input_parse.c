/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 19:08:33 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/05 16:48:46 by rmaes         ########   odam.nl         */
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

static void	parse_cmd(t_comm_data *c_data, t_dllist *lex, t_dllist *env)
{
	int	i;

	i = 0;
	c_data->cmd = malloc ((sizeof(char *) * lex->arg_l) + 1);
	while (lex->head && *(int *)lex->head->value == COMMAND)
	{
		check_expansion(c_data, lex->head, env);
		c_data->cmd[i] = lex->head->name;
		lex->head->name = NULL;
		cdl_listdelnode(lex, 0);
		printf("%s ", c_data->cmd[i]);
		i++;
	}
}

static void	parser(char **array, t_comm_data *c_data, t_dllist *env)
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
	printf("\n\n");
	cdl_listclear(lex);
}
	// func_infiles;
	// func_outfiles;

t_comm_data	*input_parse(char *input, t_dllist *env)
{
	char		**array;
	t_comm_data	*c_data;

	array = input_split(input);
	if (array == NULL)
		return (NULL);
	c_data = malloc(sizeof(t_comm_data) + 1);
	parser(array, c_data, env);
	return (c_data);
}
