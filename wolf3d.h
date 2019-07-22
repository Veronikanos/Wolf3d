/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtlostiu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 21:32:53 by vtlostiu          #+#    #+#             */
/*   Updated: 2019/07/22 22:20:55 by vtlostiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <pthread.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "libft.h"

//# include "SDL.h"
//# include "./frameworks/SDL2.framework/Headers/SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"

//# define WIDTH		512
//# define HEIGHT		384
# define WIDTH		1000
# define HEIGHT		600
# define NAME		"Wolf3d by vtlostiu"
# define TEXTURES	8

# define TEXWIDTH	64
# define TEXHEIGHT	64

# define DIST		28.2

# define RED		0xFC0000
# define GREEN		0x4BE800
# define BLUE		0x7FE6F8
# define YELLOW		0xFFFC00
# define PURPLE		0xB234FD
# define MAGENTA	0xE949FA
# define PINK		0xFA2BD8
# define CORAL		0xFA2B8D
# define DEF_COL	0x0C00FF
# define FLOOR_COL	0xFFEBED
# define CEIL_COL	0xB7F1FA

typedef struct			s_map
{
	int				x;
	int				y;
}						t_map;

typedef struct			s_flag
{
	bool			straight;
	bool			back;
	bool			right;
	bool			left;
	bool			tex_change;
}						t_flag;

typedef struct		s_vector2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_player
{
	t_vec2			pos;
	t_vec2			dir;
	double			move_rate;
	double			rot_rate;
}					t_plr;

typedef struct		s_ray
{
	t_vec2			dir;
	t_vec2			sideDist;
	t_vec2			deltaDist;

}					t_ray;

typedef struct		s_pix
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Texture		*image;
	SDL_Surface		*screen_surf;
	SDL_Surface		**tex_arr;
	int				fd;
	size_t 			width;
	size_t			height;
	t_flag			flag;
	double			time; // время текущего кадра
	double			oldTime; // время предыдущего кадра
	double			cameraX;
	double			frameTime;

	double			wallX;
	int				texX;
	int				texY;
	int				texNum;
	int				d;

	int				*screen;
	int				**map;
	int				lineHeight;
	int				side;
	t_vec2			plane;
	t_map			ray_map_cord;
	t_map			drawfromto;
	t_map			step;
	t_plr			player;
	t_ray			ray;
	int				running;

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
int					parsing(t_pix *pix, t_lines *lst, t_vec2 *pos);
int					choose_color(t_pix *pix);
void				event_handler(t_pix *pix);
void				game_process(t_pix *pix);
void				verLine(t_pix *pix, size_t x, int y, int _end, int color);
void				clear_screen(t_pix *pix);
t_pix				*init(t_pix *pix);


#endif
