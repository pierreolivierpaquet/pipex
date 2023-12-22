/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 11:24:17 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/20 17:07:10 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_check_files(t_pipe *env)
{
	int	file;

	if (env == NULL)
		return (FAILURE);
	if (env->fd == NULL)
	{
		env->fd = malloc(OPENED_FILE_DEFAULT * sizeof(*env->fd));
		if (env->fd == NULL)
			return (FAILURE);
	}
	file = DEFAULT;
	while (file < OPENED_FILE_DEFAULT)
		env->fd[file++] = DEFAULT;
	file = DEFAULT;
	file = open(env->files[IF], O_RDONLY, S_IRUSR);
	if (file == FAILURE)
		pipex_perror("[ERROR] Opening infile", 0);
	env->fd[IF] = file;
	file = DEFAULT;
	file = open(env->files[OF], O_RDWR | O_CREAT | O_TRUNC, O_PERMISSIONS);
	if (file == FAILURE)
		pipex_perror("[ERROR] Opening OR Creating outfile", 0);
	env->fd[OF] = file;
	return (SUCCESS);
}

char	*pipex_find_bin(int command)
{
	t_pipe	*env;
	int		i;
	char	*location;
	char	*cmd_path;

	env = pipex_env_pull();
	if (env == NULL || command < 0 || env->paths == NULL || env->cmds == NULL)
		return (NULL);
	i = 0;
	cmd_path = ft_strjoin(SEPARATOR, env->cmds[command][0]);
	while (env->paths[i] != NULL && cmd_path != NULL)
	{
		location = ft_strjoin(env->paths[i], cmd_path);
		if (access(location, X_OK) == SUCCESS)
		{
			free(cmd_path);
			return (location);
		}
		free(location);
		location = NULL;
		i++;
	}
	free(cmd_path);
	pipex_perror("[ERROR] Command not found", 0);
	return (NULL);
}
