/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danuno-g <danuno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:11:52 by danuno-g          #+#    #+#             */
/*   Updated: 2026/03/20 23:25:09 by danuno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(t_ast *node)
{
	char	*cmd;

	if (!node || !node->cmd_args || !node->cmd_args[0])
		return (0);
	cmd = node->cmd_args[0];
	if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	if (!ft_strncmp(cmd, "env", 4))
		return (1);
	if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	exec_builtin(t_shell *shell, char **args)
{
	if (!args || !args[0])
		return (1);
	if (!ft_strncmp(args[0], "echo", 5))
		return (ft_echo(args));
	if (!ft_strncmp(args[0], "cd", 3))
		return (ft_cd(shell, args));
	if (!ft_strncmp(args[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(args[0], "export", 7))
		return (ft_export(shell, args));
	if (!ft_strncmp(args[0], "unset", 6))
		return (ft_unset(shell, args));
	if (!ft_strncmp(args[0], "env", 4))
		return (ft_env(shell));
	if (!ft_strncmp(args[0], "exit", 5))
		return (ft_exit(shell, args));
	return (1);
}
