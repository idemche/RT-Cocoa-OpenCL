/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/19 19:16:17 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSON_H
# define JSON_H

# include "cJSON.h"
# include "rt.h"

typedef struct	s_json_env
{
	cJSON		*e;
	cJSON		*height;
	cJSON		*width;
	cJSON		*ambient;
	cJSON		*gamma;
	cJSON		*max_peers;
	cJSON		*p_l_d;
	cJSON		*p_l_e;
	cJSON		*ind_light;
	cJSON		*par_light;
	cJSON		*spot_light;
	cJSON		*dof;
	cJSON		*spppc;
	cJSON		*m;
	cJSON		*tone_mapper;
}				t_json_env;

typedef struct	s_json_material
{
	cJSON		*material;
	cJSON		*emission;
	cJSON		*g;
	cJSON		*kd;
	cJSON		*absorption;
	cJSON		*abs_r;
	cJSON		*abs_g;
	cJSON		*abs_b;
	cJSON		*refr_index;
	cJSON		*texture;
	cJSON		*scale;
	cJSON		*shift;
	cJSON		*u;
}				t_json_material;

typedef struct	s_json_sequence
{
	cJSON		*s;
	cJSON		*is_on;
	cJSON		*fps;
	cJSON		*time;
	cJSON		*axis;
	cJSON		*t;
}				t_json_sequence;

typedef struct	s_json_cam
{
	char		*json;
	cJSON		*root;
	cJSON		*cam;
	cJSON		*pos;
	cJSON		*dir;
	cJSON		*fov;
	cJSON		*t;
	cJSON		*focal;
	cJSON		*aperture;
}				t_json_cam;

typedef struct	s_json_light
{
	cJSON		*light;
	cJSON		*pos;
	cJSON		*dir;
	cJSON		*emission;
	cJSON		*alpha;
	cJSON		*radius;
}				t_json_lt;

typedef struct	s_json_object
{
	cJSON		*obj;
	cJSON		*p1;
	cJSON		*p2;
	cJSON		*p3;
	cJSON		*dir;
	cJSON		*angle;
	cJSON		*color;
	cJSON		*bot;
	cJSON		*top;
	cJSON		*r;
	cJSON		*r_big;
	cJSON		*k;
	cJSON		*vec1;
	cJSON		*vec2;
	cJSON		*n;
	cJSON		*period;
	cJSON		*length;
	cJSON		*width;
	cJSON		*freq;
}				t_json_object;

typedef struct	s_json_scene
{
	char		*json;
	cJSON		*root;
	cJSON		*objects;
	cJSON		*n_object;
	cJSON		*object;
	cJSON		*type;
	cJSON		*spotlights;
	cJSON		*light;
	cJSON		*texture;
}				t_json_scene;

#endif
