/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/11 15:33:15 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parsing(char *argv, t_parsing *param, char **envp)
{
	int			i;
	char		*buf;
	char		*line;
	t_parsing	*tmp;

	line = NULL;
	if (!ft_init(param, &i, argv))
		return (0);
	tmp = param;
	while (argv[i])
	{
		buf = malloc(sizeof(char) * 2);
		if (argv[i] == 34)
		{
			line = ft_double_quote(line, &i, argv, tmp);
			if (tmp->stop == 1)
				return (0);
			if (line == 0)
				break ;
			mdquote2(line, envp, param);
			if (!mdquote3(argv, &i))
				break ;
			line = NULL;
		}
		else if (argv[i] == 39)
		{
			if (!ft_simple_quote(line, &i, argv, tmp))
				return (0);
			if (argv[i + 1] == '\0')
				break ;
			ft_pass_squote(argv, &i);
			line = NULL;
		}
		else if (argv[i] == '|')
		{
			if (!ft_mpipe(argv, &i, tmp, param))
				return (0);
			tmp = tmp->next;
		}
		else if ((argv[i] == '<' || argv[i] == '>'))
		{
			if (!ft_mredoc(line, &i, argv, tmp))
				return (0);
		}
		else if (argv[i] == '$' && argv[i + 1] && \
			argv[i + 1] != '?' && ft_change(&argv[i]))
		{
			line = ft_mdolar(argv, &i, line, param);
			line = ft_mdolar2(argv, &i, line, envp);
			ft_tabs(tmp, line);
			line = NULL;
		}
		else if (argv[i] == ' ')
		{
			ft_mspace(argv, &i, tmp, line);
			line = NULL;
		}
		else
		{
			ft_fill(argv, &i, buf, line);
			line = ft_line(line, buf[0]);
			if (!argv[i] && line)
				ft_tabs(tmp, line);
		}
		free(buf);
	}
//	return (1);
//}

//-->>>>> 6 fonction A faire pour la norme si elles return 0 break;


	
	t_parsing	*tmp2;
	t_file		*curs;
	tmp2 = param;
	i = 0;
	int l = 0;
	int j = 0;
	while(tmp2)
	{
		curs = tmp2->file;
		printf("//////maillon %d//////\n", i);
		printf("enume type %u\n", tmp2->type);
		printf("valeur de pipe: %i\n", tmp2->pipe);
		printf("index : %i\n", tmp2->index);
		printf("nb_cmd : %i\n", tmp2->nb_cmd);
		if (tmp2->tabs)
		{
			printf("il y'a des arguments\n");
			while (tmp2->tabs[l])
			{
				printf("tab[%d] %s\n", l, tmp2->tabs[l]);
				l++;
			}
			printf("tab[%d] %s\n", l, tmp2->tabs[l]);
		}
		printf("curs before = %p\n", curs);
		if (curs)
		{
			printf("file existe\n");
			while (curs)
			{
				printf("name_file %d vaut %s\n", j, curs->name);
				printf("type_file %d vaut %d\n", j, curs->ftype);
				j++;
				curs = curs->next;
			}
		}
		printf("on est d'accord que le next %p\n", tmp2->next);
		l = 0;
		j = 0;
		tmp2 = tmp2->next;
		i++;
		
	}
	printf("----This is after parsing----\n");
	////->print tabs tout en lisant la liste chainee	et les files et type
	return (1);
}

int	ft_fill(char *argv, int *i, char *buf, char *line)
{
	if (!argv[(*i)])
		return (0);
	buf[0] = argv[(*i)];
	buf[1] = '\0';
	(void)line;
	(*i)++;
	return (1);
}

void	ft_fill2(char *argv, char *line, t_parsing *tmp, int *i)
{
	if (!argv[(*i)] && line)
		ft_tabs(tmp, line);
}

void	mdquote2(char *line, char **envp, t_parsing *param)
{
	if (dolar_quotes(line))
		line = ft_replace_var(line, envp);
	ft_tabs(param, line);
}

int		mdquote3(char *argv, int *i)
{
	if (argv[(*i) + 1] == '\0')
		return (0);
	ft_pass_dquote(argv, i);
	return (1);
}