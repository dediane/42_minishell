


        ////HEADER///


#include "../../inc/minishell.h"

char	*find_var(char **envp, char *line)
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
		if (ft_strncmp(var, &line[1], ft_strlen(var)) == 0)
		{
			free(line);
			line = NULL;
			line = ft_strdup(&envp[j][++i]);
			free(var);
			return (line);
		}
		i = 0;
		free(var);
		var = NULL;
	}
	return (line);
}

char	*ft_check_dolar(char *line, char **envp)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '$')
		{
			return (find_var(envp, &line[i]));
		}
		i++;
	}
	return (line);
}