/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:07:12 by joltra-r          #+#    #+#             */
/*   Updated: 2024/04/14 18:07:14 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **routes)
{
	int	i;

	i = -1;
	while (routes[++i])
		free(routes[i]);
	free(routes);
}

char	*check_command(char *command, char **envp)
{
	char	**routes;
	char	*complete_command;
	int		i;

	i = 0;
	if (ft_strchr(command, '/'))
		return (command);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (command);
	routes = ft_split(envp[i] + 5, ':');
	i = -1;
	while (routes[++i])
	{
		complete_command = ft_strjoin(ft_strdup(routes[i]), "/");
		complete_command = ft_strjoin(complete_command, command);
		if (access(complete_command, F_OK) == 0)
		{
			ft_free(routes);
			return (complete_command);
		}
		free(complete_command);
	}
	return (ft_free(routes), command);
}

void	create_firstpid(t_vb *vb, char **envp)
{
	vb->command = ft_split(vb->argv[2 + vb->hd], ' ');
	vb->exec = check_command(vb->command[0], envp);
	if (!vb->hd)
		vb->fd_in = open(vb->argv[1], O_RDONLY);
	else
		vb->fd_in = open(".here_doc", O_RDONLY);
	if (vb->fd_in < 0)
		error("fd_in not opened");
	else if (vb->pid[0] == 0)
	{
		dup2(vb->fd_in, STDIN_FILENO);
		dup2(vb->pipefd[0][1], STDOUT_FILENO);
		closepipes(vb);
		close(vb->fd_in);
		execve(vb->exec, vb->command, envp);
		error("Error al ejecutar comando1");
	}
}

void	create_midpid(t_vb *vb, char **argv, char **envp, int i)
{
	if (vb->pid[i - 2] == 0)
	{
		vb->command = ft_split(argv[i], ' ');
		vb->exec = check_command(vb->command[0], envp);
		dup2(vb->pipefd[i - 3][0], STDIN_FILENO);
		dup2(vb->pipefd[i - 2][1], STDOUT_FILENO);
		closepipes(vb);
		execve(vb->exec, vb->command, envp);
		error("Error al ejecutar comando intermedio");
	}
}

void	create_lastpid(t_vb *vb, char **argv, char **envp)
{
	vb->command = ft_split(argv[vb->argc - 2], ' ');
	vb->exec = check_command(vb->command[0], envp);
	if (!vb->hd)
		vb->fd_out = open(argv[vb->argc - 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		vb->fd_out = open(argv[vb->argc - 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (vb->fd_out == -1)
		error("Error al abrir o crear el archivo de salida");
	else if (vb->pid[vb->pnum] == 0)
	{
		dup2(vb->pipefd[vb->pnum - 1][0], STDIN_FILENO);
		dup2(vb->fd_out, STDOUT_FILENO);
		closepipes(vb);
		close(vb->fd_out);
		execve(vb->exec, vb->command, envp);
		error("Error al ejecutar comando2");
	}
}
