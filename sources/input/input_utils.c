/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 16:08:18 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/21 16:15:43 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

// whitespace is: space ' ', tab '\t', carriage return '\r',
// newline '\n', vertical tab ( '\v' ) and formfeed '\f'.
int	ms_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

void	*num(int i)
{
	int	*o;

	o = malloc(sizeof(int));
	*o = i;
	return (o);
}