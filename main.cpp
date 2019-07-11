#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "cl_tools.hpp"

#include <iostream>
#include <tuple>

int main()
{
    // To execute the program, we need context and device.
    auto [program, context, device] = program_builder("../kernels/helloworld.cl");

    char buff[16];
    cl::Buffer mem_buff(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(buff));
    cl::Kernel kernel(program, "HelloWorld");

    kernel.setArg(0, mem_buff); // A kernel is from a function(program). And it needs memory(mem_buff).

    cl::CommandQueue queue(context, device);
    queue.enqueueTask(kernel);
    queue.enqueueReadBuffer(mem_buff, CL_TRUE, 0, sizeof(buff), buff);

    std::cout << buff;
}