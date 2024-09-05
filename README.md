
# Simulacion ns-3

En este repositorio se encuentra almacenado el codigo utilizado para diseñar una Simulacion de una red punto a punto, y una red con topologia triangular interconectada.

En la carpeta de `diagramas_red` se puede ver de una manera mas visual la topologia de las redes simuladas.
## Requisitos
Para poder correr el codigo correctamente se recomientda:
- Estar trabajando en alguna distribucion de Linux
- Tener gcc instalado o algun compilador de C++ como `g++`
- Tener la herramienta `ns-3` correctamente instalada, para ello se puede seguir la [documentación oficial](https://www.nsnam.org/docs/release/3.42/tutorial/ns-3-tutorial.pdf).
- Tener NetAnim [construido](https://www.nsnam.org/wiki/NetAnim_3.108)

### Estructura del proyecto

Los archivos `pointToPoint.cc` y `threeNode.cc` son los que se deben ejecutar para generar las animaciones que pueden ser visualizadas con la herramienta NetAnim, esta herramienta por defecto ya debe venir incluida si se instala `ns-3` a partir del tar, sin embargo se debe meter a la carpeta que la contiene y construir la app con `make`.

### ¿Comó correr el proyecto?
Para correr el proyecto es necesario copiar todo el contenido de este repositorio dentro de la carpeta scratch en `ns-3` suele estar en la ruta `~/ns-allinone-3.42/ns-3.42/scratch`, esto, porque para que ns-3 pueda leer el archivo correctamente debe estar en esa ruta.

Una vez los archivos de `pointToPoint.cc` y `threeNode.cc` se encuentren en scratch pueden ser ejecutados facilmente con el comando:
```bash
ns3 run pointToPoint.cc
```
En este caso se usa `ns3` porque ese es el nombre con el que lo tengo añadido al path, en dado caso de que se tenga asignado bajo otro nombre debe ser reemplazado

**Ejemplo del Path**
```bash
/home/pissarello-dev/.pyenv/shims:/usr/local/bin:/usr/bin:/usr/local/sbin:/var/lib/flatpak/exports/bin:/usr/lib/jvm/default/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl:/home/pissarello-dev/.spicetify:/home/pissarello-dev/ns-allinone-3.42/ns-3.42
```

Adicionalmente, se deben cambiar las rutas de NetAnim, por las deseadas en su máquina.
### pointToPoint

Se pude ejecutar `pointPoint.cc` con el sigguiente comando:
```bash
ns3 run pointToPoint.cc
```
Al ejecutarlo, se espera una salida parecida a esta:

```bash
[0/2] Re-checking globbed directories...
ninja: no work to do.
Envie el número de paquetes a enviar: 2
Ingrese el tamaño del paquete (KB): 25
Ingrese el Data rate (Tasa de transferencia ) (Mbps): 50
Ingrese el delay (congestión del canal (ms)): 1
Ingrese el timeout (s): 20
AnimationInterface WARNING:Node:0 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:1 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:0 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:1 Does not have a mobility model. Use SetConstantPosition if it is stationary
At time +2s client sent 25600 bytes to 10.0.0.1 port 8080
At time +2.00516s server received 25600 bytes from 10.0.0.2 port 49153
At time +2.00516s server sent 25600 bytes to 10.0.0.2 port 49153
At time +2.01032s client received 25600 bytes from 10.0.0.1 port 8080
At time +3s client sent 25600 bytes to 10.0.0.1 port 8080
At time +3.00516s server received 25600 bytes from 10.0.0.2 port 49153
At time +3.00516s server sent 25600 bytes to 10.0.0.2 port 49153
At time +3.01032s client received 25600 bytes from 10.0.0.1 port 8080
Total packets sent: 2
Total packets received: 2
```

El codigo nos permite manipular variables que afectan las simulacion como:
- Número de paquetes
- Tamaño del paquete en KB
- Tasa de transferencia en Mbps
- Delay en segundos
- Timeout en segundos

### threeNode
Teniendo `threeNode.cc` en la carpeta scratch, se ejecuta con el siguiente comando:
```bash
ns3 run threeNode
```

Se espera una salida como esta:
```bash
[0/2] Re-checking globbed directories...
ninja: no work to do.
Envie el número de paquetes a enviar: 5
Ingrese el tamaño del paquete (KB): 25
Ingrese el Data rate (Tasa de transferencia ) (Mbps): 50
Ingrese el delay (congestión del canal (ms)): 1
Ingrese el timeout (s): 30
Ingrese el número de acciones (envíos de paquetes): 3
Acción 1 - Ingrese el número del nodo origen (0, 1 o 2): 0
Acción 1 - Ingrese el número del nodo destino (0, 1 o 2): 2
Acción 2 - Ingrese el número del nodo origen (0, 1 o 2): 1
Acción 2 - Ingrese el número del nodo destino (0, 1 o 2): 2
Acción 3 - Ingrese el número del nodo origen (0, 1 o 2): 2
Acción 3 - Ingrese el número del nodo destino (0, 1 o 2): 0
AnimationInterface WARNING:Node:0 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:1 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:2 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:0 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:1 Does not have a mobility model. Use SetConstantPosition if it is stationary
AnimationInterface WARNING:Node:2 Does not have a mobility model. Use SetConstantPosition if it is stationary
At time +2s client sent 25600 bytes to 10.0.1.2 port 8080
At time +2.00516s server received 25600 bytes from 10.0.2.1 port 49153
At time +2.00516s server sent 25600 bytes to 10.0.2.1 port 49153
At time +2.01032s client received 25600 bytes from 10.0.2.2 port 8080
At time +3s client sent 25600 bytes to 10.0.1.2 port 8080
At time +3s client sent 25600 bytes to 10.0.1.2 port 8081
At time +3.00516s server received 25600 bytes from 10.0.2.1 port 49153
At time +3.00516s server sent 25600 bytes to 10.0.2.1 port 49153
At time +3.00516s server received 25600 bytes from 10.0.1.1 port 49153
At time +3.00516s server sent 25600 bytes to 10.0.1.1 port 49153
At time +3.01032s client received 25600 bytes from 10.0.2.2 port 8080
At time +3.01032s client received 25600 bytes from 10.0.1.2 port 8081
At time +4s client sent 25600 bytes to 10.0.1.2 port 8080
At time +4s client sent 25600 bytes to 10.0.1.2 port 8081
At time +4s client sent 25600 bytes to 10.0.0.1 port 8082
At time +4.00516s server received 25600 bytes from 10.0.2.1 port 49153
At time +4.00516s server sent 25600 bytes to 10.0.2.1 port 49153
At time +4.00516s server received 25600 bytes from 10.0.1.1 port 49153
At time +4.00516s server sent 25600 bytes to 10.0.1.1 port 49153
At time +4.00516s server received 25600 bytes from 10.0.2.2 port 49153
At time +4.00516s server sent 25600 bytes to 10.0.2.2 port 49153
At time +4.01032s client received 25600 bytes from 10.0.2.2 port 8080
At time +4.01032s client received 25600 bytes from 10.0.1.2 port 8081
At time +4.01032s client received 25600 bytes from 10.0.2.1 port 8082
At time +5s client sent 25600 bytes to 10.0.1.2 port 8080
At time +5s client sent 25600 bytes to 10.0.1.2 port 8081
At time +5s client sent 25600 bytes to 10.0.0.1 port 8082
At time +5.00516s server received 25600 bytes from 10.0.2.1 port 49153
At time +5.00516s server sent 25600 bytes to 10.0.2.1 port 49153
At time +5.00516s server received 25600 bytes from 10.0.1.1 port 49153
At time +5.00516s server sent 25600 bytes to 10.0.1.1 port 49153
At time +5.00516s server received 25600 bytes from 10.0.2.2 port 49153
At time +5.00516s server sent 25600 bytes to 10.0.2.2 port 49153
At time +5.01032s client received 25600 bytes from 10.0.2.2 port 8080
At time +5.01032s client received 25600 bytes from 10.0.1.2 port 8081
At time +5.01032s client received 25600 bytes from 10.0.2.1 port 8082
At time +6s client sent 25600 bytes to 10.0.1.2 port 8080
At time +6s client sent 25600 bytes to 10.0.1.2 port 8081
At time +6s client sent 25600 bytes to 10.0.0.1 port 8082
At time +6.00516s server received 25600 bytes from 10.0.2.1 port 49153
At time +6.00516s server sent 25600 bytes to 10.0.2.1 port 49153
At time +6.00516s server received 25600 bytes from 10.0.1.1 port 49153
At time +6.00516s server sent 25600 bytes to 10.0.1.1 port 49153
At time +6.00516s server received 25600 bytes from 10.0.2.2 port 49153
At time +6.00516s server sent 25600 bytes to 10.0.2.2 port 49153
At time +6.01032s client received 25600 bytes from 10.0.2.2 port 8080
At time +6.01032s client received 25600 bytes from 10.0.1.2 port 8081
At time +6.01032s client received 25600 bytes from 10.0.2.1 port 8082
At time +7s client sent 25600 bytes to 10.0.1.2 port 8081
At time +7s client sent 25600 bytes to 10.0.0.1 port 8082
At time +7.00516s server received 25600 bytes from 10.0.1.1 port 49153
At time +7.00516s server sent 25600 bytes to 10.0.1.1 port 49153
At time +7.00516s server received 25600 bytes from 10.0.2.2 port 49153
At time +7.00516s server sent 25600 bytes to 10.0.2.2 port 49153
At time +7.01032s client received 25600 bytes from 10.0.1.2 port 8081
At time +7.01032s client received 25600 bytes from 10.0.2.1 port 8082
At time +8s client sent 25600 bytes to 10.0.0.1 port 8082
At time +8.00516s server received 25600 bytes from 10.0.2.2 port 49153
At time +8.00516s server sent 25600 bytes to 10.0.2.2 port 49153
At time +8.01032s client received 25600 bytes from 10.0.2.1 port 8082
Total packets sent: 15
Total packets received: 15
```

Podemos manipular las mismas variables que en `pointToPoint.cc` y adicionalmente nos permite decidir el numero de **acciones** a realizar.

Entendemos por **acción** como el intercambio de paquetes desde un nodo de origen a un nodo de destino, por lo que podemos tener mas de una **acción** (intercambio de paquetes) en la misma simulacion.Esto, en palabras mas sencillas, se traduce como el intercambio de paquetes entre diferentes nodos "al mismo tiempo".

Como mencionamos para cada **acción** se seleccionan dos cosas:
- Nodo de origen (0, 1, o 2)
- Nodo de destino (0, 1 o 2)

### Visualizar las animaciones

Al momento de correr una simulacion, se tendra un archivo .xml ubicado en la ruta que se haya definido.

Para visualizar el paquete debemos ingresar a NetAnim, usualmente se encuentra en la siguiente ruta `~/ns-allinone-3.42/netanim-3.109`.

Teniendo ya creada con `make` la aplicacion de [NetAnim](https://www.nsnam.org/wiki/NetAnim_3.108). Podemos abrirla con el comando:
```bash
./NetAnim
```

Una vez abierto, en la esquina superior izquierda se tendrá el logo de una carpeta, al hacer click podremos seleccionar un archivo, aqui es donde se ira a la ruta donde se haya almacenado el .xml.

De esta manera se pueden visualizar las animacines generadas a partir de las simulaciones.


## Relacionado

[ns-3](https://github.com/nsnam)


## Autores

- Mateo Pissarello Londoño [@MateoPissarello](https://github.com/MateoPissarello?tab=repositories) 
- Julián Rincón [@MalianR](https://github.com/MalianR)
- Daniela López Rincòn [@Dani213343](https://github.com/Dani213343)



