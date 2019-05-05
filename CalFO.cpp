#include "CalFO.h"

CalFO::CalFO(void)
{
	

}

CalFO::~CalFO(void)
{
	
}

void CalFO::setData1D(vector<float> &data)
{
    Data1D=data;
  
}

void CalFO::runFD()
{
	const float pi=3.1415926;
	
	float a_d;
	float gamma;
	float sum;
	float dt=0.001;
	
	int datasize=Data1D.size();
	for(int i=0;i<datasize;i++)
	{
		FOD.push_back(0);
	}
    gamma=(float)gammaF(order_d_1);
	

	
	for (int i=0;i<datasize;i++)
	{
		sum = 0;
		for (int k=0;k<i+1;k++)
		{
			a_d = pow((float)(i-k+1),order_d_1)-pow((float)(i-k),order_d_1);
			if (k==0)
			{
				sum=sum+a_d*Data1D[k]/dt;
			} 
			else if(k==i)
			{
				sum=sum+a_d*(Data1D[k]-Data1D[k-1])/dt;
			}
			else
			{
				
				sum=sum+a_d*(Data1D[k+1]-Data1D[k-1])/(2.0*dt);

			}

		}	
        
		FOD[i] =(1/order_d_1)*pow(dt,order_d_1)*sum/(gamma);
		
	}


}

void CalFO::run1D()
{
	
	float dt=0.001;
	int datasize=Data1D.size();
	for(int i=0;i<datasize;i++)
	{
		FOD.push_back(0);
	}
	for (int i=0;i<datasize;i++)
	{
		
		if (i==0)
		{
			FOD[i]=0;

		}else if (i==(datasize-1))
		{
			FOD[i]=0;
		}
		else
		{
			FOD[i] =(Data1D[i+1]-Data1D[i-1])/(2.0*dt);

		}
		
	}

}

void CalFO::run2D()
{
	float dt=0.001;
	int datasize=Data1D.size();
	for(int i=0;i<datasize;i++)
	{
		FOD.push_back(0);
	}
	for (int i=0;i<datasize;i++)
	{

		if (i==0)
		{
			FOD[i]=0;

		}else if (i==(datasize-1))
		{
			FOD[i]=0;
		}
		else
		{
			FOD[i] =(Data1D[i-1]-2*Data1D[i]+Data1D[i+1])/dt*dt;

		}

	}

}

void CalFO::runFIF()
{
	const float pi=3.1415926;

	float a_d;
	float gamma;
	float sum;
	float dt=0.001;

	int datasize=Data1D.size();
	for(int i=0;i<datasize;i++)
	{
		FOD.push_back(0);
	}
	gamma=(float)gammaF(order_d_1+1);



	for (int i=0;i<datasize;i++)
	{
		sum = 0;
		for (int k=0;k<i+1;k++)
		{
			a_d = pow((float)(i-k+1),order_d_1)-pow((float)(i-k),order_d_1);
			
			sum=sum+a_d*Data1D[k];			

		}	

		FOD[i] =pow(dt,order_d_1)*sum/(gamma);

	}


}


double CalFO::gammaF(double x)
{ 
	int i;
	double y,t,s,u;
	static double a[11]={ 0.0000677106,-0.0003442342,
	0.0015397681,-0.0024467480,0.0109736958,
	-0.0002109075,0.0742379071,0.0815782188,
	0.4118402518,0.4227843370,1.0};
	if (x<=0.0)
	{ return(-1.0);}
	y=x;
	if (y<=1.0)
	{ t=1.0/(y*(y+1.0)); y=y+2.0;}
	else if (y<=2.0)
	{ t=1.0/y; y=y+1.0;}
	else if (y<=3.0) t=1.0;
	else
	{ t=1.0;
	while (y>3.0)
	{ y=y-1.0; t=t*y;}
	}
	s=a[0]; u=y-2.0;
	for (i=1; i<=10; i++)
	s=s*u+a[i];
	s=s*t;
	return(s);
}
