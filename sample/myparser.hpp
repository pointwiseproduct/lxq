#ifndef MYPARSER_HPP_
#define MYPARSER_HPP_

#include <functional>
#include <exception>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>

#include "lxq.hpp"
#include "mylexer.hpp"

namespace myparser{
    using semantic_data = lxq::semantic_data;

    // parser
    template<class Lexer, class SemanticDataProc>
    class parser{
    private:
        using term = int;
        using iterator = typename Lexer::iterator;
        using token_type = typename Lexer::token_type;
        using arg_type = std::vector<std::unique_ptr<semantic_data>>;
        using call_function = std::function<std::unique_ptr<semantic_data>(parser&, arg_type const&)>;

    public:
        // parsing_error
        class parsing_error : public std::runtime_error{
        public:
            parsing_error(iterator first, iterator last, std::size_t line_num, std::size_t char_num, std::size_t word_num) :
                std::runtime_error("parsing error."),
                first(first),
                last(last),
                line_num(line_num),
                char_num(char_num),
                word_num(word_num)
            {}

            parsing_error(parsing_error const &other) :
                std::runtime_error("parsing error."),
                first(other.first),
                last(other.last),
                line_num(other.line_num),
                char_num(other.char_num),
                word_num(other.word_num)
            {}

            iterator first, last;
            std::size_t line_num, char_num, word_num;
        };

    private:
        struct term_sequence_data{
            std::size_t norm;
            call_function call;
        };

        struct parsing_table_item{
            enum class enum_action{
                shift,
                reduce,
                accept
            };

            enum_action action;
            std::size_t num;
        };

        struct parsing_data{
            std::size_t first;
            std::map<std::size_t, std::pair<term, term_sequence_data>> n2r;
            std::map<std::size_t, std::map<term, parsing_table_item>> parsing_table;
            std::map<std::size_t, std::map<term, std::size_t>> goto_table;
        };

