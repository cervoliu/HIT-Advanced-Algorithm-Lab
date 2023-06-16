# Usage

`make analyzer` - compile the ip packet analyzer.

`./analyzer [CM/CU/Count/CMM/naive] [network_interface] [number_of_packet]` - run analyzer, where

- `CM` - Count-Min sketch
- `CU` - Count-Unique sketch
- `Count` - Count sketch
- `CMM` - Count-Mean-Min sketch
- `naive` - STL unordered_map (baseline)

`number_of_packet` is the number of ethernet packets to be captured (note : only IP packets would be analyzed).

`network_interface` can be found by `ifconfig` on Linux, for example :
```
$ ifconfig
docker0: flags=4099<UP,BROADCAST,MULTICAST>  mtu 1500
        inet 172.17.0.1  netmask 255.255.0.0  broadcast 172.17.255.255
        ether 02:42:bf:03:4c:b9  txqueuelen 0  (Ethernet)
        RX packets 0  bytes 0 (0.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 0  bytes 0 (0.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

lo: flags=73<UP,LOOPBACK,RUNNING>  mtu 65536
        inet 127.0.0.1  netmask 255.0.0.0
        inet6 ::1  prefixlen 128  scopeid 0x10<host>
        loop  txqueuelen 1000  (Local Loopback)
        RX packets 2501801  bytes 2484859359 (2.4 GB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 2501801  bytes 2484859359 (2.4 GB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

wlp0s20f3: flags=4163<UP,BROADCAST,RUNNING,MULTICAST>  mtu 1500
        inet 172.20.167.204  netmask 255.255.0.0  broadcast 172.20.255.255
        inet6 2001:250:fe01:130:66f1:2c8c:3b39:15af  prefixlen 64  scopeid 0x0<global>
        inet6 2001:250:fe01:130:6b88:3381:37be:e314  prefixlen 64  scopeid 0x0<global>
        inet6 fe80::977c:4da3:8baf:1781  prefixlen 64  scopeid 0x20<link>
        ether 28:7f:cf:ba:3b:23  txqueuelen 1000  (Ethernet)
        RX packets 2766060  bytes 3769892720 (3.7 GB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 1093377  bytes 138416670 (138.4 MB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
```
Then the network interfaces are `docker0`, `lo` and `wlp0s20f3`.

If `permision denied` is occured, try running under `sudo`.

To get time and memory information upon running, try running under `time -v`, for example :
```
$ sudo time -v ./analyzer Count wlp0s20f3 1000
[sudo] password for cervol: 
100 200 300 400 500 600 700 800 900 1000 
        Command being timed: "./analyzer Count wlp0s20f3 1000"
        User time (seconds): 0.01
        System time (seconds): 0.00
        Percent of CPU this job got: 0%
        Elapsed (wall clock) time (h:mm:ss or m:ss): 0:07.00
        Average shared text size (kbytes): 0
        Average unshared data size (kbytes): 0
        Average stack size (kbytes): 0
        Average total size (kbytes): 0
        Maximum resident set size (kbytes): 6912
        Average resident set size (kbytes): 0
        Major (requiring I/O) page faults: 0
        Minor (reclaiming a frame) page faults: 237
        Voluntary context switches: 14
        Involuntary context switches: 6
        Swaps: 0
        File system inputs: 0
        File system outputs: 112
        Socket messages sent: 0
        Socket messages received: 0
        Signals delivered: 0
        Page size (bytes): 4096
        Exit status: 0
```

sudo time -v ./analyzer Count wlp0s20f3 100000 > Count.out & sudo time -v ./analyzer naive wlp0s20f3 100000 > naive.out & sudo time -v ./analyzer CM wlp0s20f3 100000 > CM.out & sudo time -v ./analyzer CU wlp0s20f3 100000 > CU.out &