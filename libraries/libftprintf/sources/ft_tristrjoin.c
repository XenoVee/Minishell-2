/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rmaes <rmaes@student.codam.nl>			 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/12/17 16:42:11 by rmaes			 #+#	#+#			 */
/*   Updated: 2022/03/29 17:21:03 by rmaes			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>

static void	ft_null_array(void *array, int len)
{
	int	i;
	int	*p;

	i = 0;
	p = array;
	while (i < len)
	{
		p[i] = 0;
		i++;
	}
}

static size_t	ft_strlenprot(const char *s)
{
	int	a;

	a = 0;
	if (s)
		while (s[a])
			a++;
	return (a);
}

char	*ft_tristrjoin(char const *s1, char const *s2, char const *s3)
{
	unsigned int	i;
	unsigned int	len[3];
	char			*str;

	i = 0;
	ft_null_array(len, 3);
	len[0] = ft_strlenprot(s1);
	len[1] = ft_strlenprot(s2);
	len[2] = ft_strlenprot(s3);
	str = malloc((len[0] + len[1] + len[2] + 1) * sizeof(char));
	if (!str)
		return (0);
	while (i < len[0] || i < len[1] || i < len[2])
	{
		if (i < len[0])
			str[i] = s1[i];
		if (i < len[1])
			str[len[0] + i] = s2[i];
		if (i < len[2])
			str[len[0] + len[1] + i] = s3[i];
		i++;
	}
	str[len[0] + len[1] + len[2]] = '\0';
	return (str);
}
