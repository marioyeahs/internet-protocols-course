#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>

#include <asm/types.h>

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

struct {
    // ETHERNET HEADER
	unsigned char destinoEthernet[6];      /*Dirección de difusión 0xFF*/
	unsigned char origenEthernet[6];       /*Dirección MAC del transmisor*/
	unsigned short tipoEthernet;             /*Tipo de mensaje en la trama Ethernet*/
    // ARP MESSAGE
	unsigned short tipoHardware;           /*Tipo de hardware utilizado para difundir el mensaje ARP (Ethernet), tecnología subyacente*/
	unsigned short tipoProtocolo;          /*Tipo de protocolo de red utilizado para difundir el mensaje ARP (IP), de capa superior*/
    unsigned char longitudHardware;  /*Tamaño de direcciones de hardware (6bytes)*/
    unsigned char longitudProtocolo;  /*Tamaño de direcciones del protocolo (4bytes)*/
    unsigned short tipoMensaje;          /* Solicitud o respuesta, request or response*/
	unsigned char origenMAC[6];         /*Dirección MAC del transmisor*/
	unsigned char origenIP[4];             /*Dirección IP del transmisor*/
	unsigned char destinoMAC[6];  /*Dirección MAC del receptor (dirección solicitada), la queremos consultar*/
    unsigned char destinoIP[4];         /*Dirección IP del receptor (dato de entrada), la queremos consultar*/
} msgARP;



int main (int argc, char **arg){
    sfd = socket (PF_INET, SOCK_PACKET, ETH_P_ARP);

    // cuando mando un paquete ARP, mando la solicitud a una dirección de DIFUSIÓN
    // es decir una paquete broadcast, los sockets por lo general NO lo permite,
    // por lo general son de UNIDIFUSIÓN, por lo que tengo que modificar el socket
    // con ayuda de la función:
    brd = setsockopt(sfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));// modificar el 
    // comportamiento del socket (sfd, SOL_SOCKET, sizeof(int len)),

    if (brd >= 0) {
        // si se pudo modificar su comportamiento
    }else{
        // no se pudo modificar
    }
    // el valor que devuelva debe ser positivo o cero
    // SOL_SOCKET -> modificar a nivel de socket (programacion) el intercambio de paquetes, 
    // qué mensajes voy a enviar o cómo se va a comportar, en este caso BROADCAST

    // antes de mandar el mensaje se tienen q llenar cada uno de los campos de la estructura

    // definimos el campo cabecera con ayuda de la función ioctl() y de la estructura ifreq, 
    // que tiene almacenada toda la información de la tarjeta de red, leemos la estructura y obtenemos la
    // info que es el nombre de la tarjeta de red y con eso obtenemos su dirección MAC e IP, sólo del ORIGEN

    // la dirección ETHERNET y MAC origen son las mismas

    // la dirección destino ETHERNET es la de difusión, en bits todos 1´s y en bytes todos en F, con bcopy()
    // copia la información, puras F's

    // la dirección de destino MAC es la que yo quiero obtener y yo no la conozco cuando envío el mensaje,
    // así que todos los bytes en 0's con bzero()

    // llenar este campo con que voy a utilizar el protocolo ARP y este 	unsigned short tipoEthernet;             /*Tipo de mensaje en la trama Ethernet*/
    con las etiquetas de la practica

    // longitud potocolo y hardware son los bytes que necesito para especificar una dirección lógica y física
    msgARP.longitudProtocolo = 4; // valor_bytes_direccionIP  
    msgARP.longitudHardware = 6;

    // ahora si ya con sendto() envío el mensaje, el búfer es el mensaje ARP que acabamos de llenar y con
    // recvfrom recibimos el mensaje, este tiene q estar dentro de un ciclo en donde debo de comparar los 
    // mensajes que yo reciba, dirección IP destino sea la IP desde donde hice la consulta y que el tipo de 
    // mensaje sea de respuesta,si coincide tomo la dirección destino MAC que es donde viene la dirección 
    // solicitada y se imprimer, recordemos que este campo fue el que llenamos con 0's, pero ya ahorita en 
    // la respuesta va a tener la info que necesitamos


}