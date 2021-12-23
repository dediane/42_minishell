/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2021/12/23 12:31:20 by balkis           ###   ########.fr       */
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
	(void)envp;
	if (!ft_init(param))
		return (0);
	ft_pass_space(argv, &i);
	tmp = param;
	while(argv[i])
	{
		buf = malloc(sizeof(char) * 2);
		if (argv[i] == 34)
		{
			line = ft_double_quote(line, &i, argv, tmp);
			if (line == 0)
				return (0);
			if (dolar_quotes(line))
				line = ft_replace_var(line, envp);
			if (!ft_tabs(param, line))
				return (0);
			if (argv[i + 1] == '\0')//->si on arrive a la fin de argv
				break ;
			ft_pass_dquote(argv, &i);
			line = NULL;
		}
		else if (argv[i] == 39)								//c'est l'ascii du char ' simple quote
		{
			//printf("faire fonction pour mettre dans tab tout ce qu'il y a dans les simple quote\n");
			if (!ft_simple_quote(line, &i, argv, tmp))
				return (0);
			if (argv[i + 1] == '\0')//->si on arrive a la fin de argv
				break ;
			ft_pass_squote(argv, &i);
			line = NULL;
		}
		else if (argv[i] == '|')
		{
			//printf("nouveau maillon a faire car pipe nouvelle commande\n");
			ft_add_maillon(param);
			tmp->next->pipe = tmp->pipe + 1;
			tmp = tmp->next;
			i++;
			while(argv[i] && argv[i] == ' ')
				i++;
			if (!argv[i]) //enfaite c'est pas cas d'erreur 
			{
				printf("Pas de commande après le pipe, cas à gérer, tu veux que je le parse comment?\
					pck ca va creer un maillon vide -> et du coup segfault quand tu l'utilise\n");
				return (0);
			}
		}
		else if ((argv[i] == '<' || argv[i] == '>'))//&& (argv[i - 1] == ' '|| i == 0))
		{
			if (!ft_check_redoc(argv, i))
			{
				printf("Minishell: syntax error near unexpected token `newline'\n");
				return (0);
			}
			if (line)										//->pour gerer les cas d'interpretation si on a a='ls -la'
			{
				if (!ft_tabs(tmp, line))
					return (0);								//->secure malloc
				line = NULL;
			}
			ft_define_redicretcion(argv, &i, tmp);
			ft_add_file(tmp, &i, argv, line);		//alloue line (= nom du fichier) pour le mettre dans la stack file
			if (!tmp->file)
				return (0);
			while (argv[i] == ' ')
				i++;
			line = NULL; //line free dans ft_add_file
		}
		else if (argv[i] == '$' && argv[i + 1] && argv[i + 1] != '?' && ft_change(&argv[i])) //&& argv[i - 1] == ' ')
		{
			if (line)											//->pour gérer les cas d'interpretation si on a a= "ls -la"
			{
				if (!ft_tabs(param, line))
					return (0);									//->secure malloc
				line = NULL;
			}
			while (argv[i] && argv[i] != ' ')
			{
				line = ft_line(line, argv[i]);
				i++;
			}
			line = find_var(envp, line); //line ne sera modifier que si la variable est trouve dans envp 
			if (argv[i])
			{
				while (argv[i] == ' ')
					i++;
			}
			ft_tabs(tmp, line);
			line = NULL;
		}
		else if (argv[i] == ' ')
		{
			if (argv[i])
			{
				while (argv[i] == ' ')
				i++;
			}	
			if (!ft_tabs(tmp, line))
				return (0);			
			line = NULL;
		}
		else
		{
			if (!argv[i])
				break ;
			buf[0] = argv[i];							//on est sur que ici que argv[i] est un char autre que | ' " ou espace
			buf[1] = '\0';
			if (!(line = ft_line(line, buf[0])))		//fonction : mettre dans line tout en allouant et free a chaque fois//
				return (0);								// ->allocation a echoue
			i++;										//only if (argv[i]) ->condtion a mettre
			if (!argv[i] && line)
			{
			if (!ft_tabs(tmp, line))
				return (0);
			}
		}
		free(buf);
	}
	ft_index(param);
	
	
	/*//////////////////////////////////////////
	
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
		while (tmp2->tabs[l])
		{
			printf("tab[%d] %s\n", l, tmp2->tabs[l]);
			l++;
		}
		printf("tab[%d] %s\n", l, tmp2->tabs[l]);
		printf("curs before = %p\n", curs);
		while (curs)
		{
			printf("name_file %d vaut %s\n", j, curs->name);
			printf("type_file %d vaut %d\n", j, curs->ftype);
			j++;
			curs = curs->next;
		}
		printf("on est d'accord que le next %p\n", tmp2->next);
		l = 0;
		j = 0;
		tmp2 = tmp2->next;
		i++;
		
	}
	printf("----This is after parsing----\n");*/
	//////////////////////////////////////->print tabs tout en lisant la liste chainee	et les files et type
	return (1);
}
