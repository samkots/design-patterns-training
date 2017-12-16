
#include <iostream>

using namespace std;

///

class IStrategy {
public:
	virtual void do_stuff() = 0;
};

///

class Strategy_a : public IStrategy {
public:
	void do_stuff() {
		cout << "Strategy_a::do_stuff() called" << endl;
	}
};

class Strategy_b : public IStrategy {
public:
	void do_stuff() {
		cout << "Strategy_b::do_stuff() called" << endl;
	}
};

///

class Context {
public:
	Context()								// strategy can also be passed to this
	{
		cout << "Enter a number<even/odd condition>: ";			// strategy selection algorithm
		int n = 0;
		cin >> n;
		if (n % 2 == 0)
			strategy_ = new Strategy_a;
		else
			strategy_ = new Strategy_b;
	}

	void run() {
		if (strategy_)
			strategy_->do_stuff();
	}

private:
	IStrategy* strategy_;
};

///

int main()
{
	Context* ctx = new Context;
	ctx->run();
}

// // //
