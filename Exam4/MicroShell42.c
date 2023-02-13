/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MicroShell42.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:02:07 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/13 17:48:36 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//			######			//
//		--- STRUCT ---		//

typedef	struct		s_cmd
{
	char			**content;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}					t_cmd;

typedef	struct		s_chain
{
	t_cmd			*head_cmd_line;
	t_cmd			*cmd_line;
	int				fd_in;
	int				fd_out;
	struct s_chain	*next;
}					t_chain;

typedef	struct		s_mcroshell
{
	t_chain			*head_chain;
	t_chain			*chain;
}					t_mcroshell;

//			######			//
//		 --- UTILS ---		//

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*new_str(char *src)
{
	char	*new;
	int		i;

	i = ft_strlen(src);
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

int	count_cmd_plus_args(char **av, int start)
{
	int	pos;

	pos = start;
	while (av[start])
	{
		if (!ft_strcmp("|", av[start]) || !ft_strcmp(";", av[start]))
			break ;
		start++;
	}
	return (start - pos + 1);
}

//			######			//
//		 --- PROG ---		//

int	print_chains(t_mcroshell *micro_shell)
{
	int	i;

	micro_shell->chain = micro_shell->head_chain;
	while (micro_shell->chain)
	{
		micro_shell->chain->cmd_line = micro_shell->chain->head_cmd_line;
		while (micro_shell->chain->cmd_line)
		{
			i = 0;
			while (micro_shell->chain->cmd_line->content[i])
			{
				dprintf(2, "%s\n", micro_shell->chain->cmd_line->content[i]);
				i++;
			}
			micro_shell->chain->cmd_line = micro_shell->chain->cmd_line->next;
			dprintf(2, "%s\n", "PIPE");
		}
		micro_shell->chain = micro_shell->chain->next;	
		dprintf(2, "%s\n", "CHAIN");
	}
	return (1);
}

t_mcroshell	*init_microshell(char **av)
{
	t_mcroshell	*init;
	int			content;

	init = malloc(sizeof(t_mcroshell));
	if (!init)
		return (NULL);
	init->chain = malloc(sizeof(t_chain));
	if (!init->chain)
		return (NULL);
	init->head_chain = init->chain;
	init->chain->cmd_line = malloc(sizeof(t_cmd));
	if (!init->chain->cmd_line)
		return (NULL);
	init->chain->cmd_line->fd_in = 0;  
	init->chain->cmd_line->fd_out = 1;
	init->chain->head_cmd_line = init->chain->cmd_line;
	content = count_cmd_plus_args(av, 0);
	init->chain->cmd_line->content = calloc(sizeof(char *), (content + 1));
	if (!init->chain->cmd_line->content)
		return (NULL);
	return (init);
}

int	parse_commands(char **av, t_mcroshell *m)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	while (av[i])
	{
		if (!j)
		{
			j = count_cmd_plus_args(av, i);
			m->chain->cmd_line->content = calloc(sizeof(char *), (j + 1));
			if (!m->chain->cmd_line->content)
				return (0);
			k = 0;
		}
		else if (!ft_strcmp(av[i], "|"))
		{
			m->chain->cmd_line->next = malloc(sizeof(t_cmd));
			if (!m->chain->cmd_line->next)
				return (0);
			m->chain->cmd_line->next->fd_in = 0;
			m->chain->cmd_line->next->fd_out = 1;
			m->chain->cmd_line = m->chain->cmd_line->next;
			j = 0;
			i++;
		}
		else if (av[i + 1] && !ft_strcmp(av[i], ";"))
		{
			m->chain->cmd_line->next = NULL;
			m->chain->next = malloc(sizeof(t_chain));
			if (!m->chain->next)
				return (0);
			m->chain = m->chain->next;
			m->chain->cmd_line = malloc(sizeof(t_cmd));
			if (!m->chain->cmd_line)
				return (0);
			m->chain->cmd_line->fd_in = 0;
			m->chain->cmd_line->fd_out = 1;
			m->chain->head_cmd_line = m->chain->cmd_line;
			j = 0;
			i++;
		}
		else
		{
			m->chain->cmd_line->content[k] = new_str(av[i]);
			k++;
			i++;
		}
	}
	m->chain->cmd_line->next = NULL;
	m->chain->next = NULL;
	return (i);

}

int	exec_chains(t_mcroshell *m, char **env)
{
	int	pipe_fds[2];
	int	pid;

	m->chain = m->head_chain;
	while (m->chain)
	{
		m->chain->cmd_line = m->chain->head_cmd_line;
		while (m->chain->cmd_line)
		{
			if (m->chain->cmd_line->next)
			{
				if (pipe(pipe_fds) == -1)
					return (strerror(errno), 0);
				m->chain->cmd_line->fd_out = pipe_fds[1];
				m->chain->cmd_line->next->fd_in = pipe_fds[0];
			}
			pid = fork();
			if (!pid)
			{
				if (m->chain->cmd_line->fd_in != 0)
				{
					dup2(m->chain->cmd_line->fd_in, STDIN_FILENO);
					close(m->chain->cmd_line->fd_in);
				}
				if (m->chain->cmd_line->fd_out != 1)
				{
					dup2(m->chain->cmd_line->fd_out, STDOUT_FILENO);
					close(m->chain->cmd_line->fd_out);
				}
				if (m->chain->cmd_line->next)
					close(m->chain->cmd_line->next->fd_in);
				execve(m->chain->cmd_line->content[0], m->chain->cmd_line->content, env);
				exit(1);
			}
			if (pid > 0)
			{
				if (m->chain->cmd_line->fd_in != 0)
					close(m->chain->cmd_line->fd_in);
				if (m->chain->cmd_line->fd_out != 1)
					close(m->chain->cmd_line->fd_out);
				waitpid(pid, NULL, 0);
			}
			m->chain->cmd_line = m->chain->cmd_line->next;
		}
		m->chain = m->chain->next;
	}
	return (1);
}

int	free_process(t_mcroshell *m)
{
	t_chain *tmp_chain;
	t_cmd	*tmp_cmd;
	int	i;

	m->chain = m->head_chain;
	while (m->chain)
	{
		tmp_chain = m->chain;
		m->chain->cmd_line = m->chain->head_cmd_line;
		while (m->chain->cmd_line)
		{
			i = 0;
			tmp_cmd = m->chain->cmd_line;
			while (m->chain->cmd_line->content[i])
			{
				free(m->chain->cmd_line->content[i]);
				m->chain->cmd_line->content[i] = NULL;
			}
			free(m->chain->cmd_line->content);
			m->chain->cmd_line->content = NULL;
			m->chain->cmd_line = m->chain->cmd_line->next;
			free(tmp_cmd);
		}
		m->chain = m->chain->next;
		free(tmp_chain);
	}
	return (1);
}

//			######			//
//		 --- MAIN ---		//
int main(int ac, char **av, char **env)
{
	dprintf(2, "\n%s\n\n", " - % MicroShell42 training % - ");
	t_mcroshell		*micro_shell;

	micro_shell = init_microshell(av);
	parse_commands(av, micro_shell);
	exec_chains(micro_shell, env);
	free_process(micro_shell);
	(void)ac;
	return (0);
}
// print_chains(micro_shell);
