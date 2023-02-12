/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MicroShell42.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:02:07 by oboutarf          #+#    #+#             */
/*   Updated: 2023/02/12 18:46:48 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

//			######			//
//		--- STRUCT ---		//

typedef	struct		s_cmd
{
	char			**content;
	struct s_cmd	*next;
}					t_cmd;

typedef	struct		s_chain
{
	t_cmd			*cmd_line;
	int				fd_in;
	int				fd_out;
	struct t_chain	*next;

}					t_chain;

typedef	struct		s_mcroshell
{
	t_chain			*head_chain;
	t_chain			*chain;
}					t_mcroshell;

//			######			//
//		 --- UTILS ---		//

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

//			######			//
//		 --- PROG ---		//

t_mcroshell	*init_microshell()
{
	t_mcroshell	*init;

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
	return (init);
}

int	parse_commands(char **av, t_mcroshell *m)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "|"))
		{
			m->chain->cmd_line->next = malloc(sizeof(t_cmd));
			if (!m->chain->cmd_line->next)
				return (0);
			m->chain->cmd_line = m->chain->cmd_line->next;
		}
		else if (!ft_strcmp(av[i], ";"))
		{
			m->chain->next = malloc(sizeof(t_chain));
			if (!m->chain->next)
				return (0);
			m->chain = m->chain->next;
		}
		else if (!av[i + 1])
		{
			m->chain = m->head_chain;
			break ;
		}
		else
		{
			m->chain->cmd_line->content
		}
	}

}

//			######			//
//		 --- MAIN ---		//

int main(int ac, char **av)
{
	dprintf(2, "\n%s\n\n", " - % MicroShell42 training % - ");
	t_mcroshell		*micro_shell;
	int 			pipe_fds[2];
	int			i;

	i = 0;
	micro_shell = init_microshell();
	parse_chains(micro_shell);
	
	return (0);
}