/* 
 * yuv2rgb_mlib.c, Software YUV to RGB coverter using mediaLib
 *
 *  Copyright (C) 2000, H�kan Hjort <d95hjort@dtek.chalmers.se>
 *  All Rights Reserved.
 *
 *  This file is part of mpeg2dec, a free MPEG-2 video decoder
 *
 *  mpeg2dec is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  mpeg2dec is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#include <mlib_types.h>
#include <mlib_status.h>
#include <mlib_sys.h>
#include <mlib_video.h>
#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>

#include "../libvo/img_format.h" //FIXME try to reduce dependency of such stuff
#include "swscale.h"

static void mlib_YUV2ARGB420_32(SwsContext *c, uint8_t* srcParam[], int srcStrideParam[], int srcSliceY, 
             int srcSliceH, uint8_t* dst[], int dstStride[]){
    uint8_t *src[3];
    int srcStride[3];

    sws_orderYUV(c->srcFormat, src, srcStride, srcParam, srcStrideParam);
    if(c->srcFormat == IMGFMT_422P){
	srcStride[1] *= 2;
	srcStride[2] *= 2;
    }
    
    assert(srcStride[1] == srcStride[2]);
 
    mlib_VideoColorYUV2ARGB420(dst[0], src[0], src[1], src[2], c->dstW,
			     c->dstH, dstStride[0], srcStride[0], srcStride[1]);
}

static void mlib_YUV2ABGR420_32(SwsContext *c, uint8_t* srcParam[], int srcStrideParam[], int srcSliceY, 
             int srcSliceH, uint8_t* dst[], int dstStride[]){
    uint8_t *src[3];
    int srcStride[3];

    sws_orderYUV(c->srcFormat, src, srcStride, srcParam, srcStrideParam);
    if(c->srcFormat == IMGFMT_422P){
	srcStride[1] *= 2;
	srcStride[2] *= 2;
    }
    
    assert(srcStride[1] == srcStride[2]);
 
    mlib_VideoColorYUV2ABGR420(dst[0], src[0], src[1], src[2], c->dstW,
			     c->dstH, dstStride[0], srcStride[0], srcStride[1]);
}

static void mlib_YUV2RGB420_24(SwsContext *c, uint8_t* srcParam[], int srcStrideParam[], int srcSliceY, 
             int srcSliceH, uint8_t* dst[], int dstStride[]){
    uint8_t *src[3];
    int srcStride[3];

    sws_orderYUV(c->srcFormat, src, srcStride, srcParam, srcStrideParam);
    if(c->srcFormat == IMGFMT_422P){
	srcStride[1] *= 2;
	srcStride[2] *= 2;
    }
    
    assert(srcStride[1] == srcStride[2]);
 
    mlib_VideoColorYUV2RGB420(dst[0], src[0], src[1], src[2], c->dstW,
			     c->dstH, dstStride[0], srcStride[0], srcStride[1]);
}


SwsFunc yuv2rgb_init_mlib(SwsContext *c) 
{
	switch(c->dstFormat){
	case IMGFMT_RGB24: return mlib_YUV2RGB420_24;
	case IMGFMT_RGB32: return mlib_YUV2ARGB420_32;
	case IMGFMT_BGR32: return mlib_YUV2ARGB420_32;
	default: return NULL;
	}
}

