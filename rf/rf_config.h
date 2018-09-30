/*
 * rf_config.h
 *
 *  Created on: 2018. 9. 9.
 *      Author: eclipse
 */

#ifndef RF_RF_CONFIG_H_
#define RF_RF_CONFIG_H_

//#include "rf/net/tcpip.h"
//#include "rf/net/uip.h"
//#include "net/uip-fw.h"
//#include "rf/net/uip-fw-drv.h"
//#include "rf/net/uip_arp.h"
//#include "rf/net/uiplib.h"
//#include "rf/net/uip-udp-packet.h"
//#include "rf/net/simple-udp.h"
//
//#if UIP_CONF_IPV6
//#include "net/uip-icmp6.h"
//#include "net/uip-ds6.h"
//#endif /* UIP_CONF_IPV6 */
//
//#include "rf/net/resolv.h"
//
//#include "rf/net/psock.h"
//
//#include "rf/net/rime.h"
//
//#include "rf/net/netstack.h"

#define CCIF

typedef	unsigned char	uint8_t;
typedef char			int8_t;
typedef unsigned short	uint16_t;
typedef short			int16_t;
typedef unsigned int	uint32_t;
typedef int				int32_t;

typedef uint8_t 		u8_t;
typedef uint16_t		u16_t;
typedef uint32_t 		u32_t;
typedef int32_t 		s32_t;

typedef unsigned short uip_stats_t;

typedef unsigned int  	process_event_t;

#define PACKETBUF_CONF_SIZE        128
#define PACKETBUF_CONF_HDR_SIZE    32
#define QUEUEBUF_CONF_STATS        1

#define UIP_CONF_UIP_IP4ADDR_T_WITH_U32 1

#define UIP_CONF_ICMP_DEST_UNREACH 1

#define UIP_CONF_MAX_CONNECTIONS 40
#define UIP_CONF_MAX_LISTENPORTS 40
//#define UIP_CONF_BUFFER_SIZE     120

#define UIP_CONF_BYTE_ORDER      UIP_LITTLE_ENDIAN

#define UIP_CONF_BROADCAST       1

#define UIP_CONF_IP_FORWARD      1

/* TCP splitting does not work well with multi hop routing. */
#define UIP_CONF_TCP_SPLIT       0

#define UIP_CONF_LOGGING         1

#define UIP_CONF_UDP_CHECKSUMS   0

/* DMA Configuration */
#ifndef DMA_CONF_ON
#define DMA_CONF_ON 0
#endif

/* Viztool on by default for IPv6 builds */
#if UIP_CONF_IPV6
#ifndef VIZTOOL_CONF_ON
#define VIZTOOL_CONF_ON        1
#endif /* VIZTOOL_CONF_ON */
#endif /* UIP_CONF_IPV6 */

/* Network Stack */
#ifndef NETSTACK_CONF_NETWORK
#if UIP_CONF_IPV6
#define NETSTACK_CONF_NETWORK sicslowpan_driver
#else
#define NETSTACK_CONF_NETWORK rime_driver
#endif /* UIP_CONF_IPV6 */
#endif /* NETSTACK_CONF_NETWORK */

#ifndef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC     csma_driver
#endif

#ifndef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC     nullrdc_driver
#define NULLRDC_802154_AUTOACK 1
#define NULLRDC_802154_AUTOACK_HW 1
#endif

#ifndef NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 8
#endif

#ifndef NETSTACK_CONF_FRAMER
#define NETSTACK_CONF_FRAMER  framer_802154
#endif

#define NETSTACK_CONF_RADIO   cc2530_rf_driver

/* RF Config */
#define IEEE802154_CONF_PANID 0x5449 /* TI */

#ifndef CC2530_RF_CONF_CHANNEL
#define CC2530_RF_CONF_CHANNEL    25
#endif /* CC2530_RF_CONF_CHANNEL */

#ifndef CC2530_RF_CONF_AUTOACK
#define CC2530_RF_CONF_AUTOACK 1
#endif /* CC2530_CONF_AUTOACK */

#if UIP_CONF_IPV6
/* Addresses, Sizes and Interfaces */
/* 8-byte addresses here, 2 otherwise */
#define RIMEADDR_CONF_SIZE                   8
#define UIP_CONF_LL_802154                   1
#define UIP_CONF_LLH_LEN                     0
#define UIP_CONF_NETIF_MAX_ADDRESSES         3

/* TCP, UDP, ICMP */
#define UIP_CONF_TCP                         0
#define UIP_CONF_UDP                         1
#define UIP_CONF_UDP_CHECKSUMS               1

/* ND and Routing */
#ifndef UIP_CONF_ROUTER
#define UIP_CONF_ROUTER                      1
#endif

#define UIP_CONF_ND6_SEND_RA                 0
#define UIP_CONF_IP_FORWARD                  0
#define RPL_CONF_STATS                       0
#define RPL_CONF_MAX_DAG_ENTRIES             1
#ifndef RPL_CONF_OF
#define RPL_CONF_OF rpl_mrhof
#endif

#define UIP_CONF_ND6_REACHABLE_TIME     600000
#define UIP_CONF_ND6_RETRANS_TIMER       10000

#ifndef NBR_TABLE_CONF_MAX_NEIGHBORS
#define NBR_TABLE_CONF_MAX_NEIGHBORS                 4 /* Handle n Neighbors */
#endif
#ifndef UIP_CONF_MAX_ROUTES
#define UIP_CONF_MAX_ROUTES               4 /* Handle n Routes */
#endif

/* uIP */
#ifndef UIP_CONF_BUFFER_SIZE
#define UIP_CONF_BUFFER_SIZE               240
#endif
#define UIP_CONF_IPV6_QUEUE_PKT              0
#define UIP_CONF_IPV6_CHECKS                 1
#define UIP_CONF_IPV6_REASSEMBLY             0

/* 6lowpan */
#define SICSLOWPAN_CONF_COMPRESSION          SICSLOWPAN_COMPRESSION_HC06
#ifndef SICSLOWPAN_CONF_FRAG
#define SICSLOWPAN_CONF_FRAG                 0 /* About 2KB of CODE if 1 */
#endif
#define SICSLOWPAN_CONF_MAXAGE               8

/* Define our IPv6 prefixes/contexts here */
#define SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS    1
#define SICSLOWPAN_CONF_ADDR_CONTEXT_0 { \
  addr_contexts[0].prefix[0] = 0xaa; \
  addr_contexts[0].prefix[1] = 0xaa; \
}

#define MAC_CONF_CHANNEL_CHECK_RATE          8

#ifndef QUEUEBUF_CONF_NUM
#define QUEUEBUF_CONF_NUM                    6
#endif

#else /* UIP_CONF_IPV6 */
/* Network setup for non-IPv6 (rime). */
#define UIP_CONF_IP_FORWARD                  1
#define UIP_CONF_BUFFER_SIZE               108
#define RIME_CONF_NO_POLITE_ANNOUCEMENTS     0
#define QUEUEBUF_CONF_NUM                    8
#endif /* UIP_CONF_IPV6 */

/* Prevent SDCC compile error when UIP_CONF_ROUTER == 0 */
#if !UIP_CONF_ROUTER
#define UIP_CONF_DS6_AADDR_NBU               1
#endif


#endif /* RF_RF_CONFIG_H_ */
