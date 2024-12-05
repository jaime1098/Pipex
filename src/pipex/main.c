/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <joltra-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:07:12 by joltra-r          #+#    #+#             */
/*   Updated: 2024/12/04 15:05:31 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_vb	vb;
	int		status;

	status = 0;
	if (argc != 5)
		error("Argumentos incorrectos");
	check_nulls(argv);
	if (pipe(vb.pipefd) == -1)
		error("Error al crear el pipe");
	vb.pid[0] = fork();
	if (vb.pid[0] == 0)
		create_pid1(vb, argv, envp);
	else if (vb.pid[0] < 0)
		error("Error al crear pid1");
	vb.pid[1] = fork();
	if (vb.pid[1] == 0)
		create_pid2(vb, argv, envp);
	else if (vb.pid[1] < 0)
		error("Error al crear pid2");
	close(vb.pipefd[0]);
	close(vb.pipefd[1]);
	waitpid(vb.pid[0], NULL, 0);
	waitpid(vb.pid[1], &status, 0);
	return (WEXITSTATUS(status));
}
