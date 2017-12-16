
#include <iostream>
#include <vector>

using namespace std;


class ISubject;

class IObserver {
public:
	virtual ~IObserver() {};

	virtual void update(ISubject* subject) = 0;
};

// observable / publisher
class ISubject {
public:
	virtual ~ISubject() {};

	virtual void attach(IObserver* observer) = 0;
	virtual void notify(int event_info) = 0;
	virtual int get_event_info() const = 0;
};

///


class Concrete_observer : public IObserver {
public:
	~Concrete_observer() {}

	void update(ISubject* subject) override {
		if (subject)
			cout << "event: " << subject->get_event_info() << endl;
	}
};

class Concrete_subject : public ISubject {
public:
	~Concrete_subject() {}

	void attach(IObserver* observer) override {
		observers_.push_back(observer);
	}

	void notify(int event_info) override {
		cout << "Concrete_subject::notify() called" << endl;
		event_info_ = event_info;
		for (auto* observer : observers_)
			if (observer)
				observer->update(this);
	}

	int get_event_info() const override {
		return event_info_;
	}

private:
	vector<IObserver*> observers_;
	int event_info_;
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

