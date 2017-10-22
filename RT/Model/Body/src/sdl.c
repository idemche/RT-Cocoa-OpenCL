/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 20:08:43 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			destroy_sdl(t_info *a)
{
	SDL_DestroyRenderer(a->w->ren);
	SDL_DestroyWindow(a->w->win);
	SDL_Quit();
	ft_putstr("Exit succesfully\n");
}

void			init_sdl(t_info *a)
{
	SDL_Init(SDL_INIT_VIDEO);
	a->w = (t_window*)malloc(sizeof(t_window));
	a->w->win = SDL_CreateWindow("RT", 100, 100, a->scene->image_width,
			a->scene->image_height, SDL_WINDOW_SHOWN);
	a->w->ren = SDL_CreateRenderer(a->w->win, -1, SDL_RENDERER_ACCELERATED);
	a->quit = 0;
	a->w->data = (t_uch*)malloc(4 * a->server.image_size);
}

static void		handle_updates(t_info *a)
{
	if (a->update_map)
	{
		reinit_server(a);
		free(a->json_file);
	}
	else if (a->update_camera)
		update_camera_call(a);
	else if (a->update_scene)
		update_scene_call(a);
}

static void		present_image(t_info *a)
{
	a->w->surf = SDL_CreateRGBSurfaceFrom((void*)a->w->data,
		a->scene->image_width, a->scene->image_height, 32,
		a->scene->image_width * 4, 0, 0, 0, 0);
	a->w->tex = SDL_CreateTextureFromSurface(a->w->ren, a->w->surf);
	SDL_RenderClear(a->w->ren);
	SDL_RenderCopy(a->w->ren, a->w->tex, NULL, NULL);
	SDL_RenderPresent(a->w->ren);
	SDL_FreeSurface(a->w->surf);
	SDL_DestroyTexture(a->w->tex);
}

void			sdl_loop(t_info *a)
{
	SDL_Event	event;

	ft_putstr("SDL_LOOP\n");
	while (!a->quit)
	{
		while (SDL_PollEvent(&event))
			handle_events(a, event, 0);
		if (a->sequence.is_on == 1)
			sequence_call(a);
		else
		{
			if (a->keys.update)
				update_from_gui(a, a->keys);
			handle_updates(a);
			render_call(a);
			get_image(a);
		}
		present_image(a);
	}
}
