#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>

template <typename T>

class Array
{
    private:
        T				*_data;
        unsigned int	_size;

    public:
        Array(void);
        Array(unsigned int n);
        Array(Array const &other);
        Array	&operator=(Array const &other);
        ~Array(void);
        T		&operator[](unsigned int index);
        T const	&operator[](unsigned int index) const;
        unsigned int	size(void) const;
};

# include "Array.tpp"

#endif
