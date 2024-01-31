<AutoPilot:project xmlns:AutoPilot="com.autoesl.autopilot.project" top="TcpTop" name="Tcp">
    <includePaths/>
    <libraryFlag/>
    <files>
        <file name="/root/okx/src/Tcp/Test/TcpTest.cpp" sc="0" tb="1" cflags=" -lpcap -Wno-unknown-pragmas" csimflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="/root/okx/src/Tcp/TcpTop.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="/root/okx/src/Tcp/TcpPayloadParsor.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="/root/okx/src/Tcp/TcpInputProcessor.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="/root/okx/src/Tcp/TcpTop.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="/root/okx/src/Tcp/TcpPayloadParsor.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="/root/okx/src/Tcp/TcpInputProcessor.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
    </files>
    <solutions>
        <solution name="solution1" status=""/>
    </solutions>
    <Simulation argv="">
        <SimFlow name="csim" setup="false" optimizeCompile="false" clean="false" ldflags="-lpcap" mflags=""/>
    </Simulation>
</AutoPilot:project>

