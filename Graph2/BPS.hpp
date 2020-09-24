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

#ifndef BPS_H
#define BPS_H

#include <string>
#include <vector>
#include <fstream>
#include <ctype.h>

#include "util.hpp"

namespace BPS
{
    class Data
    {
    private:
        std::string key;
    public:
        Data(std::string);
        virtual ~Data();
        std::string getKey();
        void setKey(std::string);
    };

    class StringData : public Data
    {
    private:
        std::string value;
    public:
        StringData(std::string, std::string);
        ~StringData();
        std::string getValue();
        void setValue(std::string);
    };

    class CharData : public Data
    {
    private:
        char value;
    public:
        CharData(std::string, char);
        ~CharData();
        char getValue();
        void setValue(char);
    };

    class BoolData : public Data
    {
    private:
        bool value;
    public:
        BoolData(std::string, bool);
        ~BoolData();
        bool getValue();
        void setValue(bool);
    };

    class IntData : public Data
    {
    private:
        int value;
    public:
        IntData(std::string, int);
        ~IntData();
        int getValue();
        void setValue(int);
    };

    class DoubleData : public Data
    {
    private:
        double value;
    public:
        DoubleData(std::string, double);
        ~DoubleData();
        double getValue();
        void setValue(double);
    };

    class ArrayData : public Data
    {
    private:
        std::vector<Data*> value;
    public:
        ArrayData(std::string, std::vector<Data*>);
        ~ArrayData();
        std::vector<Data*> getValue();
        void setValue(std::vector<Data*>);
    };

    class Section
    {
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

    class File
    {
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

    std::string normalizePath(std::string);
    std::string removeComments(std::string);

    File* read(std::string);
    void write(File*, std::string);

    // token
    bool isToken(std::string);
    bool isOpenToken(std::string);
    bool isCloseToken(std::string);

    // parser
    std::vector<std::string> lexer(std::string);

    bool isString(std::string);
    bool isChar(std::string);
    bool isBool(std::string);
    bool isNumeric(std::string);
    bool isInt(std::string);
    bool isDouble(std::string);
    bool isArray(std::string);

    std::string parseString(std::string);
    char parseChar(std::string);
    bool parseBool(std::string);
    int parseInt(std::string);
    double parseDouble(std::string);
    template <typename T>
    Data* parseData(std::string, std::string);

    template <typename T>
    std::vector<Section*> parser(std::vector<std::string>);

    template <typename T>
    File* compile(std::string);
}

#endif // BPS_H
