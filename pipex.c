/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:28:22 by nreher            #+#    #+#             */
/*   Updated: 2023/04/18 10:46:12 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envvars[])
{
	t_all	*a;

	if (argc < 5)
		return (1);
	urandom_protection(argv);
	a = ft_calloc(1, sizeof(t_all));
	error_manager(a, 1);
	a->fd = open(argv[1], O_RDONLY);
	error_manager(a, 2);
	a->args = ft_calloc(argc - 2, sizeof(char **));
	error_manager(a, 3);
	a->c = 2;
	while (a->c < argc - 1)
	{
		a->args[a->c - 2] = ft_split(argv[a->c], ' ');
		error_manager(a, 4);
		a->c++;
	}
	a->paths = path_maker(envvars);
	error_manager(a, 5);
	a->perr = pipe_maker(a, argc);
	error_manager(a, 6);
	a->werr = worker(a, argc, argv);
	error_manager(a, 7);
	return (0);
}

void	error_manager(t_all *a, int err)
{
	if (err == 1 && a == NULL)
	{
		perror("allocation of struct failed");
		exit(1);
	}
	error_manager_1(a, err);
}

void	error_manager_1(t_all *a, int err)
{
	if (err == 4 && a->args[a->c - 2] == NULL)
	{
		perror("an argument could not be read in");
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
	if (err == 3 && a->args == NULL)
	{
		perror("allocation of argument array failed");
		close(a->fd);
		exit(1);
	}
	error_manager_2(a, err);
}

void	error_manager_2(t_all *a, int err)
{
	if (err == 5 && a->paths == NULL)
	{
		perror("Path creation failed");
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
	if (err == 2 && a->fd == -1)
	{
		perror("infile could not be opened");
		exit(1);
	}
	error_manager_3(a, err);
}

void	error_manager_3(t_all *a, int err)
{
	if (err == 6 && a->perr > 0)
	{
		if (a->perr == 1)
			perror("Pipe array creation failed");
		if (a->perr == 2)
		{
			perror("A Pipe could not be created");
			a->c = 0;
			while (a->pipefd[a->c] != NULL)
				free(a->pipefd[a->c++]);
			free(a->pipefd);
		}
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
	error_manager_4(a, err);
}
