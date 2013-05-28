Quart
=====

Quart is a modern C++11 Winapi wrapper that aims to provide a simple way of creating GUIs for your applications.

Unlike Qt/wxWidgets and other libraries, Quart uses a callback system which in combination with lambdas lead to easy to read and concise code.

Installation
============

First of all you will need a compiler that supports C++11:

- MSVC11 ( provided by Visual Studio 2012 )
- GCC ( 4.4+ )
- ICC ( 12.1+ )

Actual installation is rather easy, just add the path to the 'Quart' folder to your include path:

***Code::Blocks***

Build options -> Search directories -> Compiler

***Visual Studio***

Project proprieties -> Configuration proprieties -> C/C++ -> Additional include directories


And that's it ! You can now use Quart ! (start by compiling the example)

API Refference
==============

***Classes***

<pre>Window</pre>

*Parameters*
- width  (unsigned int)
- height (unsigned int) 
- title  (string)
- parent (Window* = nullptr)