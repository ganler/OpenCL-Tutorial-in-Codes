#define CL_HPP_TARGET_OPENCL_VERSION 120 // This is important. Or u'll get a warning.

// There are many versions of OpenCL: 1.0 ~ 1.1 ~ 1.2 ~ [2.0 ~ 2.1 ~ 2.2]

// But you cannot use any kinds of versions in "[]". Because NVIDIA doesn't want u to ...
// NVIDIA has its own CUDA ... Though it does supported some of the versions ...
// So if you want to enjoy the `cross-platform` ability, u'd better use older versions.

#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

// I just personaly prefer C++ language to C.
// To use c++ as front, you need download cl.hpp / cl2.hpp(if you're using opencl2+)
// To get cl.hpp for your OpenCL 1.x, just go to https://www.khronos.org/registry/OpenCL/api/2.1/cl.hpp

#include<iostream>

int main()
{
    std::vector<cl::Platform> platforms;
    // Copies on cl::Platforms are inexpensive, since they don't 'own' 
    // any underlying resources or data structures.
    cl::Platform::get(&platforms);
    std::cout << "[ Platform num: ]" << platforms.size() << '\n';

    for(const auto& platform : platforms)
    {
        std::cout << platform.getInfo<CL_PLATFORM_VERSION>() << '\n';
        std::vector<cl::Device> devices;
        platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

        std::cout << "\t>>> Device num: " << devices.size() << '\n';

        for(const auto& device : devices)
            std::cout << "\t\t" << device.getInfo<CL_DEVICE_VENDOR>() \
                      << '\t'  << device.getInfo<CL_DEVICE_VERSION>() << '\n';
    }
    
}