/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:45:51 by ppaquet           #+#    #+#             */
/*   Updated: 2023/07/26 11:10:49 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TO DELETE

#include "pipex.h"

void	pipex_is_whitespace(char *s)
{
	if (s == NULL || *s == 0)
		return ;
	if ((*s >= 8) && (*s <= 13))
		*s = 32;
	return ;
}

int	pipex_whitespaces_to_space(t_pipe *env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	if (env == NULL || env->cmds == NULL)
		return (FAILURE);
	while (env->cmds[i] != NULL)
	{
		j = 0;
		while (env->cmds[i][j] != NULL)
		{
			k = 0;
			while (env->cmds[i][j][k] != '\0')
				pipex_is_whitespace(&env->cmds[i][j][k++]);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	pipex_assign_commands(char *command1, char *command2, t_pipe *env)
{
	char	***cmds;
	char	*buf[2];

	cmds = NULL;
	if (command1 == NULL || command2 == NULL || env == NULL)
		return (FAILURE);
	cmds = malloc(((N_CMDS_DEFAULT + 1) * sizeof(*cmds)));
	if (cmds == NULL)
		return (FAILURE);
	if (env->cmds == NULL)
	{
		buf[0] = ft_strtrim(command1, CHAR_TRIM);
		buf[1] = ft_strtrim(command2, CHAR_TRIM);
		env->cmds = cmds;
		env->cmds[N_CMDS_DEFAULT] = NULL;
		env->cmds[0] = ft_split(buf[0], 32);
		env->cmds[1] = ft_split(buf[1], 32);
		free(buf[0]);
		free(buf[1]);
	}
	pipex_whitespaces_to_space(env);
	return (SUCCESS);
}

int	pipex_assign_files(char *infile, char *outfile, t_pipe *env)
{
	char	**temp;

	temp = NULL;
	if (infile == NULL || outfile == NULL || env == NULL)
		return (FAILURE);
	if (env->files == NULL)
	{
		temp = malloc((OPENED_FILE_DEFAULT + 1) * sizeof(*temp));
		if (temp == NULL)
			return (FAILURE);
		env->files = temp;
		env->files[OPENED_FILE_DEFAULT] = NULL;
		env->files[0] = ft_strdup(infile);
		env->files[1] = ft_strdup(outfile);
	}
	return (SUCCESS);
}

int	pipex_arg_pull(int ac, char **argv)
{
	t_pipe	*env;

	env = pipex_env_pull();
	if (env == NULL)
		return (FAILURE);
	pipex_assign_files(argv[1], argv[ac - 1], env);
	pipex_assign_commands(argv[2], argv[3], env);
	return (SUCCESS);
}
