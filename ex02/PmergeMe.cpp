#include "PmergeMe.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <climits>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
	: _vec(other._vec), _deq(other._deq) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other) { _vec = other._vec; _deq = other._deq; }
	return *this;
}

PmergeMe::~PmergeMe() {}

std::vector<int>	PmergeMe::_jacobsthal(int n) const
{
	std::vector<int> jac;
	jac.push_back(0);
	jac.push_back(1);
	while (jac.back() < n)
	{
		int sz = (int)jac.size();
		jac.push_back(jac[sz - 1] + 2 * jac[sz - 2]);
	}
	return jac;
}

void	PmergeMe::_sortVector(std::vector<int> &seq)
{
	int n = (int)seq.size();
	if (n <= 1) return;

	bool hasStraggler = (n % 2 != 0);
	int  straggler    = 0;
	if (hasStraggler) { straggler = seq.back(); seq.pop_back(); n--; }

	for (int i = 0; i < n; i += 2)
		if (seq[i] < seq[i + 1]) std::swap(seq[i], seq[i + 1]);

	std::vector<std::pair<int,int> > pairs;
	for (int i = 0; i < n; i += 2)
		pairs.push_back(std::make_pair(seq[i], seq[i + 1]));

	std::vector<int> winners;
	for (int i = 0; i < (int)pairs.size(); ++i)
		winners.push_back(pairs[i].first);
	_sortVector(winners);

	std::vector<bool> used(pairs.size(), false);
	std::vector<int>  pend;
	for (int i = 0; i < (int)winners.size(); ++i)
	{
		for (int j = 0; j < (int)pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].first == winners[i])
			{
				pend.push_back(pairs[j].second);
				used[j] = true;
				break;
			}
		}
	}
	std::vector<int> chain(winners);
	chain.insert(std::lower_bound(chain.begin(), chain.end(), pend[0]), pend[0]);
	if ((int)pend.size() > 1)
	{
		std::vector<int>  jac = _jacobsthal((int)pend.size());
		std::vector<bool> ins((int)pend.size(), false);
		ins[0] = true;

		for (int k = 2; k < (int)jac.size(); ++k)
		{
			int hi = std::min(jac[k] - 1, (int)pend.size() - 1);
			int lo = jac[k - 1];
			for (int idx = hi; idx >= lo; --idx)
			{
				if (!ins[idx])
				{
					chain.insert(
						std::lower_bound(chain.begin(), chain.end(), pend[idx]),
						pend[idx]);
					ins[idx] = true;
				}
			}
		}
		for (int i = 1; i < (int)pend.size(); ++i)
			if (!ins[i])
				chain.insert(
					std::lower_bound(chain.begin(), chain.end(), pend[i]), pend[i]);
	}
	if (hasStraggler)
		chain.insert(std::lower_bound(chain.begin(), chain.end(), straggler), straggler);
	seq = chain;
}

void	PmergeMe::_sortDeque(std::deque<int> &seq)
{
	int n = (int)seq.size();
	if (n <= 1) return;
	bool hasStraggler = (n % 2 != 0);
	int  straggler    = 0;
	if (hasStraggler) { straggler = seq.back(); seq.pop_back(); n--; }
	for (int i = 0; i < n; i += 2)
		if (seq[i] < seq[i + 1]) std::swap(seq[i], seq[i + 1]);
	std::vector<std::pair<int,int> > pairs;
	for (int i = 0; i < n; i += 2)
		pairs.push_back(std::make_pair(seq[i], seq[i + 1]));
	std::deque<int> winners;
	for (int i = 0; i < (int)pairs.size(); ++i)
		winners.push_back(pairs[i].first);
	_sortDeque(winners);
	std::vector<bool> used(pairs.size(), false);
	std::deque<int>   pend;
	for (int i = 0; i < (int)winners.size(); ++i)
	{
		for (int j = 0; j < (int)pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].first == winners[i])
			{
				pend.push_back(pairs[j].second);
				used[j] = true;
				break;
			}
		}
	}
	std::deque<int> chain(winners);
	chain.insert(std::lower_bound(chain.begin(), chain.end(), pend[0]), pend[0]);
	if ((int)pend.size() > 1)
	{
		std::vector<int>  jac = _jacobsthal((int)pend.size());
		std::vector<bool> ins((int)pend.size(), false);
		ins[0] = true;
		for (int k = 2; k < (int)jac.size(); ++k)
		{
			int hi = std::min(jac[k] - 1, (int)pend.size() - 1);
			int lo = jac[k - 1];
			for (int idx = hi; idx >= lo; --idx)
			{
				if (!ins[idx])
				{
					chain.insert(
						std::lower_bound(chain.begin(), chain.end(), pend[idx]),
						pend[idx]);
					ins[idx] = true;
				}
			}
		}
		for (int i = 1; i < (int)pend.size(); ++i)
			if (!ins[i])
				chain.insert(
					std::lower_bound(chain.begin(), chain.end(), pend[i]), pend[i]);
	}
	if (hasStraggler)
		chain.insert(std::lower_bound(chain.begin(), chain.end(), straggler), straggler);

	seq = chain;
}

bool	PmergeMe::parseInput(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::istringstream ss(argv[i]);
		long n;
		ss >> n;
		if (ss.fail() || !ss.eof() || n <= 0 || n > INT_MAX)
		{
			std::cerr << "Error" << std::endl;
			return false;
		}
		_vec.push_back(static_cast<int>(n));
		_deq.push_back(static_cast<int>(n));
	}
	return true;
}

void	PmergeMe::run()
{
	std::cout << "Before:";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << " " << _vec[i];
	std::cout << std::endl;
	std::clock_t startVec = std::clock();
	_sortVector(_vec);
	std::clock_t endVec = std::clock();
	double timeVec = 1e6 * (double)(endVec - startVec) / CLOCKS_PER_SEC;
	std::clock_t startDeq = std::clock();
	_sortDeque(_deq);
	std::clock_t endDeq = std::clock();
	double timeDeq = 1e6 * (double)(endDeq - startDeq) / CLOCKS_PER_SEC;
	std::cout << "After:";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << " " << _vec[i];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
