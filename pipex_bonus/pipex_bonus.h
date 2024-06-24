/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:42:49 by joltra-r          #+#    #+#             */
/*   Updated: 2024/04/20 16:42:51 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define READ_OUT 0
# define WRITE_OUT 1

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_vb
{
	int		**pipefd;
	pid_t	*pid;
	int		hd;
	int		fd_in;
	int		fd_out;
	int		argc;
	int		cnum;
	int		pnum;
	char	*exec;
	char	**command;
	char	**argv;
}				t_vb;

void	error(const char *msg);
void	closepipes(t_vb *vb);
void	initialize(t_vb *vb, int argc);
void	check_hd(char *s);
int		heredoc(t_vb *vb, char **argv);
void	create_firstpid(t_vb *vb, char **envp);
void	create_midpid(t_vb *vb, char **argv, char **envp, int i);
void	create_lastpid(t_vb *vb, char **argv, char **envp);
char	*check_command(char *command, char **envp);

#endif
