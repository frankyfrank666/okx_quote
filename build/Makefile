.PHONY: host kernel run clean clean_all all

enviroment:
	/root/faasTools/vitis_setup.sh



XILINX_XRT := /opt/xilinx/xrt/
XILINX_HLS := /opt/Xilinx/Vitis/2020.1/

exe_name   := host_exe
PLATFORM = /opt/xilinx/platforms/xilinx_aliyun-f3_dynamic_5_0/xilinx_aliyun-f3_dynamic_5_0.xpfm
xclbin_name :=x3.xclbin
VPP := /opt/Xilinx/Vitis/2020.1/bin/v++
XRT := $(XILINX_XRT)
HLS := $(XILINX_HLS)
TARGET := hw_emu
HOST := ../host/host.cpp
VPP_COMPILE := --platform $(PLATFORM) --target $(TARGET) --compile -g -s
VPP_LINK 	:= --platform $(PLATFORM) --target $(TARGET) --link -g -s --optimize 0 --config kernel-link.cfg




TARGETS := Vadd EthIn EthOut 
xo: $(TARGETS)
$(TARGETS): %:
	/root/okx/build/hls_bug_workaround.sh && $(VPP) $(VPP_COMPILE) -k $@Top -o"build/$@Top.xo" "../src/$@/$@Top.cpp"
	/root/okx/build/hls_bug_workaround_rev.sh

Tcp:
	/root/okx/build/hls_bug_workaround.sh && $(VPP) $(VPP_COMPILE) -k $@Top -o"build/$@Top.xo" "../src/$@/$@Top.cpp" "../src/Tcp/TcpInputProcessor.cpp" "../src/Tcp/TcpPayloadParsor.cpp"
	/root/okx/build/hls_bug_workaround_rev.sh


kernel += Tcp

$(foreach kk,$(kernel),$(eval KERNELS += build/$(basename $(kk))Top.xo))
kernel: $(kernel)

link: $(KERNELS)
	/root/okx/build/hls_bug_workaround.sh &&  $(VPP) $(VPP_LINK) -o"$(xclbin_name)" $^ 
	/root/okx/build/hls_bug_workaround_rev.sh

run:
	make enviroment
ifeq ($(TARGET),hw)
	./$(exe_name) $(xclbin_name)
else
	emconfigutil --platform $(PLATFORM)
	export XCL_EMULATION_MODE=hw_emu && ./$(exe_name) $(xclbin_name)
endif

all: 
	make -j20 kernel
	make link
	make host
	make run

host: $(HOST)
	make enviroment
	g++ -Wall -g -std=c++11 $(HOST) -o $(exe_name) \
	-I${XILINX_XRT}/include/ \
	-I$(HLS)/include/ \
	-L${XILINX_XRT}/lib/ -lOpenCL -lpthread -lrt -lstdc++ -lpcap
	@echo $(HOST)

clean:
	rm -rf *.ltx .ipcache xsim* binary_container_1.build .run _x .Xil *.log *.mdb *.info *.link_summary *.run_summary *.o *.str
	rm -rf *.jou *.wcfg *.wdb emconfig.json sample_link.ini sample_compile.ini obj*  bin* *.csv *.jpg *.jpeg *.png *.protoinst *log

clean_all:
	make clean
	rm -rf $(xclbin_name) build
	rm -rf $(exe_name)

# view_xsim: 
# 	xsim  -gui /xilinx_x3522p_gen4x8_hn10g_202220_1-0-$(patsubst %.xclbin,%,$(xclbin_name)).wdb &