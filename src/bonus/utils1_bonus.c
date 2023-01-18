/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nomargen <nomargen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:25:49 by cjanetta          #+#    #+#             */
/*   Updated: 2022/10/21 21:32:03 by nomargen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/draw_map_bonus.h"

void	make_textures_addr(t_draw *draw, t_game *game)
{
	int		i;
	void	*tex_img;
	int		arg[2];

	i = 0;
	while (i != TEXTURE_CNT)
	{
		tex_img = mlx_xpm_file_to_image(draw->mlx.mlx, game->textures_path[i],
				&arg[0], &arg[1]);
		if (arg[0] != 64 || arg[1] != 64 || !tex_img)
		{
			if (tex_img)
				mlx_destroy_image(draw->mlx.mlx, tex_img);
			print_err_with_header(i + 1,
				"Texture file must be in xpm format!\n");
			exit_func(NULL, draw);
		}
		get_tex_pixels(&(draw->textures[i++]), tex_img);
		mlx_destroy_image(draw->mlx.mlx, tex_img);
	}
}

void	exit_func(char *msg, t_draw *draw)
{
	free_game(draw->game);
	if (draw->textures[TEXTURE_INDEX_NORTH])
		free(draw->textures[TEXTURE_INDEX_NORTH]);
	if (draw->textures[TEXTURE_INDEX_SOUTH])
		free(draw->textures[TEXTURE_INDEX_SOUTH]);
	if (draw->textures[TEXTURE_INDEX_WEST])
		free(draw->textures[TEXTURE_INDEX_WEST]);
	if (draw->textures[TEXTURE_INDEX_EAST])
		free(draw->textures[TEXTURE_INDEX_EAST]);
	if (draw->mlx.img)
		mlx_destroy_image(draw->mlx.mlx, draw->mlx.img);
	if (draw->mlx.win)
		mlx_destroy_window(draw->mlx.mlx, draw->mlx.win);
	if (msg)
		ft_putstr_fd(msg, ERR_FD);
	exit(EXIT_FAILURE);
}

int	stop_exit(t_draw *draw)
{
	exit_func(NULL, draw);
	return (0);
}
