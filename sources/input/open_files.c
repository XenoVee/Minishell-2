/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/16 18:06:15 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/25 14:40:14 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <readline/readline.h>

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

static int	heredoc(int *fd, t_dllist *lex)
{
	char	*input;

	if (fd[0] != 0)
		close (fd[0]);
	if (pipe(fd) != 0)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(input, (char *)lex->current->name))
		{
			close (fd[1]);
			free (input);
			return (0);
		}
		write(fd[1], input, ft_strlen(input));
		write(fd[1], "\n", 1);
		free (input);
	}
}

static int	infile(int *fd, t_dllist *lex, t_dllist *env)
{
	if (((char *)lex->current->name)[0] == '~')
		lex->current->name = abs_filepath(lex->current->name, env);
	if (fd[0] != 0)
		close (fd[0]);
	fd[0] = open(lex->current->name, *(int *)lex->current->value);
	if (fd[0] == -1)
		return (-1);
	return (0);
}

int	func_infiles(t_comm_data *c_data, t_dllist *lex, t_dllist *env)
{
	int	fd[2];
	int	do_while;

	do_while = 0;
	fd[0] = 0;
	lex->current = lex->head;
	while ((do_while == 0) || lex->current != lex->head)
	{
		if (*(int *)lex->current->value == INFILE)
			if (infile(fd, lex, env) == -1)
				return (-1);
		if (*(int *)lex->current->value == HEREDOC)
			if (heredoc(fd, lex) == -1)
				return (-1);
		c_data->fd_input = fd[0];
		do_while = 1;
		lex->current = lex->current->next;
	}
	if (fd[0] == 0)
		c_data->fd_input = -1;
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
