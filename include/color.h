#ifndef COLOR_H
#define COLOR_H

/**
 * @file color.h Defines helper macros around color gestion
 *
 * The colors should stay within the 8-16 bit color range for compatibility with most
 * terminals, at least for the base version of `ubsh`.
 */

#define RESET "\x1B[0m"

/* Font color */
#define RED(__S) "\x1B[31m" __S RESET
#define GREEN(__S) "\x1B[32m" __S RESET
#define YELLOW(__S) "\x1B[33m" __S RESET
#define BLUE(__S) "\x1B[34m" __S RESET
#define MAGENTA(__S) "\x1B[35m" __S RESET

/* Highlight color */
#define RED_HI(__S) "\x1B[101m" __S RESET

#endif /* ! COLOR_H */
