/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <vtlostiu@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 21:32:53 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/04 21:24:28 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <pthread.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"

//# include "SDL.h"
//# include "./frameworks/SDL2.framework/Headers/SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"

# define WIDTH		512
# define HEIGHT		384
# define NAME		"Wolf3d by vtlostiu"

//typedef struct		s_player
//{
//	double			x;
//	double			y;
//}					t_player;

//typedef struct		s_vector2
//{
//	double			x;
//	double			y;
//}					t_vec2;

typedef struct		s_pix
{
	SDL_Window		*win;
	int				fd;
	size_t 			width;
	size_t			height;
	int				j;
	int				**map_val;
}					t_pix;

typedef struct		s_lines
{
	char			*str;
	struct s_lines	*next;
}					t_lines;

void				is_file_valid(t_pix *pix, t_lines **lines_head);
int					errors_msg(int err);
void				ft_add_to_end(t_lines **head, char *str);
void				ft_del_all(t_lines **head);
int					parsing(t_pix *pix, t_lines *lines_head);


#endif
