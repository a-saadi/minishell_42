/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 11:33:40 by asaadi            #+#    #+#             */
/*   Updated: 2021/03/05 16:21:26 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"

typedef struct	s_exec
{
	char	**envp;
	char	**args;
	int		index;
	int		code_ret;
	int		r;
	t_list	*tl;
	t_list	*cond;
	int		pipe;
	pid_t	*c_pid_s;
}				t_exec;

# define CB 1000
# define CC 1001

int				g_var;
int				g_sig;

typedef struct	s_cmd
{
	t_list			*word_list;
	t_list			*redir_list;
}				t_cmd;

typedef struct	s_pipe
{
	t_list	*cmd_list;
}				t_pipe;

#endif
