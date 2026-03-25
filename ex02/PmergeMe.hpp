#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>
# include <string>

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;

	// Ford-Johnson pour vector
	void	_sortVector(std::vector<int> &seq);
	void	_insertVector(std::vector<int> &main, const std::vector<int> &pend);

	// Ford-Johnson pour deque
	void	_sortDeque(std::deque<int> &seq);
	void	_insertDeque(std::deque<int> &main, const std::deque<int> &pend);

	// Generateur de nombres de Jacobsthal
	std::vector<int>	_jacobsthal(int n) const;

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe	&operator=(const PmergeMe &other);
	~PmergeMe();

	bool	parseInput(int argc, char **argv);
	void	run();
};

#endif
