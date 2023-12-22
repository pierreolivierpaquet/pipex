/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 10:47:41 by ppaquet           #+#    #+#             */
/*   Updated: 2023/07/26 14:00:07 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipe	*pipex_env_init(void)
{
	t_pipe	*env_init;

	env_init = NULL;
	env_init = malloc(sizeof(t_pipe));
	if (env_init == NULL)
		return (NULL);
	env_init->cmds = NULL;
	env_init->files = NULL;
	env_init->fd = NULL;
	env_init->paths = NULL;
	env_init->envp = NULL;
	return (env_init);
}

t_pipe	*pipex_env_pull(void)
{
	static t_pipe	*pipex_env;

	if (!pipex_env)
	{
		pipex_env = pipex_env_init();
		return (pipex_env);
	}
	else
		return (pipex_env);
	return (NULL);
}

char	*pipex_locate_paths(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], X_PATH, ft_strlen(X_PATH)) == OK)
		{
			path = ft_strnstr(envp[i], X_PATH, ft_strlen(envp[i]));
			return (&path[ft_strlen(X_PATH)]);
		}
		i++;
	}
	return (NULL);
}

char	**pipex_get_paths(char **envp)
{
	char	*paths;
	char	**path_tab;
	t_pipe	*env;

	paths = NULL;
	path_tab = NULL;
	if (envp == NULL || envp[0] == NULL)
		return (NULL);
	paths = pipex_locate_paths(envp);
	if (paths == NULL)
		return (path_tab);
	path_tab = ft_split(paths, ':');
	if (path_tab != NULL)
	{
		env = pipex_env_pull();
		if (env != NULL)
		{
			env->paths = path_tab;
			env->envp = envp;
		}
	}
	return (path_tab);
}

int	pipex(int ac, char **av, char **envp)
{
	t_pipe	*env;
	int		status;

	status = SUCCESS;
	env = pipex_env_pull();
	if (env == NULL)
		return (FAILURE);
	pipex_get_paths(envp);
	pipex_arg_pull(ac, av);
	pipex_check_files(env);
	status = pipex_processes(env);
	pipex_free_env(&env);
	if (status != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
