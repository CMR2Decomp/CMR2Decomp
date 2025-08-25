# CMR2Decomp Project

This is a very feable attempt at Colin Mcrae Rally 2.0 (PC) decompilation with the help of [reccmp](https://github.com/isledecomp/reccmp) from the Lego Island [isledecomp](https://github.com/isledecomp) folks.

This is being used to verify accuracy of functions/globals so far. A lot more is known in Ghidra, it's just not been put into this actual source project yet.

## Local Development

The solution file provided is for use with Visual Studio 2022 and the latest x86 targeting that it comes with. When writing code, keep in mind it needs to be compilable with MSVC6.0 so be careful with what `#include`s you use etc.

# GitHub Workflows

However, when pushing to this repository it is being compiled with the help of a portable version of [MSVC6.0](https://github.com/itsmattkc/MSVC600). Which we understand is probably the closest compiler we'll get to what was originally used. As you can see from the [reccmp output](https://cmr2decomp.github.io/CMR2Decomp/) the accuracy is much better than when it was compiled with modern day compilers.
