/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <joltra-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:07:12 by joltra-r          #+#    #+#             */
/*   Updated: 2024/12/04 15:04:35 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

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
		complete_command = ft_strjoin(routes[i], "/");
		complete_command = ft_strjoin(complete_command, command);
		if (access(complete_command, F_OK) == 0)
			return (complete_command);
	}
	return (command);
}

void	create_pid1(t_vb vb, char **argv, char **envp)
{
	vb.command = ft_split(argv[2], ' ');
	vb.exec = check_command(vb.command[0], envp);
	vb.fd_in = open(argv[1], O_RDONLY);
	if (vb.fd_in < 0)
	{
		close(vb.pipefd[0]);
		close(vb.pipefd[1]);
		error("fd_in not opened");
	}
	else if (vb.pid[0] == 0)
	{
		close(vb.pipefd[0]);
		dup2(vb.pipefd[1], STDOUT_FILENO);
		close(vb.pipefd[1]);
		dup2(vb.fd_in, STDIN_FILENO);
		close(vb.fd_in);
		execve(vb.exec, vb.command, envp);
		error("Error al ejecutar comando1");
	}
}

void	create_pid2(t_vb vb, char **argv, char **envp)
{
	vb.command = ft_split(argv[3], ' ');
	vb.exec = check_command(vb.command[0], envp);
	vb.fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (vb.fd_out == -1)
	{
		close(vb.pipefd[0]);
		close(vb.pipefd[1]);
		error("Error al abrir o crear el archivo de salida");
	}
	else if (vb.pid[1] == 0)
	{
		close(vb.pipefd[1]);
		dup2(vb.pipefd[0], STDIN_FILENO);
		close(vb.pipefd[0]);
		dup2(vb.fd_out, STDOUT_FILENO);
		close(vb.fd_out);
		execve(vb.exec, vb.command, envp);
		error("Error al ejecutar comando2");
	}
}
