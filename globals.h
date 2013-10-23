#ifndef GLOBALS_H
#define GLOBALS_H

#define UNUSED(x) (void)x

#ifdef USE_HLT
#define wait() __asm__ ("hlt")
#else
#define wait()
#endif

#endif
