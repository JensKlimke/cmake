#include <iostream>

#include <two/two.h>
#include <one/one.h>

#include <cxxopts.hpp>

int main(int argc, char* argv[]) {

    cxxopts::Options options("MyProgram", "One line description of MyProgram");

    options.add_options()
            ("d,debug", "Enable debugging") // a bool parameter
            ("i,integer", "Int param", cxxopts::value<int>())
            ("f,file", "File name", cxxopts::value<std::string>())
            ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
            ;


    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    bool debug = result["debug"].as<bool>();

    std::string bar;
    if (result.count("file"))
        bar = result["file"].as<std::string>();

    int foo = result["integer"].as<int>();

    std::cout << "debug: " << (debug ? "yes" : "no") << std::endl;
    std::cout << "bar: " << bar << std::endl;
    std::cout << "foo: " << foo << std::endl;

    one();
    two();

    std::cout << "Hello, World!" << std::endl;
    return 0;

}