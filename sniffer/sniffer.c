#include "headerFiles.h"

#define MAXBUFF 65536

/*
    sniffer para capturar tramas Ethernet
    determinar a partir del campo  longitud o tipo 
    si es una trama IEEE 802.3(0x0000 A 0x05DC) o
    una trama Ethernet II(mayor o igual 0x0600).
    
*/

void get_data(int, char[5]);
void ProcessPacket(unsigned char *buffer, int size);
void print_ethernet_header(unsigned char *Buffer, int Size);


FILE *logfile;
unsigned MAC[6], MASK[6], IP[4];
int len, total; //tamaño del buffer

int main()
{

    int socket_fd;
    //unsigned char packet_buffer[MAXBUFF]; // buffer para almacenar paquetes
    unsigned char *packet_buffer = (unsigned char *)malloc(65536); //Its Big!
    int len;
    char name[6];                                                       //package len
    //ifconfig enp2s0 -promisc
    printf("\nNIC name:");
    scanf("%s",name);
    //char name[6] = "wlp1s0";
    struct ifreq eth_req;
    struct sockaddr_ll sll;
    struct sockaddr_ll packet_info;
    int packet_info_size = sizeof(packet_info);

    logfile = fopen("log.txt", "w");
    if (logfile == NULL)
    {
        printf("Unable to create log.txt file.");
    }

    socket_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); //receive all ethernet frames

    if (socket_fd == -1)
    {
        printf("Error creating socket\n");
    }
    else
    {
        printf("Socket opened successfully\n");

        // set promiscuous mode
        strncpy(eth_req.ifr_name, name, 6);
        if (ioctl(socket_fd, SIOCGIFFLAGS, &eth_req) == -1)
        {
            printf("Failed   to get flags for interface\n");
        }
        else
        {
            printf("Interface flags successfully\n");
        }
        eth_req.ifr_flags |= IFF_PROMISC;
        if (ioctl(socket_fd, SIOCSIFFLAGS, &eth_req) == -1)
        {
            printf("Failed to set promiscuous mode\n");
        }
        else
        {
            printf("Set promiscuous mode\n");
        }

        //get_data(socket_fd, name);

        struct ifreq eth_req;
        printf("NIC %s\n", name);
        strcpy(eth_req.ifr_name, name);

        //Get NIC index
        if (ioctl(socket_fd, SIOCGIFINDEX, &eth_req) == -1)
        {
            printf("Error: cannot get index");
        }
        else
        {
            printf("Index: %d\n", eth_req.ifr_ifindex);
        }
        // sll.sll_family = PF_PACKET;
        // sll.sll_ifindex = eth_req.ifr_ifindex;
        // sll.sll_protocol = ETH_P_ALL;
        // // bind socket('wlsp0',sfd,eth_p_all)
        // if (bind(socket_fd, (struct sockaddr *)&sll, sizeof(sll)) == -1)
        // {
        //     printf("Error binding raw socket");
        // }
        // else
        // {
        //     printf("Socket binded successfully");
        // }

        int packets_to_sniff;
        printf("\n# packages? ");
        scanf("%d",&packets_to_sniff);
        //captura de paquetes
        while (packets_to_sniff !=0)
        {
            if (len = recvfrom(socket_fd, packet_buffer, MAXBUFF, 0, (struct sockaddr *)&packet_info, &packet_info_size) == -1)
            {
                printf("recvfrom failed");
                exit - 1;
            }
            else
            {
                struct ethhdr *data;
                ProcessPacket(packet_buffer, len);
                --packets_to_sniff;
                printf("\nReceiving packets...");
            }
        }
    }
    close(socket_fd);
    return 0;
}

void get_data(int sfd, char name[])
{
    int i = 0;
    struct ifreq eth_req;
    printf("NIC %s\n", name);
    strcpy(eth_req.ifr_name, name);

    //Get NIC index
    if (ioctl(sfd, SIOCGIFINDEX, &eth_req) == -1)
    {
        printf("Error: cannot get index");
    }
    else
    {
        printf("Index: %d\n", eth_req.ifr_ifindex);
    }
}

void ProcessPacket(unsigned char *buffer, int size)
{
    //Get the IP Header part of this packet , excluding the ethernet header
    struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
    ++total;
    print_ethernet_header(buffer, size);

    printf("Total: %d\r", total);
}

