/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadi <asaadi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 11:00:04 by asaadi            #+#    #+#             */
/*   Updated: 2021/02/03 18:20:49 by asaadi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_cmd(char **args, char **envp)
{
	pid_t _pid;
	int status;

	_pid = 0;
	status = 0;
	_pid = fork();
	if (_pid == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit_function(1);
	}
	else if (_pid > 0)
	{
		waitpid(_pid, &status, 0);
		kill(_pid, SIGTERM);
	}
	else
	{
		if (execve(args[0], args, envp) < 0)
		{
			ft_putendl_fd(strerror(errno), 2);
			exit_function(1);
		}
	}
}

void non_built_ins_execution(t_exec *exec, char **envp)
{
	// segfault 3ada3adaw chno hada
	if (get_cmd_path(exec->args, envp))
		exec_cmd(exec->args, envp);
}

int check_if_built_in(char *cmd)
{
	if (cmd && ft_strcmp(cmd, "env") && ft_strcmp(cmd, "cd") &&
		ft_strcmp(cmd, "pwd") && ft_strcmp(cmd, "exit") &&
		ft_strcmp(cmd, "export") && ft_strcmp(cmd, "unset") &&
		ft_strcmp(cmd, "echo"))
		return (0);
	return (1);
}

void built_ins_execution(t_exec *exec, char ***envp)
{
	if (!ft_strcmp(exec->args[0], "cd"))
		change_directory(exec->args[1], *envp);
	if (!ft_strcmp(exec->args[0], "pwd") ||
		!ft_strcmp(exec->args[0], "PWD"))
		pwd_function();
	if (!ft_strcmp(exec->args[0], "echo") ||
		!ft_strcmp(exec->args[0], "ECHO"))
	{
		if (exec->args[1] && !ft_strcmp(exec->args[1], "-n"))
			echo_function(exec->args, 1);
		else
			echo_function(exec->args, 0);
	}
	if (!ft_strcmp(exec->args[0], "export"))
	{
		if (exec->args[1])
			export_function(envp, exec->args);
		else
			sort_print_envp_alpha(*envp);
	}
	if (!ft_strcmp(exec->args[0], "unset"))
		unset_function(envp, exec->args);
	if (!ft_strcmp(exec->args[0], "env") ||
		!ft_strcmp(exec->args[0], "ENV"))
		env_function(*envp);
	if (!ft_strcmp(exec->args[0], "exit"))
	{
		if (!exec->args[1])
			exit_function(0);
		else
			exit_function(ft_atoi(exec->args[1]));
	}
}

// void get_arr_of_args(t_list *word_list, t_exec *exec)
// {
// 	if (!(exec->args = (char **)malloc(sizeof(char *) * (ft_lstsize(word_list) + 1))))
// 		ft_putendl_fd("ERROR AT MALLOC", 2);
// 	exec->index = 0;
// 	while (word_list != NULL)
// 	{
// 		exec->args[exec->index] = ft_strdup(word_list->content);
// 		word_list = word_list->next;
// 		exec->index++;
// 	}
// 	// cmd = cmd->next;
// 	exec->args[exec->index] = NULL;
// }

// int lst_cmd(t_list *tmp)
// {
// 	t_list *tmps = tmp;
// 	int i = 0;
// 	while (tmp && ((t_token *)tmp->content)->type == e_state_nsc)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	tmp = tmps;
// 	return (0);
// }

void execution_cmds(t_list *token_list, char **envp)
{
	t_list *tmp__list;
	// t_cond *cond;
	t_pipe *pipe;
	// t_cmd *cmd;
	// t_list *cmd_list;
	t_cmd *tmp__cmd;
	t_exec exec;
	int i, list;

	(void)envp;

	tmp__list = token_list;
	fill_pipe(tmp__list, &pipe, e_state_pipe);
	list = 0;
	while (pipe->cmd_list)
	{
		i = 0;
		tmp__cmd = (t_cmd *)pipe->cmd_list->content;
		if (!(exec.args = (char **)malloc(sizeof(char *) * (ft_lstsize(tmp__cmd->word_list) + 1))))
			ft_putendl_fd("ERROR AT MALLOC", 2);
		i = 0;
		while (tmp__cmd->word_list != NULL)
		{
			printf("arg0%d: |%s|\n", i, tmp__cmd->word_list->content);
			exec.args[i++] = ft_strdup(tmp__cmd->word_list->content);
			tmp__cmd->word_list = tmp__cmd->word_list->next;
		}
		exec.args[i] = NULL;
		i = 0;
		while (tmp__cmd->redir_list)
		{
			printf("redir0%d: |%s|\n", i, ((t_redir *)tmp__cmd->redir_list->content)->file);
			tmp__cmd->redir_list = tmp__cmd->redir_list->next;
			i++;
		}
		// if (check_if_built_in(&exec))
		// {
		// 	built_ins_execution(&exec, &envp);
		// 	puts("HEERE_b");
		// }
		// else
		// {
		// 	non_built_ins_execution(&exec, envp);
		// 	puts("HEERE_no_b");
		// }
		printf("***LIST_PIPE0%d\n", list++);
		pipe->cmd_list = pipe->cmd_list->next;
	}
}
/*
**  if (check_if_built_in(exec))
**  	built_ins_execution(exec, &envp);
**  else
**  	non_built_ins_execution(exec, envp);
*/
