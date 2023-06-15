#include "sketch.h"

#include <iostream>
#include <pcap/pcap.h>
#include <string>
#include <unordered_map>

using namespace std;

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer);

int main(int argc, char **argv)
{
    // Check command-line arguments
    if(argc < 3)
    {
        cerr << "Usage: " << argv[0] << " <sketch_type> <network_interface>" << endl;
        return 1;
    }
    
    string sketch_type = argv[1];
    Sketch* sketch = nullptr;

    if(sketch_type == "CM")
    {
        sketch = new CM_Sketch(1000, 5); // create a Count-Min Sketch object
    }
    else if(sketch_type == "CU")
    {
        sketch = new CU_Sketch(1000, 5); // create a Count-Unique Sketch object
    }
    else if(sketch_type == "Count")
    {
        sketch = new Count_Sketch(1000, 5); // create a Count Sketch object
    }
    else
    {
        cerr << "Invalid sketch type: " << sketch_type << endl;
        return 1;
    }

    // Open network interface for packet capture
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(argv[2], BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        cerr << "Error: could not open network interface " << argv[2] << ": " << errbuf << endl;
        return 1;
    }

    // Start packet capture loop
    pcap_loop(handle, 1000, process_packet, (u_char *)sketch);

    // Close network interface
    pcap_close(handle);

    for(int i = 0; i < 200; ++i)
        printf("%d\n", sketch->query(i));

    delete sketch;
    return 0;
}

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer)
{
    // Extract Sketch data structure from arguments
    auto *sketch = (Sketch *)args;

    // Parse Ethernet header
    const u_char *ethernet_header = buffer;
    int ethernet_type = (ethernet_header[12] << 8) | ethernet_header[13];
    if (ethernet_type != 0x0800) {
        return; // Not an IP packet
    }

    // Parse IP header
    const u_char *ip_header = buffer + 14;
    int ip_length = (ip_header[0] & 0x0f) * 4;
    const u_char *ip_payload = ip_header + ip_length;
    int ip_protocol = ip_header[9];
    if (ip_protocol != 6) {
        return; // Not a TCP packet
    }

    // Parse TCP header
    const u_char *tcp_header = ip_payload;
    int tcp_length = ((tcp_header[12] >> 4) & 0x0f) * 4;
    const u_char *tcp_payload = tcp_header + tcp_length;

    // Extract source IP address and payload length
    string src_ip = to_string(ip_header[12]) + "." + to_string(ip_header[13]) + "." + to_string(ip_header[14]) + "." + to_string(ip_header[15]);
    int payload_length = header->len - (ip_length + tcp_length);

    // Update Sketch with payload length for source IP address
    sketch->insert(payload_length);
    //printf("%d\n", sketch->query(payload_length));
}