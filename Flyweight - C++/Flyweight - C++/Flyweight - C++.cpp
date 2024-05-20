#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct Shared {
	string company;
	string position;

	Shared(const string& company_, const string& position_) : company(company_), position(position_) {}
};

struct Unique {
	string passport;
	string name;
	Unique(const string& name_, const string& passport_) : name(name_), passport(passport_) {}
};

class Flyweight {
private:
	Shared* shared;
public:
	Flyweight(const Shared* shared_) : shared(new Shared(*shared_)){}
	Flyweight(const Flyweight& other) : shared(new Shared(*other.shared)){}
	~Flyweight() {
		delete shared;
	}
	void Process(const Unique& unique) const {
		cout << "" << shared->company << "_" << shared->position << unique.name << unique.passport << "\n";
	}
};

class FlyweightFactory {
private:
	unordered_map<string, Flyweight> flyweights;
	string GetKey(const Shared& shared) const {
		return shared.company + "_" + shared.position;
	}
public:
	FlyweightFactory(initializer_list<Shared> shareds) {
		for (const Shared& shared : shareds) {
			this->flyweights.insert(make_pair<string, Flyweight>(this->GetKey(shared), Flyweight(&shared)));
		}
	}
	Flyweight GetFlyweight(const Shared& shared) {
		string key = this->GetKey(shared);
		if (this->flyweights.find(key) == this->flyweights.end()) {
			cout << key << "\n";
			this->flyweights.insert(make_pair(key, Flyweight(&shared)));
		}
		else {
			cout << key << "\n";
		}
		return this->flyweights.at(key);
	}
	void ListWeight() const {
		size_t count = this->flyweights.size();
		cout << "\n" << count << "\n";
		for (pair <string, Flyweight> pair : this->flyweights) {
			cout << pair.first << "\n";
		}
	}
};

void AddSpecialistDatabase(FlyweightFactory& ff, const string& company, const string& position, const string& name, const string passport) {
	cout << "\n";
	const Flyweight& flyweight = ff.GetFlyweight({ company, position });
	flyweight.Process({ name, passport });
}

int main() {
	FlyweightFactory* factory = new FlyweightFactory({ { "Microsoft", "Director" },
													{ "Google", "Android - developer" },
													{ "Google", "Web - developer" },
													{ "Apple", "Iphone - developer" } });
	factory->ListWeight();
	AddSpecialistDatabase(*factory, "Google", "Web - developer", "Boris", "AM-17234332");
	AddSpecialistDatabase(*factory, "Apple", "Director", "Alex", "DE-22212244");
	factory->ListWeight();
	delete factory;
}