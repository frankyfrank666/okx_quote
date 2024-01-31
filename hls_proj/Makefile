$(eval PARENT_FOLDER := $(shell dirname "$(CURDIR)"))

PART = {xqvu9p-fsqd2104-2LV-e}

create_project:
	/opt/Xilinx/Vitis/2020.1/bin/vitis_hls $(shell pwd)/create_proj.tcl ${NAME} ${PARENT_FOLDER} ${PART} 

csim:
	/opt/Xilinx/Vitis/2020.1/bin/vitis_hls $(shell pwd)/csim.tcl ${NAME} ${PARENT_FOLDER} ${PART} 

csynth:
	/opt/Xilinx/Vitis/2020.1/bin/vitis_hls $(shell pwd)/csynth.tcl ${NAME} ${PARENT_FOLDER} ${PART}