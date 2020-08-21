

#include "TravellingSalesmanProblem.h"


namespace TSP
{

	const double &TravellingSalesmanProblem::getShortestDistance() const
	{
		return shortestDistance;
	}

	void TravellingSalesmanProblem::setShortestDistance(const double &value)
	{
		shortestDistance = value;
	}

	const std::wstring &TravellingSalesmanProblem::getFilePath() const
	{
		return filePath;
	}

	void TravellingSalesmanProblem::setFilePath(const std::wstring &value)
	{
		filePath = value;
	}

	const std::vector<int> &TravellingSalesmanProblem::getCitiesOrder() const
	{
		return currentOrder;
	}

	void TravellingSalesmanProblem::setCitiesOrder(const std::vector<int> &value)
	{
		currentOrder = value;
	}

	void TravellingSalesmanProblem::LoadCities()
	{
		StreamReader *reader = new StreamReader(filePath);

		std::wstring cities = reader->ReadToEnd();

		reader->Close();

//C# TO C++ CONVERTER WARNING: C# to C++ Converter has converted this array to a pointer. You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: string[] rows = cities.Split('\n');
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to this .NET String method:
		std::wstring *rows = cities.Split(L'\n');

		distances = RectangularArrays::AllocatedAndInitializedDoubleArray(rows->Length, rows->Length);

		for (int i = 0; i < rows->Length; i++)
		{
//C# TO C++ CONVERTER WARNING: C# to C++ Converter has converted this array to a pointer. You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: string[] distance = rows[i].Split(' ');
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to this .NET String method:
			std::wstring *distance = rows[i].Split(L' ');
			for (int j = 0; j < distance->Length; j++)
			{
				distances[i][j] = std::stod(distance[j]);
			}

			//the number of rows in this matrix represent the number of cities
			//we are representing each city by an index from 0 to N - 1
			//where N is the total number of cities
			currentOrder.push_back(i);
		}

		if (currentOrder.size() < 1)
		{
			throw std::exception(L"No cities to order.");
		}
	}

	double TravellingSalesmanProblem::GetTotalDistance(std::vector<int> &order)
	{
		double distance = 0;

		for (int i = 0; i < order.size() - 1; i++)
		{
			distance += distances[order[i]][order[i + 1]];
		}

		if (order.size() > 0)
		{
			distance += distances[order[order.size() - 1]][0];
		}

		return distance;
	}

	std::vector<int> TravellingSalesmanProblem::GetNextArrangement(std::vector<int> &order)
	{
		std::vector<int> newOrder = std::vector<int>();

		for (int i = 0; i < order.size(); i++)
		{
			newOrder.push_back(order[i]);
		}

		//we will only rearrange two cities by random
		//starting point should be always zero - so zero should not be included

		int firstRandomCityIndex = random->Next(1, newOrder.size());
		int secondRandomCityIndex = random->Next(1, newOrder.size());

		int dummy = newOrder[firstRandomCityIndex];
		newOrder[firstRandomCityIndex] = newOrder[secondRandomCityIndex];
		newOrder[secondRandomCityIndex] = dummy;

		return newOrder;
	}

	void TravellingSalesmanProblem::Anneal()
	{
		int iteration = -1;

		double temperature = 10000.0;
		double deltaDistance = 0;
		double coolingRate = 0.9999;
		double absoluteTemperature = 0.00001;

		LoadCities();

		double distance = GetTotalDistance(currentOrder);

		while (temperature > absoluteTemperature)
		{
			nextOrder = GetNextArrangement(currentOrder);

			deltaDistance = GetTotalDistance(nextOrder) - distance;

			//if the new order has a smaller distance
			//or if the new order has a larger distance but satisfies Boltzman condition then accept the arrangement
			if ((deltaDistance < 0) || (distance > 0 && exp(-deltaDistance / temperature) > random->NextDouble()))
			{
				for (int i = 0; i < nextOrder.size(); i++)
				{
					currentOrder[i] = nextOrder[i];
				}

				distance = deltaDistance + distance;
			}

			//cool down the temperature
			temperature *= coolingRate;

			iteration++;
		}

		shortestDistance = distance;
	}
}
