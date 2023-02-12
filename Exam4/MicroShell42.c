/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MicroShell42.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:02:07 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/12 23:56:35 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//			######			//
//		--- STRUCT ---		//

typedef	struct		s_cmd
{
	char			**content;
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
	init->chain->head_cmd_line = init->chain->cmd_line;
	content = count_cmd_plus_args(av, 0);
	init->chain->cmd_line->content = malloc(sizeof(char *) * (content + 1));
	if (!init->chain->cmd_line->content)
		return (NULL);
	return (init);
}

int	parse_commands(char **av, t_mcroshell *m)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (av[i])
	{
		if (!j)
		{
			j = count_cmd_plus_args(av, i);
			m->chain->cmd_line->content = malloc(sizeof(char *) * (j + 1));
			if (!m->chain->cmd_line->content)
				return (0);
			k = 0;
		}
		else if (!ft_strcmp(av[i], "|"))
		{
			m->chain->cmd_line->next = malloc(sizeof(t_cmd));
			if (!m->chain->cmd_line->next)
				return (0);
			m->chain->cmd_line = m->chain->cmd_line->next;
			j = 0;
			i++;
		}
		else if (av[i + 1] && !ft_strcmp(av[i], ";"))
		{
			m->chain->next = malloc(sizeof(t_chain));
			if (!m->chain->next)
				return (0);
			m->chain = m->chain->next;
			m->chain->cmd_line = malloc(sizeof(t_cmd));
			if (!m->chain->cmd_line)
				return (0);
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
	return (i);

}

//			######			//
//		 --- MAIN ---		//

int main(int ac, char **av)
{
	dprintf(2, "\n%s\n\n", " - % MicroShell42 training % - ");
	t_mcroshell		*micro_shell;
	int 			pipe_fds[2];
	int				i;

	i = 0;
	micro_shell = init_microshell(av);
	parse_commands(av, micro_shell);
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
	(void)pipe_fds;
	(void)ac;
	return (0);
}