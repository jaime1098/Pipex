/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <joltra-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:07:12 by joltra-r          #+#    #+#             */
/*   Updated: 2024/12/04 15:22:37 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	check_nulls(char **argv)
{
	int i;

	i = -1;
	while (argv[++i])
	{
		if (!argv[i] || argv[i] == NULL || argv[i][0] == '\0')
			error("Invalid argument");
	}
}

void	error(const char *msg)
{
	perror(msg);
	exit(127);
}

void	initialize(t_vb *vb, int argc)
{
	int	i;

	vb->cnum = argc - 3 + vb->hd;
	i = -1;
	vb->pid = malloc(sizeof(pid_t) * (vb->cnum + 1));
	if (!vb->pid)
		error("Malloc error");
	vb->pipefd = ft_calloc(vb->cnum + 1, sizeof(int *));
	if (!vb->pipefd)
		error("Malloc error");
	while (++i < vb->cnum)
	{
		vb->pipefd[i] = malloc(sizeof(int) * 2);
		if (!vb->pipefd)
			error("Malloc error");
		if (pipe(vb->pipefd[i]) == -1)
			error("Error al crear el pipe");
	}
}

void	closepipes(t_vb *vb)
{
	int	i;

	i = -1;
	while (++i < vb->cnum)
	{
		close(vb->pipefd[i][0]);
		close(vb->pipefd[i][1]);
	}
}
