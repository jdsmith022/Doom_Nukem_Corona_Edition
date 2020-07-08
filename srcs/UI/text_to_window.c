/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text_to_window.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/08 13:13:24 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void fontInit(t_doom *doom)
{
        TTF_Init();
        font = TTF_OpenFont("text/amatic/AmaticSC-Regular.tff", 12);
        fColor.r = 255;
        fColor.g = 255;
        fColor.b = 255;
}

void        draw_text(t_doom *doom)
{
    fontInit(doom);
}
