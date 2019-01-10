#include "container.h"

void print(const Container<int> &u) {
	auto i = u.begin();
	while (i) {
		cout << *i << ' ';
		++i;
	}
	cout << endl;
}

class selector : public Validator<int> {
	Validator<int>* clone() const override { return new selector; }
	bool operator () (const int &i) const override { return !(i%2); }
};

void a() {
	Container<int> a;
	for (int i = 0; i < 40; i++)
		a.push_back(i);
	print(a);
	cout << "hi" << endl;
	for (Container<int>::iterator it = a.select(new selector); it; cout << "it:" << *it << endl, it.delete_and_advance());
	cout << "mydick" << endl;
	print(a);
}
