/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sdl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 21:25:04 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_SDL_H
# define MY_SDL_H

# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation"

# include "SDL.h"

# pragma clang diagnostic pop

typedef struct	s_keys
{
	char		update;
	int			change_scene;
	char		light;
	char		indirect_light;
	char		parallel_light;
	char		spot_light;
	char		c_mode;
	char		visual_effect;
	char		tone_mapper;
	double		scale_speed;
	double		scale_angle;
	double		aperture;
	double		fl;
}				t_keys;

typedef	struct	s_window
{
	SDL_Window		*win;
	SDL_Renderer	*ren;
	SDL_Surface		*surf;
	SDL_Texture		*tex;
	t_uch			*data;
}				t_window;

void			handle_events(t_info *a, SDL_Event event, int key);
void			update_from_gui(t_info *a, t_keys k);
void			init_sdl(t_info *a);
void			destroy_sdl(t_info *a);
void			sdl_loop(t_info *a);
void			save_image(t_info *a, char *name);
void			get_image(t_info *a);
void			modify(t_info *a);

#endif
