/*

				--------------------					----------					 --------------------								
				|    Aggregate     |<-------------------| Client |------------------>|    Iterator      |													
				--------------------				    ----------					 --------------------								
				| CreateIterator() |												 | First()          |	
				--------------------												 | Next()           |  
						/_\															 | IsDone() 		|
						 |															 | CurrentItem()    |
						 |															 --------------------
						 |																	 /_\
						 |																	  |
						 |																	  |
				---------------------												 --------------------
				| ConcreteAggregate |...............................................>| ConcreteIterator |
				---------------------												 -----;--------------
				| CreateIterator()  |<-----------------------------------------------------
				---------------------
					return new ConcreteIterator(this);

*/


///////////////////////////////////////
//////////////////////// Iterator.h
///////////////////////////////////////
template <typename Item>
class Iterator {
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() const = 0;
	virtual const Item& CurrentItem() const = 0;

	~Iterator() = default;
};


///////////////////////////////////////
//////////////////////// Aggregate.h
///////////////////////////////////////
template<typename Item>
class Aggregate {
public:
	virtual Iterator<Item> *CreateIterator() const = 0;

	~Aggregate() = default;
};


/////////////////////////////////////////////
//////////////////////// ConcreteAggregate.h
////////////////////////////////////////////
#include <cstddef> // for size_t
class ConcreteAggregate : public Aggregate<int> {
	static constexpr size_t MAX_SIZE{5};
	int m_Items[5]{10, 20, 30, 40, 50};
public:
	size_t Size() const {
		return MAX_SIZE;
	}

	Iterator<int>* CreateIterator() const override;

	const int* GetArray() const {
		return m_Items;
	}
};


////////////////////////////////////////////
//////////////////////// ConcreteIterator.h
////////////////////////////////////////////
class ConcreteIterator : public Iterator<int> {
	const  ConcreteAggregate *m_pAgg;
	size_t m_Position{0};
public:
	ConcreteIterator(const ConcreteAggregate* pAgg) : m_pAgg{pAgg} {}

	void First() override {
		m_Position = 0;
	}

	void Next() override {
		m_Position++;
	}

	bool IsDone() const override {
		return m_Position == m_pAgg->Size();
	}

	const int& CurrentItem() const override {
		return m_pAgg->GetArray()[m_Position];
	}
};


Iterator<int>* ConcreteAggregate::CreateIterator() const {
	return new ConcreteIterator{this};
}



#include <iostream>

int main() {
	ConcreteAggregate cagg{};
	auto itr = cagg.CreateIterator();
	itr->First();
	while (!itr->IsDone()) {
		std::cout << itr->CurrentItem() << ' ';
		itr->Next();
	}

	std::cout << std::endl;
	return 0;
}