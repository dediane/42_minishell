


        ////HEADER///


#include "../../inc/minishell.h"

int	ft_check_var(char *line, char **envp)
{
	if (find_var(envp, line))
		return (1);
	return (1);
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
		//printf("var vaut %s\n", var);
		//printf("line vaut %s\n", &line[1]);
		if (ft_strncmp(var, &line[1], ft_strlen(var)) == 0)
		{
		//	printf("la variable existe\n");
		//	printf("prendre l'expansion de la variable et mettre dans line\noublie pas de free line\n");
			free(var);
			return (1);
		}
		i = -1;
		free(var);
		var = NULL;
	}
	return (0);
}
