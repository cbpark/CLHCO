#include <fstream>
#include <iostream>
#include "lhco.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: test_parse input\n"
                  << "    - input: Input file in "
                  << "LHC Olympics format\n";
        return 1;
    }

    std::ifstream filename(argv[1]);
    if (!filename) {
        std::cerr << "-- Cannot open input file \"" << argv[1] << "\".\n";
        return 1;
    } else {
        std::cout << "-- Reading \"" << argv[1] << "\" ...\n";
    }

    lhco::RawEvent lhco = lhco::ParseRawEvent(&filename);
    int num_eve = 0;
    for ( ; !lhco.empty(); lhco = lhco::ParseRawEvent(&filename)) {
        ++num_eve;
        std::cout << "-- Event number: " << num_eve << '\n'
                  << lhco.show() << '\n';
    }

    std::cout << "-- " << num_eve << " events parsed.\n";
    filename.close();
}
