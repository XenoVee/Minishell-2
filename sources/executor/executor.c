/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:06:32 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/25 15:52:19 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

// if/elseifs to check if the command is a builtin. A builtin cannot be piped
static int	builtin(t_comm_data *c_data, t_dllist *env)
{
	int	fd;

	fd = 2;
	if (!c_data->next && !c_data->prev && c_data->fd_output)
		fd = c_data->fd_output;
	if (!ft_strcmp("echo", c_data->cmd[0]))
		bi_echo(c_data, fd);
	else if (!ft_strcmp("cd", c_data->cmd[0]))
		bi_cd(env, c_data);
	else if (!ft_strcmp("pwd", c_data->cmd[0]))
		bi_pwd(fd);
	else if (!ft_strcmp("export", c_data->cmd[0]))
		bi_export(c_data, env, fd);
	else if (!ft_strcmp("unset", c_data->cmd[0]))
		bi_unset(c_data, env);
	else if (!ft_strcmp("env", c_data->cmd[0]))
		bi_env(env, fd);
	else if (!ft_strcmp("exit", c_data->cmd[0]))
		bi_exit(c_data);
	else
		return (0);
	return (1);
}

// the child. Minishell works using execve(),
// which *replaces* the calling process with
// an executable passed as argument.
// if you were to call it in the main process, it would close minishell.
static void	child(t_comm_data *c_data, int *p_new, int *pipeold, t_dllist *env)
{
	char	*path;
	char	**envp;

	startpipe(c_data, p_new, pipeold);
	if (builtin(c_data, env))
		exit(0);
	else
	{
		path = pathfinder(c_data->cmd[0], env, 1);
		if (path == NULL)
			exit(1);
		if (access(path, X_OK) != 0)
			exit(2);
		if (env)
			envp = arrayize(env);
		if (execve(path, c_data->cmd, envp) == -1)
			perror("minishell");
		exit(1);
	}
}

// setup pipes, and create a child
static int	execute(t_comm_data *cmd, t_dllist *env, int *pipenew, int *pipeold)
{
	int	pid;
	int	status;

	// status = 0;
	if (cmd->next)
		pipe(pipenew);
	pid = fork();
	if (pid == 0)
		child(cmd, pipenew, pipeold, env);
	else
	{
		waitpid(pid, &status, 0);
		// if (WIFEXITED(status))
		// 	if (WEXITSTATUS(status) == 1)
		// 		exit (0);
		endpipe(cmd, pipenew, pipeold);
	}
	return (0);
}

// The executor runs with two arguments: a 'commands' struct list that contains
// all the information about the commands it is to run,
// and a linked list 'env' containing all the env variables.
int	executor(t_comm_data *cmd, t_dllist *env)
{
	int	pipenew[2];
	int	pipeold[2];

	pipenew[0] = 0;
	pipenew[1] = 0;
	pipeold[0] = 0;
	pipeold[1] = 0;
	if (!(cmd->next) && builtin(cmd, env))
		return (0);
	else
	{
		while (cmd->next)
			cmd = cmd->next;
		while (cmd)
		{
			execute(cmd, env, pipenew, pipeold);
			cmd = cmd->prev;
		}
	}
	return (0);
}
