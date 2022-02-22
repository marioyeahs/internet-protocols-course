
Protocolos: un acuerdo de series de reglas y convenciones.

Modelo OSI(Open Systems Interconnection): F E R T S P A



Comunicación capa-a-capa: Un dispositivo A envía mensaje a dispositivo B, el mensaje de A baja a través del modelo OSI desde la capa 7 hasta la capa 1. En la capa 1 el paquete entero es convertido en una forma que pueda ser transferida al lado del receptor. En el lado del receptor, el mensaje es trasnferido desde la capa 1 hasta la 7.

Interfaces entre las capas: La comunicación entre las capas del lado del receptor y del transmisor es gracias a las *interfaces* que se encuentran entre las capas adyacentes. Cada interfaz define que información y servicios debe proveer la capa a la que le sigue. Interfaces y capas bien definidas proveen modulairad a una red.

Organización de las capas: Se pueden dividir en dos subgrupos:
1. Capas de soporte de red: 1, 2, 3. Se encargan con los aspectos físicos de mover los datos de un dispositivo a otro(tales como especificaiones eléctricas, conexiones físicas, direccionamiento físico, y tiempos de trasnporte y reliabilidad).
2. Capas de soporte al usuario: 5, 6, 7. permiten la interoperabilidad entre los sistemas de software sin relación.
3. Capa de transporte: 4. Relaciona los dos subgrupos y se asegura de que lo que las capas inferiores trasnmitan sea en una forma que las capas superiores puedan utilizar.

Encapsulación: La parte de los datos de un paquete en el nivel N lleva el paquete completo (data y overhead) del nivel N+1. El concepto es llamado encapsulación porque el nivel N no le importa que parte del paquete encapsulado son datos y que parte es la cabezera o la cola. Para el nivel N, el paquete completo proveniente del nivel N+1 es tratado como una unidad integral.

Resumen del Modelo OSI:

Aplicación: Permitir el acceso a las fuentes de la red.
Presentación: Encriptar, traducir y comprimir los datos.
Sesión: establecer, manejar y terminar sesiones.
Transporte: Fiabilidad y recuperación de errores en el envío de datos.
Red: Mover paquetes de fuente a destino, proveer internetworking.
Enlace de datos: Organizar bits en frames(tramas), para proveer envíos salto-a-salto.
Física: Transmitir bits en un medio, proveer especificaciones eléctricas y mecánicas.

# Suite de protocolos TCP/IP

Esta suite fue desarrollada posteriori al modelo OSI. Además, las capas de la suite de protocolo TCP/IP no hacen un match exacto con las del modelo OSI. Orignalmente la suite de protocolo TCP/IP fue definidad como cuatro capas de software construidas por hardware. Hoy en día, sin embargo, la suite de protocolo TCP/IP está pensada como un modelo de cinco capas, llamas similarmente a las del modelo OSI


# Direccionamiento
Cuatro niveles de direcciones son usadas en una internet empleando los protocolos TCP/IP: dirección física, dirección lógica, dirección de puerto y dirección de aplicación específica. Cada dirección esta relcioanda a una capa de la arquitectura TCP/IP.

* Dirección física: también llamada dirección de enlace, es la dirección de un nodo que es definida por su LAN o WAN. Está incluida en la trama(**frame**) utilizada por la capa de **Enlace de Datos**. Esta es la dirección de nivel más bajo. La dirección física tiene autoridad sobre el enlace (LAN o WAN). El tamaño y formato de estas direcciones varía dependiendo de la red. Por ejemplo, Ethernet usa un dirección física de 6-bytes(48 bits) que está impresa en la tajeta de interfaz de trabajo (NIC). LocalTalk(Apple), sin embargo, tiene una direccion dinámica de 1-byte que cambia cadad vez que la estación lo haga. 
_Ejemplo_: Hay un nodo con dirección física 10 que envía una trama al nodo con dirección física 87. Ambos nodos están conectados por un *enlace* (un Local Area Network). En la capa de enlace de datos, esta trama contiene las direcciones (*link*) físicas en el header. L trailer usualmente contiene bits extra para la detección de errores. En la capa de enlace de datos en el trasnmisor recibe los datos de una capa superior. Encapsula los datos en una trama, añadiendo el header y el trailer. El header, además de otros pedazos de información, lleva al receptor y al transmisor las direcciones (*link*) físicas. Note que en la mayoría de los casos, la dirección destino (87 en este caso), viene the la dirección fuente (10 en este caso). La trama es propagada a través de la LAN. Cada estación con una dirección física diferente a 87 ignorará el paquete y éste seguirá su camino hasta encontrar el nodo con dirección física 87. Una vez checada la trama, el header y trailer son desechados, y la parte de los datos es desencapsulada y enviada a la capa superior.

FIGURA 2.16

_Ejemplo_: Como se verá en el capítulo 3, la mayoría de las redes de área local usan un dirección física de 48-bit (6-byte) escritas con 12 digitos hexadecimales, cada byte (2 digitos hexadecimales) es separado por dos puntos, como se muestra a continuación:
							07:01:02:01:2C:4B
					A 6-byte (12 hexadecimal digits) physical address

