#include <iostream>
#include "mylexer.hpp"
#include "myparser.hpp"

struct semantic_data : lxq::semantic_data{
	semantic_data(double value) : value(value){}
	double value;
};

struct semantic_action{
	// lexer用.
	// 文字列(range)から値を生成する.
	// atoiしてるだけ
	template<class Iter>
	lxq::semantic_data *make_id(Iter first, Iter last){
		return new semantic_data(static_cast<double>(std::atoi(std::string(first, last).c_str())));
	}

	// 足す.
	lxq::semantic_data *make_add(lxq::semantic_data *x_, lxq::semantic_data *y_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		semantic_data *y = static_cast<semantic_data*>(y_);
		return new semantic_data(x->value + y->value);
	}

	// 引く.
	lxq::semantic_data *make_sub(lxq::semantic_data *x_, lxq::semantic_data *y_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		semantic_data *y = static_cast<semantic_data*>(y_);
		return new semantic_data(x->value - y->value);
	}

	// 掛ける.
	lxq::semantic_data *make_mlt(lxq::semantic_data *x_, lxq::semantic_data *y_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		semantic_data *y = static_cast<semantic_data*>(y_);
		return new semantic_data(x->value * y->value);
	}

	// 割る.
	lxq::semantic_data *make_div(lxq::semantic_data *x_, lxq::semantic_data *y_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		semantic_data *y = static_cast<semantic_data*>(y_);
		return new semantic_data(x->value / y->value);
	}

	// アイデンティティ.
	lxq::semantic_data *identity(lxq::semantic_data *x){
		return new semantic_data(static_cast<semantic_data*>(x)->value);
	}

	// 符号を反転する.
	lxq::semantic_data *make_inv(lxq::semantic_data *x_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		return new semantic_data(-x->value);
	}

	// プリント.
	lxq::semantic_data *print(lxq::semantic_data *x_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		std::cout << x->value << std::endl;
		return nullptr;
	}

	// エラー復帰.
	lxq::semantic_data *recover(){
		std::cout << "reenter expr." << std::endl;
		return nullptr;
	}

	double value;
};

int main(){
	std::string str = "-1 + + ; ; recover; (2 - 3) * 4 / 5; 1 / 4;";
	semantic_action sa;
	using lexer = mylexer<std::string::iterator>;
	std::vector<lexer::token_type> result = lexer::tokenize(str.begin(), str.end(), sa);
	std::unique_ptr<lxq::semantic_data> ptr;
	myparser::parser<lexer, semantic_action> p(sa);
	if(p.parse(ptr, result.begin(), result.end()) != result.end()){
		std::cout << "parsing error" << std::endl;
		return 0;
	}

    return 0;
}

