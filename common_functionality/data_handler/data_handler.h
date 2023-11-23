#ifndef S05_PROJECT_TEAM_SNABSQUAD_DATA_HANDLER_H
#define S05_PROJECT_TEAM_SNABSQUAD_DATA_HANDLER_H

#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>

class DataHandler {
public:
    using RawDataContainer = std::vector<std::string>;
    using PinsCOntainer = std::vector<Pin>;
    static inline std::string SplitReturnLeftPart(const std::string &string, const char delimiter = ':') {
        return string.substr(0, string.find(delimiter));
    }

    static inline std::string SplitReturnRightPart(const std::string &string, const char delimiter = ':') {
        return string.substr(string.find(':') + 2);
    }

    static RawDataContainer::iterator
    ReturnItrToElementByOption(DataHandler::RawDataContainer &dataContainer,
                               std::string userOption) {
        auto foundEl = std::find_if(dataContainer.begin(), dataContainer.end(), [&userOption](std::string &el) -> bool {
            std::string infoType = SplitReturnLeftPart(el);
            return infoType == userOption;
        });
        return foundEl;
    }
    static DataHandler::RawDataContainer ReturnNumericData(std::string &line) {
        std::vector<std::string> tokens;
        std::regex re("\\d+");
        std::sregex_token_iterator
                begin(line.begin(), line.end(), re),
                end;

        std::copy(begin, end, std::back_inserter(tokens));
        return tokens;
    }
};


#endif //S05_PROJECT_TEAM_SNABSQUAD_DATA_HANDLER_H
