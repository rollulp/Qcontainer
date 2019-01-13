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

void ab() {
	Container<int> a;
	for (int i = 0; i < 40; i++)
		a.push_back(i);
	print(a);
	cout << "hi" << endl;
	for (Container<int>::iterator it = a.select(new selector); it; cout << "it:" << *it << endl, it.delete_and_advance());
	cout << "mydick" << endl;
	print(a);
}

struct B {
	int i;
	virtual int getI() { return i; }
};
struct D1 : public B {
	int j;
	int getI() { return j; }
};
struct D2 : virtual public B {
	int k;
	int getI() { return k; }
};
void a() {
	B *b1 = new D1;
	//B *b2 = new D2;
	reinterpret_cast<D2*>(b1)->k = 3;
	b1->i = 4;
	auto f = reinterpret_cast<int(B::*)()>(&D2::getI);
	auto i = (b1->*f)();
	cout << "i : " << i << endl;
	cout << "i : " << b1->i << endl;
}
