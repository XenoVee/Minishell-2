/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:37:57 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/22 14:28:23 by rmaes         ########   odam.nl         */
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

enum e_lexer
{
	COMMAND = 0,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
};

typedef struct s_comm_data
{
	char				**cmd;
	struct s_comm_data	*next;
	struct s_comm_data	*prev;
	int					fd_input;
	int					*fd_output;
}		t_comm_data;

#endif