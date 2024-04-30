#include "FlightMap.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> askfromAndTo();

int main() {
    string filePath = "/Users/claudio/Desktop/School/LMC_CS/LMC_Courses/COMSC210_DataStructure/Semester_Project/Flight_Routes.csv";
    FlightMap flightMap = FlightMap(filePath);


    while (true) {
        vector<int> fromAndTo = askfromAndTo();
        flightMap.findCheapestByDijkstra(fromAndTo[0], fromAndTo[1]);
        flightMap.findShortestByDijkstra(fromAndTo[0], fromAndTo[1]);

        string input;
        cout << "Do you want to continue? Press Y for yes, any other for no: ";
        getline(cin, input);
        if (input != "Y" && input  != "y") break;
    }
    cout << "Thank you for using this program. Have a superior day!" << endl;
}

vector<int> askfromAndTo() {
    vector<int> fromAndTo;
    string aptCode = "\n\t\t<Code List of Airports>\n"
                     "\t\t 0: Amsterdam (AMS)     1: Barcelona (BCN)      2: Bergen (BGO)          3: Brussels (BRU)\n"
                     "\t\t 4: Copenhagen (CPH)    5: Dublin (DUB)         6: Dubrovnik (DBV)       7: Edinburgh (EDI)\n"
                     "\t\t 8: Frankfurt (FRA)     9: Helsinki (HEL)      10: Istanbul (IST)       11: Lisbon (LIS)\n"
                     "\t\t12: London (LHR)       13: Madrid (MAD)        14: Manchester (MAN)     15: Milan (MXP)\n"
                     "\t\t16: Munich (MUC)       17: Nice (NCE)          18: Oslo (OSL)           19: Palermo (PMO)\n"
                     "\t\t20: Paris (CDG)        21: Rome (FCO)          22: Stockholm (ARN)      23: Venice (VCE)\n"
                     "\t\t24: Vienna (VIE)       25: Warsaw (WAW)        26: Zagreb (ZAG)         27: Zurich (ZRH)\n";

    cout << aptCode << endl;

    string input;
    int choice;
    cout << "Please enter your origin airport by number: ";
    while (true) {
        getline(cin, input);
        stringstream convert(input);
        if (convert >> choice && choice >= 0 && choice <= APT::NUM_OF_APT-1) break;
        cout << "Invalid entry.. Please enter an integer between 0 and 10: ";
    }
    fromAndTo.push_back(choice);

    cout << "Please enter your destination airport by number: ";
    while (true) {
        getline(cin, input);
        stringstream convert(input);
        if (convert >> choice && choice >= 0 && choice <= APT::NUM_OF_APT-1 && choice != fromAndTo[0]) break;
        cout << "Invalid entry.. Please enter an integer between 0 and 10: ";
    }
    fromAndTo.push_back(choice);

    return fromAndTo;
}
