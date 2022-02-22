#include "headerFiles.h"

/*
    sniffer para capturar tramas Ethernet
    determinar a partir del campo  longitud o tipo 
    si es una trama IEEE 802.3(0x0000 A 0x05DC) o
    una trama Ethernet II(mayor o igual 0x0600).
    
*/

unsigned MAC[6], MASK[6], IP[4];

void get_data(int,char[5]);

int main(){
    
    int socket_fd;
    //ifconfig enp2s0 -promisc
    char name[6] = "wlp1s0";
    struct ifreq eth_req;
    socket_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL)); //receive all ethernet frames
    if (socket_fd == -1){
        printf("Error creating socket\n");
    }else{
        printf("Socket opened successfully\n");
        get_data(socket_fd,name);
        
        // set promiscuous mode
        strncpy (eth_req.ifr_name, name, 6);
        if(ioctl (socket_fd, SIOCGIFFLAGS, &eth_req)==-1){
            printf("Failed   to get flags for interface\n");
        }else{
            printf("Interface flags successfully\n");
        }
        eth_req.ifr_flags |= IFF_PROMISC;
        if(ioctl (socket_fd, SIOCSIFFLAGS, &eth_req) ==-1){
            printf("Failed to set promiscuous mode\n");
        }else{
            printf("Set promiscuous mode\n");
        }
    }
    close(socket_fd);
}

void get_data(int sfd, char name[]){
    int i = 0;
    struct ifreq eth_req;
    printf("NIC %s\n",name);
    strcpy(eth_req.ifr_name,name);

    //Get NIC index
    if(ioctl(sfd,SIOCGIFINDEX,&eth_req)==-1){
        printf("Error: cannot get index");
    }else{
        printf("Index: %d\n",eth_req.ifr_ifindex);
    }
}

