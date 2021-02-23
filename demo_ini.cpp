#include <iostream>
#include <string>
#include <vector>
#include "ini.h"

using namespace std;

int main() 
{
    const string fileIni = "../test.ini";
    const string sectionName = "settings";

    Ini myIni;
    if (!myIni.LoadFromFile(fileIni)) {
        cerr << "Unable to load ini file " << fileIni << endl;
        return 1;
    }
    cout << "Checking " <<  sectionName << " section...\n";
    if (!myIni.SectionExists(sectionName)) {
        cerr << sectionName << " section not found." << endl;
        return 1;
    }

    //TEST VALUES AS STRING
    cout << "\nTest values of section " << sectionName << " as strings:\n";
    vector<string> keys { "cheats", "player name", "use_joystick", "gamma", "fov"};
    for (auto key : keys) {
        cout << key << " = " << myIni.GetValueString(sectionName, key) << "\n";
    }

    //TEST VALUES AS REAL TYPES
    cout << "\nTest values of section " << sectionName << " as REAL TYPES:\n";
    bool cheats = myIni.GetValueBool(sectionName, "cheats");
    string name = myIni.GetValueString(sectionName, "player name");
    bool useJoy = myIni.GetValueBool(sectionName, "use_joystick");
    float gamma = myIni.GetValueFloat(sectionName, "gamma");
    int fov = myIni.GetValueInt(sectionName, "fov");
    cout << "cheats (bool) = " << cheats << "\nplayer name (string) = " << 
        name << "\nuse_joystick (bool) = " << useJoy << "\ngamma (float) = " << 
        gamma << "\nfov (int) = " << fov << "\n";

    //TEST SECTIONS
    cout << "\nTest present sections:\n";
    for (auto sec : myIni.GetSections()) {
        if (sec == "") {
            cout << "There are keys without section!.\n";
        } else {
            cout << sec << "\n";
        }
    }

    //TEST NO SECTION VALUES
    cout << "\nTest values without section:\n";
    keys = {"version", "release date" , "not exists"};
    for (auto key : keys) {
        cout << key << " = " << myIni.GetValueString("", key, "My default value!") << "\n";
    }

}  