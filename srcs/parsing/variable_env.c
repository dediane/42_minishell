


        ////HEADER///


#include "../../inc/minishell.h"

char	*find_var(char **envp, char *line)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = -1;
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
	free(line);
	line = NULL;
	line = ft_line(line, ' ');
	return (line);
}

int	dolar_quotes(char *line)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_change(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != ' ')
	{
		if (argv[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_replace_var(char *line, char **envp)
{
	int		len;
	int		pos;
	char	*var;
	char	*exp;

	len = 0;
	pos = 0;
	exp = line;
	while (line[len])
	{
		if (line[len] == '$')
		{
			pos = len + 1;
			len = pos_dolar(line);
			break ;
		}
		len++;
	}
	var = strndup(&line[pos], len);
	exp = ft_search_var(var, envp, exp, pos);
	var = malloc(sizeof(char) * (pos + ft_strlen(exp) + ft_strlen(&line[pos + len]) + 1));
	return (ft_copy(var, line, exp, pos));
}

char	*ft_search_var(char *var, char **envp, char *line, int pos)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	j = -1;
	name = NULL;
	(void)pos;
	(void)line;
	while (envp[++j])
	{
		while (envp[j][i] != '=')
			i++;
		name = strndup(envp[j], i);
		if (ft_strncmp(name, var, ft_strlen(var)) == 0)
		{
			free(var);
			var = NULL;
			var = ft_strdup(&envp[j][++i]);
			free(name);
			name = NULL;
			return (var);
		}
		i = 0;
		free(name);
		name = NULL;
	}
	free(var);
	var = NULL;
	var = ft_strdup(" ");
	return (var);
}

int		pos_dolar(char *line)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			while (line[i] && line[i] != ' ')
			{
				i++;
				len++;
			}
			return (len);
		}
		i++;
	}
	return (0);
}

char	*ft_copy(char *var, char *line, char *exp, int pos)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = pos_dolar(line);
	while (line[i] && i < (pos - 1))
	{
		var[i] = line[i];
		i++;
	}
	while (exp[j])
	{
		var[i] = exp[j];
		j++;
		i++;
	}
	if (line[pos + len])
	{
		while (line[pos + len])
		{
			var[i] = line[len + pos];
			i++;
			len++;
		}
	}
	var[i] = '\0';
	free(line);
	return (var);
}