/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 16:32:14 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 20:13:09 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "lodepng.h"
# include "keys.h"
# include "hdrReader.h"
# include "libft.h"
# include "util.h"
# include "render.h"
# include "my_math.h"
# include "cl.h"
# include "json.h"
# include "client.h"
# include "server.h"
# include "parsing.h"
# include "my_sdl.h"
# include "perlin.h"

struct			s_info
{
	t_camera		*camera;
	t_object		*objects;
	t_object		*negative_objects;
	t_spotlight		*spotlights;
	t_window		*w;
	t_scene			*scene;
	t_texture		*textures;
	t_perlin		perlin;
	t_state			*state;
	t_thread		*threads;
	t_client		client;
	t_server		server;
	t_sequence		sequence;
	t_keys			keys;
	cl_float3		*albedo_textures;
	cl_float3		*normal_textures;
	cl_float3		*environment_map;
	cl_float		*depth_map;
	cl_int			*current_sample;
	double			len;
	double			scale_angle;
	double			scale_speed;
	int				*unique_tex;
	int				amount_of_unique_tex;
	int				spp_per_call;
	int				image_width;
	int				image_height;
	size_t			json_len;
	char			*json_file;
	char			*file_path;
	t_uch			*line_data;
	t_uint			*seeds;
	int				keycode;
	int				tcp_port;
	char			*port;
	char			**texture_names;
	char			**available_texture;
	char			*scenes[26];
	char			*kernel_path;
	char			gui_can_change;
	char			update_camera;
	char			update_scene;
	char			update_map;
	char			save_image;
	char			quit;
	char			num_scene;
};

void			init(t_info *a, char *json_file);
void			init_scene(t_info *a);
void			quit(t_info *a);
void			reset_keys(t_info *a);

#endif
