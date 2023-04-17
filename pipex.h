/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:49:46 by nreher            #+#    #+#             */
/*   Updated: 2023/04/17 15:01:51 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_all
{
	char	***args;
	char	**paths;
	int		**pipefd;
	int		pipenbr;
	int		fd;
	int		c;
	int		i;
	int		ec;
	int		ei;
	int		perr;
	int		werr;
}t_all;

void	operation(char ***args, char **paths, int i);
int		worker(t_all *a, int argc, char *argv[]);
void	free_a(t_all *a);
char	**path_maker(char *envvars[]);
int		pipe_maker(t_all *a, int argc);
void	error_manager(t_all *a, int err);
void	error_manager_1(t_all *a, int err);
void	error_manager_2(t_all *a, int err);
void	error_manager_3(t_all *a, int err);
void	error_manager_4(t_all *a, int err);
void	extra_error_message(t_all *a);
void	urandom_protection(char *argv[]);
#endif
