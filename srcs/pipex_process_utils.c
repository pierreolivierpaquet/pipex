/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:48:03 by ppaquet           #+#    #+#             */
/*   Updated: 2023/07/24 17:59:58 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_dup2(int todup, int fd, t_pipe *env)
{
	int	check;

	if (todup < 0 || fd < 0 || env == NULL)
		return ;
	check = dup2(todup, fd);
	if (check < 0)
	{
		pipex_free_env(&env);
		perror("[ERROR] dup2() file descriptor");
		check = DEFAULT;
		exit(errno);
	}
	return ;
}

void	pipex_execve(char *command, char **cmd_param, char **envp, t_pipe *env)
{
	int	check;

	if (command == NULL || cmd_param == NULL || envp == NULL || env == NULL)
		return ;
	check = execve(command, cmd_param, envp);
	if (check < 0)
	{
		pipex_free_env(&env);
		perror("[ERROR] execve() command");
		check = DEFAULT;
		exit(errno);
	}
	return ;
}
