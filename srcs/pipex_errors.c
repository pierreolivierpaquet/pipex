/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:31:48 by ppaquet           #+#    #+#             */
/*   Updated: 2023/07/26 13:56:31 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_perror(char *err_msg, int status)
{
	if (err_msg == NULL)
		ft_putendl_fd("[ERROR]", STDERR_FILENO);
	else if (status != 0)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	else
		perror(err_msg);
	return (errno);
}

char	***pipex_free_commands(char ****tab)
{
	int	i;
	int	j;

	if (tab == NULL || *tab == NULL)
		return (NULL);
	i = 0;
	while ((*tab)[i] != NULL)
	{
		j = 0;
		while ((*tab)[i][j] != NULL)
		{
			free((*tab)[i][j]);
			(*tab)[i][j] = NULL;
			j++;
		}
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
	return (NULL);
}

char	**pipex_free_tab(char ***files)
{
	int	i;

	if (files == NULL || *files == NULL)
		return (NULL);
	i = 0;
	while ((*files)[i] != NULL)
	{
		free((*files)[i]);
		(*files)[i] = NULL;
		i++;
	}
	free(*files);
	*files = NULL;
	return (NULL);
}

int	*pipex_free_fd(int **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if ((*tab)[i] > 0)
			close((*tab)[i]);
		(*tab)[i] = 0;
		i++;
	}
	free(*tab);
	*tab = NULL;
	return (NULL);
}

void	pipex_free_env(t_pipe **env)
{
	if (env == NULL || *env == NULL)
		return ;
	(*env)->cmds = pipex_free_commands(&(*env)->cmds);
	(*env)->fd = pipex_free_fd(&(*env)->fd, OPENED_FILE_DEFAULT);
	(*env)->fd_pipe = NULL;
	(*env)->files = pipex_free_tab(&(*env)->files);
	(*env)->paths = pipex_free_tab(&(*env)->paths);
	(*env)->envp = NULL;
	free(*env);
	*env = NULL;
	return ;
}
