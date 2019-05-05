#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
class CalFO
{
public:
	CalFO(void);
	~CalFO(void);
	vector<float> FOD;
	float order_d_1;
	void runFD();
	void run1D();
	void run2D();
	void runFIF();
	void setData1D(vector<float> &data);
private:
	vector<float> Data1D;
	double gammaF(double x);
    
	
	
};

