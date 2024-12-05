/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <joltra-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:42:49 by joltra-r          #+#    #+#             */
/*   Updated: 2024/12/04 15:14:44 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_vb
{
	int		pipefd[2];
	pid_t	pid[2];
	int		fd_in;
	int		fd_out;
	char	*exec;
	char	**command;
}				t_vb;

void	error(const char *msg);
void	check_nulls(char **argv);
void	create_pid1(t_vb vb, char **argv, char **envp);
void	create_pid2(t_vb vb, char **argv, char **envp);
char	*check_command(char *command, char **envp);

#endif
