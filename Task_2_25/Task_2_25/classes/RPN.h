#include <string>
#include <vector>
#include <map>
#include <stack>
#include <memory>
#include "IExpression.h"

using namespace std;

class IRPN {
public:
	virtual void setTokens(vector<string> tokens);

	virtual string getConvertedNotation() = 0;

	virtual void convert() = 0;

	virtual float calculate() = 0;

	virtual bool canCalculate() = 0;

	virtual void setVariables(string sream) = 0;
};

class RPN : public IRPN {
public:
	RPN();

	void setTokens(vector<string> tokens);

	string getConvertedNotation();

	void convert();

	float calculate();

	bool canCalculate();

	void setVariables(string sream);

private:
	vector <string> tokens;
	stack <shared_ptr<IExpression>> stack;
	map <string, string> variables;
};