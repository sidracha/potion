Potion
=====

Potion is a very lightweight and somewhat high-performance web microframework. It is NOT made for any serious or commercial applications,
and very bad things may happen if done so. Potion provides the barebones features for a comprehensive web application in a featherweight
package. Potion was inspired by Python's Flask microframework.

Important Notes
---------------

Potion ONLY works on UNIX-based Operating Systems.

It also uses C++20.

Coming Soon
-----------

Sessions


Installing and Setting Up
-----------------------

You will need to install the `boost`_ library as Potion uses the boost/json parser and serializer.


Use the 

.. code-block:: text

    -L/folder/where/compiled/library/lives
    -lpotion_arm64
    -I/path/to/boost/library

compiler flags when compiling your app. 

.. _boost: https://www.boost.org/doc/libs/1_82_0/more/getting_started/index.html

Usage
======

Initialize PotionApp object

.. code-block:: C++

    PotionApp app(int port);

Route Handling
---------------

To handle routes, first define a route handler function like so:

.. code-block:: C++

    route_struct_t handler_func (PotionApp* app, Request* request, Response* response) {
        //do stuff
    }

And then set the route and pass in a function pointer for the handler function and run the app:

.. code-block:: C++

    app.set_get("/", &handler_func);
    app.run();
    

A Simple App
----------------

.. code-block:: C++

    route_struct_t handle_get_home(PotionApp* app, Request* request, Response* response) {
      return send_string("Hello, World!");
    }
  
    int main () {
      
      int port = 8080;
      PotionApp app(port);

      app.set_get("/", &handle_get_home);
      app.run();
      return 0;
      
    }
    

.. code-block:: text

    g++ -std=c++20 -I./boostlib -L./bin -lpotion_arm64 app.cpp -o myapp
    ./myapp


