/*
 * MIT License
 *
 * Copyright (c) 2020 Carlos Eduardo de Borba Machado
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include <string>
#include <vector>
#include <fstream>

namespace BPS {
    const auto HEADER = "# BPS File";
    const auto EXTENSION = ".bps";
    const auto KV_TAB = "    ";
    const std::string KV_NL = "\n";
    const std::string KV_VOID = "";
    const std::string KV_LAB_STR = "<";
    const std::string KV_RAB_STR = ">";
    const std::string KV_SEP_STR = ":";
    const std::string KV_CMT_STR = "#";
    const char KV_SPC = ' ';
    const char KV_CTAB = '\t';
    const char KV_LAB_CHAR = '<';
    const char KV_RAB_CHAR = '>';
    const char KV_SEP_CHAR = ':';
    const char KV_CMT_CHAR = '#';

    class Data {
    private:
        std::string key;
        std::string value;
    public:
        Data(std::string, std::string);
        ~Data();
        std::string getKey();
        void setKey(std::string);
        std::string getValue();
        void setValue(std::string);
    };

    class Section {
    private:
        std::string name;
        std::vector<Data*> data;
    public:
        Section(std::string, std::vector<Data*>);
        Section(std::string);
        ~Section();
        bool add(Data*);
        void removeAll();
        bool remove(std::string);
        std::vector<Data*> findAll();
        Data* find(std::string);
        bool exists(std::string);
        std::string getName();
        void setName(std::string);
    };

    class File {
    private:
        std::vector<Section*> sections;
    public:
        File(std::vector<Section*>);
        File();
        ~File();
        bool add(Section*);
        void removeAll();
        bool remove(std::string);
        std::vector<Section*> findAll();
        Section* find(std::string);
        bool exists(std::string);
    };

    std::vector<std::string> split(std::string, char);
    std::string trim(std::string);
    std::string normalizePath(std::string);
    std::string removeComments(std::string);

    File* read(std::string);
    void write(File*, std::string);
}
