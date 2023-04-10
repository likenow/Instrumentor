#include "Instrumentor.h"
#include <iostream>
#include <array>
#include <memory>

namespace Benchmark
{
	void fn1()
	{
		PROFILE_FUNCTION();
		int value = 0;
		{
			PROFILE_SCOPE("for loop");
			for (int i = 0; i < 1000000; i++)
			{
				value += 2;
			}
		}

		std::cout << value << std::endl;
	}

	void fn2()
	{
		PROFILE_FUNCTION();
		struct Vector2
		{
			float x, y;
		};

		std::cout << "Make shared \n";
		{
			PROFILE_SCOPE("make_shared");
			std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
			for (int i = 0; i < sharedPtrs.size(); i++)
			{
				sharedPtrs[i] = std::make_shared<Vector2>();
			}
		}

		std::cout << "New shared \n";
		{
			PROFILE_SCOPE("new_shared");
			std::array<std::shared_ptr<Vector2>, 1000> sharedPtrs;
			for (int i = 0; i < sharedPtrs.size(); i++)
			{
				sharedPtrs[i] = std::shared_ptr<Vector2>(new Vector2());
			}
		}

		std::cout << "Make unique \n";
		{
			PROFILE_SCOPE("make_unique");
			std::array<std::unique_ptr<Vector2>, 1000> uniquePtrs;
			for (int i = 0; i < uniquePtrs.size(); i++)
			{
				uniquePtrs[i] = std::make_unique<Vector2>();
			}
		}
	}
	void fn3()
	{
		PROFILE_FUNCTION();

		std::thread a([]() { fn1(); });
		a.join();
	}
}

int main()
{
	Instrumentor::Get().BeginSession("Profile");
	Benchmark::fn1();
	Benchmark::fn2();
	Benchmark::fn3();
	Instrumentor::Get().EndSession();
	return 0;
}