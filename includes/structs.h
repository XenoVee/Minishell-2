/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:37:57 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/19 18:26:22 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "env.h"
# include <fcntl.h>
# include <stdbool.h>

/*Structs*/

enum e_toggle
{
	OFF = 0,
	ON,
};

// COMMAND and HEREDOC are only defined this way to ensure
// they dont have the same value as any other entry
enum e_lexer
{
	COMMAND = O_RDWR,
	INFILE = O_RDONLY,
	HEREDOC = O_WRONLY,
	OUTFILE = O_WRONLY | O_CREAT | O_TRUNC,
	OUTFILE_APPEND = O_WRONLY | O_CREAT | O_APPEND,
};

typedef struct s_comm_data
{
	char				**cmd;
	struct s_comm_data	*next;
	struct s_comm_data	*prev;
	int					fd_input;
	int					fd_output;
}		t_comm_data;

#endif