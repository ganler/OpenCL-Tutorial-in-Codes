//
// Created by ganler-Mac on 2019/7/11.
//

#pragma once

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