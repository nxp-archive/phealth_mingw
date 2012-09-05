/**
 * @file zmouse.h
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
       zmouse.h - Header for IntelliMouse.

       This file is part of a free library for the Win32 API.

       This library is distributed in the hope that it will be useful,
       but WITHOUT ANY WARRANTY; without even the implied warranty of
       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

       FIXME: This file is obviously horribly incomplete!

*/

#ifndef _ZMOUSE_H
#define _ZMOUSE_H
#pragma GCC system_header

#ifndef WM_MOUSEWHEEL
# define WM_MOUSEWHEEL (WM_MOUSELAST + 1)
#endif

#ifndef WHEEL_DELTA
# define WHEEL_DELTA 120
#endif

#ifndef WHEEL_PAGESCROLL
# define WHEEL_PAGESCROLL UINT_MAX
#endif

#ifndef SPI_SETWHEELSCROLLLINES
# define SPI_SETWHEELSCROLLLINES 105
#endif

#endif /* _ZMOUSE_H */