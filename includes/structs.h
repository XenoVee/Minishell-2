/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:37:57 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/21 16:17:41 by rmaes         ########   odam.nl         */
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
	ARG,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
};

typedef struct s_commands
{
	char				*str;
	char				*cmd;
	char				**args;
	struct s_commands	*next;
	struct s_commands	*prev;
	int					fd_input;
	int					*fd_output;
}		t_commands;

#endif