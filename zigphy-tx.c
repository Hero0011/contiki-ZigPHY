#include "contiki.h"
#include "net/netstack.h"
#include "dev/radio.h"
#include "dev/watchdog.h"
#include "sys/clock.h"
#include <stdio.h>
#include <string.h>
#include "ieee-addr.h"

static unsigned char packet[64] = {0};

PROCESS(zigphy_tx_process, "zigphy_tx_process");
AUTOSTART_PROCESSES(&zigphy_tx_process);
PROCESS_THREAD(zigphy_tx_process, ev, data)
{
	int value, i = 0;
	PROCESS_BEGIN();
	watchdog_stop();
	NETSTACK_RADIO.set_value(RADIO_PARAM_POWER_MODE, 1);
	//NETSTACK_RADIO.get_value(RADIO_PARAM_CHANNEL, &value);
	//cc2420_set_txpower(31);
	//value = cc2420_get_txpower();
	NETSTACK_RADIO.get_value(RADIO_PARAM_TXPOWER, &value);
	printf(" TXPWR: %d dBm\n", value);
	uint8_t addr[8];
	ieee_addr_cpy_to(addr, 8);
	for (int i = 0; i < 8; ++i) {
		sprintf(packet, "%s%02X", packet, addr[i]);
	}
	while(1) {
		if (++i % 1000 == 0) printf("sending %d\n", i);
		NETSTACK_RADIO.send(packet, 64);
		clock_wait(CLOCK_SECOND); //delay between packets
	}
	PROCESS_END();
}
