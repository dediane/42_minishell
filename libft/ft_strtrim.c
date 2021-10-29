/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 01:37:59 by ddecourt          #+#    #+#             */
/*   Updated: 2021/05/31 14:00:05 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*null_malloc(void)
{
	char	*s2;

	s2 = malloc(sizeof(char) * 1);
	if (!s2)
		return (NULL);
	s2[0] = '\0';
	return (s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*s2;

	i = 0;
	j = 0;
	k = -1;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (is_in_set(s1[i], set))
		i++;
	if (i == len)
		return (null_malloc());
	while (is_in_set(s1[(len) - (j + 1)], set))
		j++;
	s2 = malloc(sizeof(char) * (len - (i + j) + 1));
	if (!s2)
		return (NULL);
	while (++k + i < (len - j))
		s2[k] = s1[k + i];
	s2[k] = '\0';
	return (s2);
}
