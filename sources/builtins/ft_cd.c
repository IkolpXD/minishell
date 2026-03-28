/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlucena- <mlucena-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:06:38 by mlucena-          #+#    #+#             */
/*   Updated: 2026/03/28 12:06:42 by mlucena-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*resolve_cd_target(t_shell *shell, char *arg)
{
	if (!arg || ft_strncmp(arg, "~", 2) == 0)
		return (get_env_value_from_env(shell->env, "HOME"));
	if (ft_strncmp(arg, "-", 2) == 0)
		return (get_env_value_from_env(shell->env, "OLDPWD"));
	return (arg);
}

static void	update_cd_env(t_shell *shell, char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (oldpwd)
		add_or_update(&shell->env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		add_or_update(&shell->env, "PWD", cwd);
}

int	ft_cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	char	*target;

	if (args[1] && args[2])
	{
		fprintf(stderr, "cd: too many arguments\n");
		return (1);
	}
	oldpwd = get_env_value_from_env(shell->env, "PWD");
	if (oldpwd)
		oldpwd = ft_strdup(oldpwd);
	target = resolve_cd_target(shell, args[1]);
	if (!target)
	{
		printf("cd: no such file or directory\n");
		free(oldpwd);
		return (1);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	update_cd_env(shell, oldpwd);
	free(oldpwd);
	return (0);
}
