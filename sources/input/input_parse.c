/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parse.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/08 19:08:33 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/09 19:22:08 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_commands *cmds)
{
		cmds->args = 0;
		cmds->cmd = 0;
		cmds->next = 0;
		cmds->prev = 0;
		cmds->fd_input = -1;
		cmds->fd_output = 0;
}

// whitespace is: space ' ', tab '\t', carriage return '\r',
// newline '\n', vertical tab ( '\v' ) and formfeed '\f'.
static int	ms_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
	{
		return (1);
	}
	return (0);
}

static t_dllist *split_command(char *command)
{
	int			i;
	int			l;
	t_dllist	*lex;

	i = 0;
	lex = cdl_listinit();
	while (command[i])
	{
		l = 0;
		while (ms_isspace(command[i]))
			i++;
		if (command[i] == '"' || command[i] == '\'')
		{
			l++;
			while (command[i + l] != '"' && command[i + l] != '\'')
				l++;
			l++;
		}
		else while (command[i + l] && !ms_isspace(command[i + l]))
			l++;
		cdl_listaddback(lex, cdl_nodenew(ft_substr(command, i, l), NULL));
		lex->current = cdl_listgetnode(lex, lex->listlen - 1);
		printf("%s\n", (char *)lex->current->name);
		i += l;
	}
	return (lex);
}

static void	lexer(char **array, t_commands *cmds)
{
	t_dllist	*lex;
	
	if (array[1] != NULL)
	{
		cmds->next = malloc(sizeof(t_commands) + 1);
		cmds->next->prev = cmds;
		lexer(&array[1], cmds->next);
	}
	else
		cmds->next = NULL;
	lex = split_command(array[0]);
	cdl_listclear(lex);
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