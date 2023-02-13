/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MicroShellAV42.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 23:06:48 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/13 23:46:54 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef	struct	s_piping
{
	int	fd_in;
	int	fd_out;
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*new_str(const char *src)
{
	char	*new;
	int		i;

	i = ft_strlen((char *)src);
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	return_cmd_and_args(char **av, int i)
{
	if (!av[i])
		return (0);
	while (av[i] && !ft_strcmp(av[i], "|") && !ft_strcmp(av[i], ";"))
		i++;
	return (i + 1);
}

int	main(int ac, char **av, char **env)
{
	char	**cmd_and_args;
	int		fds_pipe[2];
	int 	loop;
	int		cmd;
	int		pid;
	int		i;
	int		j;

	i = 1;
	loop = 0;
	while (av[i])
	{
		cmd = return_cmd_and_args(av, i);
		if (!cmd)
			break ;
		cmd_and_args = malloc(sizeof(char *) * (cmd - i + 2));
		if (!cmd_and_args)
			return (0);
		j = 0;
		while (i <= cmd)
		{
			cmd_and_args[j] = new_str(av[i]);
			j++;
			i++;
		}
		cmd_and_args[j] = NULL;
		if (pipe(fds_pipe) == -1)
			return (0);
		pid = fork();
		if (pid == -1)
		{
			dprintf(2, "microshell: fork failed\n");
			return (0);
		}
		if (!pid)
		{
			if (loop)
			{
				dup2(fds_pipe[0], STDIN_FILENO);
				dup2(fds_pipe[1], STDOUT_FILENO);
			}
			else
			{
				dup2(fds_pipe[1], STDOUT_FILENO);
			}
			execve(cmd_and_args[0], cmd_and_args, env);
		}
		return (0);
	}
	(void)fds_pipe;
	(void)ac;
	return (1);
	
}
