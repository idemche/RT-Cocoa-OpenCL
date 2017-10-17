/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshakula <hshakula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 17:44:38 by hshakula          #+#    #+#             */
/*   Updated: 2017/10/17 19:54:28 by hshakula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			save_image(t_info *a, char *name)
{
	unsigned int	*image;
	int				error;
	int				i;

	a->save_image = 0;
	image = (unsigned int*)malloc(a->scene->image_width *
							a->scene->image_height * sizeof(unsigned int));
	i = -1;
	while (++i < a->scene->image_width * a->scene->image_height)
	{
		image[i] = (a->w->data[4 * i] << 16) + (a->w->data[4 * i + 1] << 8)
									+ (a->w->data[4 * i + 2]) + 4278190080;
	}
	error = lodepng_encode32_file(name, (t_uch*)image, a->scene->image_width,
													a->scene->image_height);
	if (error)
		ft_putstr("Error while saving image\n");
	free(image);
}

void			get_image(t_info *a)
{
	int				i;

	i = -1;
	while (++i < a->server.max_peers)
		memcpy(a->w->data + i * a->server.line_size * 4, a->threads[i].data,
													a->server.line_size * 4);
	if (a->save_image)
		save_image(a, "screenshot.png");
}
