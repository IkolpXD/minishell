/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danuno-g <danuno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 09:15:14 by agrippa           #+#    #+#             */
/*   Updated: 2026/03/20 23:25:42 by danuno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cleanup_and_exit(t_shell *shell, int exit_code)
{
	free_env_list(shell->env);
	free_ast(shell->ast);
	free_token_list(shell->tokens);
	free(shell->line);
	rl_clear_history();
	exit(exit_code);
}

void	exec_cmd_aux(t_ast *node, int *fds, t_shell *shell, int fds_sup[2])
{
	char	*path;
	char	**envp;

	close(fds_sup[0]);
	close(fds_sup[1]);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (fds[0] != STDIN_FILENO)
		dup2(fds[0], STDIN_FILENO);
	if (fds[1] != STDOUT_FILENO)
		dup2(fds[1], STDOUT_FILENO);
	if (!node->cmd_args || !node->cmd_args[0])
		cleanup_and_exit(shell, 0);
	path = find_path(node->cmd_args[0], shell);
	if (!path)
	{
		ft_putstr_fd(node->cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		cleanup_and_exit(shell, 127);
	}
	envp = env_array(shell->env);
	execve(path, node->cmd_args, envp);
	perror("execve");
	free_envp(envp);
	cleanup_and_exit(shell, 1);
}
