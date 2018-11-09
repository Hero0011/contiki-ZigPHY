#include "contiki.h"
#include "net/netstack.h"
#include "dev/radio.h"
#include "dev/watchdog.h"
#include "sys/clock.h"
#include <stdio.h>

static unsigned char packet[256] = {0};

PROCESS(zigphy_tx_process, "zigphy_rx_process");
AUTOSTART_PROCESSES(&zigphy_tx_process);
PROCESS_THREAD(zigphy_tx_process, ev, data)
{
	int i = 0;
	PROCESS_BEGIN();
	watchdog_stop();
	NETSTACK_RADIO.set_value (RADIO_PARAM_POWER_MODE, 1);
	NETSTACK_RADIO.set_value (RADIO_PARAM_RX_MODE, 0); //disable Address Filtering
	while(1) {
		if (NETSTACK_RADIO.read((void*)packet, 256) > 0) {
			printf("received %d\n", ++i);
		}
	}
	PROCESS_END();
}
