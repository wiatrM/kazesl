#include <google/protobuf/stubs/common.h>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/version.hpp>

#include <cstdlib>
#include <utility>
#include <stdexcept>
#include <memory>

#include <common/Logger.hpp>
#include <app/GeneralApp.hpp>

namespace po = boost::program_options;

void
printHelp(const po::options_description &desc)
{
    std::cerr
        << "kazesl [options] <command> <params>\n"
        << desc << std::endl
        << "Commands: \n"
           "     run <port>\n"
           "     help \n";
}

int
main(int argc, char *argv[])
{
    // Set program option list
    po::variables_map vm;
    po::options_description desc("Allowed options");

    desc.add_options()("help,h", "Display help message.")
        ("run,r", "Start network node.")
        ("quiet,q", "Quiet mode (without logs output to console/file)")
        ("verbose,v", "Verbose log mode")
        ("console,c", "Console print log mode");

    // Create positional options as parameters
    po::positional_options_description p;
    p.add("parameters", -1);

    // Try to parse the program options
    try
    {
        po::store(po::command_line_parser(argc, argv)
                      .options(desc)
                      .positional(p)
                      .run(),
                  vm);
        po::notify(vm);
    }
    catch (std::exception const &)
    {
        std::cerr << "Kaze-SL: Incorrect command line syntax." << std::endl;
        std::cerr << "Use '--help' for a list of options." << std::endl;
        return 1;
    }

    if (vm.count("help"))
    {
        printHelp(desc);
        return 0;
    }

    // Default severity
    kazeCommon::LogSeverity thresh = kazeCommon::LogSeverity::info;

    if (vm.count("quiet"))
        thresh = kazeCommon::LogSeverity::fatal;
    else if (vm.count("verbose"))
        thresh = kazeCommon::LogSeverity::trace;

    bool log_console = false;
    if (vm.count("console"))
        log_console = true;

    auto logger = std::make_unique<kazeCommon::Logger>(thresh, log_console);
    logger->initGeneralLogger();

    logger->debug("kazeCommon::Logger started.");

    // On run parameter or without parameters
    if (vm.count("run") or !vm.count("parameters"))
    {
        logger->info("Starting the kaze-sl node...");

        // Create general app, unique pointer to logger & config instances
        auto general_app = kazesl::create_GeneralApp(std::move(logger));

        if(!general_app->setup())
        {
            logger->fatal("Cannot set up the general application instance! Exiting...");
            return -1;
        }

        general_app->beforeStart();

        // Block and handle operations
        general_app->run();

        return 0;
    }

    return 0;
}
