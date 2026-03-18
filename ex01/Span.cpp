#include "Span.hpp"

Span::Span(unsigned int n) : _max(n) {}

Span::Span(const Span &other) : _max(other._max), _data(other._data) {}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        _max = other._max;
        _data = other._data;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int n)
{
    if (_data.size() >= _max)
        throw std::runtime_error("Span is full");
    _data.push_back(n);
}

int Span::shortestSpan() const
{
    if (_data.size() < 2)
        throw std::runtime_error("Not enough elements to find a span");

    std::vector<int> sorted(_data);
    std::sort(sorted.begin(), sorted.end());

    std::vector<int> diffs(sorted.size());
    std::adjacent_difference(sorted.begin(), sorted.end(), diffs.begin());

    return *std::min_element(diffs.begin() + 1, diffs.end());
}

int Span::longestSpan() const
{
    if (_data.size() < 2)
        throw std::runtime_error("Not enough elements to find a span");

    int min = *std::min_element(_data.begin(), _data.end());
    int max = *std::max_element(_data.begin(), _data.end());
    return max - min;
}
