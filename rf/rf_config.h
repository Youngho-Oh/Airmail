/*
 * rf_config.h
 *
 *  Created on: 2018. 9. 9.
 *      Author: eclipse
 */

#ifndef RF_RF_CONFIG_H_
#define RF_RF_CONFIG_H_


#define CCIF

#define	uint8_t		unsigned char
#define	int8_t		char
#define	uint16_t	unsigned short
#define int16_t		short
#define uint32_t	unsigned int
#define int32_t		int

typedef uint8_t u8_t;

typedef uint16_t u16_t;

typedef uint32_t u32_t;

typedef int32_t s32_t;

typedef unsigned short uip_stats_t;

//TODO
#define process_event_t	unsigned int

#define PACKETBUF_CONF_SIZE        128
#define PACKETBUF_CONF_HDR_SIZE    32
#define QUEUEBUF_CONF_STATS        1

#define UIP_CONF_UIP_IP4ADDR_T_WITH_U32 1

#define UIP_CONF_ICMP_DEST_UNREACH 1

#define UIP_CONF_MAX_CONNECTIONS 40
#define UIP_CONF_MAX_LISTENPORTS 40
#define UIP_CONF_BUFFER_SIZE     120

#define UIP_CONF_BYTE_ORDER      UIP_LITTLE_ENDIAN

#define UIP_CONF_BROADCAST       1

#define UIP_CONF_IP_FORWARD      1

/* TCP splitting does not work well with multi hop routing. */
#define UIP_CONF_TCP_SPLIT       0

#define UIP_CONF_LOGGING         1

#define UIP_CONF_UDP_CHECKSUMS   0

#endif /* RF_RF_CONFIG_H_ */
