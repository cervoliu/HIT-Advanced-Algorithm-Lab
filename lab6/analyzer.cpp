#include "sketch.h"

#include <iostream>
#include <pcap/pcap.h>
#include <string>
#include <unordered_map>

using namespace std;

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer);

unordered_map<string, void*> sketches;

int main(int argc, char **argv)
{
    // Check command-line arguments
    if(argc < 4)
    {
        cerr << "Usage: " << argv[0] << " <sketch_type> <network_interface> <#_of_package>" << endl;
        return 1;
    }
    string sketch_type = argv[1];
    if(sketch_type != "CM" && sketch_type != "CU" && sketch_type != "Count")
    {
        cerr << "Invalid sketch type: " << sketch_type << endl;
        return 1;
    }
    int num_package = atoi(argv[3]);

    // Open network interface for packet capture
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live(argv[2], BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        cerr << "Error: could not open network interface " << argv[2] << ": " << errbuf << endl;
        return 1;
    }

    // Start packet capture loop
    pcap_loop(handle, num_package, process_packet, (u_char *)argv[1]);
    cerr << endl;

    // Close network interface
    pcap_close(handle);

    freopen("output.txt", "w", stdout);
    for(auto p : sketches)
    {
        Sketch* sketch = (Sketch*)p.second;
        printf("ip = %s, max = %d, total = %d\n", p.first.c_str(), sketch->max_x, sketch->total);
        for(int i = 1; i <= sketch->max_x; i++)
        {
            printf("%d ", sketch->query(i));
        }
        printf("\n");
        delete sketch;
    }
    fclose(stdout);
    return 0;
}

int now = 0;

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer)
{
    if(++now % 100 == 0)
    {
        cerr << now << " ";
    }
    // Extract Sketch data structure from arguments
    string sketch_type = (char *)args;

    // Parse Ethernet header
    const u_char *ethernet_header = buffer;
    int ethernet_type = (ethernet_header[12] << 8) | ethernet_header[13];
    if (ethernet_type != 0x0800 && ethernet_type != 0x86DD) {
        return; // Not an IP packet
    }

    // Parse IP header
    const u_char *ip_header = buffer + 14;
    int ip_version = (ip_header[0] >> 4) & 0x0f;
    int ip_header_length = (ip_header[0] & 0x0f) * 4;

    // Extract source IP address and payload length
    std::string src_ip;
    int payload_length;
    if (ip_version == 4) {
        // IPv4 packet
        src_ip = std::to_string(ip_header[12]) + "." + std::to_string(ip_header[13]) + "." + std::to_string(ip_header[14]) + "." + std::to_string(ip_header[15]);
        payload_length = header->len - ip_header_length;
    } else if (ip_version == 6) {
        // IPv6 packet
        src_ip = "";
        for (int i = 8; i < 24; i += 2) {
            src_ip += std::to_string((ip_header[i] << 8) | ip_header[i+1]) + ":";
        }
        src_ip.pop_back(); // remove last colon
        payload_length = header->len - ip_header_length;
    } else {
        return; // Not an IP packet
    }

    //cerr << src_ip << " " << payload_length << endl;

    Sketch* sketch = nullptr;
    if(sketches[src_ip] == nullptr)
    {
        if(sketch_type == "CM")
        {
            sketch = new CM_Sketch(1000, 5);
        }
        else if(sketch_type == "CU")
        {
            sketch = new CU_Sketch(1000, 5);
        }
        else if(sketch_type == "Count")
        {
            sketch = new Count_Sketch(1000, 5);
        }
        sketches[src_ip] = sketch;
    }
    sketch = (Sketch*)sketches[src_ip];
    // Update Sketch with payload length for source IP address
    sketch->insert(payload_length);
}