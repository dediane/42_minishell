/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:28:41 by ddecourt          #+#    #+#             */
/*   Updated: 2021/05/31 13:51:49 by ddecourt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_c(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static int	nb_words(char const *s, char c)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (s[i] && is_c(s[i], c))
		i++;
	while (s[i])
	{
		if (!is_c(s[i], c) && (is_c(s[i + 1], c) || s[i + 1] == '\0'))
			nb++;
		i++;
	}
	return (nb);
}

static int	word_size(char const *s, char c)
{
	int	i;

	i = 0;
	while (!is_c(s[i], c) && s[i] != '\0')
		i++;
	return (i);
}

static char	**fill_tab(char **tab, char const *s, char c, int size)
{
	int	i;
	int	j;
	int	k;
	int	to_malloc;

	i = -1;
	j = 0;
	while (++i <= size)
	{
		k = 0;
		while (s[j] && is_c(s[j], c))
			j++;
		if (s[j] && !is_c(s[j], c))
		{
			to_malloc = word_size(&s[j], c);
			tab[i] = malloc(sizeof(char) * (to_malloc + 1));
			if (!tab)
				return (NULL);
			while (s[j] && !is_c(s[j], c))
				tab[i][k++] = s[j++];
			tab[i][k] = '\0';
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		size;

	if (!s)
		return (NULL);
	size = nb_words(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tab[size] = NULL;
	tab = fill_tab(tab, s, c, size);
	return (tab);
}
