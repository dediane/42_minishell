


        ////HEADER///


#include "../../inc/minishell.h"

void	ft_check_var(char *line, char **envp)
{
	if (find_var(envp, line))
	{
		printf("icii line vaut %s\n", line);
	}
}

int		find_var(char **envp, char *line)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = -1;
	(void)line;
	while (envp[++j])
	{
		while (envp[j][i] != '=')
			i++;
		var = strndup(envp[j], i);
		printf("var vaut %s\n", var);
		printf("line vaut %s\n", &line[1]);
		if (ft_strncmp(var, &line[1], ft_strlen(var)) == 0)
		{
			printf("la variable existe\n");
			printf("prendre l'expansion de la variable et mettre dans line\noublie pas de free line\n");
			printf("envp[j] vaut %s\n", envp[j]);
			//printf("expansion envp[j] %s\n", &envp[j][++i]);
			//free(line);
			line = NULL;
			line = ft_strdup(&envp[j][++i]);
			printf("line apres avoir chercher l'expansion %s\n", line);
			free(var);
			return (1);
		}
		i = 0;
		free(var);
		var = NULL;
	}
	return (0);
}
