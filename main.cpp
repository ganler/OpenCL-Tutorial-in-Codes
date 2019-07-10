#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>

decltype(auto) program_builder(
        const std::string& file_name,
        const std::size_t Dev = CL_DEVICE_TYPE_ALL,
        const std::size_t Pind = 0,
        const std::size_t Dind = 0)
{
    static std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    static std::vector<cl::Device> devices;

    const auto& platform = platforms.at(Pind);
    platform.getDevices(Dev, &devices);

    const auto& device = devices.at(Dind);
    // Build the context.
    cl::Context context(device);

    std::ifstream kernel_file(file_name);
    static std::string src;
    src = std::move(static_cast<std::stringstream const&>(std::stringstream{} << kernel_file.rdbuf()).str());

    static cl::Program::Sources srcs(1);
    srcs[0] = std::make_pair(src.c_str(), src.length()+1);
    cl::Program program(context, srcs);

    auto err = program.build("-cl-std=CL1.2");
    if(CL_BUILD_SUCCESS != err)
        std::cout << "OpenCL -> Build faild. === error code is " << err << '\n';
    return std::make_tuple(program, context, device);
}

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