
Potion
======

Potion is a very lightweight somewhat high performance web microframework for C++.
This is NOT made for any commercial or any serious use, and bad things will happen if done so.
It provides just enough features to make a somewhat comprehensive web application.
Potion was inspired by Python's flask microframework.

Notes:

Potion ONLY works on UNIX-based Operating Systems (so no windows :[ ).
Potiion uses C++20.


Coming Soon
-----------

Support for sessions
framework-level https
Database sessions


Installing and Setting Up
------------------------

Potion uses the boost/json library. Make sure to have `boost`_ installed.

In the /bin folder, you will find the compiled binaries for x86-64 and arm64 architectures. Download the right one.

Download the library and link it with your program when compiling.

.._boost: https://www.boost.org/doc/libs/1_82_0/more/getting_started/index.html

Use the
.. code-block:: text

  -I/path/to/boost/libary

  -L/folder/where/binary/lives

  -lpotion_arm64

compiler flags to link the potion and boost libraries with your app.

Usage
-----


  




