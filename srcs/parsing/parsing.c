/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddecourt <ddecourt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:03:50 by bben-yaa          #+#    #+#             */
/*   Updated: 2021/11/09 19:32:56 by ddecourt         ###   ########.fr       */
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
				le buf va lire 'c' puis 'a' puis 't' (il s'arrete de lire quamd il tombe sur un espace pck on a pas commencer avec un " ou un ')
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

/*int	parsing_comande(char *argv, t_parsing *param, int *i)
{
	
}*/