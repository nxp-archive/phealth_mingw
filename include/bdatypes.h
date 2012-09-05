/**
 * @file bdatypes.h
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
#ifndef _BDATYPES_H
#define _BDATYPES_H
#pragma GCC system_header

#ifdef __cplusplus
extern "C" {
#endif

/*--- DirectShow Reference - DirectShow Enumerated Types */
typedef enum {
	MEDIA_TRANSPORT_PACKET,
	MEDIA_ELEMENTARY_STREAM,
	MEDIA_MPEG2_PSI,
	MEDIA_TRANSPORT_PAYLOAD
} MEDIA_SAMPLE_CONTENT;
/*--- DirectShow Reference - DirectShow Structures */
typedef struct {
	DWORD dwOffset;
	DWORD dwPacketLength;
	DWORD dwStride;
} MPEG2_TRANSPORT_STRIDE;
typedef struct {
	ULONG ulPID;
	MEDIA_SAMPLE_CONTENT MediaSampleContent ;
} PID_MAP;

#ifdef __cplusplus
}
#endif
#endif