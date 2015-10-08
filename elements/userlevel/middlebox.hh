#ifndef CLICK_MIDDLEBOX_HH
#define CLICK_MIDDLEBOX_HH
#include <click/element.hh>
CLICK_DECLS


class Middlebox : public Element { public:

  Middlebox() CLICK_COLD;

  const char *class_name() const        { return "Middlebox"; }
  const char *port_count() const        { return PORTS_1_1; }
  const char *processing() const        { return PROCESSING_A_AH; }

  int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;

  void push(int, Packet *);
  Packet *pull(int);

 protected:
    void processPacket(WritablePacket*);
    void processContent(unsigned char*);


};

CLICK_ENDDECLS
#endif
