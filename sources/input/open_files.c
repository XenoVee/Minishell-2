/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 18:06:15 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/16 18:08:10 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static char	*abs_filepath(char *str, t_dllist *env)
{
	char	*new;
	char	*tmp;

	tmp = ft_strjoin("/home/", ft_getenv(env, "USER"));
	new = ft_tristrjoin(tmp, "/", &str[2]);
	free (str);
	free (tmp);
	return (new);
}

int	func_infiles(t_comm_data *c_data, t_dllist *lex, t_dllist *env)
{
	int		do_while;
	int		fd;

	do_while = 0;
	fd = 0;
	lex->current = lex->head;
	while ((do_while == 0) || lex->current != lex->head)
	{
		if (*(int *)lex->current->value == INFILE)
		{
			if (((char *)lex->current->name)[0] == '~')
				lex->current->name = abs_filepath(lex->current->name, env);
			if (fd != 0)
				close (fd);
			fd = open(lex->current->name, *(int *)lex->current->value);
			if (fd == -1)
				return (-1);
		}
		c_data->fd_input = fd;
		do_while = 1;
		lex->current = lex->current->next;
	}
	return (0);
}

int	func_outfiles(t_comm_data *c_data, t_dllist *lex, t_dllist *env)
{
	int		do_while;
	int		fd;

	do_while = 0;
	fd = 0;
	lex->current = lex->head;
	while ((do_while == 0) || lex->current != lex->head)
	{
		if (*(int *)lex->current->value == OUTFILE
			|| *(int *)lex->current->value == OUTFILE_APPEND)
		{
			if (((char *)lex->current->name)[0] == '~')
				lex->current->name = abs_filepath(lex->current->name, env);
			if (fd != 0)
				close (fd);
			fd = open(lex->current->name,
					*(int *)lex->current->value, S_IRUSR | S_IWUSR);
			if (fd == -1)
				return (-1);
		}
		c_data->fd_output = fd;
		do_while = 1;
		lex->current = lex->current->next;
	}
	return (0);
}
