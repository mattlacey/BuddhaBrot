/*
 *  Mandlebrot.c
 *  Mandlebrot
 *
 *  Created by Matt Lacey on 29/08/10.
 *  Copyright 2010 Tin Man Games. All rights reserved.
 *
 */

#include "SDL.h"

#include "Mandlebrot.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WITHIN(X, MIN, MAX) ((X) < (MIN) ? 0 : ((X) > (MAX) ? 0 : 1))

float	* pData = NULL;

// This controls the 'zoom' and position of the image. Default is 3 / X_RES which gives a good fit for the whole image.
double	dScale = (3.0 / RENDER_X);			
double	dCentreX = 0;
double	dCentreY = 0;

// This gives a nice detail snapshot near the 'head'
/*
double	dScale = (0.5 / RENDER_X);
double	dCentreX = -1.2;
double	dCentreY = 0.2;
*/

void Init()
{
	int i;
	pData = (float *)malloc(sizeof(float) * RENDER_X * RENDER_Y * 3);
	
	for(i = 0; i < RENDER_X * RENDER_Y * 3; i++)
	{
		pData[i] = 1.0f;
	}
}

int Calculate(void * channel)
{
	int			j, xx, yy;
	double		dInc = dScale;
	double		dSize = 0;
	TComplex	c, z;
	int			iCount = 0, iEscape = 2;

	int i = *((int *)channel);

	while (i--)
	{
		rand();
	}

	i = *((int *)channel);
	
	for(int x = 0; x < RENDER_X; x++)
	{
		for(int y = 0; y < RENDER_Y; y++)
		{
			if(rand() < (RAND_MAX * (0.1 + (.4 * i))))
			{
				continue;
			}
				
			iCount = 0;
				
			for (j = 0; j < RESOLUTION; j++)
			{
				c.dR = (x - RENDER_X / 2) * dInc + (dInc * j / RESOLUTION) + dCentreX;
				c.dI = (y - RENDER_Y / 2) * dInc + (dInc * j / RESOLUTION) + dCentreY;

				z.dR = 0;
				z.dI = 0;

				dSize = (c.dR * c.dR) + (c.dI * c.dI);

				while (dSize < iEscape && iCount < ITERATIONS * (i + 1))
				{
					TComplex temp;

					temp.dR = (z.dR * z.dR - z.dI * z.dI);
					temp.dI = (2 * z.dR * z.dI);

					z.dR = temp.dR + c.dR;
					z.dI = temp.dI + c.dI;

					iCount++;
					dSize = (z.dR * z.dR) + (z.dI * z.dI);
				}

				// for Mandelbrot you basically do if(iCount < ITERATIONS) pData[x][y] = iCount here intead of the crap below

				if (iCount < ITERATIONS  * (i + 1))
				{
					c.dR = (x - RENDER_X / 2) * dInc + (dInc * j / RESOLUTION) + dCentreX;
					c.dI = (y - RENDER_Y / 2) * dInc + (dInc * j / RESOLUTION) + dCentreY;

					z.dR = 0;
					z.dI = 0;

					dSize = (c.dR * c.dR) + (c.dI * c.dI);

					while (dSize < iEscape)
					{
						TComplex temp;

						temp.dR = (z.dR * z.dR - z.dI * z.dI);
						temp.dI = (2 * z.dR * z.dI);

						z.dR = temp.dR + c.dR;
						z.dI = temp.dI + c.dI;

						dSize = (z.dR * z.dR) + (z.dI * z.dI);

						xx = (int)((RENDER_X / 2) + (z.dR - dCentreX) / dInc);
						yy = (int)((RENDER_Y / 2) + (z.dI - dCentreY) / dInc);

						if (WITHIN(xx, 0, RENDER_X - 1) && WITHIN(yy, 0, RENDER_Y - 1))
						{
							float * pValue = pData + (RENDER_X * RENDER_Y * i) + yy * RENDER_X + xx;

							// decrease this for higher resolution renderings or it gets over exposed, also as iterations go up 
							// pixels get more coverage so that's a factor.
							*pValue += 16.0f;
						}
					}
				}
			}
		}

		printf("Done: %i%\n", i);
	}

	return 0;
}

void DumpImage()
{
	FILE * pFile;
	pFile = fopen("dump.data", "wb");
	unsigned char r, g, b;
	
	if(pFile)
	{
		float max[3] = {1, 1, 1};
		
		for(int i = 0; i < 3; i++)
		{
			for(int x = 0; x < RENDER_X; x++)
			{
				for(int y = 0; y < RENDER_Y; y++)
				{
					float fVal = pData[i * RENDER_X * RENDER_Y + y * RENDER_X + x];
					
					if(fVal > max[i])
					{
						max[i] = fVal;
					}
				}
			}
		}
		
		for(int y = 0; y < RENDER_Y; y++)
		{
			for(int x = 0; x < RENDER_X; x++)
			{
				r = (pData[y * RENDER_X + x] * 255) / max[0];
				g = (pData[RENDER_X * RENDER_Y + y * RENDER_X + x] * 255) / max[1];
				b = (pData[RENDER_X * RENDER_Y * 2 + y * RENDER_X + x] * 255) / max[2];
				
				// int col = RGBA(r, g, b, 255);
				//fwrite(&col, sizeof(int), 1, pFile);
				fwrite(&r, 1, 1, pFile);
				fwrite(&g, 1, 1, pFile);
				fwrite(&b, 1, 1, pFile);
			}
		}
		
		fclose(pFile);
	}
}

void Render(SDL_Surface * pScreen)
{
	Uint8 r, g, b, a;
	int i, x, y;

	a = 255;
	r = 0;
	g = 0;
	b = 0;
	
	float max[3] = {1, 1, 1};
	
	for(i = 0; i < 3; i++)
	{
		for(x = 0; x < RENDER_X; x++)
		{
			for(y = 0; y < RENDER_Y; y++)
			{
				float fVal = pData[i * RENDER_X * RENDER_Y + y * RENDER_X + x];
				
				if(fVal > max[i])
				{
					max[i] = fVal;
				}
			}
		}
	}
	
	for(x = 0; x < SCREEN_X; x++)
	{
		for(y = 0; y < SCREEN_Y; y++)
		{
			r = (pData[y * RENDER_X + x] * 256) / max[0];
			g = (pData[RENDER_X * RENDER_Y + y * RENDER_X + x] * 256) / max[1];
			b = (pData[RENDER_X * RENDER_Y * 2 + y * RENDER_X + x] * 256) / max[2];
			a = 255;			
			
			((unsigned int *)pScreen->pixels)[y * SCREEN_X + x] = ARGB(a, r, g, b);
		}
	}
}
