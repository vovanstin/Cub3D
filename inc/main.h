/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjanetta <cjanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 20:40:25 by nomargen          #+#    #+#             */
/*   Updated: 2022/10/20 16:31:19 by cjanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include "../lib/libft/libft.h"
# include "parser.h"
# include "draw_map.h"

void	free_game(t_game *game);

#endif