Direcciones físicas Unicast, Multicast y Broadcast.
Unicast(un sólo receptor), multicast(un grupo de receptores) y broadcast(recibido por todos los sistemas en la red). Algunas redes soportan las tres direcciones. Por ejemplo Ethernet soporta la direcciones físicas unicast (6 bytes), las direcciones multicast y las direcciones broadcast. Algunas redes no soportan las direcciones multicast o broadcast. Si una trama debe ser enviada a un grupo de receptores o a todo el sistema, las direcciones multicast o broadcast deben ser simuladas usando una dirección unicast. Esto significa que multiples paquetes son enviados son enviados usando direcciones unicast.

# Direcciones Lógicas
Son necesarias para las comunicaciones universales que son independientes de underlying redes físicas. Direcciones físicas no son adecuadas en un ambiente de red de internet donde diferentes redes pueden tener diferentes formatos de direcciones. Una sistema de direccionamiento universal es necesario en el cual cada host puede ser identificado como único, gracias al underlying de red física. Las direcciones lógicas son designadas para éste propósito. Una dirección lógica en el Internet actualmente es de 32-bit que puede definir únicamente a un host conectado a Internet. Ningún host visible o direccionado públicamente en Internet puede tener la misma dirección IP.
Las direcciones físicas cambiarán de hop to hop, pero las direcciones lógicas se mantienen igual.

# Interfaz de Socket
Un programa de computadora es un conjunto de instrucciones predefinidas que le indica a la computadora lo que debe de hacer. Un programa de computadora tiene un set de instrucciones para operaciones matemáticas, otro set para manipulación de strings y otro set para para accesos de entrada/salida. Si necesitamos un programa capaz de comunicarse con otro programa ejecutandose en otra computadora, necesitaremos de un conjunto de instrucciones para indicarle a la capa de transporte que abra la conexión, envíe y reciba los datos del otro extremo; y cerrar la conexión. Un set de instrucciones de este tipo es normalmente llamado **interfaz**.
Una **interfaz** es un conjunto de instrucciones designado para la interacción entre dos entidades.

# Socket
Un socket es un software abstracto que simula un socket físico que vemos en la vida real. Para usar el canal de comunicación, un programa de aplicación (cliente o servidor) necesita pedirle a SO sistema operativo crear un socket. El programa de aplicación entones se puede conectar al socket para enviar y recibir datos. Para que la comunicación de datos ocurra, un par de sockets, uno en cada extremo de la comunnicación es necesario. En el Internet un socket es un software de estructura de datos.

# Estructura de datos
El formato de una estructura de datos para definir un socket depende en el leguage undelaying usado por los procesos. En lenguaje C, un socket está definido como una estructura de cinco campos (estructura o registro).
_Figura 17.6_ Estructura de datos de un socket
	struct socket
	{
		int family;
		int type;
		int protocol;
		socketaddr local;
		socketaddr remote;
	};

El programador NO debe redefinir esta estructura; ya está definida.

**Family**. Este campo define el grupo de protocolo: IPv4, IPv6, protocolos de dominio UNIX, y así. El tipo de familia que usamos en TCP/IP es definida por la constante IF_INET para el protocolo IPv4 y IF_INET6 para el protocolo IPv6.
**Type**. Este campo define cuatro tipos de sockets: SOCK_STREAM (para TCP), SOCK_DGRAM (para UDP), SOCK_SEQPACKET (para SCTP), y SOCK_RAW (para aplicaciones que directamente usan los servicios IP)
**Protocol**. Este campo define el protocolo que usa la interfaz. Es 0 para la suite de protocolo TCP/IP.
**Local Socket Address**. Este campo define la dirección del socket local. Una dirección de socket, es una combinación de una dirección IP y un número de puerto.
**Remote socket address**. Es la dirección del socket remoto.

# Estructura de la dirección de un socket.
Antes de poder usar un socket, necesitamos entender la estructura de la dirección de un socket, que es una combinación de direcciones IP y un número de puerto. Es una estructura compleja (struct en C).
__Figure 17.8__ IPv4 socket address.
La estructura sockaddr_in tiene cinco campos, uno de ellos es sin_addr es por sí mismo una estructura de tipo in_addr con un sólo campo s_addr. Nosotros primero definimos una estructura in_addr como se muestra a continuación:
struct in_addr
{
	in_addr_t s_addr; // una dirección IPv4 de 32 bits
}

Ahora definimos una estructura sockaddr_in:
struct sockaddr_in
{
	uint8_t sin_len; // length of structure (16 bytes)
	sa_family_t sin_family; // set to AF_INET
	in_port_t sin_port; // A 16-bit port number
	struct in_addr sin_addr; // A 32-bit IPv4 address
	char sin_zero[8]; // unused
}

# Funciones
* La Función de socket
El sistema operativo define la estrutura de la figura 17.6. Sin embargo el SO no crea un socket hasta que se cree la instrucción por el proceso. El proceso necesita usar la llamada a la función _socket_  para crear el socket.
	int socket (int family, int type, int protocol);

_Ejemplo 17.3_ página 562


