/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:02:24 by ppaquet           #+#    #+#             */
/*   Updated: 2023/10/04 10:04:27 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_child_process1(t_pipe *data, int command, char **env)
{
	char	*cmd;

	cmd = pipex_find_bin(command);
	if (data == NULL || cmd == NULL || data->fd[IF] == FAILURE)
	{
		pipex_free_env(&data);
		exit(errno);
	}
	if (data->fd[IF] != FAILURE)
	{
		pipex_dup2(data->fd[IF], STDIN_FILENO, data);
		data->fd[IF] = close(data->fd[IF]);
	}
	data->fd[OF] = close(data->fd[OF]);
	if (data->fd_pipe[1] != FAILURE)
		pipex_dup2(data->fd_pipe[1], STDOUT_FILENO, data);
	data->fd_pipe[READING_END] = close(data->fd_pipe[READING_END]);
	data->fd_pipe[WRITING_END] = close(data->fd_pipe[WRITING_END]);
	pipex_execve(cmd, data->cmds[command], env, data);
	exit(EXIT_FAILURE);
}

void	pipex_child_process2(t_pipe *data, int command, char **envp)
{
	char	*cmd;

	cmd = pipex_find_bin(command);
	if (data == NULL || cmd == NULL)
	{
		pipex_free_env(&data);
		exit(errno);
	}
	if (data->fd_pipe[IF] != FAILURE)
	{
		pipex_dup2(data->fd_pipe[0], STDIN_FILENO, data);
		data->fd_pipe[IF] = close(data->fd_pipe[IF]);
	}
	data->fd_pipe[WRITING_END] = close(data->fd_pipe[WRITING_END]);
	if (data->fd[OF] != FAILURE)
		pipex_dup2(data->fd[OF], STDOUT_FILENO, data);
	data->fd[OF] = close(data->fd[OF]);
	data->fd[IF] = close(data->fd[IF]);
	pipex_execve(cmd, data->cmds[command], envp, data);
	exit(EXIT_FAILURE);
}

int	pipex_p_dispatch(t_pipe *data, int cmd, pid_t p1, pid_t p2)
{
	int	status;

	cmd = DEFAULT;
	p1 = fork();
	if (data == NULL)
		return (FAILURE);
	if (p1 < 0)
		return (pipex_perror("[ERROR] fork() first process", STDIN_FILENO));
	// p1 = OK; // test
	if (p1 == OK)
		pipex_child_process1(data, cmd, data->envp);
	waitpid(p1, NULL, 0);
	p2 = fork();
	if (p2 < 0)
		return (pipex_perror("[ERROR] fork() second process", STDIN_FILENO));
	if (p2 == OK)
		pipex_child_process2(data, ++cmd, data->envp);
	data->fd_pipe[1] = close(data->fd_pipe[1]);
	data->fd_pipe[0] = close(data->fd_pipe[0]);
	waitpid(p2, &status, 0);
	if (status != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	pipex_processes(t_pipe *data)
{
	int		flange[2];
	pid_t	process1;
	pid_t	process2;
	int		command;

	if (data == NULL)
		return (FAILURE);
	pipe(flange);
	process1 = 0;
	process2 = 0;
	command = 0;
	data->fd_pipe = flange;
	if (pipex_p_dispatch(data, command, process1, process2) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
