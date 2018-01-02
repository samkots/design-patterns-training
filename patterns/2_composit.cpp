
//
// Composit Design pattern
//


#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Entity {
public:
	explicit Entity(const string& name)
		:name_(name) {}
		
	virtual void display() = 0;

protected:
	string name_;
};

///

class File : public Entity {
public:
	explicit File(const string& name)
		:Entity(name) {}
		
	void display() override {
		cout << "file name: " << name_ << endl;
	}
};

///

class Directory : public Entity {
public:
	explicit Directory(const string& name)
		:Entity(name) {}
	
	void display() override {
		cout << "directory name: " << name_ << endl;
		
		if (entities_.empty())
			return;
		
		cout << "Directory contains " << entities_.size() << " items." << endl;
		
		for (unsigned i = 0; i < entities_.size(); ++i)
			entities_[i]->display();
	}
	
	void add_entity(Entity* e) {
		if (!e || e == this)														// can't add nullptr or itself. cyclic add is still there
			throw runtime_error("Directory::add_entity(): bad argument");
		
		entities_.push_back(e);
	}
	
	int count() const { return entities_.size(); }
	
private:
	vector<Entity*> entities_;
};


int main() try
{
	Entity* file1 = new File("a.txt");
	file1->display();
	Directory* dir1 = new Directory("dir1");

	dir1->add_entity(file1);
	dir1->display();
	
	//dir1->add_entity(dir1);						// adding self is not allowed
}
catch (const exception& x) {
	cerr << "error: " << x.what() << endl;
	return 1;
}




