/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlucena- <mlucena-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:03:43 by mlucena-          #+#    #+#             */
/*   Updated: 2026/03/28 13:28:17 by mlucena-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	save_stds(int fds[2])
{
	fds[0] = dup(STDIN_FILENO);
	fds[1] = dup(STDOUT_FILENO);
}

void	exec_cmd_for_builtin(t_ast *node, int *fds_sup, t_shell *shell)
{
	if (!ft_strncmp(node->cmd_args[0], "exit", 5))
		restore_stds(fds_sup);
	shell->last_exit = exec_builtin(shell, node->cmd_args);
	if (ft_strncmp(node->cmd_args[0], "exit", 5))
		restore_stds(fds_sup);
}

static void	write_status(int exit_code)
{
	if (exit_code == 131)
		write(1, "Quit\n", 5);
	if (exit_code == 2)
		write(1, "\n", 1);
}

void	exec_cmd(t_ast *node, int *fds, t_shell *shell)
{
	pid_t	pid;
	int		fds_sup[2];
	int		exit_code;

	save_stds(fds_sup);
	if (apply_redirecs(node->redirs))
	{
		restore_stds(fds_sup);
		shell->last_exit = 1;
		return ;
	}
	if (is_builtin(node))
		return (exec_cmd_for_builtin(node, fds_sup, shell));
	ign_signals();
	pid = fork();
	if (pid == 0)
		exec_cmd_aux(node, fds, shell, fds_sup);
	restore_stds(fds_sup);
	if (pid > 0)
	{
		waitpid(pid, &exit_code, 0);
		if (WIFEXITED(exit_code))
			shell->last_exit = WEXITSTATUS(exit_code);
		else if (WIFSIGNALED(exit_code))
			shell->last_exit = 128 + WTERMSIG(exit_code);
		write_status(shell->last_exit);
	}
	else if (pid < 0)
		perror("fork");
}
