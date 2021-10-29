/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:21:24 by ddecourt          #+#    #+#             */
/*   Updated: 2021/05/31 13:47:31 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p_s1;
	unsigned char	*p_s2;

	i = -1;
	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	while (++i < n)
	{
		if (p_s1[i] != (p_s2[i]))
			return ((int)(p_s1[i] - p_s2[i]));
	}
	return (0);
}
