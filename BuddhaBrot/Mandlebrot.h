/*
 *  Mandlebrot.h
 *  Mandlebrot
 *
 *  Created by Matt Lacey on 29/08/10.
 *  Copyright 2010 Tin Man Games. All rights reserved.
 *
 */

#ifndef _MANDLEBROT_H
#define _MANDLEBROT_H

#include "Defines.h"

void Init();
void Calculate();
void DumpImage();
void Render(SDL_Surface * pScreen);


#endif