
#include <iostream>

using namespace std;

///

class IVisitor;

class IElement {
public:
	virtual void accept(IVisitor* v) = 0;
};

///

class Element_a;

class IVisitor {
public:
	virtual void visit(Element_a* elem) = 0;
};


///

class Element_a : public IElement {
public:
	Element_a(bool visitable = true)
		:visitable_{visitable} {}

	void accept(IVisitor* v) override {
		v->visit(this);
	}

	bool is_visitable() { return visitable_; }
	void set_visitable(bool b) { visitable_ = b; }

	void f() {
		cout << "Element_a::f() called" << endl;
	}

private:
	bool	visitable_;
};

///

class Visitor_a : public IVisitor {
public:
	void visit(Element_a* elem) {
		cout << "Visitor_a::visit() called" << endl;
		if (elem->is_visitable())
			elem->f();
	}
};

///

int main()
{
	Element_a* element_a = new Element_a;
	Visitor_a* visitor_a = new Visitor_a;

	element_a->accept(visitor_a);

	element_a->set_visitable(false);

	element_a->accept(visitor_a);

}