void print_ethernet_header(unsigned char *Buffer, int Size)
{
    struct ethhdr *eth = (struct ethhdr *)Buffer;

    fprintf(logfile, "\n");
    fprintf(logfile, "Ethernet Header\n");
    fprintf(logfile, "   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0], eth->h_dest[1], eth->h_dest[2], eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);
    fprintf(logfile, "   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0], eth->h_source[1], eth->h_source[2], eth->h_source[3], eth->h_source[4], eth->h_source[5]);
    fprintf(logfile, "   |-Protocolo            : %.2X \n", eth->h_proto); //solo aceptar trama Ethernet II (>=0x0600) >1536, asume protocolo
}

// void print_ip_header(unsigned char* Buffer, int Size)
// {
// 	print_ethernet_header(Buffer , Size);

// 	unsigned short iphdrlen;

// 	struct iphdr *iph = (struct iphdr *)(Buffer  + sizeof(struct ethhdr) );
// 	iphdrlen =iph->ihl*4;

// 	memset(&source, 0, sizeof(source));
// 	source.sin_addr.s_addr = iph->saddr;

// 	memset(&dest, 0, sizeof(dest));
// 	dest.sin_addr.s_addr = iph->daddr;

// 	fprintf(logfile , "\n");
// 	fprintf(logfile , "IP Header\n");
// 	fprintf(logfile , "   |-IP Version        : %d\n",(unsigned int)iph->version);
// 	fprintf(logfile , "   |-IP Header Length  : %d DWORDS or %d Bytes\n",(unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
// 	fprintf(logfile , "   |-Type Of Service   : %d\n",(unsigned int)iph->tos);
// 	fprintf(logfile , "   |-IP Total Length   : %d  Bytes(Size of Packet)\n",ntohs(iph->tot_len));
// 	fprintf(logfile , "   |-Identification    : %d\n",ntohs(iph->id));
// 	//fprintf(logfile , "   |-Reserved ZERO Field   : %d\n",(unsigned int)iphdr->ip_reserved_zero);
// 	//fprintf(logfile , "   |-Dont Fragment Field   : %d\n",(unsigned int)iphdr->ip_dont_fragment);
// 	//fprintf(logfile , "   |-More Fragment Field   : %d\n",(unsigned int)iphdr->ip_more_fragment);
// 	fprintf(logfile , "   |-TTL      : %d\n",(unsigned int)iph->ttl);
// 	fprintf(logfile , "   |-Protocol : %d\n",(unsigned int)iph->protocol);
// 	fprintf(logfile , "   |-Checksum : %d\n",ntohs(iph->check));
// 	fprintf(logfile , "   |-Source IP        : %s\n",inet_ntoa(source.sin_addr));
// 	fprintf(logfile , "   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
// }

// void print_tcp_packet(unsigned char* Buffer, int Size)
// {
// 	unsigned short iphdrlen;

// 	struct iphdr *iph = (struct iphdr *)( Buffer  + sizeof(struct ethhdr) );
// 	iphdrlen = iph->ihl*4;

// 	struct tcphdr *tcph=(struct tcphdr*)(Buffer + iphdrlen + sizeof(struct ethhdr));

// 	int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;

// 	fprintf(logfile , "\n\n***********************TCP Packet*************************\n");

// 	print_ip_header(Buffer,Size);

// 	fprintf(logfile , "\n");
// 	fprintf(logfile , "TCP Header\n");
// 	fprintf(logfile , "   |-Source Port      : %u\n",ntohs(tcph->source));
// 	fprintf(logfile , "   |-Destination Port : %u\n",ntohs(tcph->dest));
// 	fprintf(logfile , "   |-Sequence Number    : %u\n",ntohl(tcph->seq));
// 	fprintf(logfile , "   |-Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
// 	fprintf(logfile , "   |-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
// 	//fprintf(logfile , "   |-CWR Flag : %d\n",(unsigned int)tcph->cwr);
// 	//fprintf(logfile , "   |-ECN Flag : %d\n",(unsigned int)tcph->ece);
// 	fprintf(logfile , "   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
// 	fprintf(logfile , "   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
// 	fprintf(logfile , "   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
// 	fprintf(logfile , "   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
// 	fprintf(logfile , "   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
// 	fprintf(logfile , "   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
// 	fprintf(logfile , "   |-Window         : %d\n",ntohs(tcph->window));
// 	fprintf(logfile , "   |-Checksum       : %d\n",ntohs(tcph->check));
// 	fprintf(logfile , "   |-Urgent Pointer : %d\n",tcph->urg_ptr);
// 	fprintf(logfile , "\n");
// 	fprintf(logfile , "                        DATA Dump                         ");
// 	fprintf(logfile , "\n");

// 	fprintf(logfile , "IP Header\n");
// 	PrintData(Buffer,iphdrlen);

// 	fprintf(logfile , "TCP Header\n");
// 	PrintData(Buffer+iphdrlen,tcph->doff*4);

// 	fprintf(logfile , "Data Payload\n");
// 	PrintData(Buffer + header_size , Size - header_size );

// 	fprintf(logfile , "\n###########################################################");
// }
