/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 21:32:53 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/11 20:03:16 by vtlostiu         ###   ########.fr       */
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
# define TEXTURES	4

# define RED		0xFC0000
# define GREEN		0x45A400
# define BLUE		0x7FE6F8
# define YELLOW		0xFEF963

typedef struct			s_draw
{
	int		x;
	int		y;
}						t_draw;

typedef struct		s_vector2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_pix
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*image;

	SDL_Surface		*surf;
	int				fd;
	size_t 			width;
	size_t			height;
	t_vec2			pos;
//	int				buf[HEIGHT][WIDTH];
	int				*screen;
	int				**map;
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
int					parsing(t_pix *pix, t_lines *lst, t_vec2 pos);


#endif
