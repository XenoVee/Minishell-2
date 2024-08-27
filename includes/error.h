/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:38:15 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/27 14:34:35 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/*includes*/
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libraries/libftprintf/libft.h"

/*Defines*/
# define ERR_QUOTES		"Unclosed quotes"

# define SUCCES 0
# define FAILURE 1

/*global variable*/

/*Functions*/
void		error(char *errmsg);
void		*parse_error(char *errmsg);

#endif