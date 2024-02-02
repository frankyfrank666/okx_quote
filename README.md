# okx_quote
# okx_quote

requires libpcap for reading the pcap packets for simulation. yum install libpcap

Run software c-simulation:
In hls_proj folder:
  make csim NAME=Tcp

Run hardware emulation:
In build folder:
  First add the kernel names into the target and kernel lists
  make kernel
  make link
  make host
  make run
