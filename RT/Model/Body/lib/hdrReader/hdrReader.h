#ifndef _HDR_H
#define _HDR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <OpenCL/OpenCL.h>

cl_float3	*read_hdr(const char *filename, int *w, int *h);

#endif