/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joltra-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:37:53 by joltra-r          #+#    #+#             */
/*   Updated: 2024/05/20 17:37:55 by joltra-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "get_next_line/get_next_line.h"

void	check_hd(char *s)
{
	int	n;

	n = ft_strncmp(s, "here_doc", ft_strlen(s));
	if (n == 0)
		error("Invalid arguments");
}

int	heredoc(t_vb *vb, char **argv)
{
	char	*buff;
	char	*delete;

	if (ft_strncmp("here_doc", argv[1], 9) != 0)
		return (0);
	vb->fd_in = open(".here_doc", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (vb->fd_in < 0)
		error("Error opening here_doc");
	delete = ft_strjoin(ft_strdup(argv[2]), "\n");
	while (1)
	{
		buff = get_next_line(0);
		if (!buff || !ft_strncmp(buff, delete, ft_strlen(buff)))
			break ;
		write(vb->fd_in, buff, ft_strlen(buff));
		free (buff);
	}
	free(delete);
	if (buff)
		free(buff);
	close (vb->fd_in);
	return (1);
}
