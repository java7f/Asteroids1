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
	//To be implemented later
	bool GetKeyF();
	bool GetKeyQ();
	bool GetKeyE();
	bool GetKeySpaceBar();


	void SetKeyW(bool);
	void SetKeyA(bool);
	void SetKeyD(bool);
	//To be implemented later
	void SetKeyF(bool);
	void SetKeyQ(bool);
	void SetKeyE(bool);
	void SetKeySpaceBar(bool);

private:
	/*Members*/
	bool keyW_;
	bool keyA_;
	bool keyD_;

	//Members that would be used later
	bool keyF_;
	bool keyQ_;
	bool keyE_;
	bool spaceBarKey_;
};

