/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_split.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmaes <rmaes@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/23 17:07:24 by rmaes         #+#    #+#                 */
/*   Updated: 2024/08/23 18:41:31 by rmaes         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	skipover_quotes(char const *s, int *i, int j)
{
	if (s[j + *i] == '"')
		while (s[j + ++*i] != '"')
			;
	else if (s[j + *i] == '\'')
		while (s[j + ++*i] != '\'')
			;
}

static int	word_count(char const *s)
{
	int	i;
	int	count;

	// Unused pipe should do.. something. error probably
	i = 0;
	count = 1;
	while (s[i])
	{
		skipover_quotes(s, &i, 0);
		if (s[i] == '|')
			count++;
		i++;
	}
	printf("count: %i\n", count);
	return (count);
}

static void	*free_array(char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**split(char const *s, char **array, int count)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (s[i + tmp] && j < count)
	{
		skipover_quotes(s, &tmp, i);
		tmp++;
		if (s[i + tmp] == '|' || s[i + tmp] == '\0')
		{
			array[j] = ft_substr(&s[i], 0, tmp);
			if (array[j] == 0)
				return (free_array(array, j));
			i += 1 + tmp;
			j++;
			tmp = 0;
		}
	}
	return (array);
}

char	**input_split(char const *s)
{
	char	**array;
	int		count;

	if (!s[0])
		return (NULL);
	count = word_count(s);
	array = ft_calloc((count + 1), sizeof(char *));
	if (array == 0)
		return (0);
	array[count] = 0;
	return (split(s, array, count));
}
