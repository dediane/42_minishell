/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2022/01/17 23:26:24 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_init_param(char*argv, char **envp, t_param *arg)
{
	arg->argv = argv;
	arg->i = 0;
	arg->line = NULL;
	arg->envp = envp;
	arg->buf = NULL;
}

int	parsing(char *argv, t_parsing *param, char **envp)
{
	t_param		arg;
	t_parsing	*tmp;
	int			ret;

	//ft_init_param(argv, envp, &arg);
	if (!ft_init(param, &arg, argv, envp))
		return (0);
	tmp = param;
	while (arg.argv[arg.i])
	{
		ret = ft_first_if(param, tmp, &arg);
		if (ret == 1)
			return (1);
		else if (ret == 0)
			return (1);
		else if (ret == -1)
			break ;
		else if (arg.argv[arg.i] == '|')
		{
			if (!ft_mpipe(arg.argv, &(arg.i), tmp, param))
				return (0);
			tmp = tmp->next;
		}
		else if (ret == 2)
		{
			ret = ft_second_if(&arg, param, tmp);
			if (ret == 0)
				return (0);
			else if (ret == 3)
				ft_third_if(&arg, tmp);
		}
	}
	return (1);
}

int	ft_first_if(t_parsing *param, t_parsing *tmp, t_param *arg)
{
	if (arg->argv[arg->i] == 34)
	{
		arg->line = ft_double_quote(arg->line, &(arg->i), arg->argv, tmp);
		if (tmp->stop == 1)
			return (1);
		if (arg->line == 0)
			return (-1);
		mdquote2(arg->line, arg->envp, param);
		if (!mdquote3(arg->argv, &(arg->i)))
			return (-1);
		arg->line = NULL;
	}
	else if (arg->argv[arg->i] == 39)
	{
		if (!ft_simple_quote(arg->line, &(arg->i), arg->argv, tmp))
			return (1);
		if (arg->argv[arg->i + 1] == '\0')
			return (-1);
		ft_pass_squote(arg->argv, &(arg->i));
		arg->line = NULL;
	}
	else
		return (2);
	return (3);

}

int	ft_second_if(t_param *arg, t_parsing *param, t_parsing *tmp)
{
	if ((arg->argv[arg->i] == '<' || arg->argv[arg->i] == '>'))
	{
		if (!ft_mredoc(arg->line, &(arg->i), arg->argv, tmp))
			return (0);
		arg->line = NULL;
	}
	else if (arg->argv[arg->i] == '$' && arg->argv[arg->i + 1] && \
		arg->argv[arg->i + 1] != '?' && ft_change(&(arg->argv[arg->i])))
	{
		arg->line = ft_mdolar(arg->argv, &(arg->i), arg->line, param);
		arg->line = ft_mdolar2(arg->argv, &(arg->i), arg->line, arg->envp);
		ft_tabs(tmp, arg->line);
		arg->line = NULL;
	}
	else if (arg->argv[arg->i] == ' ')
	{
		ft_mspace(arg->argv, &(arg->i), tmp, arg->line);
		arg->line = NULL;
	}
	else
		return (3);
	return (1);
}

void	ft_third_if(t_param *arg, t_parsing *tmp)
{
	arg->buf = malloc(sizeof(char) * 2);
	ft_fill(arg->argv, &(arg->i), arg->buf, arg->line);
	arg->line = ft_line(arg->line, arg->buf[0]);
	if (!arg->argv[arg->i] && arg->line)
		ft_tabs(tmp, arg->line);
	free(arg->buf);
}

//-->>>>> 6 fonction A faire pour la norme si elles return 0 break;	
/*	t_parsing	*tmp2;
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
}*/

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

int	mdquote3(char *argv, int *i)
{
	if (argv[(*i) + 1] == '\0')
		return (0);
	ft_pass_dquote(argv, i);
	return (1);
}
