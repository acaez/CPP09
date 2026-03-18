#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <stdexcept>
# include <algorithm>
# include <numeric>

class Span
{
    private:
        unsigned int        _max;
        std::vector<int>    _data;

    public:
        Span(unsigned int n);
        Span(const Span &other);
        Span &operator=(const Span &other);
        ~Span();

        void    addNumber(int n);
        template <typename Iterator>
        void    addNumbers(Iterator begin, Iterator end)
        {
            unsigned int incoming = std::distance(begin, end);
            if (_data.size() + incoming > _max)
                throw std::runtime_error("Span is full");
            _data.insert(_data.end(), begin, end);
        }
        int             shortestSpan() const;
        int             longestSpan() const;
};

#endif
