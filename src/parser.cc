#include "parser.h"
#include <memory>
#include <sstream>
#include <string>
#include <utility>

using std::istringstream;

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

const std::string RawEvent::show() const {
    std::string str = "RawEvent {" + header_.show() + ",[";
    for (const auto& o : objects_) {
        str += o.show() + ",";
    }
    str.pop_back();
    str += "]}";
    return str;
}

Object GetObj(std::unique_ptr<istringstream> iss, const int& typ) {
    Object obj;
    obj.typ = typ;
    *iss >> obj;
    return obj;
}

RawEvent ParseRawEvent(std::istream *is) {
    std::string line;
    Header header;
    Objects objs;
    RawEvent lhco;

    while (std::getline(*is, line)) {
        if (line.find("#") == std::string::npos) {
            std::unique_ptr<std::istringstream> iss(new istringstream(line));
            int first_digit = 0, second_digit = 0;
            *iss >> first_digit >> second_digit;
            if (first_digit == 0) {  // line for event header
                header.event_number = second_digit;
                *iss >> header;
            } else if (second_digit < 6) {
                Object obj = GetObj(std::move(iss), second_digit);
                objs.push_back(obj);
            } else if (second_digit == 6) {  // line for missing energy
                Object obj = GetObj(std::move(iss), second_digit);
                objs.push_back(obj);
                lhco.set_event(header, objs);
                break;
            } else {  // undefined line
                lhco(RawEvent::EventStatus::Empty);
                break;
            }
        } else {  // comment line
            continue;
        }
    }

    return lhco;
}
}  // namespace lhco
