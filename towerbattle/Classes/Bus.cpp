#include "Bus.h"

Bus* Bus::b=NULL;

Bus::Bus(void)
{
	
}


Bus::~Bus(void)
{
}


Bus* Bus::getInstance()
{
	if(!b)
	{
		b=new Bus();
	}

	return b;
}


