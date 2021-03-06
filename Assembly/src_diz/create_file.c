/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:29:28 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:30:22 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		take_start(char *old_name)
{
	int start;
	int i;

	i = -1;
	start = 0;
	while (old_name[++i])
	{
		if (old_name[i] == '/')
			start = i + 1;
	}
	return (start);
}

int		take_new_name(t_dsm *src_code, char *old_name)
{
	int i;
	int start_name;

	start_name = take_start(old_name);
	if (!((src_code->file_name) =\
				(char *)malloc((ft_strlen(old_name) - start_name) + 1)))
		return (FAIL);
	i = 0;
	while (old_name[start_name] && old_name[start_name] != '.')
	{
		(src_code->file_name)[i] = old_name[start_name];
		i++;
		start_name++;
	}
	(src_code->file_name)[i++] = '.';
	(src_code->file_name)[i++] = 's';
	(src_code->file_name)[i++] = '\0';
	return (SUCCESS);
}

int		fill_new_file(t_dsm *src_code)
{
	int fd;

	if ((fd = open(src_code->file_name,\
					O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 1)
	{
		free(src_code->file_name);
		return (FAIL);
	}
	ft_putstr_fd(src_code->output, fd);
	close(fd);
	free(src_code->file_name);
	return (SUCCESS);
}
