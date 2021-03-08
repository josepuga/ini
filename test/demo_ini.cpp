#include <iostream>
#include <string>
#include <vector>
#include "ini.hpp"

using namespace std;
int main()
{
    const string fileIni = "../test.ini";
    const string sectionName = "settings";

    Ini ini;
    if (!ini.LoadFromFile(fileIni)) {
        cerr << "Unable to load ini file " << fileIni << endl;
        return 1;
    }
    cout << "Checking " <<  sectionName << " section...\n";
    if (!ini.SectionExists(sectionName)) {
        cerr << sectionName << " section not found." << endl;
        return 1;
    }


    //TEST VALUES AS STRING
    cout << "\nTest values of section " << sectionName << " as strings:\n";
    vector<string> keys { "cheats", "player name", "use_joystick", "gamma", "fov"};

    for (auto key : keys) {
        cout << key << " = " << ini.GetValue(sectionName, key) << "\n"; //Implicit string type
    }

    //TEST VALUES AS DIFFERENT TYPES
    cout << "\nTest values of section " << sectionName << " as different types:\n";
    auto cheats = ini.GetValue<bool>(sectionName, "cheats");
    auto name = ini.GetValue<string>(sectionName, "player name");  //Explicit string type
    auto useJoy = ini.GetValue<bool>(sectionName, "use_joystick");
    auto gamma = ini.GetValue<float>(sectionName, "gamma", 1.0f); 
    auto fov = ini.GetValue<int>(sectionName, "fov", 75); //75 = Defaul value
    auto avatarColor = ini.GetValueHex<uint32_t>(sectionName, "avatar hex color");

    cout << "cheats (bool) = " << cheats << "\nplayer name (string) = " << 
        name << "\nuse_joystick (bool) = " << useJoy << "\ngamma (float) = " << 
        gamma << "\nfov (int) = " << fov << "\navatar hex color (uint32_t) = " <<
        avatarColor << endl;;


    //TEST SECTIONS
    cout << "\nTest present sections:\n";
    for (auto sec : ini.GetSections()) {
        if (sec == "") {
            cout << "There are keys without section!.\n";
        } else {
            cout << sec << "\n";
        }
    }


    //TEST NO SECTION VALUES AND DEFAULT VALUE
    cout << "\nTest values without section:\n";
    keys = {"version", "release date" , "not exists"};

    for (auto key : keys) {
        cout << key << " = " << ini.GetValue<string>("", key, "My default value!") << "\n";
    }

    //TEST SPLIT VALUES WITH SEPARATOR AND HEX
    cout << "\nTest split values with separator\n";
    //             WARNING: check always if vectors are empty
    vector<int> res1 = ini.GetSplitValues<int>(sectionName, "resolution", 'x');
    cout << "Resolution: Width = " << res1.at(0) << " and Height = " << res1.at(1) << "\n";

    //These values should be uint8_t but std::cout prints uint8_t like char. Just to avoid typecasting
    vector<uint32_t> res2 = ini.GetSplitValues<uint32_t>(sectionName, "flag rgb color", ',', 255); //255 = white
    cout << "Flag RGB Color (default is white) = " << res2.at(0) << ", " << res2.at(1) << ", " << res2.at(2) << "\n";

    vector<uint32_t> res3 = ini.GetSplitValuesHex<uint32_t>(sectionName, "avatar rgb color");
    cout << "Avatar RGB Color = " << res3.at(0) << ", " << res3.at(1) << ", " << res3.at(2) << "\n";
  
    return 0;
}
