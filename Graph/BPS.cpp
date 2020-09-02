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

#include "BPS.h"

namespace BPS {

    Data::Data(std::string key, std::string value) {
        this->key = key;
        this->value = value;
    }

    Data::~Data() {
        key.~basic_string();
        value.~basic_string();
    }

    std::string Data::getKey() {
        return key;
    }

    void Data::setKey(std::string key) {
        this->key = key;
    }

    std::string Data::getValue() {
        return value;
    }

    void Data::setValue(std::string value) {
        this->value = value;
    }

    Section::Section(std::string name, std::vector<Data*> data) {
        this->name = name;
        this->data = data;
    }

    Section::Section(std::string name) {
        this->name = name;
        data = std::vector<Data*>();
    }

    Section::~Section() {
        name.~basic_string();
        data.~vector();
    }

    bool Section::add(Data* data) {
        if (!exists(data->getKey())) {
            this->data.push_back(data);
            return true;
        }
        return false;
    }

    void Section::removeAll() {
        data.clear();
    }

    bool Section::remove(std::string key) {
        for (auto i = 0; i < data.size(); i++) {
            if (data[i]->getKey()._Equal(key)) {
                // verificar se está apagando a pos certa
                data.erase(data.begin() + i);
                return true;
            }
        }
        return false;
    }

    std::vector<Data*> Section::findAll() {
        return data;
    }

    Data* Section::find(std::string key) {
        for (auto d : data) {
            if (d->getKey()._Equal(key)) {
                return d;
            }
        }
        return nullptr;
    }

    bool Section::exists(std::string key) {
        return find(key) != nullptr;
    }

    std::string Section::getName() {
        return name;
    }

    void Section::setName(std::string name) {
        this->name = name;
    }

    File::File(std::vector<Section*> sections) {
        this->sections = sections;
    }

    File::File() {
        sections = std::vector<Section*>();
    }

    File::~File() {
        sections.~vector();
    }

    bool File::add(Section* section) {
        if (!exists(section->getName())) {
            this->sections.push_back(section);
            return true;
        }
        return false;
    }

    void File::removeAll() {
        sections.clear();
    }

    bool File::remove(std::string key) {
        for (auto i = 0; i < sections.size(); i++) {
            if (sections[i]->getName()._Equal(key)) {
                // verificar se está apagando a pos certa
                sections.erase(sections.begin() + i);
                return true;
            }
        }
        return false;
    }

    std::vector<Section*> File::findAll() {
        return sections;
    }

    Section* File::find(std::string name) {
        for (auto s : sections) {
            if (s->getName()._Equal(name)) {
                return s;
            }
        }
        return nullptr;
    }

    bool File::exists(std::string name) {
        return find(name) != nullptr;
    }

    std::vector<std::string> split(std::string str, char sc) {
        auto strings = std::vector<std::string>();
        std::string sstr = "";
        for (auto c : str) {
            if (c == sc) {
                strings.push_back(sstr);
                sstr = "";
                continue;
            }
            sstr += c;
        }
        strings.push_back(sstr);
        return strings;
    }

    std::string trim(std::string str) {
        auto s = 0, c = 0;
        for (auto i = 0; i < str.size(); i++) {
            if (str[i] != ' ') {
                s = i;
                break;
            }
        }
        for (auto i = str.size(); i > 0; i--) {
            if (str[i - 1] != ' ') {
                c = i - s;
                break;
            }
        }
        return str.substr(s, c);
    }

    std::string normalizePath(std::string path) {
        auto length = path.size();
        if (length > 4) {
            if (!path.substr(length - 4, 4)._Equal(EXTENSION)) {
                return path + EXTENSION;
            }
            else {
                return path;
            }
        }
        else if (path._Equal(EXTENSION)) {
            return path;
        }
        else {
            return path + EXTENSION;
        }
    }

    std::string removeComments(std::string str) {
        auto r = split(str, KV_CMT_CHAR);
        r[0] = trim(r[0]);
        return r[0];
    }

