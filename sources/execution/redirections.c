/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danuno-g <danuno-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:44:20 by agrippa           #+#    #+#             */
/*   Updated: 2026/03/20 23:26:02 by danuno-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	apply_redirecs(t_redir *redirs)
{
	while (redirs)
	{
		if (handle_what_redir(redirs))
			return (1);
		redirs = redirs->next;
	}
	return (0);
}

int	handle_what_redir(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (redir_in(redir->filename));
	else if (redir->type == REDIR_OUT)
		return (redir_out(redir->filename));
	else if (redir->type == APPEND)
		return (redir_append(redir->filename));
	else if (redir->type == HEREDOC)
		return (here_doc_execution(redir));
	return (0);
}

int	redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redir_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
