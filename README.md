# okx_quote
# okx_quote

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
