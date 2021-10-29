/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 21:53:33 by ddecourt          #+#    #+#             */
/*   Updated: 2021/05/31 13:48:25 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*p_dst;
	unsigned char	*p_src;

	if (dst || src)
	{
		i = -1;
		p_dst = (unsigned char *)dst;
		p_src = (unsigned char *)src;
		if (p_dst > p_src)
		{
			while (len--)
				p_dst[len] = p_src[len];
		}
		else
		{
			while (++i < len)
				*(p_dst + i) = *(p_src + i);
		}
	}
	return (dst);
}