        static parsing_data const &parsing_data_storage(){
            auto init = [](){
                return parsing_data{
                    0, // first
                    // n2r
                    decltype(parsing_data::n2r){
                        std::make_pair(
                            0,
                            std::make_pair(-3, term_sequence_data{ 3, [](parser &p, arg_type const &arg){ return call_make_mlt(p, arg[0], arg[2]); } })
                        ),
                        std::make_pair(
                            1,
                            std::make_pair(-3, term_sequence_data{ 3, [](parser &p, arg_type const &arg){ return call_make_div(p, arg[0], arg[2]); } })
                        ),
                        std::make_pair(
                            2,
                            std::make_pair(-3, term_sequence_data{ 3, [](parser &p, arg_type const &arg){ return call_make_add(p, arg[0], arg[2]); } })
                        ),
                        std::make_pair(
                            3,
                            std::make_pair(-3, term_sequence_data{ 3, [](parser &p, arg_type const &arg){ return call_make_sub(p, arg[0], arg[2]); } })
                        ),
                        std::make_pair(
                            4,
                            std::make_pair(-3, term_sequence_data{ 2, [](parser &p, arg_type const &arg){ return call_make_inv(p, arg[1]); } })
                        ),
                        std::make_pair(
                            5,
                            std::make_pair(-3, term_sequence_data{ 3, [](parser &p, arg_type const &arg){ return call_identity(p, arg[1]); } })
                        ),
                        std::make_pair(
                            6,
                            std::make_pair(-3, term_sequence_data{ 1, [](parser &p, arg_type const &arg){ return call_identity(p, arg[0]); } })
                        ),
                        std::make_pair(
                            7,
                            std::make_pair(-2, term_sequence_data{ 0, [](parser &p, arg_type const &arg){ return std::unique_ptr<lxq::semantic_data>(nullptr); } })
                        ),
                        std::make_pair(
                            8,
                            std::make_pair(-2, term_sequence_data{ 3, [](parser &p, arg_type const &arg){ return call_print(p, arg[1]); } })
                        ),
                        std::make_pair(
                            9,
                            std::make_pair(-2, term_sequence_data{ 2, [](parser &p, arg_type const &arg){ return std::unique_ptr<lxq::semantic_data>(nullptr); } })
                        ),
                        std::make_pair(
                            10,
                            std::make_pair(-2, term_sequence_data{ 3, [](parser &p, arg_type const &arg){ return call_recover(p); } })
                        ),
                    },

                    // parsing_table
                    decltype(parsing_data::parsing_table){
                        std::make_pair(
                            0,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 7 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::reduce, 7 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 7 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::reduce, 7 }),
                                std::make_pair(2147483646, parsing_table_item{ parsing_table_item::enum_action::shift, 31 }),
                                std::make_pair(2147483647, parsing_table_item{ parsing_table_item::enum_action::reduce, 7 })
                            }
                        ),
                        std::make_pair(
                            3,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 8 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::shift, 3 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::shift, 28 })
                            }
                        ),
                        std::make_pair(
                            8,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 8 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::shift, 3 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::shift, 28 })
                            }
                        ),
                        std::make_pair(
                            9,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 8 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::shift, 3 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::shift, 28 })
                            }
                        ),
                        std::make_pair(
                            10,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 8 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::shift, 3 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::shift, 28 })
                            }
                        ),
                        std::make_pair(
                            11,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 8 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::shift, 3 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::shift, 28 })
                            }
                        ),
                        std::make_pair(
                            12,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 8 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::shift, 3 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::shift, 28 })
                            }
                        ),
                        std::make_pair(
                            13,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 8 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::shift, 3 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::shift, 32 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::shift, 28 }),
                                std::make_pair(2147483647, parsing_table_item{ parsing_table_item::enum_action::accept, 0 })
                            }
                        ),
                        std::make_pair(
                            16,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::shift, 9 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::shift, 10 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::shift, 11 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 12 }),
                                std::make_pair(7, parsing_table_item{ parsing_table_item::enum_action::shift, 30 })
                            }
                        ),
                        std::make_pair(
                            21,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::reduce, 4 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::reduce, 4 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::reduce, 4 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 4 }),
                                std::make_pair(7, parsing_table_item{ parsing_table_item::enum_action::reduce, 4 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 4 })
                            }
                        ),
                        std::make_pair(
                            22,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::shift, 9 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::shift, 10 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::reduce, 0 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 0 }),
                                std::make_pair(7, parsing_table_item{ parsing_table_item::enum_action::reduce, 0 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 0 })
                            }
                        ),
                        std::make_pair(
                            23,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::shift, 9 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::shift, 10 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::reduce, 1 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 1 }),
                                std::make_pair(7, parsing_table_item{ parsing_table_item::enum_action::reduce, 1 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 1 })
                            }
                        ),
                        std::make_pair(
                            24,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::shift, 9 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::shift, 10 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::shift, 11 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 12 }),
                                std::make_pair(7, parsing_table_item{ parsing_table_item::enum_action::reduce, 2 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 2 })
                            }
                        ),
                        std::make_pair(
                            25,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::shift, 9 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::shift, 10 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::shift, 11 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 12 }),
                                std::make_pair(7, parsing_table_item{ parsing_table_item::enum_action::reduce, 3 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 3 })
                            }
                        ),
                        std::make_pair(
                            26,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::shift, 9 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::shift, 10 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::shift, 11 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::shift, 12 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::shift, 34 })
                            }
                        ),
                        std::make_pair(
                            28,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::reduce, 6 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::reduce, 6 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::reduce, 6 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 6 }),
                                std::make_pair(7, parsing_table_item{ parsing_table_item::enum_action::reduce, 6 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 6 })
                            }
                        ),
                        std::make_pair(
                            30,
                            std::map<term, parsing_table_item>{
                                std::make_pair(2, parsing_table_item{ parsing_table_item::enum_action::reduce, 5 }),
                                std::make_pair(3, parsing_table_item{ parsing_table_item::enum_action::reduce, 5 }),
                                std::make_pair(4, parsing_table_item{ parsing_table_item::enum_action::reduce, 5 }),
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 5 }),
                                std::make_pair(7, parsing_table_item{ parsing_table_item::enum_action::reduce, 5 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 5 })
                            }
                        ),
                        std::make_pair(
                            31,
                            std::map<term, parsing_table_item>{
                                std::make_pair(8, parsing_table_item{ parsing_table_item::enum_action::shift, 33 })
                            }
                        ),
                        std::make_pair(
                            32,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 9 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::reduce, 9 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 9 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::reduce, 9 }),
                                std::make_pair(2147483647, parsing_table_item{ parsing_table_item::enum_action::reduce, 9 })
                            }
                        ),
                        std::make_pair(
                            33,
                            std::map<term, parsing_table_item>{
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::shift, 35 })
                            }
                        ),
                        std::make_pair(
                            34,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 8 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::reduce, 8 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 8 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::reduce, 8 }),
                                std::make_pair(2147483647, parsing_table_item{ parsing_table_item::enum_action::reduce, 8 })
                            }
                        ),
                        std::make_pair(
                            35,
                            std::map<term, parsing_table_item>{
                                std::make_pair(5, parsing_table_item{ parsing_table_item::enum_action::reduce, 10 }),
                                std::make_pair(6, parsing_table_item{ parsing_table_item::enum_action::reduce, 10 }),
                                std::make_pair(9, parsing_table_item{ parsing_table_item::enum_action::reduce, 10 }),
                                std::make_pair(10, parsing_table_item{ parsing_table_item::enum_action::reduce, 10 }),
                                std::make_pair(2147483647, parsing_table_item{ parsing_table_item::enum_action::reduce, 10 })
                            }
                        )
                    },

                    // goto_table
                    decltype(parsing_data::goto_table){
                        std::make_pair(
                            0,
                            std::map<term, std::size_t>{
                                std::make_pair(-2, 13)
                            }
                        ),
                        std::make_pair(
                            3,
                            std::map<term, std::size_t>{
                                std::make_pair(-3, 16)
                            }
                        ),
                        std::make_pair(
                            8,
                            std::map<term, std::size_t>{
                                std::make_pair(-3, 21)
                            }
                        ),
                        std::make_pair(
                            9,
                            std::map<term, std::size_t>{
                                std::make_pair(-3, 22)
                            }
                        ),
                        std::make_pair(
                            10,
                            std::map<term, std::size_t>{
                                std::make_pair(-3, 23)
                            }
                        ),
                        std::make_pair(
                            11,
                            std::map<term, std::size_t>{
                                std::make_pair(-3, 24)
                            }
                        ),
                        std::make_pair(
                            12,
                            std::map<term, std::size_t>{
                                std::make_pair(-3, 25)
                            }
                        ),
                        std::make_pair(
                            13,
                            std::map<term, std::size_t>{
                                std::make_pair(-3, 26)
                            }
                        ),
                        std::make_pair(
                            16,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            21,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            22,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            23,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            24,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            25,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            26,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            28,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            30,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            31,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            32,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            33,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            34,
                            std::map<term, std::size_t>{}
                        ),
                        std::make_pair(
                            35,
                            std::map<term, std::size_t>{}
                        )
                    }
                };
            };
            static parsing_data data = init();
            return data;
        }

        static std::unique_ptr<semantic_data> call_make_mlt(parser &p, std::unique_ptr<semantic_data> const &v_0, std::unique_ptr<semantic_data> const &v_1){
            return std::move(std::unique_ptr<semantic_data>(p.semantic_data_proc.make_mlt(v_0.get(), v_1.get())));
        }

        static std::unique_ptr<semantic_data> call_make_div(parser &p, std::unique_ptr<semantic_data> const &v_0, std::unique_ptr<semantic_data> const &v_1){
            return std::move(std::unique_ptr<semantic_data>(p.semantic_data_proc.make_div(v_0.get(), v_1.get())));
        }

        static std::unique_ptr<semantic_data> call_make_add(parser &p, std::unique_ptr<semantic_data> const &v_0, std::unique_ptr<semantic_data> const &v_1){
            return std::move(std::unique_ptr<semantic_data>(p.semantic_data_proc.make_add(v_0.get(), v_1.get())));
        }

        static std::unique_ptr<semantic_data> call_make_sub(parser &p, std::unique_ptr<semantic_data> const &v_0, std::unique_ptr<semantic_data> const &v_1){
            return std::move(std::unique_ptr<semantic_data>(p.semantic_data_proc.make_sub(v_0.get(), v_1.get())));
        }

        static std::unique_ptr<semantic_data> call_make_inv(parser &p, std::unique_ptr<semantic_data> const &v_0){
            return std::move(std::unique_ptr<semantic_data>(p.semantic_data_proc.make_inv(v_0.get())));
        }

        static std::unique_ptr<semantic_data> call_identity(parser &p, std::unique_ptr<semantic_data> const &v_0){
            return std::move(std::unique_ptr<semantic_data>(p.semantic_data_proc.identity(v_0.get())));
        }

        static std::unique_ptr<semantic_data> call_print(parser &p, std::unique_ptr<semantic_data> const &v_0){
            return std::move(std::unique_ptr<semantic_data>(p.semantic_data_proc.print(v_0.get())));
        }

        static std::unique_ptr<semantic_data> call_recover(parser &p){
            return std::move(std::unique_ptr<semantic_data>(p.semantic_data_proc.recover()));
        }

    public:
        SemanticDataProc &semantic_data_proc;

        parser() = delete;
        parser(SemanticDataProc &semantic_data_proc) : semantic_data_proc(semantic_data_proc){}

        template<class InputIter>
        InputIter parse(std::unique_ptr<semantic_data> &value, InputIter first, InputIter last){
            parsing_data const &table = parsing_data_storage();
            std::vector<std::size_t> state_stack;
            std::vector<std::unique_ptr<semantic_data>> value_stack;
            state_stack.push_back(table.first);
            while(true){
                token_type &token = *first;
                term const &t = static_cast<term>(token.identifier);
                std::size_t s = state_stack.back();
                auto const *table_second = &table.parsing_table.find(s)->second;
                auto iter = table_second->find(t);
                if(iter == table_second->end()){
                    while(state_stack.size() > 1){
                        table_second = &table.parsing_table.find(state_stack.back())->second;
                        iter = table_second->find(static_cast<term>(lxq::token_id::error));
                        if(iter == table_second->end() || iter->second.action != parsing_table_item::enum_action::shift){
                            state_stack.pop_back();
                            value_stack.pop_back();
                            continue;
                        }
                        break;
                    }
                    table_second = &table.parsing_table.find(state_stack.back())->second;
                    iter = table_second->find(static_cast<term>(lxq::token_id::error));
                    if(iter == table_second->end()){
                        throw parsing_error(token.first, token.last, token.line_num, token.char_num, token.word_num);
                    }
                }
                parsing_table_item const &i = iter->second;
                if(i.action == parsing_table_item::enum_action::shift){
                    state_stack.push_back(i.num);
                    value_stack.push_back(std::unique_ptr<semantic_data>(nullptr));
                    value_stack.back().swap(token.value);
                    ++first;
                }else if(i.action == parsing_table_item::enum_action::reduce){
                    auto &p = *table.n2r.find(i.num);
                    std::size_t norm = p.second.second.norm;
                    state_stack.resize(state_stack.size() - norm);
                    if(state_stack.empty()){
                        throw parsing_error(token.first, token.last, token.line_num, token.char_num, token.word_num);
                    }
                    std::vector<std::unique_ptr<semantic_data>> arg;
                    arg.reserve(norm);
                    for(std::size_t i = 0; i < norm; ++i){
                        arg.push_back(std::unique_ptr<semantic_data>(nullptr));
                        arg.back().swap(std::move(value_stack[value_stack.size() - norm + i]));
                    }
                    value_stack.resize(value_stack.size() - norm);
                    value_stack.push_back(std::move(p.second.second.call(*this, arg)));
                    state_stack.push_back(table.goto_table.find(state_stack.back())->second.find(p.second.first)->second);
                }else if(i.action == parsing_table_item::enum_action::accept){
                    if(value_stack.size() != 1){
                        throw parsing_error(token.first, token.last, token.line_num, token.char_num, token.word_num);
                    }
                    value = std::move(value_stack.front());
                    ++first;
                    break;
                }
            }
            return first;
        }
    };
}

#endif
