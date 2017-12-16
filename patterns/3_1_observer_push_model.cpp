
#include <iostream>
#include <vector>

using namespace std;



class IObserver {
public:
	virtual ~IObserver() {};

	virtual void update(int event_param) = 0;
};

// observable / publisher
class ISubject {
public:
	virtual ~ISubject() {};

	virtual void attach(IObserver* observer) = 0;
	virtual void notify(int event_info) = 0;
};

///


class Concrete_observer : public IObserver {
public:
	~Concrete_observer() {}

	void update(int event_param) {
		cout << "Concrete_observer::update() called: " << event_param << endl;
	}
};

class Concrete_subject : public ISubject {
public:
	~Concrete_subject() {}

	void attach(IObserver* observer) {
		observers_.push_back(observer);
	}

	void notify(int event_info) {
		cout << "Concrete_subject::notify() called" << endl;
		for (auto* observer : observers_)
			if (observer)
				observer->update(event_info);
	}

private:
	vector<IObserver*> observers_;
};

///

int main()
{
	Concrete_observer* observer1	= new Concrete_observer;
	Concrete_subject* subject1	= new Concrete_subject;

	subject1->attach(observer1);					// registeration

	// event with event info
	subject1->notify(10);

	delete subject1;
	delete observer1;
}

// // //

