#pragma once

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>


namespace TSP
{
	class TravellingSalesmanProblem
	{
	private:
		std::wstring filePath;
		std::vector<int> currentOrder = std::vector<int>();
		std::vector<int> nextOrder = std::vector<int>();
//C# TO C++ CONVERTER WARNING: C# to C++ Converter has converted this array to a pointer. You will need to call 'delete[]' where appropriate:
//ORIGINAL LINE: private double[,] distances;
		double **distances;
		Random *random = new Random();
		double shortestDistance = 0;

	public:
		const double &getShortestDistance() const;
		void setShortestDistance(const double &value);

		const std::wstring &getFilePath() const;
		void setFilePath(const std::wstring &value);

		const std::vector<int> &getCitiesOrder() const;
		void setCitiesOrder(const std::vector<int> &value);

		/// <summary>
		/// Load cities from the text file representing the adjacency matrix
		/// </summary>
	private:
		void LoadCities();

		/// <summary>
		/// Calculate the total distance which is the objective function
		/// </summary>
		/// <param name="order">A list containing the order of cities</param>
		/// <returns></returns>
		double GetTotalDistance(std::vector<int> &order);

		/// <summary>
		/// Get the next random arrangements of cities
		/// </summary>
		/// <param name="order"></param>
		/// <returns></returns>
		std::vector<int> GetNextArrangement(std::vector<int> &order);

		/// <summary>
		/// Annealing Process
		/// </summary>
	public:
		void Anneal();
	};
}
