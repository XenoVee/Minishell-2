/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:37:57 by rmaes         #+#    #+#                 */
/*   Updated: 2024/07/11 14:10:39 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "env.h"
# include <stdbool.h>

/*Structs*/

enum e_toggle
{
	OFF = 0,
	ON,
};

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
	char				*str;
	char				*cmd;
	char				**args;
	bool				pipe;
	struct s_commands	*next;
	struct s_commands	*prev;
	int					fd_input;
	int					*fd_output;
}		t_commands;

#endif