/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:24:57 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/10 20:46:08 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/parser.h"

int	check_alloc(void *ptr)
{
	if (ptr == NULL)
	{
		ft_putstr_fd("Allocation fail!\n", ERR_FD);
		return (0);
	}
	return (1);
}

int	free_alloced_ptr_mas(char ***mass)
{
	int	i;

	i = 0;
	if (*mass == NULL)
		return (0);
	while ((*mass)[i] != NULL)
	{
		free((*mass)[i]);
		i++;
	}
	free(*mass);
	*mass = NULL;
	return (0);
}

int	skip_lines(int fd, int cnt)
{
	int		i;
	char	buf;

	i = 0;
	while (i < cnt)
	{
		if (read(fd, &buf, 1) < 0)
		{
			ft_putstr_fd("File read fail!\n", ERR_FD);
			return (0);
		}
		if (buf == '\n')
			i++;
	}
	return (1);
}

int	allocate_n_open_map(t_game *game, int *map_file_fd,
		char const *map_file_path)
{
	if (game->map == NULL)
	{
		ft_putstr_fd("Allocation fail!\n", ERR_FD);
		return (0);
	}
	*map_file_fd = open(map_file_path, O_RDONLY);
	if (*map_file_fd < 0)
	{
		safe_free(game->map, 0);
		perror(map_file_path);
		return (0);
	}
	return (1);
}

int	check_map_walls2(t_game *game, int i, int j)
{
	if (i == 0 || !(game->map[i - 1][j] == '1'
		|| game->map[i - 1][j] == '0'))
		return (0);
	if (j == 0 || !(game->map[i][j - 1] == '1'
		|| game->map[i][j - 1] == '0'))
		return (0);
	if (j == game->map_size_x - 1 || !(game->map[i][j + 1] == '1'
		|| game->map[i][j + 1] == '0'))
		return (0);
	if (i == game->map_size_y - 1 || !(game->map[i + 1][j] == '1'
		|| game->map[i + 1][j] == '0'))
		return (0);
	return (1);
}
