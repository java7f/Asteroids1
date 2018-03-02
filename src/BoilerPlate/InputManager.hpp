#pragma once
class InputManager
{
public:
	/*Constructors*/
	InputManager();
	~InputManager();


	/*Functions*/
	bool GetKeyW();
	bool GetKeyA();
	bool GetKeyD();


	void SetKeyW(bool);
	void SetKeyA(bool);
	void SetKeyD(bool);

private:
	/*Members*/
	bool keyW_;
	bool keyA_;
	bool keyD_;
};

