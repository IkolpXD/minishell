/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlucena- <mlucena-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:03:53 by mlucena-          #+#    #+#             */
/*   Updated: 2026/03/28 13:12:55 by mlucena-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_ast(t_ast *node, int *fds, t_shell *shell)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		exec_pipe(node, fds, shell);
	else if (node->type == NODE_CMD)
		exec_cmd(node, fds, shell);
}

void	wait_for_all_children(t_shell *shell)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		pid = wait(&status) > 0;
		if (pid <= 0)
			break ;
		if (WIFEXITED(status))
			shell->last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit = 128 + WTERMSIG(status);
	}
}
