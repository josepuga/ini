/*
MIT License

Copyright (c) 2020-2021 José Puga

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

#ifndef INI_H
#define INI_H
#define INI_H_VERSION "0.9.1"

#include <string>
#include <utility>
#include <vector>
#include <map>

namespace ini {
    typedef std::pair<std::string, std::string> keyvalue_t;
    typedef std::multimap<std::string, keyvalue_t> sections_t;
}

class Ini
{
public:
    Ini();

    /**
     * @brief Load all data from the file.
     * @param fileName.
     * @return true if success.
     * */
    bool LoadFromFile(const std::string& fileName);

    /**
     * @brief Returns the file name of the last LoadFromFile() call.
     * @return file name.
     * */
    inline const std::string& GetFileName() const {return m_fileName;}

    /**
     * @brief Return the value's section as string
     * @param section. "" for no section.
     * @param key.
     * @param default (optional) default value if is not set.
     * @return value.
     * */
    std::string GetValueString(const std::string& section, const std::string& key, 
                    const std::string def = "") const;

    /**
     * @brief Return the value's section as int
     * @param section. "" for no section.
     * @param key.
     * @param default (optional) default value if is not set or error converting.
     * @return value.
     * */
    int GetValueInt(const std::string& section, const std::string& key, 
            const int def = 0) const;

    /**
     * @brief Return the value's section as float
     * @param section "" for no section.
     * @param key.
     * @param default (optional) default value if is not set or error converting.
     * @return value.
     * */
    float GetValueFloat(const std::string& section, const std::string& key, 
            const float def = 0.0) const;

    /**
     * @brief Return the value's section as bool
     * @param section "" for no section.
     * @param key.
     * @param default (optional) default value if is not set or value <> (0, 1, false, true)
     * @return value.
     * */
    bool GetValueBool(const std::string& section, const std::string& key, 
            const bool def = false) const;

    /**
     * @brief Return a vector of string splitting the value with a separator
     * @param section "" for no section.
     * @param key.
     * @param separator (optional) separator to split the values. Defaul is comma ','.
     * @param default (optional) default value if an element is an empty string. 
     * @return vector with values or empty if the key is empty or doesnt exists.
     * */
    std::vector<std::string> GetSplitValuesString(const std::string& section, const std::string& key, 
                        const char sep = ',', const std::string& def = "");

    /**
     * @brief Return a vector of int splitting the value with a separator
     * @param section "" for no section.
     * @param key.
     * @param separator (optional) separator to split the values. Defaul is comma ','.
     * @param default (optional) default value if an element has an error converting
     * @return vector with values or empty if the key is empty or doesnt exists.
     * */
    std::vector<int> GetSplitValuesInt(const std::string& section, const std::string& key, 
                        const char sep = ',', const int def = 0);

    /**
     * @brief Return a vector of float splitting the value with a separator
     * @param section "" for no section.
     * @param key.
     * @param separator (optional) separator to split the values. Defaul is comma ','.
     * @param default (optional) default value if an element has an error converting
     * @return vector with values or empty if the key is empty or doesnt exists.
     * */
    std::vector<float> GetSplitValuesFloat(const std::string& section, const std::string& key, 
                        const char sep = ',', const float def = 0.0);

    /**
     * @brief Return a vector of bool splitting the value with a separator
     * @param section "" for no section.
     * @param key.
     * @param separator (optional) separator to split the values. Defaul is comma ','.
     * @param default (optional) default value if an element has an error converting
     * @return vector with values or empty if the key is empty or doesnt exists.
     * */
    std::vector<bool> GetSplitValuesBool(const std::string& section, const std::string& key, 
                        const char sep = ',', const bool def = false);

    /**
     * @brief Check if the section exist
     * @param section name.
     * @return true if success.
     * */
    bool SectionExists(const std::string& section) const;

    //TODO: bool KeyExists(const std::string& section, const std::string& key) const; 

    /**
     * @brief Gets all the sections names.
     * NOTE: if one or more keys are outside section a new section named "" will be created.
     * @return vector of strings with all the sections names.
     * */
    std::vector<std::string> GetSections();

    //TODO: ini::keyvalue_t GetSectionValues(const std::string& section) const; 

private:
    std::string GetValue(const std::string& section, const std::string& key) const;
    void ParseLines();
    void Trim(std::string&);

    bool IfLineIsSectionSet(const std::string& lin, std::string& sec);
    bool IfLineIsKeySet(const std::string& lin, std::string& key, std::string& val);
    bool LineIsComment(const std::string& lin); //Not jet implemented.

    std::string m_fileName;
    std::vector<std::string> m_linesBuffer;
    //std::vector<std::string> m_comments;
    ini::sections_t m_sections;
};
#endif // INI_H
