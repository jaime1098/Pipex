/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:07:12 by joltra-r          #+#    #+#             */
/*   Updated: 2024/04/14 18:07:14 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_vb	vb;
	int		i;
	int		status;

	status = 0;
	vb.argc = argc;
	vb.argv = argv;
	vb.pnum = 0;
	if (argc < 5)
		error("Argumentos incorrectos");
	if (argc == 5)
		check_hd(argv[1]);
	vb.hd = heredoc(&vb, argv);
	initialize(&vb, argc);
	vb.pid[0] = fork();
	if (vb.pid[0] == 0)
		create_firstpid(&vb, envp);
	else if (vb.pid[0] < 0)
		error("Error al crear firstpid");
	i = 3;
	while (++vb.pnum < vb.cnum - 1)
	{
		vb.pid[vb.pnum] = fork();
		if (vb.pid[vb.pnum] == 0)
			create_midpid(&vb, argv, envp, i);
		else if (vb.pid[vb.pnum] < 0)
			error("Error al crear midpid");
		i++;
	}
	vb.pid[vb.pnum] = fork();
	if (vb.pid[vb.pnum] == 0)
		create_lastpid(&vb, argv, envp);
	else if (vb.pid[vb.pnum] < 0)
		error("Error al crear lastpid");
	closepipes(&vb);
	i = -1;
	while (++i < vb.cnum)
		waitpid(vb.pid[i], &status, 0);
	if (vb.hd)
		unlink(".here_doc");
	i = -1;
	while (vb.pipefd[++i])
		free(vb.pipefd[i]);
	free(vb.pipefd);
	free(vb.pid);
	return (WEXITSTATUS(status));
}
