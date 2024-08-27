/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/21 16:08:18 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/27 15:36:07 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

int	skipover_quotes(char const *s, int *i, int j)
{
	char	c;

	c = 0;
	if (s[j + *i] == '"' || s[j + *i] == '\'')
		c = s[j + *i];
	else
		return (0);
	while (s[j + ++*i] != c)
		if (s[j + *i] == '\0')
			return (1);
	return (0);
}

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
