#include <fstream>
#include <iostream>
#include "lhco.h"

double InvMass(const lhco::Event& lhco) {
    double invmass = 0.0;
    if (NumMuon(lhco) == 1 && NumBjet(lhco) == 1) {
        lhco::Visibles ps;
        ps.push_back(lhco.muon().front());
        ps.push_back(lhco.bjet().front());
        invmass = InvariantMass(ps);
    }
    return invmass;
}

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

    lhco::Event lhco = lhco::ParseEvent(&filename);
    lhco::Pt ptcut(30.0);
    lhco::Eta etacut(2.0);
    int num_eve = 0;
    for ( ; !lhco.empty(); lhco = lhco::ParseEvent(&filename)) {
        ++num_eve;
        std::cout << "-- Event number: " << num_eve << '\n'
                  << lhco.show() << '\n';
        std::cout << "---- Missing ET = " << MissingET(lhco) << '\n';
        std::cout << "---- Before cut:\n------ ";
        std::cout << "# of photons: " << NumPhoton(lhco) << ", "
                  << "electrons: " << NumElectron(lhco) << ", "
                  << "muons: " << NumMuon(lhco) << ", "
                  << "taus: " << NumTau(lhco) << ", "
                  << "all jets: " << NumAllJet(lhco) << ", "
                  << "bjets: " << NumBjet(lhco) << '\n'
                  << "------ Invariant mass of muon and b-jet = "
                  << InvMass(lhco) << '\n';
        std::cout << "---- After cut:\n------ ";
        std::cout << "# of photons: " << NumPhoton(ptcut, etacut, lhco) << ", "
                  << "electrons: " << NumElectron(ptcut, etacut, lhco) << ", "
                  << "muons: " << NumMuon(ptcut, etacut, lhco) << ", "
                  << "taus: " << NumTau(ptcut, etacut, lhco) << ", "
                  << "all jets: " << NumAllJet(ptcut, etacut, lhco) << ", "
                  << "bjets: " << NumBjet(ptcut, etacut, lhco) << '\n';
    }

    std::cout << "-- " << num_eve << " events parsed.\n";
    filename.close();
}
