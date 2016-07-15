#ifndef MIDDLEBOX_PATHMERGER_HH
#define MIDDLEBOX_PATHMERGER_HH
#include <click/element.hh>
#include "stackelement.hh"
#include "tcpelement.hh"

CLICK_DECLS

class PathMerger : public TCPElement, public StackElement
{
public:
    PathMerger() CLICK_COLD;
    ~PathMerger() CLICK_COLD;

    const char *class_name() const        { return "PathMerger"; }
    const char *port_count() const        { return "2/1"; }
    const char *processing() const        { return PUSH; }

    int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;

    void push_packet(int port, Packet *packet);

    #if HAVE_BATCH
    void push_batch(int port, PacketBatch *batch);
    #endif

    virtual void addStackElementInList(StackElement* element, int port);

protected:
    virtual void setPacketDirty(struct fcb *fcb, WritablePacket* packet);
    virtual void removeBytes(struct fcb *fcb, WritablePacket* packet, uint32_t position, uint32_t length);
    virtual WritablePacket* insertBytes(struct fcb *fcb, WritablePacket* packet, uint32_t position, uint32_t length) CLICK_WARN_UNUSED_RESULT;
    virtual void requestMorePackets(struct fcb *fcb, Packet *packet, bool force = false);
    virtual void packetSent(struct fcb *fcb, Packet* packet);
    virtual void closeConnection(struct fcb* fcb, WritablePacket *packet, bool graceful, bool bothSides);
    virtual bool isLastUsefulPacket(struct fcb* fcb, Packet *packet);
    virtual unsigned int determineFlowDirection();

private:
    StackElement* previousStackElements[2];

    int getPortForPacket(struct fcb *fcb, Packet *packet);
    void setPortForPacket(struct fcb *fcb, Packet *packet, int port);
    StackElement* getElementForPacket(struct fcb *fcb, Packet* packet);
    void removeEntry(struct fcb *fcb, Packet* packet);
    void addEntry(struct fcb *fcb, Packet* packet, int port);
};

CLICK_ENDDECLS

#endif
