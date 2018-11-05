#include <iostream>
#include <array>
#include <vector>
#include <sstream>


using Permutation = std::vector<size_t>;

template<typename Fn>
void permutate(size_t n, Permutation& arr, Fn store)
{
	size_t c = 0;
	if (n == arr.size())
	{
		store(arr);
	}
	while (true)
	{
		if (n > 2)
			permutate(n - 1, arr, store);
		if (n <= c + 1)
			break;
		std::swap(arr[c*(1 - (n % 2))], arr[n-1]);
		store(arr);
		++c;
	}
}

void print(const Permutation& arr)
{
	std::cout << "[";
	for(auto i = 0; i < arr.size(); ++i)
	{
		std::cout << arr[i];
		if (i < arr.size()-1)
			std::cout << ", ";
	}
	std::cout << "]";
}

void testPermutations(size_t n)
{
	// Test permutations
	Permutation p;
	for(size_t i = 1; i <= n; ++i)
		p.push_back(i);

	size_t count = 0;
	auto store = [&count](auto p) {
		//print(p);
		//std::cout << std::endl;
		++count;
	};
	permutate(p.size(), p, store);
	std::cout << count << std::endl;
}


struct Bin {
	size_t width;
	size_t color;
};

std::array<Bin, 12> bins
	{{
		 {1, 0}, {1, 0}, {2, 0},   // 0 always before 1
		 {1, 1}, {1, 1}, {2, 1},   // 3 always before 4
		 {1, 2}, {1, 2}, {2, 2},   // 6 always before 7
		 {1, 3}, {1, 3}, {2, 3},   // 9 always before 10
	 }};


template<bool DistinguishIdenticalBins, bool Debug>
bool validBins(const Permutation& arr, std::string& why)
{
	std::array<size_t, 12> indexOfBin;
	size_t width = 0;
	size_t nextWidth = 4;
	for(size_t i = 0; i < 12; ++i)
	{
		auto binIdx = arr[i];
		auto& b = bins[binIdx];
		width += b.width;
		if (width == nextWidth)
			nextWidth += 4;
		else if (width > nextWidth)
		{
			if constexpr (Debug)
			{
				std::stringstream ss;
				ss << "straddled " << nextWidth;
				why = ss.str();
			}
			return false;
		}
		if constexpr (!DistinguishIdenticalBins)
		{
			indexOfBin[arr[i]] = i;
		}
	}
	if constexpr (!DistinguishIdenticalBins)
	{
		for(auto i : {0, 3, 6, 9})
			if (indexOfBin[i] > indexOfBin[i+1])
			{
				if constexpr (Debug)
				{
					std::stringstream ss;
					ss << "bin[" << i << "] after bin[" << i+1 << "]";
					why = ss.str();
				}
				return false;
			}
	}
	return true;

}

template<bool DistinguishIdenticalBins, bool Print, bool Debug>
void countArrangements()
{
	// Test permutations
	Permutation p;
	for(size_t i = 0; i < 12; ++i)
		p.push_back(i);

	size_t goodCount = 0;
	size_t considered = 0;
	auto store = [&goodCount, &considered](auto p) {
		std::string why;
		bool good = validBins<DistinguishIdenticalBins, Debug>(p, why);
		if (good) ++goodCount;
		++considered;
		if constexpr (Debug)
		{
			if (0 == (considered % 10000))
				std::cout << goodCount << "/" << considered << std::endl;

		}
		if constexpr (Print)
		{
			auto hdr = good ? "GOOD: " : "BAD:  ";
			std::cout << hdr;
			print(p);
			if constexpr (Debug)
			{
				std::cout << "  " << why << std::endl;
			}
		}
	};
	permutate(p.size(), p, store);
	std::cout << "Total good count: " << goodCount << std::endl;
}

int main()
{
	//testPermutations(12);
	//countArrangements<true, false, true>();
	countArrangements<false, false, false>();
 	return 0;
}

