/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 16:05:51 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 14:28:33 by rmaes         ########   odam.nl         */
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

t_dllist	*lexer(char *command)
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
	}
	return (lex);
}
