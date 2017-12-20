#ifndef CONFIG_H_
#define CONFIG_H_

/******************************************* INCLUDE *******************************************/

#include <stdint.h>
#include <avr/io.h>

/*******************************************  DEFINE *******************************************/

#ifndef NULL
#define NULL ((void *)0)
#endif

typedef uint8_t BOOL;
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif


#endif /* CONFIG_H_ */