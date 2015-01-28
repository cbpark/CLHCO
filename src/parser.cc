#include "parser.h"
#include <memory>
#include <sstream>
#include <string>
#include <utility>

using std::istringstream;

namespace lhco {
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
            std::unique_ptr<istringstream> iss(new istringstream(line));
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
                lhco(EventStatus::Empty);
                break;
            }
        } else {  // comment line
            continue;
        }
    }

    return lhco;
}
}  // namespace lhco
