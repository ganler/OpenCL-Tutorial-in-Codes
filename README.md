## Add `cl.hpp` to use C++ as your front end not C.

Add [cl.hpp](https://www.khronos.org/registry/OpenCL/api/2.1/cl.hpp) to your include directories.

- For linux: `sudo cp cl.hpp /usr/includes/CL`
- For OS X: Cancel SIP if you are in higher OS X version, then do the same thing with `/System/Library/Frameworks/OpenCL.framework/Headers`

## OpenCL Terms

- Platform     : Vendor specific OpenCL implementation. (platform -> compute units -> processing elements)
- Context      : The domain in which synchronization and memory management is defined.
    - A set of devices;
    - The memories accessible to those devices;
    - Command-queues used to schedule execution of kernels or operations on memory objs.
- Device       : Physical devices.
- Host         : The program running the OpenCL.
- Kernel       : Key computing function of your OpenCL program.
- Work item    : A unit of work executing a kernel.
- Work groups  : A collection of work items.
- Command queue: The only way to communicate with/control a device.
- Memory       : Local / global / private / constant
- Buffer       : Area of memory on the GPU.
- Compute unit : A work group + its local memory.

![](https://i.loli.net/2019/07/09/5d23f4b104cc792374.png)



## Ref

https://software.intel.com/sites/default/files/m/d/4/1/d/8/OpenCL-intro.pdf
https://www.youtube.com/watch?v=AJnIdwbP5jI&list=PLzy5q1NUJKCJocUKsRxZ0IPz29p38xeM-&index=3