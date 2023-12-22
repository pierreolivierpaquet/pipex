/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:02:53 by ppaquet           #+#    #+#             */
/*   Updated: 2023/07/26 12:06:52 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
	{
		pipex_perror("[ERROR] Not enough arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (argc > 5)
	{
		pipex_perror("[ERROR] Too many arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (pipex(argc, argv, envp) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
