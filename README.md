
#  MoTo - Motion Toolkit

MoTo is a software library written in C++ and contains class and
function templates that are useful for animation and simulation of
rigid bodies. MoTo evolved while being applied in SOLID, the software
library for interference detection, as well as numerous other project
involving graphics and physics.

A proper set of documentation is still pending, however I would like
to give a preview of MoTo's features and peculiarities.

First of all, since MoTo is composed of headers only, there is no need to build
and link a library. All class and function templates are fully inlined. 
 
Secondly, MoTo tries to mimic the Cg shader language as much as possible. This
shows in the naming of functions, e.g. `normalize` and `saturate`, but also in
the use of `operator*`. In MoTo `operator*` is always component-wise. For
algebraic products such as a quaternion or matrix product, MoTo uses an
overloaded global `mul` function. So beware

```
mt::Matrix3x3<float> a, b, c;
...
c = a * b; // performs a component-wise multiply
c = mul(a, b); // performs a matrix product
```

Component-wise multiplies of matrix types (`operator*`) are disabled by default
in order to avoid confusion with other matrix libraries where `operator*` is used as algabraic product. You can enable component-wise products by setting

```
#define USE_MATRIX_COMP_MULT 1
```

before including the MoTo header.
 

There is no dedicated quaternion class. In order to represent a quaternion,
simply use `mt::Vector4`. Again beware   

```
mt::Vector4<float> a, b, c;
...
c = a * b; // performs a component-wise multiply e.g. color modulate
c = mul(a, b); // performs a quaternion product
```

MoTo has a number of types that do not hold any values but are used to change
the behavior of constructors, operators and functions. These are

```
struct Zero; // The algebraic zero
struct Identity; // The identity for operator "mul"
template <int> struct Unit; // The i-th unit vector
```

See Algebra.hpp for a definition of these types.


Functions that involve a metric such as `distance` and `normalize` are found in
Metric.hpp. These function templates use a `dot` function and are generic for
all vector types.

Functions that involve angles such as `slerp` and `euler` are found in
Trigonometric.hpp. 

`mt::Vector4` and `mt::Matrix4x4` have specializations for `float` on an ia32 or
emt64 (amd64) platform. The specializations are implemented using SSE
intrinsics. See Vector4_SSE.hpp and Matrix4x4_SSE.hpp for details.


A dual number class is defined in Dual.hpp. Pluecker coordinates, spatial
vectors, and motor algebra requires DualVector3.hpp. Dual quaternions can be
created using DualVector4.hpp. See my GDC Europe 2009
presentation "Dual Numbers. Simple Math, Easy C++ Coding, and Lots of Tricks"
for details.

Sample code on how to make use of mt::Dual and other classes can be found in
UnitTest.cpp


The directory 'jointlimits' holds the sample code accompanying Chapter 10
_Rotational Joint Limits in Quaternion Space_ of _Game Engine Gems 3_.
Please, refer to the source code and chapter for details. Documentation for
the jointlimits can be generated using Doxygen + graphpviz.


Installation
------------

MoTo itself can be readily used. For building consolid and the UnitTest.cpp
sample you need CMake 2.4 or up. Please, check the CMake documentation on how
to generate a MSVC project or makefiles for GCC.


Platforms
---------

MoTo has been tested on the following platforms:

    Linux 32-bit/64-bit  gcc 3.4
	Win32 32-bit/64-bit	 MSVC 8.0 SP1, 9.0 SP1, 10, 11, 12, 14

  

Good luck,


Gino van den Bergen
www.dtecta.com
