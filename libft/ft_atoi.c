/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:20:20 by ddecourt          #+#    #+#             */
/*   Updated: 2021/10/04 18:03:01 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_checkcount(int j)
{
	if (j == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	nb;
	int	count;

	i = 0;
	j = 1;
	nb = 0;
	count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j = j * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i++] - 48);
		count++;
	}
	if (count > 10)
		return (ft_checkcount(j));
	return (nb * j);
}
