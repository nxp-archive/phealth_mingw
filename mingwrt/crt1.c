/*
 * crt1.c
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is a part of the mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within the package.
 *
 * Source code for the startup proceedures used by all programs. This code
 * is compiled to make crt1.o, which should be located in the library path.
 *
 */

/* Hide the declaration of _fmode with dllimport attribute in stdlib.h to
 * avoid problems with older GCC.
 */
#define __IN_MINGW_RUNTIME
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <process.h>
#include <float.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <signal.h>

#include "cpu_features.h"

extern void __main ();
extern void _pei386_runtime_relocator (void);

/* Main program entry point, and argument initialization hook.
 */
extern int main (int, char **, char **);
extern void _setargv (void);

int    _argc = 0;
char **_argv = NULL;

/* NOTE: Thanks to Pedro A. Aranda Gutiirrez <paag@tid.es> for pointing
 * this out: the GetMainArgs() function, (provided by CRTDLL.DDL, as an
 * argument initialization hook), takes a fourth argument (an int), which
 * controls the globbing of the command line; if it is non-zero the command
 * line will be globbed (e.g. *.* will be expanded to a list, separated by
 * spaces, of all files in the startup directory).
 *
 * We determine how globbing should be performed, by inspection of the two
 * least significant bits of the global int variable _CRT_glob, (defined in
 * the mingw32 library, with a default value of 2).  If this pair of bits
 * represent a value of 2 or more, the new MinGW globbing algorithm, (as
 * implemented by function _setargv() in setargv.c), will be applied; for
 * values of one or zero, _setargv() will delegate the globbing function to
 * the _mingw32_init_mainargs() callback function implemented below, and so
 * invoking the Microsoft GetMainArgs() algorithm, with its fourth argument
 * set to one or zero, to match the least significant bit of _CRT_glob.
 *
 * The mingw32 library default value of 2 for _CRT_glob enables command line
 * globbing using the MinGW algorithm.  If you prefer to adopt the Microsoft
 * algorithm, you should define _CRT_glob as a global variable, by including
 * a line in one of your own source code files, like this:
 *
 *    int _CRT_glob = 1;
 *
 * Alternatively, if you prefer to disable globbing, and do all command line
 * processing yourself, (and so evade possible bogons in the Microsoft or in
 * the MinGW globbing code), include a similar line in one of your own source
 * code files, defining _CRT_glob with a value of zero, like this:
 *
 *    int _CRT_glob = 0;
 */
extern int _CRT_glob;

#ifdef __MSVCRT__
/* In MSVCRT.DLL, Microsoft's initialization hook is called __getmainargs(),
 * and it expects a further structure argument, (which we don't use, but pass
 * it as a dummy, with a declared size of zero in its first and only field).
 */
typedef struct { int newmode; } _startupinfo;
extern void __getmainargs( int *, char ***, char ***, int, _startupinfo * );

#else
/* In CRTDLL.DLL, the initialization hook is called __GetMainArgs().
 */
extern void __GetMainArgs( int *, char ***, char ***, int );
#endif

void _mingw32_init_mainargs()
{
  /* This is the old start-up mechanism, in which we use a start-up
   * hook provided by Microsoft's runtime library to initialize the
   * argument and environment vectors.
   *
   * Note that the preferred method for accessing the environment
   * vector is via a direct pointer retrieved from the runtime DLL,
   * using a system call declared in stdlib.h; thus, we don't need
   * to preserve the pointer returned by the start-up hook, so we
   * may simply capture it locally, and subsequently discard it.
   */
  char **dummy_envp;

# define _CRT_GLOB_OPT  _CRT_glob & __CRT_GLOB_USE_MSVCRT__
# ifdef __MSVCRT__
    /* The MSVCRT.DLL start-up hook requires this invocation
     * protocol...
     */
    _startupinfo start_info = { 0 };
    __getmainargs( &_argc, &_argv, &dummy_envp, _CRT_GLOB_OPT, &start_info );

# else
    /* ...while a somewhat simpler protocol is applicable, in
     * the case of the CRTDLL.DLL version.
     */
    __GetMainArgs( &_argc, &_argv, &dummy_envp, _CRT_GLOB_OPT );
# endif
}

