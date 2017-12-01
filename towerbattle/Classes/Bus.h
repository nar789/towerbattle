
#include "cocos2d.h"
using namespace std;

class Bus
{

	
public:
	Bus(void);
	~Bus(void);

	static Bus* b;
	static Bus* getInstance();
	string email;
	string password;
	string account;
	int point;
	string src;
};

