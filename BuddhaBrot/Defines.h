/*
 *  Defines.h
 *  Mandlebrot
 *
 *  Created by Matt Lacey on 29/08/10.
 *  Copyright 2010 Tin Man Games. All rights reserved.
 *
 */

#ifndef _DEFINES_H
#define _DEFINES_H

//#define FULLSCREEN	(1)

#ifdef FULLSCREEN
	#define SCREEN_X	(1440)
	#define SCREEN_Y	(900)
#else
	#define SCREEN_X	(800)
	#define SCREEN_Y	(600)
#endif

#define RENDER_X		(800) //(4800)
#define RENDER_Y		(600) //(3200)

// more iterations take longer obviously :) 
#define ITERATIONS		(2048) //(131072)
#define RESOLUTION		(10)

#define ARGB(a, r, g, b)	((b) << 24 | (g) << 16 | (r) << 8 | a)
#define RGBA(r, g, b, a)	((a) << 24 | (b) << 16 | (g) << 8 | r)

typedef struct sComplex
{
	double	dR;
	double	dI;
} TComplex;

#endif