/* TLS initialization hook.
 */
extern const PIMAGE_TLS_CALLBACK __dyn_tls_init_callback;

/* Must have the correct app type for MSVCRT.
 */
#ifdef __MSVCRT__
# define __UNKNOWN_APP    0
# define __CONSOLE_APP    1
# define __GUI_APP        2

__MINGW_IMPORT void __set_app_type(int);

#endif /* __MSVCRT__ */

/* Global _fmode for this .exe, (not the one in msvcrt.dll).
 *
 * The default is set in txtmode.o in libmingw32.a
 * Override the dllimport'd declarations in stdlib.h
 */
#undef _fmode
extern int _fmode;
#ifdef __MSVCRT__
extern int* __p__fmode(void); /* To access the dll _fmode */
#endif

/*
 * Setup the default file handles to have the _CRT_fmode mode, as well as
 * any new files created by the user.
 */
extern int _CRT_fmode;

static void
_mingw32_init_fmode (void)
{
  /* Don't set the std file mode if the user hasn't set any value for it.
   */
  if (_CRT_fmode)
  {
    _fmode = _CRT_fmode;

    /* This overrides the default file mode settings for stdin,
     * stdout and stderr. At first I thought you would have to
     * test with isatty, but it seems that the DOS console at
     * least is smart enough to handle _O_BINARY stdout and
     * still display correctly.
     */
    if (stdin) _setmode (_fileno (stdin), _CRT_fmode);
    if (stdout) _setmode (_fileno (stdout), _CRT_fmode);
    if (stderr) _setmode (_fileno (stderr), _CRT_fmode);
  }

  /* Now sync the dll _fmode to the one for this .exe.
   */
# ifdef __MSVCRT__
    *__p__fmode() = _fmode;
# else
    *_imp___fmode_dll = _fmode;
# endif
}

/* This function will be called when a trap occurs.  Thanks to
 * Jacob Navia for this contribution.
 */
static CALLBACK long
_gnu_exception_handler (EXCEPTION_POINTERS * exception_data)
{
  void (*old_handler) (int);
  long action = EXCEPTION_CONTINUE_SEARCH;
  int reset_fpu = 0;

  switch (exception_data->ExceptionRecord->ExceptionCode)
    {
    case EXCEPTION_ACCESS_VIOLATION:
      /* test if the user has set SIGSEGV */
      old_handler = signal (SIGSEGV, SIG_DFL);
      if (old_handler == SIG_IGN)
	{
	  /* this is undefined if the signal was raised by anything other
	     than raise ().  */
	  signal (SIGSEGV, SIG_IGN);
	  action = EXCEPTION_CONTINUE_EXECUTION;
	}
      else if (old_handler != SIG_DFL)
	{
	  /* This means 'old' is a user defined function. Call it */
	  (*old_handler) (SIGSEGV);
	  action = EXCEPTION_CONTINUE_EXECUTION;
	}
      break;

    case EXCEPTION_ILLEGAL_INSTRUCTION:
    case EXCEPTION_PRIV_INSTRUCTION:
      /* test if the user has set SIGILL */
      old_handler = signal (SIGILL, SIG_DFL);
      if (old_handler == SIG_IGN)
	{
	  /* this is undefined if the signal was raised by anything other
	     than raise ().  */
	  signal (SIGILL, SIG_IGN);
	  action = EXCEPTION_CONTINUE_EXECUTION;
	}
      else if (old_handler != SIG_DFL)
	{
	  /* This means 'old' is a user defined function. Call it */
	  (*old_handler) (SIGILL);
	  action = EXCEPTION_CONTINUE_EXECUTION;
	}
      break;

    case EXCEPTION_FLT_INVALID_OPERATION:
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    case EXCEPTION_FLT_DENORMAL_OPERAND:
    case EXCEPTION_FLT_OVERFLOW:
    case EXCEPTION_FLT_UNDERFLOW:
    case EXCEPTION_FLT_INEXACT_RESULT:
      reset_fpu = 1;
      /* fall through. */

    case EXCEPTION_INT_DIVIDE_BY_ZERO:
      /* test if the user has set SIGFPE */
      old_handler = signal (SIGFPE, SIG_DFL);
      if (old_handler == SIG_IGN)
	{
	  signal (SIGFPE, SIG_IGN);
	  if (reset_fpu)
	    _fpreset ();
	  action = EXCEPTION_CONTINUE_EXECUTION;
	}
      else if (old_handler != SIG_DFL)
	{
	  /* This means 'old' is a user defined function. Call it */
	  (*old_handler) (SIGFPE);
	  action = EXCEPTION_CONTINUE_EXECUTION;
	}
      break;

    default:
      break;
    }
  return action;
}

