#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <string>

class RPN
{
    private:
        std::stack<int>	_stack;

        bool	_isOperator(char c) const;
        bool	_applyOperator(char op);

    public:
        RPN();
        RPN(const RPN &other);
        RPN	&operator=(const RPN &other);
        ~RPN();

        bool	evaluate(const std::string &expression);
};

#endif
