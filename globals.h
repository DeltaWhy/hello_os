#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef USE_HLT
#define wait() __asm__ ("hlt")
#else
#define wait()
#endif

#endif
