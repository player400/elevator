
/*
 * MIT License
 *
 * Copyright (c) 2022 magistermaks
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * General WINX documentation:
 *
 *	WINX is a simple to use, minimal, cross-platform single-header window management library
 *	designed to easily create an OpenGL 3.0+ compatible window on both Windows and Linux (as well as on MacOS
 *	through X11).
 *
 *	To create a new window call the 'winxOpen' function. Note: WINX is a state machine and supports only
 *	one window per thread! If that call returns true window should have been successfully initialized and
 *	an OpenGL context created. Otherwise use 'winxGetError' to get the error message string.
 *
 *	if (!winxOpen(500, 300, "test")) {
 *		printf("Error occured! %s\n", winxGetError());
 *		exit(1);
 *	}
 *
 *	Some properties of the window created with 'winxOpen' can be modified with "hints" that have to be set prior to its
 *	creation with the 'winxHint' function. Note that WINX is allowed to ignore impossible to satisfy hints! See the list of available
 *	hints below the function list, under "hint keys".
 *
 *	Once a window is open you can begin the render loop and call 'winxSwapBuffers' and 'winxPollEvents'.
 *	To register callbacks for window events use the 'winxSet*EventHandle' family of functions and their respective
 *	'Winx*EventHandle' callback types. Clicking on a "close window" button can be detected with the 'winxSetCloseEventHandle'.
 *	The Vsync behaviour can also be changed after window creation using 'winxSetVsync'.
 *
 *	while(1) {
 *		// draw here
 *
 *		winxSwapBuffers(); // swap frame buffers
 *		winxPollEvents(); // poll events and call user event callbacks
 *	}
 *
 *	To close the window call 'winxClose'. Note that this doesn't reset any modified window hints!
 */

#ifndef WINX_H
#define WINX_H

#define WINX_VERSION "1.1.0"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct WinxCursor_s WinxCursor;

typedef void (*WinxCursorEventHandle)(int x, int y);
typedef void (*WinxButtonEventHandle)(int state, int button);
typedef void (*WinxKeybordEventHandle)(int state, int keycode);
typedef void (*WinxScrollEventHandle)(int scroll);
typedef void (*WinxCloseEventHandle)(void);
typedef void (*WinxResizeEventHandle)(int width, int height);
typedef void (*WinxFocusEventHandle)(bool focused);

/// set a window hint
/// has to be called prior to winxOpen()
void winxHint(int hint, int value);

/// return and clear last winx error
/// returns a NULL pointer if there was no error
char* winxGetError();

/// used to open new window with a given size and title
/// the title can later be changed with winxSetTitle()
bool winxOpen(int width, int height, const char* title);

/// process pending events
/// this will call the registered event handlers
void winxPollEvents();

/// swap display buffers
/// this needs to be called every frame
void winxSwapBuffers();

/// used to close current window
/// this resets all internal state apart from the window hints
void winxClose();

/// set title for current window
/// UTF-8 strings should be supported by this function
void winxSetTitle(const char* title);

/// set the icon of the current window to a RGBA image
/// pass WINX_ICON_DEFAULT as buffer to reset the icon (width and height will be ignored)
void winxSetIcon(int width, int height, unsigned char* buffer);

/// set desired vsync behaviour for current window
/// use one of WINX_VSYNC_DISABLED, WINX_VSYNC_ENABLED, or WINX_VSYNC_ADAPTIVE
void winxSetVsync(int vsync);

/// check if the current window is focused
/// you can also register a focus event handle using winxSetFocusEventHandle()
bool winxGetFocus();

/// focus the current window
/// this call is not guaranteed to be respected by the system
void winxSetFocus();

/// constrain the cursor pointer to the current window
/// this call is known to sometimes be ignored inside Virtual Machines
void winxSetCursorCapture(bool capture);

/// create a icon for the cursor from a RGBA image
/// the returned value should be freed with winxDeleteCursorIcon() when no longer needed
WinxCursor* winxCreateCursorIcon(int width, int height, unsigned char* buffer, int x, int y);

/// create an empty icon for the cursor
/// a helper method for creating an fully transparent cursor icon
WinxCursor* winxCreateNullCursorIcon();

/// free the allocated icon
/// deletes system resources associated with the icon if needed
void winxDeleteCursorIcon(WinxCursor* cursor);

/// set the cursor icon for the current window
/// pass WINX_ICON_DEFAULT to revert to the default system value
void winxSetCursorIcon(WinxCursor* cursor);

