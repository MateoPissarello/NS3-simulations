#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

#include <format>
#include <iostream>

using namespace std;
using namespace ns3;

NS_LOG_COMPONENT_DEFINE("FirstScriptExample");

uint32_t sentPackets = 0;
uint32_t receivedPackets = 0;
int SERVER_PORT = 8080;

// Callback para contar paquetes enviados por el cliente
void
PacketSentCallback(Ptr<const Packet> packet)
{
    sentPackets++;
}

// Callback para contar paquetes recibidos por el servidor
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
    nodes.Create(2);

    int packet_size;
    string data_rate;
    int num_packets;
    double timeout;
    string delay;

    cout << "Envie el número de paquetes a enviar: ";
    cin >> num_packets;
    cout << "Ingrese el tamaño del paquete (KB): ";
    cin >> packet_size;
    std::string animFile = std::format("/home/pissarello-dev/ns-allinone-3.42/ns-3.42/scratch/"
                                       "netanim_simulations/point_to_point/pointToPoint{}KB.xml",
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

    PointToPointHelper pointToPoint;
    pointToPoint.SetDeviceAttribute("DataRate", StringValue(data_rate));
    pointToPoint.SetChannelAttribute("Delay", StringValue(delay));

    NetDeviceContainer devices;
    devices = pointToPoint.Install(nodes);

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.0.0.0", "255.0.0.0");

    Ipv4InterfaceContainer interfaces = address.Assign(devices);

    UdpEchoServerHelper echoServer(SERVER_PORT);
    ApplicationContainer serverApps = echoServer.Install(nodes.Get(0));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(timeout));

    UdpEchoClientHelper echoClient(interfaces.GetAddress(0), SERVER_PORT);
    echoClient.SetAttribute("MaxPackets", UintegerValue(num_packets));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(packet_size));

    ApplicationContainer clientApps = echoClient.Install(nodes.Get(1));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(timeout));

    // Conectar los callbacks para contar paquetes a nivel de aplicación
    clientApps.Get(0)->TraceConnectWithoutContext("Tx", MakeCallback(&PacketSentCallback));
    serverApps.Get(0)->TraceConnectWithoutContext("Rx", MakeCallback(&PacketReceivedCallback));

    // NetAnim
    AnimationInterface anim(animFile);
    // cout << "Done" << endl;

    Simulator::Run();
    Simulator::Destroy();

    // Imprimir resultados
    cout << "Total packets sent: " << sentPackets << endl;
    cout << "Total packets received: " << receivedPackets << endl;

    return 0;
}
