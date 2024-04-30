#ifndef APT_H
#define APT_H

#include <string>
#include <unordered_map>

namespace APT {
    const int NUM_OF_APT {28};

    const std::unordered_map<int, std::string> APT_DICT {
        {0, "AMS"}, {1, "BCN"}, {2, "BGO"}, {3, "BRU"},
        {4, "CPH"}, {5, "DUB"}, {6, "DBV"}, {7, "EDI"},
        {8, "FRA"}, {9, "HEL"}, {10, "IST"}, {11, "LIS"},
        {12, "LHR"}, {13, "MAD"}, {14, "MAN"}, {15, "MXP"},
        {16, "MUC"}, {17, "NCE"}, {18, "OSL"}, {19, "PMO"},
        {20, "CDG"}, {21, "FCO"}, {22, "ARN"}, {23, "VCE"},
        {24, "VIE"}, {25, "WAW"}, {26, "ZAG"}, {27, "ZRH"}
    };
}

#endif
