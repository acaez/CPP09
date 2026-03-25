#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>

class BitcoinExchange
{
    private:
        std::map<std::string, float>	_db;
        
        bool	_loadDatabase(const std::string &csvFile);
        bool	_isValidDate(const std::string &date) const;
        bool	_isLeapYear(int year) const;
        float	_getRate(const std::string &date) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange	&operator=(const BitcoinExchange &other);
        ~BitcoinExchange();
        
        bool	loadDatabase(const std::string &csvFile);
        void	processInput(const std::string &inputFile) const;
};

#endif
