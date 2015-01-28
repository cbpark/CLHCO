#include "object.h"
#include <iostream>

namespace lhco {
const std::string Header::show() const {
    return "Header {event_number=" + std::to_string(event_number)
        + ",trigger_word=" + std::to_string(trigger_word) + "}";
}

std::istream& operator>>(std::istream& is, Header& h) {
    is >> h.trigger_word;
    return is;
}

const std::string Object::show() const {
    std::string str = "Object {";
    str += "typ="    + std::to_string(typ);
    str += ",eta="   + std::to_string(eta);
    str += ",phi="   + std::to_string(phi);
    str += ",pt="    + std::to_string(pt);
    str += ",jmass=" + std::to_string(jmass);
    str += ",ntrk="  + std::to_string(ntrk);
    str += ",btag="  + std::to_string(btag);
    str += ",hadem=" + std::to_string(hadem) + "}";
    return str;
}

std::istream& operator>>(std::istream& is, Object& obj) {
    double ntrk, btag, dummy;
    is >> obj.eta
       >> obj.phi
       >> obj.pt
       >> obj.jmass
       >> ntrk
       >> btag
       >> obj.hadem
       >> dummy >> dummy;
    obj.ntrk = static_cast<int>(ntrk);
    obj.btag = static_cast<int>(btag);
    return is;
}
}  // namespace lhco
