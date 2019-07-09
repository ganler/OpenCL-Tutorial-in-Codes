// Kernel function must:
// - use `__kernel` prefix;
// - Return type is `void`;
// - Take at least 1 argument.

// get_global_id() uniquely identifies each work item executing the kernel.
// get_local_id() uniquely identifies each work item in a work group.

__kernel void HelloWorld(__global char* data)
{
    data[0 ] = 'H' ;
    data[1 ] = 'E' ;
    data[2 ] = 'L' ;
    data[3 ] = 'L' ;
    data[4 ] = 'O' ;
    data[5 ] = '-' ;
    data[6 ] = 'W' ;
    data[7 ] = 'O' ;
    data[8 ] = 'R' ;
    data[9 ] = 'L' ;
    data[10] = 'D' ;
    data[11] = '!' ;
    data[12] = '\n';
    data[13] = '\0';  // You must have '\0' at the end of your string. Or you will not see any output answer at all.
}
