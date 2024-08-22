/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/21 15:39:36 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 14:24:27 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*Defines*/
enum e_strlens
{
	NAME=0,
	VALUE,
};
enum e_fildes
{
	STDIN = 0,
	STDOUT,
	STDERR,
};

/*Functions*/
int		executor(t_comm_data *cmd, t_dllist *env);
char	*pathfinder(char *find, t_dllist *env);
char	**arrayize(t_dllist *env);
size_t	safestrlen(char *s);
void	endpipe(t_comm_data *cmd, int *pipenew, int *pipeold);
void	startpipe(t_comm_data *cmd, int *pipenew, int *pipeold);

#endif