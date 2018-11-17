/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 23:43:06 by jyeo              #+#    #+#             */
/*   Updated: 2017/11/25 23:43:08 by jyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	t_line	*ft_newlst(int fd)
{
	t_line			*line;

	if ((line = (t_line *)malloc(sizeof(t_line))) == NULL)
		return (NULL);
	line->fd = fd;
	line->n_line = NULL;
	line->next = NULL;
	return (line);
}

static	t_line	*ft_fetch_line(t_line **list, int fd)
{
	t_line			*lst;
	t_line			*new;

	if (!(*list))
		*list = ft_newlst(fd);
	lst = *list;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	if (!lst)
	{
		new = ft_newlst(fd);
		new->next = *list;
		*list = new;
	}
	return (*list);
}

static	char	*ft_get_line(char **next_line)
{
	int				i;
	char			*tmp;
	char			*line;

	i = 0;
	while ((*next_line)[i] && (*next_line)[i] != '\n')
		i++;
	tmp = ft_strsub(*next_line, 0, i);
	line = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	if ((*next_line)[i] != '\0')
		i++;
	tmp = *next_line;
	*next_line = ft_strdup(*next_line + i);
	free(tmp);
	tmp = NULL;
	return (line);
}

static	int		ft_get(const int fd, char *buf, char **next_line)
{
	int				ret;
	char			*tmp;

	if (!(*next_line) || **next_line == '\0')
		*next_line = ft_strnew(0);
	while (!(ft_strchr(buf, '\n')))
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[ret] = '\0';
			tmp = *next_line;
			*next_line = ft_strjoin(*next_line, buf);
			free(tmp);
			tmp = NULL;
		}
		else if (ret == 0)
			return (0);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			*buf;
	t_line			*lst;
	static t_line	*list;

	lst = ft_fetch_line(&list, fd);
	buf = ft_strnew(BUFF_SIZE);
	if (fd == -1 || (read(fd, buf, 0)) == -1 || !line)
		return (-1);
	ft_get(fd, buf, &lst->n_line);
	free(buf);
	buf = NULL;
	if (*lst->n_line != '\0')
		*line = ft_get_line(&lst->n_line);
	else
		return (0);
	return (1);
}
