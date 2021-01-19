/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_map.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikeda <sikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 23:40:07 by sikeda            #+#    #+#             */
/*   Updated: 2021/01/19 23:40:08 by sikeda           ###   ########.fr       */
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
# define KeyPress				2
# define KeyRelease				3
# define ButtonPress			4
# define ButtonRelease			5
# define MotionNotify			6
# define EnterNotify			7
# define LeaveNotify			8
# define FocusIn				9
# define FocusOut				10
# define KeymapNotify			11
# define Expose					12
# define GraphicsExpose			13
# define NoExpose				14
# define VisibilityNotify		15
# define CreateNotify			16
# define DestroyNotify			17
# define UnmapNotify			18
# define MapNotify				19
# define MapRequest				20
# define ReparentNotify			21
# define ConfigureNotify		22
# define ConfigureRequest		23
# define GravityNotify			24
# define ResizeRequest			25
# define CirculateNotify		26
# define CirculateRequest		27
# define PropertyNotify			28
# define SelectionClear			29
# define SelectionRequest		30
# define SelectionNotify		31
# define ColormapNotify			32
# define ClientMessage			33
# define MappingNotify			34
# define GenericEvent			35
# define LASTEvent				36

/*
** X11 MASKS
*/
# define MASK_NOEVENT			0L
# define MASK_KEYPRESS			1L<<0
# define MASK_KEYRELEASE		1L<<1
# define MASK_BUTTONPRESS		1L<<2
# define MASK_BUTTONRELEASE 	1L<<3
# define MASK_ENTERWINDOW		1L<<4
# define MASK_LEAVEWINDOW		1L<<5
# define MASK_POINTERMOTION		1L<<6
# define MASK_POINTERMOTIONHINT	1L<<7
# define MASK_BUTTON1MOTION		1L<<8
# define MASK_BUTTON2MOTION		1L<<9
# define MASK_BUTTON3MOTION		1L<<10
# define MASK_BUTTON4MOTION		1L<<11
# define MASK_BUTTON5MOTION		1L<<12
# define MASK_BUTTONMOTION		1L<<13
# define MASK_KEYMAPSTATE		1L<<14
# define MASK_EXPOSURE			1L<<15
# define MASK_VISIBILITYCHANGE	1L<<16
# define MASK_STRUCTURENOTIFY	1L<<17
# define MASK_RESIZEREDIRECT	1L<<18
# define MASK_SUBSTRUCTNOTIFY	1L<<19
# define MASK_SUBSTRUCTREDIRECT	1L<<20
# define MASK_FOCUSCHANGE		1L<<21
# define MASK_PROPERTYCHANGE	1L<<22
# define MASK_COLORMAPCHANGE	1L<<23
# define MASK_OWNERGRABBUTTON	1L<<24
#endif
