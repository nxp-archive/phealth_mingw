/**
 * @file gdiplusimagecodec.h
 * @copy 2012 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/*
 * gdiplusimagecodec.h
 *
 * GDI+ image decoders and encoders
 *
 * This file is part of the w32api package.
 *
 * Contributors:
 *   Created by Markus Koenig <markus@stber-koenig.de>
 *
 * THIS SOFTWARE IS NOT COPYRIGHTED
 *
 * This source code is offered for use in the public domain. You may
 * use, modify or distribute it freely.
 *
 * This code is distributed in the hope that it will be useful but
 * WITHOUT ANY WARRANTY. ALL WARRANTIES, EXPRESS OR IMPLIED ARE HEREBY
 * DISCLAIMED. This includes but is not limited to warranties of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef __GDIPLUS_IMAGECODEC_H
#define __GDIPLUS_IMAGECODEC_H
#pragma GCC system_header

static __inline__ GpStatus GetImageDecoders(UINT numDecoders, UINT size,
		ImageCodecInfo *decoders)
{
	#ifdef __cplusplus
	return DllExports::GdipGetImageDecoders(numDecoders, size, decoders);
	#else
	return GdipGetImageDecoders(numDecoders, size, decoders);
	#endif
}

static __inline__ GpStatus GetImageDecodersSize(UINT *numDecoders, UINT *size)
{
	#ifdef __cplusplus
	return DllExports::GdipGetImageDecodersSize(numDecoders, size);
	#else
	return GdipGetImageDecodersSize(numDecoders, size);
	#endif
}

static __inline__ GpStatus GetImageEncoders(UINT numEncoders, UINT size,
		ImageCodecInfo *encoders)
{
	#ifdef __cplusplus
	return DllExports::GdipGetImageEncoders(numEncoders, size, encoders);
	#else
	return GdipGetImageEncoders(numEncoders, size, encoders);
	#endif
}

static __inline__ GpStatus GetImageEncodersSize(UINT *numEncoders, UINT *size)
{
	#ifdef __cplusplus
	return DllExports::GdipGetImageEncodersSize(numEncoders, size);
	#else
	return GdipGetImageEncodersSize(numEncoders, size);
	#endif
}

#endif /* __GDIPLUS_IMAGECODEC_H */