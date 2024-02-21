/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:37:57 by rmaes         #+#    #+#                 */
/*   Updated: 2024/02/21 11:49:42 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "env.h"
# include <stdbool.h>

/*Structs*/

typedef struct s_data_fd
{
	char	*infile;
	char	*outfile;
	int		fd_in;
	int		fd_out;
	char	*delim_hd;
	bool	*quotes_hd;
}	t_data_fd;

typedef struct s_commands
{
	char		*cmd;
	char		**args;
	bool		pipe;
	t_commands	*next;
	t_commands	*prev;
	t_data_fd	*fd_data;
}		t_commands;

#endif