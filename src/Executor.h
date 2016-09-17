#pragma once

#include "Clustering.hpp"
#include "FuzzyCMeans.hpp"
#include "FuzzyCMeansOpenMP.hpp"

namespace ParallelClustering
{
	using namespace std;
	using namespace ParallelClustering;
	using namespace ParallelClustering::CMeansCollection;

	template<class IncomingType, class OutcommingType>
	class Executor
	{
	public:
		double a;
		
		Executor(double b)
		{
			a=b;
		}

		void CalculateProbabilities()
		{
			
			IncomingType* data = (IncomingType*)_mm_malloc(9*sizeof(IncomingType), 64);;			
			
			
			
			Clustering<IncomingType,OutcommingType>* clustering;
			clustering = new FuzzyCMeansOpenMP<IncomingType,OutcommingType>(data,10);
			clustering->StartClustering();
			
		}

		virtual ~Executor()
		{
			
		}
	};
}