#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include <format>
#include <iostream>

using namespace std;
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("TriangleNetworkExample");

uint32_t sentPackets = 0;
uint32_t receivedPackets = 0;
int SERVER_PORT = 8080;

// Callback para contar paquetes enviados
void
PacketSentCallback(Ptr<const Packet> packet)
{
    sentPackets++;
}

// Callback para contar paquetes recibidos
void
PacketReceivedCallback(Ptr<const Packet> packet)
{
    receivedPackets++;
}

int
main(int argc, char* argv[])
{
    CommandLine cmd(__FILE__);
    cmd.Parse(argc, argv);

    Time::SetResolution(Time::NS);
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    NodeContainer nodes;
    nodes.Create(3); // Tres nodos

    double packet_size;
    string data_rate;
    int num_packets;
    double timeout;
    string delay;

    cout << "Envie el número de paquetes a enviar: ";
    cin >> num_packets;
    cout << "Ingrese el tamaño del paquete (KB): ";
    cin >> packet_size;
    std::string animFile = std::format(
        "/home/pissarello-dev/ns-allinone-3.42/ns-3.42/scratch/netanim_simulations/three_nodes/threeNode{}KB.xml",
        packet_size);
    packet_size = packet_size * 1024;
    cout << "Ingrese el Data rate (Tasa de transferencia ) (Mbps): ";
    cin >> data_rate;
    data_rate = data_rate + "Mbps";
    cout << "Ingrese el delay (congestión del canal (ms)): ";
    cin >> delay;
    cout << "Ingrese el timeout (s): ";
    cin >> timeout;

    delay = delay + "ms";

    // Configuración de enlaces punto a punto
    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue(data_rate));
    pointToPoint.SetChannelAttribute("Delay", StringValue(delay));

    // Conexión nodo 0 <-> nodo 1
    NetDeviceContainer devices01;
    devices01 = pointToPoint.Install(nodes.Get(0), nodes.Get(1));

    // Conexión nodo 1 <-> nodo 2
    NetDeviceContainer devices12;
    devices12 = pointToPoint.Install(nodes.Get(1), nodes.Get(2));

    // Conexión nodo 0 <-> nodo 2
    NetDeviceContainer devices02;
    devices02 = pointToPoint.Install(nodes.Get(0), nodes.Get(2));

    InternetStackHelper stack;
    stack.Install(nodes);

    // Asignar direcciones IP
    Ipv4AddressHelper address;

    address.SetBase("10.0.0.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces01 = address.Assign(devices01);

    address.SetBase("10.0.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces12 = address.Assign(devices12);

    address.SetBase("10.0.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces02 = address.Assign(devices02);

    // Habilitar el enrutamiento global para todos los nodos
    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    int num_actions;
    cout << "Ingrese el número de acciones (envíos de paquetes): ";
    cin >> num_actions;

    for (int i = 0; i < num_actions; i++)
    {
        int sourceNode, targetNode;
        cout << "Acción " << i + 1 << " - Ingrese el número del nodo origen (0, 1 o 2): ";
        cin >> sourceNode;
        cout << "Acción " << i + 1 << " - Ingrese el número del nodo destino (0, 1 o 2): ";
        cin >> targetNode;

        // Configurar servidor en el nodo destino
        UdpEchoServerHelper echoServer(SERVER_PORT + i); // Diferente puerto para cada acción
        ApplicationContainer serverApps = echoServer.Install(nodes.Get(targetNode));
        serverApps.Start(Seconds(1.0 + i)); // Escalonado en el tiempo
        serverApps.Stop(Seconds(timeout));

        // Configurar cliente en el nodo origen que se comunica con el servidor
        UdpEchoClientHelper echoClient(
            nodes.Get(targetNode)->GetObject<Ipv4>()->GetAddress(1, 0).GetLocal(),
            SERVER_PORT + i);
        echoClient.SetAttribute("MaxPackets", UintegerValue(num_packets));
        echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
        echoClient.SetAttribute("PacketSize", UintegerValue(packet_size));

        ApplicationContainer clientApps = echoClient.Install(nodes.Get(sourceNode));
        clientApps.Start(Seconds(2.0 + i));
        clientApps.Stop(Seconds(timeout));

        // Conectar los callbacks para contar paquetes a nivel de aplicación
        clientApps.Get(0)->TraceConnectWithoutContext("Tx", MakeCallback(&PacketSentCallback));
        serverApps.Get(0)->TraceConnectWithoutContext("Rx", MakeCallback(&PacketReceivedCallback));
    }

    // NetAnim
    AnimationInterface anim(animFile);

    Simulator::Run();
    Simulator::Destroy();

    // Imprimir resultados
    cout << "Total packets sent: " << sentPackets << endl;
    cout << "Total packets received: " << receivedPackets << endl;

    return 0;
}
