#include <iostream>
#include <random>
#include <math.h>  
#include <fstream>
#include "CreateGraph.h"

using namespace std;

// Ex. functions // 
Graph build_random_graph(int, double);
int connectivity(Graph);
int diameter(Graph);
int is_isolated(Graph);

// Utility functions // 
bool random_prob(double);
double calcThreshold1_3(Graph);
double calcThreshold2(Graph);
int firstTest(Graph, double);
int secondTest(Graph, double);
int thirdTest(Graph, double);
void writeResultToCsv(double* , double* , string );

// Random utility methods // 
std::knuth_b rand_engine;
std::uniform_real_distribution<> uniform_zero_to_one(0.0, 1.0);

//return True or False for the prob
bool random_prob(double prob)
{
	return uniform_zero_to_one(rand_engine) < prob;
}


//Building graph with probability.
Graph build_random_graph(int v, double p) {
	Graph g(v);
	for (int i = 0; i < v; i++)
	{
		for (int j = i + 1; j < v; j++)
		{
			if (random_prob(p)) {
				g.addEdge(i, j);
			}
		}
	}
	return g;
}


// Connectivity of the graph.
int connectivity(Graph g) {
	int* distances = g.BFS(0);
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] == -1)
			return 0;
	}
	return 1;
}


// Diameter of graph 
int diameter(Graph g) {
	int* distances = g.BFS(0);
	int maxDiameter = 0, saveV = 0;
    // find the other-end point of diameter
    // fisrt other-end
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] == -1)
			return -1; // the Graph is not connected
		if (distances[i] > maxDiameter) {
			maxDiameter = distances[i];
			saveV = i;
		}
	}
	distances = g.BFS(saveV);
	maxDiameter = 0;
    // second other-end
	for (int i = 0; i < g.getV(); i++)
	{
		if (distances[i] > maxDiameter) 
		{
			maxDiameter = distances[i];
			saveV = i;
		}
	}
	return maxDiameter;
}


// Check if there is vertex without neighbors
int is_isolated(Graph g) {
	for (int i = 0; i < g.getV(); i++)
	{
		if (g.getAdjList(i).empty())
			return 1;
	}
	return 0;
}


//calculation threshold 1,3
double calcThreshold1_3(Graph g)
{
	double V = (double)g.getV();
	return (log(V) / V);
	
	/*Result is: 0.1175 */
}

//calculation threshold 2
double calcThreshold2(Graph g)
{
	double V = (double)g.getV();
	return sqrt((2 * log(V)) / V);

	/*Result is: 0.00690 */
}

// First feature tests --- IsConnected
int firstTest(Graph g,double p) {
	int isConnected = connectivity(g);
	double threshold1 = calcThreshold1_3(g);
	if (( p > threshold1 && isConnected == 1 ) || ( p < threshold1 && isConnected == 0 ))
	{
		return 1;
	}
	return 0;
}

// Second feature tests --- Diameter 
int secondTest(Graph g, double p)
{
	int diam = diameter(g);
	double threshold2 = calcThreshold2(g);

	if (( p > threshold2 && diam == 2 ) || (p < threshold2 && diam > 2))
	{
		return 1;
	}
	return 0;
}

// Third feature tests --- IsIsolated 
int thirdTest(Graph g, double p)
{
	int verticeIsLonely = is_isolated(g);
	double threshold3 = calcThreshold1_3(g);

	if (( p < threshold3 && verticeIsLonely ==1 ) || ( p > threshold3 && verticeIsLonely == 0 ))
	{
		return 1;
	}
	return 0;
}

// Exporting to CSV file the results
void writeResultToCsv(double* Plist, double* results, string filename)
{
	ofstream saveToFile(filename);
	saveToFile << "P,";
	for (int p = 0; p < 9; p++)
	{
		saveToFile << Plist[p] << ",";
	}
	saveToFile << Plist[9] << endl;

	saveToFile << "The probability that the Feature exists,";
	for (int p = 0; p < 9; p++)
	{
		saveToFile << results[p] << ",";
	}
	saveToFile << results[9] << endl;

	saveToFile.close();
}



// MAIN 
int main() {
	
	cout << "Generating graphs and run tests"<<endl;
	int numberOfRuns = 500;
	cout << "Number of graphs to generate:" << numberOfRuns << endl;



	cout << "*************************************************" << endl;
	cout << "**               Test 1 is in progress...      **" << endl;
	cout << "*************************************************" << endl;
	double firstTestPList[] = { 0.004 ,0.0045 ,0.005 ,0.0055 ,0.006 ,0.0075 ,0.008 ,0.0085 ,0.009 ,0.0095 };
	double* firstTestResults = new double[10];
	
	for (int p = 0; p < 10; p++) 
	{
		cout << endl << endl << "Probability: " << firstTestPList[p] << endl;
		double countOfFirst = 0;
		for (int i = 0; i < numberOfRuns; i++)
		{	
			cout << "Progress: " << i+1 << "/" << numberOfRuns << "\r";
			Graph g = build_random_graph(1000, firstTestPList[p]);
			if(firstTest(g, firstTestPList[p]) == 1)
			{
				countOfFirst++;
			}
			
		}
		firstTestResults[p] = countOfFirst/numberOfRuns;
	}
	cout << endl << endl << "exporting to file..." << endl;
	writeResultToCsv(firstTestPList, firstTestResults, "Test1Results.csv");
	cout << "Done." << endl;




	cout << "*************************************************" << endl;
	cout << "**               Test 2 is in progress...      **" << endl;
	cout << "*************************************************" << endl;
	double secondTestPList[] = { 0.075 ,0.08 ,0.085 ,0.09 ,0.1 ,0.2 ,0.25 ,0.3 ,0.35 ,0.4 };
	double* secondTestResults = new double[10];
	
	for (int p = 0; p < 10; p++)
	{
		cout << endl << endl << "Probability: " << secondTestPList[p] << endl;
		double countOfSecond = 0;
		for (int i = 0; i < numberOfRuns; i++)
		{
			cout << "Progress: " << i + 1 << "/" << numberOfRuns << "\r";
			Graph g = build_random_graph(1000, secondTestPList[p]);
			if (secondTest(g, secondTestPList[p]) == 1)
			{
				countOfSecond++;
			}
		}
		secondTestResults[p] = countOfSecond / numberOfRuns;
	}
	cout << endl << endl << "exporting to file..." << endl;
	writeResultToCsv(secondTestPList, secondTestResults, "Test2Results.csv");
	cout << "Done." << endl;



	cout << "*************************************************" << endl;
	cout << "**               Test 3 is in progress...      **" << endl;
	cout << "*************************************************" << endl;
	double thirdTestPList[] = { 0.004 ,0.0045 ,0.005 ,0.0055 ,0.006 ,0.0075 ,0.008 ,0.0085 ,0.009 ,0.0095 };
	double* thirdTestResults = new double[10];

	for (int p = 0; p < 10; p++)
	{
		cout << endl << endl << "Probability: " << thirdTestPList[p] << endl;
		double countOfthird = 0;
		for (int i = 0; i < numberOfRuns; i++)
		{
			cout << "Progress: " << i + 1 << "/" << numberOfRuns << "\r";
			Graph g = build_random_graph(1000, thirdTestPList[p]);
			if (thirdTest(g, thirdTestPList[p]) == 1)
			{
				countOfthird++;
			}

		}
		thirdTestResults[p] = countOfthird / numberOfRuns;
	}
	cout << endl << endl << "exporting to file..." << endl;
	writeResultToCsv(thirdTestPList, thirdTestResults, "Test3Results.csv");
	cout << "Done." << endl;
}
