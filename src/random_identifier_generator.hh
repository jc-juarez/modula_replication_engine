// *************************************
// Modula Replication Engine
// Utilities
// 'random_identifier_generator.hh'
// Author: jcjuarez
// *************************************

#ifndef RANDOM_IDENTIFIER_GENERATOR_
#define RANDOM_IDENTIFIER_GENERATOR_

#include "utilities.hh"

#include <mutex>
#include <string>
#include <random>

namespace modula
{

//
// Random identifier generator utility class.
//
class random_identifier_generator
{

public:

    //
    // Constructor.
    //
    random_identifier_generator();

    //
    // Generates a double <8 bytes> random identifier.
    //
    std::string
    generate_double_random_identifier();

    //
    // Generates a triple <8 bytes> random identifier.
    //
    std::string
    generate_triple_random_identifier();

private:

    //
    // Generates a random 8 bytes number.
    //
    uint64
    generate_random_number();

    //
    // Lock for synchronizing access across threads.
    //
    std::mutex m_lock;

    //
    // Random number generator for random identifiers.
    //
    std::mt19937 m_random_number_generator;

    //
    // Distribution for random numbers generation.
    //
    std::uniform_int_distribution<uint64> m_random_number_distribution;
    
};

} // namespace modula.

#endif
