/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 01:32:27 by ddecourt          #+#    #+#             */
/*   Updated: 2021/05/31 13:56:39 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		size;
	char	*dst;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	i = 0;
	dst = malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	dst[size] = '\0';
	while (s[i])
	{
		dst[i] = (*f)(i, s[i]);
		i++;
	}
	return (dst);
}
