/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaquet <pierreolivierpaquet@hotmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:02:44 by ppaquet           #+#    #+#             */
/*   Updated: 2023/07/26 14:53:56 by ppaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <stdio.h>

# define X_PATH "PATH="
# define SEPARATOR "/"

# define OPENED_FILE_DEFAULT 2
# define N_CMDS_DEFAULT 2
# define DEFAULT 0
# define IF 0
# define OF 1
# define READING_END 0
# define WRITING_END 1

# define FAILURE -1
# define SUCCESS 0
# define OK 0

# define CHAR_TRIM " 	"
# define O_PERMISSIONS 0644

typedef struct s_pipe
{
	char	**files;
	char	***cmds;
	int		*fd;
	int		*fd_pipe;
	char	**paths;
	char	**envp;
}	t_pipe;

// ---------------------------------------------------------------< PIPEX >----
t_pipe	*pipex_env_init(void);
t_pipe	*pipex_env_pull(void);
char	*pipex_locate_paths(char **envp);
char	**pipex_get_paths(char **envp);
int		pipex(int ac, char **av, char **env);

// -------------------------------------------------------------< PARSING >----
void	pipex_is_whitespace(char *s);
int		pipex_whitespaces_to_space(t_pipe *env);
int		pipex_assign_commands(char *command1, char *command2, t_pipe *env);
int		pipex_assign_files(char *infile, char *outfile, t_pipe *env);
int		pipex_arg_pull(int ac, char **argv);

// --------------------------------------------------------------< CHECKS >----
int		pipex_check_files(t_pipe *env);
char	*pipex_find_bin(int command);

// -----------------------------------------------------------< PROCESSES >----
void	pipex_child_process1(t_pipe *data, int command, char **env);
void	pipex_child_process2(t_pipe *data, int command, char **env);
int		pipex_p_dispatch(t_pipe *data, int cmd, pid_t p1, pid_t p2);
int		pipex_processes(t_pipe *data);

// --------------------------------------------------------------< ERRORS >----
int		pipex_perror(char *err_msg, int status);
char	***pipex_free_commands(char ****tab);
char	**pipex_free_tab(char ***files);
int		*pipex_free_fd(int **tab, int n);
void	pipex_free_env(t_pipe **env);

// -----------------------------------------------------< PROCESSES UTILS >----
void	pipex_dup2(int todup, int fd, t_pipe *env);
void	pipex_execve(char *command, char **cmd_param, char **envp, t_pipe *env);

#endif
