Potion
=====

Potion is a very lightweight and somewhat high-performance HTTP microframework. Potion provides the barebones features for a comprehensive web application in a featherweight package. Potion was inspired by Python's Flask microframework.

**Please do not use this for any serious or commercial applications; bad things will happen if you do. It was just a small thing I wrote for fun because I was bored over the summer.**

Important Notes
---------------

Potion ONLY works on UNIX-based Operating Systems.

It also uses C++20.

I am lazy so the binary in the /bin directory is the latest release.

Coming Soon
-----------

Sessions


Installing and Setting Up
-----------------------

Download the compiled binary for your architecture in the /bin folder.

You will need to install the `boost`_ library as Potion uses the boost/json parser and serializer.

Download the boost tarfile and unzip.


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

Return Values
-------------

To return anything from the handler function, use the given return methods in the Response object. They are defined as follows:

.. code-block:: C++

    route_struct_t send_string(std::string str); //returns a string
    route_struct_t send_status_code(int status_code); //returns HTTP status code and nothing else
    route_struct_t send_file(std::string file_path, std::string content_type); //sends a file
    route_struct_t serve_static_file(std::string file_path); //sends the file found in the /static file folder
    route_struct_t send_json(boost::json::object obj); //sends a boost/json object

Other methods on the Response class:

.. code-block:: C++ 

    void set_header(std::string key, std::string value); //sets a response header to a value


The Request
-----------

Here are the methods for the Request class:

.. code-block:: C++

    std::map<std::string, std::string> get_headers(); //returns the request headers
    boost::json::object get_json(); //parses and returns any json value in request **ONLY WORKS WITH application/json CONTENT-TYPE**
    std::map<std::string, std::string> get_args(); //returns the query parameters
    
    receive_struct_t get_request_buffer(); //returns the request buffer
    //receive_struct_t is defined as:
    typedef struct {
        std::vector<std::byte>* buffer;
        size_t bytes_read;
    }

    size_t get_content_start_index(); //gets the index of the byte where the content of the request starts in the request buffer


App Configurations
-------------------

.. code-block:: C++

    std::map<std::string, std::variant<std::string, int>> config;

Configs: 

.. code-block:: C++

    app.config["READ_TIMEOUT"] = int; //number of seconds before connection closes with no activity. DEFAULT 30
    app.config["READ_SIZE"] = int; //"chunk" size of reading from request in kilobytes (1028 bytes). DEFAULT 2
    app.config["READ_SIZE_MAX"] = int; //maximum allowed number of kilobytes to be read from request. DEFAULT 512

    app.config["STATIC_FOLDER"] = std::string; //set the directory path from where app serves static files DEFAULT /static


A Simple App
----------------

.. code-block:: C++

    route_struct_t handle_get_home(PotionApp* app, Request* request, Response* response) {
      return response->send_string("Hello, World!");
    }
  
    int main () {
      
      int port = 8080;
      PotionApp app(port);

      app.set_get("/", &handle_get_home);
      app.run();
      return 0;
      
    }
    

.. code-block:: text

    $ g++ -std=c++20 -I./boostlib -L./bin -lpotion_arm64 app.cpp -o myapp
    $ ./myapp


Contributing
------------

Open a pull request and it will be looked at.

Issues
------

If there are any issues at all - serious or minor - please bring it up in the issues section 
