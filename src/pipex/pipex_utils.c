/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <joltra-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:07:12 by joltra-r          #+#    #+#             */
/*   Updated: 2024/12/04 15:22:00 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

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
	exit(1);
}
