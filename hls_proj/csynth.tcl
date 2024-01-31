set kernel_name [lindex $argv 0]
set path [lindex $argv 1]
set part [lindex $argv 2]

cd ${path}/hls_proj/

open_project ${kernel_name} -reset
set_top ${kernel_name}Top

set file_list [glob -directory ${path}/src/${kernel_name} -type f *.cpp *.h]
foreach file $file_list {
    add_files $file
}
set file_list [glob -directory ${path}/src/${kernel_name}/Test -type f *.cpp *.h]
foreach file $file_list {
    add_files -tb $file  -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
}

open_solution "solution1" -flow_target vitis
set_part ${part}
create_clock -period 3

set_directive_top -name ${kernel_name}Top "${kernel_name}Top"
csynth_design

export_design -rtl verilog -format xo -version 2.0.1 
exit