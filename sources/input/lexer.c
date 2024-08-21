/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 16:05:51 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/21 16:13:43 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"

static int	setmode(char *c, int i, int *mode)
{
	if (c[i] == '<')
		*mode = INFILE;
	else if (c[i] == '>' && c[i + 1] == '>')
	{
		*mode = OUTFILE_APPEND;
		return (2);
	}
	else if (c[i] == '>')
		*mode = OUTFILE;
	else
		return (0);
	return (1);
}

static int	make_fill_node(t_dllist *lex, char *command, int mode)
{
	int	l;

	l = 0;
	while (command[l] && !ms_isspace(command[l]))
		l++;
	cdl_listaddback(lex, cdl_nodenew(ft_substr(command, 0, l), num(mode)));
	lex->current = cdl_listgetnode(lex, lex->listlen - 1);
	printf("%s\nMode:%i\n", (char *)lex->current->name,
		*(int *)lex->current->value);
	return (l);
}

// new idea: cycle through whitespace until find special character
// then act based on the found
static t_dllist	*split_command(char *command)
{
	int			i;
	t_dllist	*lex;
	int			mode;

	mode = COMMAND;
	i = 0;
	lex = cdl_listinit();
	while (command[i])
	{
		while (ms_isspace(command[i]))
		{
			i++;
			i += setmode(command, i, &mode);
		}
		i += make_fill_node(lex, &command[i], mode);
		if (mode == COMMAND)
			mode = ARG;
	}
	return (lex);
}

void	lexer(char **array, t_commands *cmds)
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
