//
// Created by ganler-Mac on 2019/7/9.
//

/* About the kernel */

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

// To use the kernel. We must use OpenCL C language to program our kernel
// which is just create a `.cl` file and write the `__kernel` function in it.

int main()
{
    /* Specify the platform and device */
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    auto platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    auto device = devices.front();
    cl::Context context(device); // Contains the physical devices.(To build context, we need to specify the device.)

    /* Specify the kernel */
    std::ifstream hello_world_cl("../kernels/helloworld.cl");
    std::string src(std::istreambuf_iterator<char>(hello_world_cl), std::istreambuf_iterator<char>{});

    // cl::Program::Source is just a VECTOR<const char *, std::size_t>.
    // Each element in cl::Program::Source stands for a `.cl` file.
    cl::Program::Sources srcs(1, std::make_pair(src.c_str(), src.length()+1));
    cl::Program program(context, srcs); // To build the program, we need to specify the sources and context.

    auto err = program.build("-cl-std=CL1.2"); // Compile the program with `build`.

    if(CL_BUILD_SUCCESS != err)
        std::cout << "OpenCL -> Build faild.\n";

    char buff[16]; // Host memory

    cl::Buffer mem(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buff)); // There are lots of buffer flags.
    cl::Kernel kernel(program, "HelloWorld", &err);

    kernel.setArg(0, mem);

    cl::CommandQueue queue(context, device);
    queue.enqueueTask(kernel);
    queue.enqueueReadBuffer(mem, CL_TRUE, 0, sizeof(buff), buff);

    std::cout << buff;
}