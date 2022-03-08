/*
** EPITECH PROJECT, 2022
** nanotekspice
** File description:
** Circuit
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "Sequential.hpp"
#include <fstream>
#include <map>

namespace nts {
    class Circuit {
        typedef IComponent *(*componentCreator)(std::string);
        public:
            class ParsingException: public std::exception {
                public:
                    ParsingException(std::string file, int line, std::string msg):
                    _msg(file + ":" + std::to_string(line) + ": " + msg) {}
                    const char *what() const noexcept override
                    {
                        return _msg.data();
                    }
                private:
                    const std::string _msg;
            };
            Circuit(std::string filepath);
            ~Circuit();
            void parse();
            void simulate();
            void display() const;
            void dump() const;
            void assignInput(std::string target, std::string value);

        protected:
        private:
            int _lineNb;
            std::string _filename;
            std::ifstream _file;
            std::map<std::string, componentCreator> _availableComponents;
            std::map<std::string, std::unique_ptr<IComponent>> _components;
            class Line {
                public:
                    Line(int nb, std::string str):
                    _nb(nb), _str(str) {}
                    ~Line(){};
                    int getNb() const {return _nb;}
                    std::string getStr() const {return _str;}
                private:
                    int _nb;
                    std::string _str;
            };
            Line getLine();
            void createComponents();
            void linkComponent(Circuit::Line line);
            void addComponent(Circuit::Line line);
    };
}

#endif /* !PARSER_HPP_ */
