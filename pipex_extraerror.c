/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_extraerror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:32:43 by nreher            #+#    #+#             */
/*   Updated: 2023/04/18 10:46:20 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	extra_error_message(t_all *a)
{
	if (a->werr == 1)
		perror("Could not duplicate input fd to stdin");
	if (a->werr == 2)
		perror("Could not set write side of an intermediate pipe");
	if (a->werr == 3)
		perror("Could not set read side of an intermediate pipe");
	if (a->werr == 4)
		perror("Could not dup output fd to stdout");
}

void	error_manager_4(t_all *a, int err)
{
	if (err == 7 && a->werr > 0)
	{
		extra_error_message(a);
		a->c = 0;
		a->i = 0;
		while (a->pipefd[a->c] != NULL)
			free(a->pipefd[a->c++]);
		free(a->pipefd);
		close(a->fd);
		a->c = 0;
		a->i = 0;
		while (a->args[a->c] != NULL)
		{
			while (a->args[a->c][a->i] != NULL)
				free(a->args[a->c][a->i++]);
			a->i = 0;
			free(a->args[a->c++]);
		}
		exit(1);
	}
	return ;
}
