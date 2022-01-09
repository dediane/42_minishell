/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/06 09:37:20 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parsing(char *argv, t_parsing *param, char **envp)
{
	int			i;
	char		*buf;
	char		*line;
	t_parsing	*tmp;

	i = 0;
	line = NULL;
	if (!ft_init(param))
		return (0);
	ft_pass_space(argv, &i);
	tmp = param;
	while (argv[i])
	{
		buf = malloc(sizeof(char) * 2);
		if (argv[i] == 34)
		
		//fonction break and return(0) car checkquotes
		{
			line = ft_double_quote(line, &i, argv, tmp);
			if (tmp->stop == 1)
				return (0);
			if (line == 0)
				break ;
			if (dolar_quotes(line))
				line = ft_replace_var(line, envp);
			ft_tabs(param, line);
			if (argv[i + 1] == '\0')
				break ;
			ft_pass_dquote(argv, &i);
			line = NULL;
		}
		
		//fonction break and return (0) car checkquotes
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

		//fonction 		no break here 
		else if (argv[i] == ' ')
		{
			if (argv[i])
			{
				while (argv[i] == ' ')
					i++;
			}
			ft_tabs(tmp, line);
			line = NULL;
		}
		
		//fonction
		else
		{
			if (!argv[i])
				break ;
			buf[0] = argv[i];
			buf[1] = '\0';
			line = ft_line(line, buf[0]);
			i++;
			if (!argv[i] && line)
			{
				ft_tabs(tmp, line);
			}
		}
		free(buf);
	}
	ft_index(param);
//	return (1);



//////////------------->>>>>>>>>> 6 fonction A faire pour la norme si elles return 0 break;


	
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
	//////////////////////////////////////->print tabs tout en lisant la liste chainee	et les files et type
	return (1);
}