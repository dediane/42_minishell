/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:36:22 by ddecourt          #+#    #+#             */
/*   Updated: 2021/05/31 13:48:01 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	if (dst || src)
	{
		i = 0;
		p_dst = (unsigned char *)dst;
		p_src = (unsigned char *)src;
		while (i < n)
		{
			*(p_dst + i) = *(p_src + i);
			i++;
		}
	}
	return (dst);
}
