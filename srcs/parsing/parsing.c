/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bben-yaa <bben-yaa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2021/11/20 16:00:25 by bben-yaa         ###   ########.fr       */
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

int	parsing(char *argv, t_parsing *param)
{
	int			i;
	char		*buf;
	char		*line;
	t_parsing	*tmp;

	i = 0;
	line = NULL;
	if (!alloue_elem(param))
		return (-1);
	if (!init_param(param)) 		//->fonction pour init la structure; **bien checker**
		return (-1); 				//protection si l'allocution echoue//*/
	param->next = NULL;
	while(argv[i] == ' ' || argv[i] == '\t')
		i++;						//on a passer tout les spaces et tabs du debut **checker**
	tmp = param;
	while(argv[i])
	{
		printf("argv[%d] vaut %c-\n", i, argv[i]);
		buf = malloc(sizeof(char) * 1);
		if (argv[i] == 34)
		{	
			printf("faire fonction pour mettre dans tab tout ce qu'il y a dans les doubles quotes\n");
			if (line)											//->pour gerer les cas d'interpretation si on a a="ls -la"
			{
				if (!ft_tabs(tmp, line))
					return (0);									//->secure malloc
				line = NULL;
			}
			if (!ft_add_double_quote(tmp, &i, argv, line))	//-> pck on malloc
				return (0);

			///////tout les cas apres avoir mis les doubles quotes dans le tabs//////
			
			if (argv[i + 1] == '\0')							//->si on arrive a la fin de argv
				break ;
			if (argv[i + 1] == 34 || argv[i + 1] == 39)			//pour gerer le cas de "bonjour"'cava'"comment"
				i++;
			else if (argv[i + 1] == ' ')						//->on pass tout les espaces
			{
				i++;
				while (argv[i] == ' ')
					i++;
			}
			
			line = NULL;
		}

		
		else if (argv[i] == 39)								//c'est l'ascii du char ' simple quote
		{
			printf("faire fonction pour mettre dans tab tout ce qu'il y a dans les simple quote\n");
			if (line)										//->pour gerer les cas d'interpretation si on a a='ls -la'
			{
				if (!ft_tabs(tmp, line))
					return (0);								//->secure malloc
				line = NULL;
			}
			if (!ft_add_simple_quote(tmp, &i, argv, line))
				return (0);
			
			///////tout les cas apres avoir mis les simple quote dans le tabs//////
			
			if (argv[i + 1] == '\0')						//->si on arrive a la fin de argv
				break ;
			line = NULL;
			if (argv[i + 1] == 34 || argv[i + 1] == 39)		//pour gerer le cas de "bonjour"'cava'"comment"
				i++;
			else if (argv[i + 1] == ' ')					//->on pass tout les espaces
			{
				i++;
				while (argv[i] == ' ')
					i++;
			}
			
		}
		else if (argv[i] == '|')
		{
			printf("nouveau maillon a faire car nouvelle commande\n");
			printf("l'ancien maillon a pipe pour %d\n", tmp->pipe);
			ft_add_maillon(param);
			tmp = tmp->next;
			printf("le nouveau maillon a pipe pour %d\n", tmp->pipe);
			i++;
			while(argv[i] && argv[i] == ' ')
				i++;
		}
		else if (argv[i] == ' ')
		{
			if (argv[i])
			{
				while (argv[i] == ' ')
				i++;
			}
			printf("allouer une nouvelle ligne pour le tabs copier line dans tabs\n");	
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
			printf("buf vaut %s\n", buf);
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
	
	////////////////////////////////////////
	
	t_parsing *tmp2;

	tmp2 = param;
	i = 0;
	int l = 0;
	while(tmp2)
	{
		printf("//////maillon %d//////\n", i);
		printf("pipe %d\n", tmp2->pipe);
		while (tmp2->tabs[l])
		{
			printf("tab[%d] %s\n", l, tmp2->tabs[l]);
			l++;
		}
		printf("tab[%d] %s\n", l, tmp2->tabs[l]);
		printf("on est d'accord que le next %p\n", tmp2->next);
		l = 0;
		tmp2 = tmp2->next;
		i++;
	}
	///////////////////////////////////////->print tabs tout en lisant la liste chainee	

	return (1);
}