/// set the position of the cursor within the current window
/// this call is known to sometimes be ignored inside Virtual Machines
void winxSetCursorPos(int x, int y);

/// set the handle for cursor movement events for current window
/// pass NULL to unset the associated event handler (if any)
void winxSetCursorEventHandle(WinxCursorEventHandle handle);

/// set the handle for cursor click events for current window
/// pass NULL to unset the associated event handler (if any)
void winxSetButtonEventHandle(WinxButtonEventHandle handle);

/// set the handle for keybord events for current window
/// pass NULL to unset the associated event handler (if any)
void winxSetKeybordEventHandle(WinxKeybordEventHandle handle);

/// set the handle for cursor scroll for current window
/// pass NULL to unset the associated event handler (if any)
void winxSetScrollEventHandle(WinxScrollEventHandle handle);

/// set the handle for window close button for current window
/// pass NULL to unset the associated event handler (if any)
void winxSetCloseEventHandle(WinxCloseEventHandle handle);

/// set the handle for window resize event for current window
/// pass NULL to unset the associated event handler (if any)
void winxSetResizeEventHandle(WinxResizeEventHandle handle);

/// set the handle for window focus events for current window
/// pass NULL to unset the associated event handler (if any)
void winxSetFocusEventHandle(WinxFocusEventHandle handle);

/// reset all even handles for current window
/// you can also pass NULL to a specific event handler setter to reset it
void winxResetEventHandles();

/// return a time in seconds since the winxOpen() was called (if successful)
/// this function emulates the behaviour of glfwGetTime()
double winxGetTime();

#define WINX_ICON_DEFAULT NULL
#define WINX_PRESSED 1
#define WINX_RELEASED 0

/// hint keys
#define WINX_HINT_VSYNC         0x01
#define WINX_HINT_RED_BITS      0x02
#define WINX_HINT_GREEN_BITS    0x03
#define WINX_HINT_BLUE_BITS     0x04
#define WINX_HINT_ALPHA_BITS    0x05
#define WINX_HINT_DEPTH_BITS    0x06
#define WINX_HINT_STENCIL_BITS  0x07
#define WINX_HINT_OPENGL_MAJOR  0x08
#define WINX_HINT_OPENGL_MINOR  0x09
#define WINX_HINT_OPENGL_CORE   0x0A
#define WINX_HINT_OPENGL_DEBUG  0x0B
#define WINX_HINT_OPENGL_ROBUST 0x0C
#define WINX_HINT_MULTISAMPLES  0x0D

/// hint values
#define WINX_VSYNC_DISABLED 0
#define WINX_VSYNC_ENABLED 1
#define WINX_VSYNC_ADAPTIVE -1

#if defined(__unix__) || defined(__linux__)
#	define WINX_GLX

// based on https://code.woboq.org/kde/include/X11/keysymdef.h.html
#	define WXK_SPACE    ' '
#	define WXK_TAB 		'\t'
#	define WXK_ESC      0xff1b // XK_Escape
#	define WXK_ENTER    0xff0d // XK_Return
#	define WXK_BACK     0xff08 // XK_BackSpace
#	define WXK_UP       0xff52 // XK_Up
#	define WXK_DOWN     0xff54 // XK_Down
#	define WXK_LEFT     0xff51 // XK_Left
#	define WXK_RIGHT    0xff53 // XK_Right
#	define WXB_LEFT     1 // Button1 (X.h)
#	define WXB_CENTER   2 // Button2 (X.h)
#	define WXB_RIGHT    3 // Button3 (X.h)

#elif defined(_WIN32) || defined(_WIN64)
#	define WINX_WINAPI

// based on https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
#	define WXK_SPACE    ' '
#	define WXK_TAB      '\t'
#	define WXK_ESC      0x1B // VK_ESCAPE
#	define WXK_ENTER    0x0D // VK_RETURN
#	define WXK_BACK     0x08 // VK_BACK
#	define WXK_UP       0x26 // VK_UP
#	define WXK_DOWN     0x28 // VK_DOWN
#	define WXK_LEFT     0x25 // VK_LEFT
#	define WXK_RIGHT    0x27 // VK_RIGHT
#	define WXB_LEFT     1
#	define WXB_CENTER   2
#	define WXB_RIGHT    3

#endif

#ifdef __cplusplus
}
#endif

#endif // WINX_H

