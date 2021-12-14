/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balkis <balkis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2021/12/14 18:05:40 by balkis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//int	parsing(char *argv)
//{
	//t_parsing param;
	//int	i;
	//char buf; //va lire char par char on alloue 1 char et on free a chaque fois

	/*i = 0;
	init
	while(argv[i])
	{
		buf = malloc(sizeof(char) * 1);*/
		/*
			explication pour le parsing
			en faite on va alloue au fur a mesure
			donc si on a minishell> cat salut "bonjour"
				le buf va lire 'c' puis 'a' puis 't' (il s'arrete de lire quand il tombe sur un espace pck on a pas commencer avec un " ou un ')
					-> quand il a lut 'c' il alloue un char *argv * 2(c et \0) et le met dedans
					-> quand il a lut 'a' il alloue un char *argv * stlren(argv + 1 donc 3) copie l'ancien + ajout le char 'a'
					donc argv = "ca\0"
					-> quand il a lut 't' il alloue un char *argv * stlren(argv + 1 donc 4) copie l'ancien + ajout le char 't'
					s'arrete car il trouve un espace
					il met la commande dans tabs[1]

			on va mettre la commande et les arguments dans un char **tabs
			qu'on free au fur a mesure
				--> ft_add_to_tab(la fonction va aloue a partir du tabs courant + 1 et copier le tabs courant dans le nouveau)

				si on rencontre un " faire une fonction qui add _to_argvjusqu'a qu'il rencontre un autre "
					-->(une fois au'on a add to argv on met dans le tabs)
				
				meme chose pour '
				
				  
			donc on a une structure dans laquelle il y a un tabs avec la commande et tous les arguments
			
			si on rencontre un pipe
				on fait une liste chainee le prochain element a un tabs avec la commande et tous les arguments 
			et on recommance en ayant j'usqu'on a lu toute la ligne
			

			ATTENTION avant d'ajouter il y a des condition a mettre if buf == '|' si oui aloue un nouveau maillon 
																	if buf == '<' nouvelle commande

			fonction a faire :
				- si on rencontre un " faire une fonction qui add _to_argvjusqu'a qu'il rencontre un autre "
				- ft_add_to_tab(la fonction va aloue a partir du tabs courant + 1 et copier le tabs courant dans le nouveau)
				- fonction qui alloue un char* + 1 du s1 copie du s1 dans le new + ajoute le char en param(char *s1, char c) return new
		*/
		//free(buf);		
		/* OLD PARSING
			while(argv[i] == ' ' || argv[i] == '\t')
				i++;
			if (argv[i])
				return (1); ///faire fonction parsing comande///
			return (1); ///print new prompt car on a parser QUE des spaces and tabs///
		*/
	//}
	//return (0); ///argv n'hesite pas -> print new comande
//}

/////-> si parsing == 0 -> print new prompt
/////-> si parsing == 1 -> executer commande
/////-> si parsing == -1 -> print message "Error" + new prompt

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
			//printf("faire fonction pour mettre dans tab tout ce qu'il y a dans les doubles quotes\n");
			//if (!ft_double_quote(line, &i, argv, tmp))
			//	return (0);
			line = ft_double_quote(line, &i, argv, tmp);
			printf("en sortant de add double quote line vaut %s\n", line);
			line = dolar_quotes(line, envp);


			/*if (line[curs] == '$')
			{
				line = find_var(envp, line);
			}*/


			/*
				Alors il faut deja checker que les quotes sont bien ferme en envoyent argv
				aprés il faut mettre tous dans line sans les quotes 
				(si y'a quote simple et qu'elles sont pas fermées il faut les ajouter à line)
				et pendant que j'ajoute a line si je trouve un $ au i avec un char au i++ je check si 
				la variable existe pour la remplacer par son expansion sinon je la laisse tel qu'elle 
				(il me faut la len de la variable pour la passe et bien reprendre argv pour ajouter dans line)
			*/


			/*check les dolars apres allouer line pck peut y'avoir des ' a l'interrieur ' des doubles quotes
			tu free et remplaces l'xpansion si c'esttpas dans '  */


			//je prefere mon idéé d'en haut c'est plus clean que en bas
			//line = ft_check_dolar(line, envp);
			//printf("line apres check dolar vaut %s\n", line);
			///okay donc check dolar c'est nul pour remplacer la variable par son expanssion
			//il faudrait que je parcours ma line avec maes double quote si je trouve un '$'
			// et que la variable exite alors je free copie line je rajoute l'expanssion de la variable
			// et je termine de copier la line jusqu'a la fin
			// et apres je free l'ancienne line
			// et apres je met la nouvelle line avec l'expansion a la place du nom de la line
			// dans tabs 
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
				return (0);
			if (line)										//->pour gerer les cas d'interpretation si on a a='ls -la'
			{
				if (!ft_tabs(tmp, line))
					return (0);								//->secure malloc
				line = NULL;
			}
			ft_define_redicretcion(argv, &i, tmp);
			//if (!tmp->file)
			//{
			//	printf("Minishell: syntax error near unexpected token `newline'\n");
			//	return (0);
			//}
			ft_add_file(tmp, &i, argv, line);		//alloue line (= nom du fichier) pour le mettre dans la stack file
			while (argv[i] == ' ')
				i++;
			line = NULL; //line free dans ft_add_file
		}
		else if (argv[i] == '$' && argv[i - 1] == ' ')
		{
			while (argv[i] && argv[i] != ' ')
			{
				line = ft_line(line, argv[i]);
				i++;
			}
			line = find_var(envp, line); //line ne sera modifier que si la variable est trouve dans envp 
			ft_tabs(tmp, line);
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
			//printf("ici pour argv[%d] %c\n", i, argv[i]);
			//printf("line here is %s\n\n", line);
			if (argv[i] == '$')
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
				//printf("line vaut \n");				
				line = find_var(envp, line); //line ne sera modifier que si la variable est trouve dans envp 
				ft_tabs(tmp, line);
				line = NULL;
			}
			else
			{
				buf[0] = argv[i];							//on est sur que ici que argv[i] est un char autre que | ' " ou espace
				buf[1] = '\0';
				if (!(line = ft_line(line, buf[0])))		//fonction : mettre dans line tout en allouant et free a chaque fois//
					return (0);								// ->allocation a echoue
				i++;										//only if (argv[i]) ->condtion a mettre
			}
			if (!argv[i] && line)
			{
				if (!ft_tabs(tmp, line))
					return (0);
			}
		}
		free(buf);
	}
	ft_index(param);
	
	
	/////////////////////////////////////////
	
	/*t_parsing	*tmp2;
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
