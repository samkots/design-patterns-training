
#include <iostream>
#include <string>
#include <vector>


using namespace std;


class Point {
public:
	Point(double x = 0.0, double y = 0.0, double z = 0.0)
		:x_{x}, y_{y}, z_{z} {}

private:
	double x_, y_, z_;
};

class Document {
public:
	void add_point(Point* pt) { points_.push_back(pt); }

private:
	vector<Point*> points_;
};

///

class ICommand {
public:
	virtual void exe() = 0;
};

class New_doc_cmd : public ICommand {
public:
	void exe();
};

class Exit_cmd : public ICommand {
public:
	void exe() {
		cout << "Exit_cmd::exe() called" << endl;
		exit(0);
	}
};

class Create_point_cmd : public ICommand {
public:
	void exe();
};

///

class Menu_item {						// invoker
public:
	Menu_item(const string& name)
		:name_{name}, cmd_{nullptr} {}

	void set_cmd(ICommand* cmd) { cmd_ = cmd; }

	void clicked() { if (cmd_) cmd_->exe(); }

private:
	string		name_;
	ICommand*	cmd_;
};

class Menu {
public:
	Menu(const string& name)
		:name_{name} {};

	void add_menu_item(Menu_item* mi) {
		menu_items_.push_back(mi);
	}

	// for click simulation
	Menu_item* get_menu_item(int pos) {
		try {
			return menu_items_.at(pos);
		} catch(...) {
			return nullptr;
		}
	}

private:
	string name_;
	vector<Menu_item*> menu_items_;
};

class Menu_bar {
public:
	void add_menu(Menu* menu) {
		menus_.push_back(menu);
	}

	// for click simulation
	Menu* get_menu(int pos) {
		try {
			return menus_[pos];
		} catch (...) {
			return nullptr;
		}
	}

private:
	vector<Menu*>	menus_;
};

///

class App {
public:
	App(const App&) = delete;
	App& operator = (const App&) = delete;

	void setup_ui() {
		menu_bar_ = new Menu_bar();

		// create menus
		Menu* menu_file = new Menu("File");
		menu_bar_->add_menu(menu_file);

		Menu* menu_edit = new Menu("Edit");
		menu_bar_->add_menu(menu_edit);

		menu_bar_->add_menu(new Menu("Help"));

		// populate "File" menu with "New" & "Exit"
		Menu_item* menu_item_new_doc = new Menu_item("New");
		menu_item_new_doc->set_cmd(new New_doc_cmd);
		menu_file->add_menu_item(menu_item_new_doc);

		Menu_item* menu_item_exit = new Menu_item("Exit");
		menu_item_exit->set_cmd(new Exit_cmd);
		menu_file->add_menu_item(menu_item_exit);

		// populate "Edit" menu with "Create point"
		Menu_item* mi_create_pt = new Menu_item("Create point");
		mi_create_pt->set_cmd(new Create_point_cmd);
		menu_edit->add_menu_item(mi_create_pt);
	}

	void run() {
		while (true) {
			int m_pos = 0;
			cout << "Enter the menu to click: ";
			cin >> m_pos;

			int mi_pos = 0;
			cout << "Enter the menu item to click: ";
			cin >> mi_pos;

			Menu_item* mi = this->get_menu_item(m_pos, mi_pos);
			if (!mi) {
				cerr << "invalid menu item!" << endl;
				continue;
			}
			else
				mi->clicked();
		}
	}

	void add_doc(Document* doc) {
		docs_.push_back(doc);
		active_doc_ = docs_.size() - 1;
	}

	int get_doc_count() const { return docs_.size(); }
	Document* get_active_doc() const {
		if (active_doc_ == -1)
			return nullptr;
		return docs_[active_doc_];
	}

	// for click simulation
	Menu_item* get_menu_item(int m_pos, int mi_pos) {
		if (!menu_bar_)
			return nullptr;

		Menu* menu = menu_bar_->get_menu(m_pos);
		if (!menu) {
			return nullptr;
		}
		return menu->get_menu_item(mi_pos);
	}

private:
	Menu_bar*		menu_bar_;
	vector<Document*>	docs_;
	int			active_doc_;

public:				// singleton stuff
	static App* get_app()
	{
		//cout << "App::App() called" << endl;
		if (!app_)
			app_ = new App;
		return app_;
	}

private:
	App()
		:menu_bar_{nullptr}
		,active_doc_{-1} {}

	static App*	app_;
};

App* App::app_{nullptr};

///

int test_menu_item()
{
	Menu_item* menu_item = new Menu_item("Exit");
	ICommand* exit_cmd = new Exit_cmd;

	menu_item->set_cmd(exit_cmd);
	menu_item->clicked();
	return 0;
}

///

void New_doc_cmd::exe() {
	cout << "Creating new document." << endl;
	Document* doc = new Document();

	App* app = App::get_app();
	app->add_doc(doc);
}

void Create_point_cmd::exe() {
	App* app = App::get_app();
	Document* active_doc = app->get_active_doc();
	if (!active_doc) {
		cerr << "No active document!" << endl;
		return;
	}

	cout << "Enter x, y & z coordinates: ";
	double x{0.0}, y{0.0}, z{0.0};
	cin >> x >> y >> z;

	active_doc->add_point(new Point{x, y, z});

	cout << "point created!" << endl;
}

///

int main()
{
	App* app = App::get_app();
	app->setup_ui();
	app->run();
}


