This script implements a tool that checks that device under test does not listen on any
unwanted network ports. This script requires root permission.
The configuration file allows to define the following rules:
1. List of processes that allowed to open any network sockets. This option can be used if a
   process is listening on a random port or if a process is listening on raw sockets.
1. List of TCP/UDP ports that white-listed.

The default configuration file is located under `mbl/open_ports_checker/white_list.json`
For custom configuration file, use `-w <FILE>` command line option.
If the device under test does not listen on any unwanted network port, a zero return
code will be returned, overwise a non-zero return code will be returned.
