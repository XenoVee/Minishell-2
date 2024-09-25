/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/30 15:25:50 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/25 16:02:47 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "executor.h"

// runs in parent process
void	endpipe(t_comm_data *cmd, int *pipenew, int *pipeold)
{
	if (cmd->next)
	{
		close(pipeold[0]);
		close(pipeold[1]);
	}
	if (cmd->prev)
	{
		pipeold[0] = pipenew[0];
		pipeold[1] = pipenew[1];
	}
}

// runs in child process
// opens the pipes using dup(2);
// pipe: array of two file descriptors. pipe[0] is read, pipe[1] is write
void	startpipe(t_comm_data *cmd, int *pipenew, int *pipeold)
{
	if (cmd->fd_input != -1)
	{
		dup2(cmd->fd_input, STDIN);
		close(pipeold[1]);
	}
	else if (cmd->next)
	{
		close(pipeold[1]);
		dup2(pipeold[0], STDIN);
		close(pipeold[0]);
	}
	if (cmd->fd_output)
	{
		close(pipenew[0]);
		dup2(cmd->fd_output, STDOUT);
	}
	else if (cmd->prev)
	{
		close(pipenew[0]);
		dup2(pipenew[1], STDOUT);
		close(pipenew[1]);
	}
}
