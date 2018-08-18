/*
 * common.h
 *
 *  Created on: 2018. 5. 4.
 *      Author: eclipse
 */

#ifndef HAL_COMMON_H_
#define HAL_COMMON_H_

/***********************************************************************************
 * INCLUDES
 */

#include <stdio.h>
#include <string.h>
#include <cc2530.h>

#include <hal/common_config.h>

/***********************************************************************************
 * TYPEDEFS
 */

typedef void (*ISR_FUNC_PTR)(void);

struct conf_status{
	unsigned short enable_log;
	unsigned short enable_rf;
};

#define FAILED		1
#define SUCCESS 	0


/***********************************************************************************
* MACROS
*/

#ifndef BV
#define BV(n)      (1 << (n))
#endif

#ifndef BM
#define BM(n)      (1 << (n))
#endif

#ifndef BF
#define BF(x,b,s)  (((x) & (b)) >> (s))
#endif

#ifndef MIN
#define MIN(n,m)   (((n) < (m)) ? (n) : (m))
#endif

#ifndef MAX
#define MAX(n,m)   (((n) < (m)) ? (m) : (n))
#endif

#ifndef ABS
#define ABS(n)     (((n) < 0) ? -(n) : (n))
#endif

/* uint32 processing */
#define BREAK_UINT32( var, ByteNum ) \
    (unsigned char)((unsigned int)(((var) >>((ByteNum) * 8)) & 0x00FF))

#define BUILD_UINT32(Byte0, Byte1, Byte2, Byte3) \
    ((unsigned int)((unsigned int)((Byte0) & 0x00FF) \
        + ((unsigned int)((Byte1) & 0x00FF) << 8) \
            + ((unsigned int)((Byte2) & 0x00FF) << 16) \
                + ((unsigned int)((Byte3) & 0x00FF) << 24)))

#define HI_UINT32(a) ((unsigned short) (((unsigned int)(a)) >> 16))
#define LO_UINT32(a) ((unsigned short) ((unsigned int)(a)))


/* uint16 processing */
#define BUILD_UINT16(loByte, hiByte) \
    ((unsigned short)(((loByte) & 0x00FF) + (((hiByte) & 0x00FF) << 8)))

#define HI_UINT16(a) (((unsigned short)(a) >> 8) & 0xFF)
#define LO_UINT16(a) ((unsigned short)(a) & 0xFF)


/* uint8 processing */
#define BUILD_UINT8(hiByte, loByte) \
    ((unsigned char)(((loByte) & 0x0F) + (((hiByte) & 0x0F) << 4)))

#define HI_UINT8(a) (((unsigned char)(a) >> 4) & 0x0F)
#define LO_UINT8(a) ((unsigned char)(a) & 0x0F)

/***********************************************************************************
 * Host to network byte order macros
 */
#ifdef BIG_ENDIAN
#define UINT16_HTON(x)  st( utilReverseBuf((uint8*)&x, sizeof(uint16)); )
#define UINT16_NTOH(x)  st( utilReverseBuf((uint8*)&x, sizeof(uint16)); )

#define UINT32_HTON(x)  st( utilReverseBuf((uint8*)&x, sizeof(uint32)); )
#define UINT32_NTOH(x)  st( utilReverseBuf((uint8*)&x, sizeof(uint32)); )
#else
#define UINT16_HTON(x)
#define UINT16_NTOH(x)

#define UINT32_HTON(x)
#define UINT32_NTOH(x)
#endif


/***********************************************************************************
 * VALUES
 */

#if (SYS_XSTACK_SUPPROT == 1)

/* register bank1 is used by external stack pointer */
/*
 * <Rule>
 * 1) 2bytes per stack register
 * 2) little endian
 *
 */
extern __data __at (0x08) unsigned char uc_bank1_r0;
extern __data __at (0x09) unsigned char uc_bank1_r1;
extern __data __at (0x0a) unsigned char uc_bank1_r2;
extern __data __at (0x0b) unsigned char uc_bank1_r3;
extern __data __at (0x0c) unsigned char uc_bank1_r4;
extern __data __at (0x0d) unsigned char uc_bank1_r5;
extern __data __at (0x0e) unsigned char uc_bank1_r6;
extern __data __at (0x0f) unsigned char uc_bank1_r7;

/* regitser bank2 is used by interrupt register */

#endif

extern struct conf_status sys_setting;

#endif /* HAL_COMMON_H_ */
