#ifndef CLICK_WEBSERVER_HH
#define CLICK_WEBSERVER_HH
#include <click/element.hh>
#include <click/glue.hh>
#include <click/timer.hh>
#include <click/ipaddress.hh>
#include "tcpreflector.hh"
CLICK_DECLS

/*
 * =c
 * TCPReflector()
 * =s tcp
 * pretend to be a TCP server
 * =d
 * Pretend to be a TCP server; emit a plausible reply packet
 * to each incoming TCP/IP packet. Maintains no state, so
 * should be very fast.
 * =e
 * FromDevice(eth1, 0)
 *   -> Strip(14)
 *   -> CheckIPHeader()
 *   -> IPFilter(allow tcp && dst host 1.0.0.77 && dst port 99 && not src port 99, deny all)
 *   -> Print(x)
 *   -> TCPReflector()
 *   -> Print(y)
 *   -> EtherEncap(0x0800, 1:1:1:1:1:1, 00:03:47:07:E9:94)
 *   -> ToDevice(eth1);
 */

class WebServer : public TCPReflector {
 public:

    WebServer() CLICK_COLD;
  ~WebServer() CLICK_COLD;

  const char *class_name() const override		{ return "WebServer"; }
  const char *port_count() const override		{ return PORTS_1_1; }

    int configure(Vector<String> &conf, ErrorHandler *errh) CLICK_COLD;

};

CLICK_ENDDECLS
#endif
