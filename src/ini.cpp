/*
MIT License

Copyright (c) 2020 José Puga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <fstream>
#include <regex>
#include <iostream> //DEBUG only
#include <map>

#include "ini.h"

using namespace std;

Ini::Ini() {

}

bool Ini::LoadFromFile(const std::string &fileName)
{
    m_fileName = fileName;
    ifstream file;
    file.open(m_fileName);
    if (file.bad() || file.fail()) {
        return false;
    }
    m_sections.clear();
    m_linesBuffer.clear();
    for (string ln; getline(file, ln);) {
        Trim(ln);
        m_linesBuffer.push_back(ln);
    }
    file.close();

    ParseLines();
    return true;
}

bool Ini::SectionExists(const std::string& section) const {
    auto it = m_sections.find(section);
    return (it != m_sections.end());
}

std::vector<std::string> Ini::GetSections() {
    //https://stackoverflow.com/questions/11554932/how-can-i-get-all-the-unique-keys-in-a-multimap

    vector<string> result;
    for (auto it = m_sections.begin(); it != m_sections.end(); it = m_sections.upper_bound(it->first)) {
        result.push_back(it->first);
    }
    return result;
}

std::string Ini::GetValue(const std::string& section, const std::string& key) const {
    if (!SectionExists(section)) {
        return "";
    }
    auto range = m_sections.equal_range(section);
    for (auto it = range.first; it != range.second; it++) {
        if (std::get<0>(it->second) == key) {
            return std::get<1>(it->second);
        }
    }
    return "";
}

std::string Ini::GetValueString(const std::string& section, const std::string& key, const std::string def) const {
    std::string result;
    result = GetValue(section, key);
    if (result == "") {
        result = def;
    }
    return result;
}

int Ini::GetValueInt(const std::string& section, const std::string& key, const int def) const {
    int result;
    try {
        result = std::stoi(GetValue(section, key));
    } catch (std::invalid_argument& e) {
        result = def;
    }
    return result;
}

float Ini::GetValueFloat(const std::string& section, const std::string& key, const float def) const {
    float result;
    try {
        result = std::stof(GetValue(section, key));
    } catch (std::invalid_argument& e) {
        result = def;
    }
    return result;
}

bool Ini::GetValueBool(const std::string& section, const std::string& key, const bool def) const {
    auto val = GetValue(section, key);
    std::transform(val.begin(), val.end(), val.begin(), ::tolower);
    bool result = false;
    if (val == "true" || val == "1") {
        result = true;
    } 
    else if (val == "false" || val == "0") {
        result = false;
    } 
    else {
        result = def;
    }
    return result;
}

void Ini::ParseLines() {

    string sec, key, val, com;
    string sectionActive;

    for ( auto lin : m_linesBuffer) {
        if (lin.empty()) {
            continue;
        }
        if (IfLineIsSectionSet(lin, sec)) {
            sectionActive = sec;
            continue;
        }
        if (IfLineIsKeySet(lin, key, val)) {
            m_sections.insert(std::pair<string, ini::keyvalue_t>(sectionActive, std::make_pair(key, val)));
            continue;
        }
        if (LineIsComment(lin)) {
            continue;
        }
    }
}

bool Ini::IfLineIsSectionSet(const std::string& lin, std::string& sec) {
    bool result = (*lin.begin() == '[' && *(lin.end()-1) == ']');
    if (result) {
        sec = lin.substr(1, lin.length()-2);
        Trim(sec);
    }
    return result;
}

bool Ini::IfLineIsKeySet(const std::string& lin, std::string& key, std::string& val) {
    auto pos = lin.find("=");
    bool result = (pos != std::string::npos);
    if (! result) {
        return result;
    }
    key = lin.substr(0, pos);
    val = lin.substr(pos+1, lin.length());
    Trim(key);
    Trim(val);
    return result;
}

bool Ini::LineIsComment(const std::string& lin) {
    return (lin.at(0) == '#' || lin.at(0) == ';');
}

void Ini::Trim(std::string& s) {
    static std::regex e("^\\s+|\\s+$");
    //LTrim only std::regex_replace(s, std::regex("^\\s+"), "");
    //RTrim only std::regex_replace(s, std::regex("\\s+$"), "");
    s = std::regex_replace(s, e, "");
}
