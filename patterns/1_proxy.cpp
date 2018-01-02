
#include <iostream>

using namespace std;


class ISubject {
public:
	virtual void do_something() = 0;
};

///

class Real_subject : public ISubject {
public:
	void do_something() override { cout << "Real_subject::do_something() called" << endl; }
};

///

class Proxy : public ISubject {
public:
	Proxy(Real_subject* rs)
		:real_subject_(rs) {}
		
	void do_something() {
		cout << "Proxy::do_something() called" << endl;
		if (real_subject_)
			real_subject_->do_something();
	}
	
private:
	Real_subject*	real_subject_;
};

///

ISubject* get_subject()
{
	Real_subject* rs = new Real_subject();			// who deletes this?
	Proxy* p = new Proxy(rs);
	
	return p;
}

///

int main()
{
	ISubject* s = get_subject();
	s->do_something();
}

