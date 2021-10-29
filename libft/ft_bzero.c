/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:06:26 by ddecourt          #+#    #+#             */
/*   Updated: 2021/06/01 00:56:29 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p_s;
	size_t			i;

	i = 0;
	p_s = (unsigned char *)s;
	while (i < n)
	{
		p_s[i] = '\0';
		i++;
	}
}
