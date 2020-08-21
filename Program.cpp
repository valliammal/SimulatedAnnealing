#include "Program.h"
#include "TravellingSalesmanProblem.h"


namespace TSP
{

	void Program::Main(std::wstring args[])
	{
		TravellingSalesmanProblem *problem = new TravellingSalesmanProblem();
		problem->setFilePath(L"Cities.txt");
		problem->Anneal();

		std::wstring path = L"";
		for (int i = 0; i < problem->getCitiesOrder().size() - 1; i++)
		{
			path += problem->getCitiesOrder()[i] + std::wstring(L" -> ");
		}
		path += problem->getCitiesOrder()[problem->getCitiesOrder().size() - 1];

		std::wcout << std::wstring(L"Shortest Route: ") << path << std::endl;

		std::wcout << std::wstring(L"The shortest distance is: ") << std::to_wstring(problem->getShortestDistance()) << std::endl;

		getchar();
	}
}
