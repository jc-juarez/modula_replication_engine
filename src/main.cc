// *************************************
// Modula Replication Engine
// Core
// 'main.cc'
// Author: jcjuarez
// *************************************

#include "logger.hh"
#include "modula.hh"
#include "utilities.hh"

#include <memory>

int main(int argc, char** argv)
{
    using namespace modula;

    status_code status = status::success;

    //
    // Initialize singleton logger through lazy initialization.
    //
    logger::get_logger();

    std::unique_ptr<modula::modula> modula_replication_engine = std::make_unique<modula::modula>(
        status);

    if (status::failed(status))
    {
        throw_exception(std::format("<!> Modula Replication Engine initialization failed. Status={:#X}.",
            status));
    }

    forever {}
}