    File* read(std::string path) {
        auto rawData = std::vector<std::string>();
        auto rawSections = std::vector<std::vector<std::string>>();
        auto sections = std::vector<Section*>();
        auto open = false;
        std::string line;

        std::ifstream f;
        f.open(normalizePath(path));

        while (!f.eof()) {
            getline(f, line);

            // Ignora as linhas vazias
            if (line._Equal(KV_VOID))
                continue;
            // Remove espaços em branco
            if (line.at(0) == KV_SPC)
                line = trim(line);
            // Remove comentários
            line = removeComments(line);
            // Caso houvesse linhas com apenas comentários, seria removida
            if (line._Equal(KV_VOID))
                continue;
            // Remove espaços em branco
            if (line.at(0) == KV_SPC)
                line = trim(line);
            // Caso ainda haja comentários, termina de remover
            if (line.at(0) == KV_CMT_CHAR)
                continue;
            // Caso ainda sobre alguma linha vazia
            line = trim(line);
            if (line._Equal(KV_VOID))
                continue;
            if (line.at(0) == KV_CTAB)
                if (line.size() > 1) {
                    line = line.substr(1, line.size() - 1);
                }
                else {
                    continue;
                }
            // Se a linha passou por todas as verificações é adicionada às linhas válidas
            rawData.push_back(line);

        }
        f.close();

        // Procura nos dados brutos, as seções
        for (auto d : rawData) {
            // Encontrou a tag de abrir seção
            if (d.at(0) == KV_LAB_CHAR) {
                // Se encontra uma tag de abrir seção mas ela já foi aberta
                if (open) {
                    return nullptr;
                }
                else {
                    open = true;
                }
            }
            // Encontrou a tag de fechar seção
            if (d._Equal(KV_RAB_STR)) {
                // Se encontra uma tag de fechar seção mas ela não foi aberta
                if (!open) {
                    return nullptr;
                }
                else {
                    rawSections.push_back(std::vector<std::string>());
                    open = false;
                }
            }

        }

        // Loop para cada seção encontrada anteriormente
        for (auto i = 0; i < rawSections.size(); i++) {
            // Passa todas as linhas cruas para o rawSection
            while (true) {
                auto curLine = rawData[0];
                rawData.erase(rawData.begin());
                rawSections[i].push_back(curLine);
                if (curLine._Equal(KV_RAB_STR)) break;
            }
        }

        // Percorre rawSections criando as variáveis
        for (auto rawSection : rawSections) {
            // Remove qualquer linha que não começe com '<'
            while (!rawSection[0].at(0) == KV_LAB_CHAR) {
                rawSection.erase(rawSection.begin());
            }
            for (auto rsLines : rawSection) {
                // Se estiver abrindo a seção
                if (rsLines.at(0) == KV_LAB_CHAR) {
                    auto ns = rsLines.substr(1, rsLines.size() - 1);
                    sections.push_back(new Section(ns));
                    continue;
                }
                // Encontrou o fim da seção
                if (rsLines._Equal(KV_RAB_STR)) {
                    break;
                }
                // Senão entrou em nenhum if anterior, significa que é uma key/value e será adicionada a seção
                // Divide pelo ':'
                auto r = split(rsLines, KV_SEP_CHAR);
                // Cria um novo dado com key e data
                sections[sections.size() - 1]->add(new Data(r[0], r[1]));
            }
        }

        return new File(sections);
    }

    void write(File* file, std::string path) {
        std::ofstream wf;
        wf.open(normalizePath(path));

        wf << HEADER + KV_NL + KV_NL;

        for (Section* s : file->findAll())
        {
            wf << KV_LAB_CHAR + s->getName() + KV_NL;
            for (Data* d : s->findAll())
            {
                wf << KV_TAB + d->getKey() + KV_SEP_CHAR + d->getValue() + KV_NL;
            }
            wf << KV_RAB_CHAR + KV_NL + KV_NL;
        }
        wf.close();
    }
}
