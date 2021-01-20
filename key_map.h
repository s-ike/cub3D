/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:07 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/20 14:35:49 by sikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_MAP_H
# define KEY_MAP_H

/*
** KEYS
*/
# ifdef LINUX
#  define KEY_UP				65362
#  define KEY_LEFT				65361
#  define KEY_RIGHT				65363
#  define KEY_DOWN				65364
#  define KEY_W					119
#  define KEY_A					97
#  define KEY_S					115
#  define KEY_D					100
#  define KEY_ESC				65307
# else
#  define KEY_UP				126
#  define KEY_LEFT				123
#  define KEY_RIGHT				124
#  define KEY_DOWN				125
#  define KEY_W					13
#  define KEY_A					0
#  define KEY_S					1
#  define KEY_D					2
#  define KEY_ESC				53
# endif

/*
** X11 EVENTS
*/
# define KEY_PRESS				2
# define KEY_RELEASE			3
# define BTN_PRESS				4
# define BTN_RELEASE			5
# define MOTION__NOTIFY			6
# define ENTER__NOTIFY			7
# define LEAVE_NOTIFY			8
# define FOCUS_IN				9
# define FOCUS_OUT				10
# define KEYMAP_NOTIFY			11
# define EXPOSE					12
# define GRAPHICS_EXPOSE		13
# define NO_EXPOSE				14
# define VISIBILITY_NOTIFY		15
# define CREATE_NOTIFY			16
# define DESTROY_NOTIFY			17
# define UNMAP_NOTIFY			18
# define MAP_NOTIFY				19
# define MAP_REQUEST			20
# define REPARENT_NOTIFY		21
# define CONFIGURE_NOTIFY		22
# define CONFIGURE_REQUEST		23
# define GRAVITY_NOTIFY			24
# define RESIZE_REQUEST			25
# define CIRCULATE_NOTIFY		26
# define CIRCULATE_REQUEST		27
# define PROPERTY_NOTIFY		28
# define SELECTION_CLEAR		29
# define SELECTION_REQUEST		30
# define SELECTION_NOTIFY		31
# define COLORMAP_NOTIFY		32
# define CLIENT_MESSAGE			33
# define MAPPING_NOTIFY			34
# define GENERIC_EVENT			35
# define LAST_EVENT				36

/*
** X11 MASKS
*/
# define MASK_KEYPRESS			1L << 0
# define MASK_KEYRELEASE		1L << 1
# define MASK_STRUCTURENOTIFY	1L << 17
# define MASK_FOCUSCHANGE		1L << 21`

#endif
