/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/20 15:38:15 by rmaes         #+#    #+#                 */
/*   Updated: 2024/09/10 14:52:22 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

/*includes*/
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libraries/libftprintf/libft.h"

/*Defines*/
# define START 1
# define END -1
# define RESET 10

/*Functions*/
void	logv(char *str, int m);

#endif