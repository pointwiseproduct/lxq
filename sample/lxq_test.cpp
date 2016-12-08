#include <iostream>
#include "mylexer.hpp"
#include "myparser.hpp"

struct semantic_data : lxq::semantic_data{
	semantic_data(double value) : value(value){}
	double value;
};

struct semantic_action{
	// lexer�p.
	// ������(range)����l�𐶐�����.
	// atoi���Ă邾��
	template<class Iter>
	lxq::semantic_data *make_id(Iter first, Iter last){
		return new semantic_data(static_cast<double>(std::atoi(std::string(first, last).c_str())));
	}

	// ����.
	lxq::semantic_data *make_add(lxq::semantic_data *x_, lxq::semantic_data *y_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		semantic_data *y = static_cast<semantic_data*>(y_);
		return new semantic_data(x->value + y->value);
	}

	// ����.
	lxq::semantic_data *make_sub(lxq::semantic_data *x_, lxq::semantic_data *y_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		semantic_data *y = static_cast<semantic_data*>(y_);
		return new semantic_data(x->value - y->value);
	}

	// �|����.
	lxq::semantic_data *make_mlt(lxq::semantic_data *x_, lxq::semantic_data *y_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		semantic_data *y = static_cast<semantic_data*>(y_);
		return new semantic_data(x->value * y->value);
	}

	// ����.
	lxq::semantic_data *make_div(lxq::semantic_data *x_, lxq::semantic_data *y_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		semantic_data *y = static_cast<semantic_data*>(y_);
		return new semantic_data(x->value / y->value);
	}

	// �A�C�f���e�B�e�B.
	lxq::semantic_data *identity(lxq::semantic_data *x){
		return new semantic_data(static_cast<semantic_data*>(x)->value);
	}

	// �����𔽓]����.
	lxq::semantic_data *make_inv(lxq::semantic_data *x_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		return new semantic_data(-x->value);
	}

	// �v�����g.
	lxq::semantic_data *print(lxq::semantic_data *x_){
		semantic_data *x = static_cast<semantic_data*>(x_);
		std::cout << x->value << std::endl;
		return nullptr;
	}

	// �G���[���A.
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

