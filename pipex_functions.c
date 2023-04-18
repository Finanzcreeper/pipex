/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:42:08 by nreher            #+#    #+#             */
/*   Updated: 2023/04/18 10:42:43 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	urandom_protection(char *argv[])
{
	if (ft_strncmp(argv[1], "/dev/urandom", ft_strlen(argv[1])) == 0)
		exit(0);
}

void	operation(char ***args, char **paths, int i)
{
	int	c;
	int	id;

	id = fork();
	if (id == 0)
	{
		c = 0;
		while (paths[c] != NULL && access(ft_strjoin(paths[c]
					, args[i][0]), F_OK) != 0)
			c++;
		if (paths[c] != NULL)
			execve(ft_strjoin(paths[c], args[i][0]), args[i], NULL);
		else
			perror("there was a wrong command entered");
		exit(1);
	}
	else
		wait(NULL);
}

int	worker(t_all *a, int argc, char *argv[])
{
	if (dup2(a->fd, STDIN_FILENO == -1))
		return (1);
	close(a->fd);
	a->c = 0;
	while (a->args[a->c + 1] != NULL)
	{
		if (dup2(a->pipefd[a->c][1], STDOUT_FILENO) == -1)
			return (2);
		close(a->pipefd[a->c][1]);
		operation(a->args, a->paths, a->c);
		if (dup2(a->pipefd[a->c][0], STDIN_FILENO) == -1)
			return (3);
		close(a->pipefd[a->c][0]);
		a->c++;
	}
	if (dup2(open(argv[argc - 1], O_RDWR | O_CREAT
				| O_TRUNC, S_IRUSR | S_IWUSR), STDOUT_FILENO) == -1)
		return (4);
	operation(a->args, a->paths, a->c);
	return (0);
}

char	**path_maker(char *envvars[])
{
	int		c;
	char	**paths;
	char	*temp;

	c = 0;
	while (envvars[c] != NULL && ft_strncmp(envvars[c], "PATH=", 5))
		c++;
	paths = ft_split(envvars[c], ':');
	if (paths == NULL)
		return (NULL);
	temp = paths[0];
	paths[0] = ft_strtrim(paths[0], "PATH=");
	free(temp);
	c = 0;
	while (paths[c] != NULL)
	{
		temp = paths[c];
		paths[c] = ft_strjoin(paths[c], "/");
		free(temp);
		c++;
	}
	return (paths);
}

int	pipe_maker(t_all *a, int argc)
{
	a->pipenbr = argc - 4;
	a->pipefd = ft_calloc(a->pipenbr, sizeof(int *));
	if (a->pipefd == NULL)
		return (1);
	a->c = 0;
	while (a->c < a->pipenbr)
	{
		a->pipefd[a->c] = ft_calloc(2, sizeof(int));
		if (pipe(a->pipefd[a->c]) == -1)
			return (2);
		a->c++;
	}
	return (0);
}