/* The function mainCRTStartup is the entry point for all console programs.
 */
static void  __MINGW_ATTRIB_NORETURN
__mingw_CRTStartup (void)
{
  int nRet;

  /* Initialize TLS callback.
   */
  if (__dyn_tls_init_callback != NULL)
    __dyn_tls_init_callback (NULL, DLL_THREAD_ATTACH, NULL);

  /* Set up the top-level exception handler so that signal handling
   * works as expected. The mapping between ANSI/POSIX signals and
   * Win32 SE is not 1-to-1, so caveat emptor.
   *
   */
  SetUnhandledExceptionFilter (_gnu_exception_handler);

  /* Initialize floating point unit.
   */
  __cpu_features_init ();	/* Do we have SSE, etc.*/
  _fpreset ();			/* Supplied by the runtime library. */

  /* Set up __argc, __argv and _environ.
   */
  _setargv ();

  /* Sets the default file mode.
   * If _CRT_fmode is set, also set mode for stdin, stdout
   * and stderr, as well
   * NOTE: DLLs don't do this because that would be rude!
   */
  _mingw32_init_fmode ();

  /* Adust references to dllimported data that have non-zero offsets.
   */
  _pei386_runtime_relocator ();

  /* Align the stack to 16 bytes for the sake of SSE ops in main
   * or in functions inlined into main.
   */
  asm  __volatile__  ("andl $-16, %%esp" : : : "%esp");

   /* From libgcc.a, __main calls global class constructors via
      __do_global_ctors, This in turn  registers  __do_global_dtors
      as the first entry of the app's atexit table.  We do this
      explicitly at app startup rather than rely on gcc to generate
      the call in main's  prologue, since main may be imported from a dll
      which has its own __do_global_ctors.  */
    __main ();

  /* Call the main function. If the user does not supply one
   * the one in the 'libmingw32.a' library will be linked in, and
   * that one calls WinMain. See main.c in the 'lib' dir
   * for more details.
   */
  nRet = main (_argc, _argv, environ);

  /* Perform exit processing for the C library. This means
   * flushing output and calling 'atexit' registered functions.
   */
  _cexit ();

  ExitProcess (nRet);
}

/*
 * The function mainCRTStartup is the entry point for all console programs.
 */
void
mainCRTStartup (void)
{
#ifdef __MSVCRT__
  __set_app_type (__CONSOLE_APP);
#endif
  __mingw_CRTStartup ();
}

/*
 * For now the GUI startup function is the same as the console one.
 * This simply gets rid of the annoying warning about not being able
 * to find WinMainCRTStartup when linking GUI applications.
 */
void
WinMainCRTStartup (void)
{
#ifdef __MSVCRT__
  __set_app_type (__GUI_APP);
#endif
  __mingw_CRTStartup ();
}

/*
 *  We force use of library version of atexit, which is only
 *  visible in import lib as _imp__atexit
 */
extern int (*_imp__atexit)(void (*)(void));
int atexit (void (* pfn )(void) )
{
  return ( (*_imp__atexit)(pfn));
}

/* Likewise for non-ANSI _onexit */
extern _onexit_t (*_imp___onexit)(_onexit_t);
_onexit_t
_onexit (_onexit_t pfn )
{
  return (*_imp___onexit)(pfn);
}
