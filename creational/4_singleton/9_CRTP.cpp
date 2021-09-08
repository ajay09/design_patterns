/*
	In some application, you may want multiple Classes to behave as Singletons
	so you will have to implement the singular behavior in all the classes.

	But there is a way of reusing the singular behavior in different classes
	and then all the classes will automatically become Singleton Classes.

	CRTP - Curiously Recurring Template Pattern
		   An idiom in C++ where a template based Class is inherited in a child Class
		   and then it provides some behavior which is inherited by the Child class.

		   In this case the behavior will be Singular behavior.

	
	Thus using CRTP any class can be made singleton using inheritance.
*/

///////////////////////////////////////////////
///////////////     BaseSingleton.h
///////////////////////////////////////////////

// #pragma once

template<typename T>
class BaseSingleton {
protected:
	BaseSingleton() = default;
	// to ensure the instances of this class can't be copied or assigned
	// we will implement the non-copyable idiom.
	BaseSingleton(const BaseSingleton&) = delete;
	BaseSingleton& operator=(const BaseSingleton&) = delete;
public:
	static T& Instance() {
		static T instance;
		return instance;
	}
};


///////////////////////////////////////////////
///////////////     GameManager.h
///////////////////////////////////////////////
// We want our GameManager class to be Singleton as well.

class GameManager : public BaseSingleton<GameManager> {
private:
	GameManager() = default;
	// make BaseSingleton a friend of the Child class(here GameManager)
	// This is important because an instance of GameManager will be created
	// by the BaseSingleton and since constructor of GameManager is private.
	// So, we need to make it a friend of the GameManager class
	friend class BaseSingleton<GameManager>;

public:
	void LoadAssets() {}
	void Run() {}
};


///////////////////////////////////////////////
///////////////     client.cpp
///////////////////////////////////////////////

int main() {
	GameManager &gm = GameManager::Instance();
	gm.Run();

	return 0;
}



/*
	To make declaring new Singleton Classes easier, we can define a macro.

	#define MAKE_SINGLETON(class_name) private: class_name() = default;\
	friend class BaseSingleton<class_name>

	class New_Class : public BaseSingleton<New_Class> {
		MAKE_SINGLETON<New_Class>
	public:
		void func();
	};

*/