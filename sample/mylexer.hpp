#ifndef MYLEXER_HPP_
#define MYLEXER_HPP_

#include <memory>
#include <vector>
#include <exception>
#include "lxq.hpp"

namespace lxq{
    enum class token_id : int{
        mul = 2,
        div = 3,
        add = 4,
        sub = 5,
        l_paren = 6,
        r_paren = 7,
        semicolon = 9,
        recover = 8,
        id = 10,
        space = 0,
        error = 2147483646,
        end = 2147483647
    };
}

template<class Iter>
struct mylexer{
    struct token_type{
        using identifier_type = lxq::token_id;
        token_type() : value(nullptr){}
        token_type(const token_type&) = delete;
        token_type(token_type &&other) : first(std::move(other.first)), last(std::move(other.last)), line_num(other.line_num), char_num(other.line_num), word_num(other.word_num), identifier(other.identifier), value(std::move(other.value)){}
        ~token_type() = default;
        Iter first, last;
        std::size_t line_num, char_num, word_num;
        identifier_type identifier;
        std::unique_ptr<lxq::semantic_data> value;
    };

    using iterator = Iter;

    template<class Action>
    static std::vector<token_type> tokenize(Iter iter, Iter end, Action &action){
        std::vector<token_type> result;
        Iter first = iter;
        std::size_t line_num = 0, char_num = 0, word_num = 0;
        char c;

        state_1:;
        if(iter == end){
            goto end_of_tokenize;
        }
        c = *iter;
        switch(c){
        case  32: 
            ++char_num;
            ++iter;
            goto state_2;
        case  40: 
            ++char_num;
            ++iter;
            goto state_3;
        case  41: 
            ++char_num;
            ++iter;
            goto state_4;
        case  42: 
            ++char_num;
            ++iter;
            goto state_5;
        case  43: 
            ++char_num;
            ++iter;
            goto state_6;
        case  45: 
            ++char_num;
            ++iter;
            goto state_7;
        case  47: 
            ++char_num;
            ++iter;
            goto state_8;
        case  48: case  49: case  50: case  51: case  52: case  53: case  54: case  55:
        case  56: case  57: 
            ++char_num;
            ++iter;
            goto state_9;
        case  59: 
            ++char_num;
            ++iter;
            goto state_10;
        case 114: 
            ++char_num;
            ++iter;
            goto state_11;
        }
        throw std::runtime_error("lexical error : state 1");

        state_2:;
        if(iter == end){
            goto end_of_tokenize;
        }
        c = *iter;
        switch(c){
        case  32: 
            ++char_num;
            ++iter;
            goto state_2;
        }
        {
            first = iter;
            goto state_1;
        }

        state_3:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::l_paren;
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::l_paren;
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        state_4:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::r_paren;
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::r_paren;
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        state_5:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::mul;
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::mul;
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        state_6:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::add;
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::add;
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        state_7:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::sub;
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::sub;
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        state_8:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::div;
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::div;
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        state_9:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::id;
            t.value = std::move(std::unique_ptr<lxq::semantic_data>(action.make_id(first, iter)));
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        c = *iter;
        switch(c){
        case  48: case  49: case  50: case  51: case  52: case  53: case  54: case  55:
        case  56: case  57: 
            ++char_num;
            ++iter;
            goto state_9;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::id;
            t.value = std::move(std::unique_ptr<lxq::semantic_data>(action.make_id(first, iter)));
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        state_10:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::semicolon;
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::semicolon;
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        state_11:;
        if(iter == end){
            throw std::runtime_error("lexical error : state 11");
        }
        c = *iter;
        switch(c){
        case 101: 
            ++char_num;
            ++iter;
            goto state_12;
        }
        throw std::runtime_error("lexical error : state 11");

        state_12:;
        if(iter == end){
            throw std::runtime_error("lexical error : state 12");
        }
        c = *iter;
        switch(c){
        case  99: 
            ++char_num;
            ++iter;
            goto state_13;
        }
        throw std::runtime_error("lexical error : state 12");

        state_13:;
        if(iter == end){
            throw std::runtime_error("lexical error : state 13");
        }
        c = *iter;
        switch(c){
        case 111: 
            ++char_num;
            ++iter;
            goto state_14;
        }
        throw std::runtime_error("lexical error : state 13");

        state_14:;
        if(iter == end){
            throw std::runtime_error("lexical error : state 14");
        }
        c = *iter;
        switch(c){
        case 118: 
            ++char_num;
            ++iter;
            goto state_15;
        }
        throw std::runtime_error("lexical error : state 14");

        state_15:;
        if(iter == end){
            throw std::runtime_error("lexical error : state 15");
        }
        c = *iter;
        switch(c){
        case 101: 
            ++char_num;
            ++iter;
            goto state_16;
        }
        throw std::runtime_error("lexical error : state 15");

        state_16:;
        if(iter == end){
            throw std::runtime_error("lexical error : state 16");
        }
        c = *iter;
        switch(c){
        case 114: 
            ++char_num;
            ++iter;
            goto state_17;
        }
        throw std::runtime_error("lexical error : state 16");

        state_17:;
        if(iter == end){
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::recover;
            result.push_back(std::move(t));
            goto end_of_tokenize;
        }
        {
            token_type t;
            t.first = first;
            t.last = iter;
            t.line_num = line_num;
            t.char_num = char_num;
            t.word_num = word_num++;
            t.identifier = token_type::identifier_type::recover;
            result.push_back(std::move(t));
            first = iter;
            goto state_1;
        }

        end_of_tokenize:;
        {
            token_type t;
            t.first = iter;
            t.last = iter;
            t.line_num = 0;
            t.char_num = 0;
            t.word_num = 0;
            t.identifier = token_type::identifier_type::end;
            result.push_back(std::move(t));
        }
        return result;
    }
};
#endif // MYLEXER_HPP_

