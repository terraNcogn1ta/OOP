#ifndef __BASECLASS_H
#define __BASECLASS_H


#include <string>
#include <vector>
class BaseClass;
extern std::vector <std::string> miscellaneousMessages;


//www.newty.de/fpt/fpt.html#defi*/
//using SIGNAL_TYPE = void (BaseClass::* const)(std::string&);
//using HANDLER_TYPE = void (BaseClass::* const)(std::string);
typedef void (BaseClass::* SIGNAL_TYPE) (std::string&);
typedef void (BaseClass::* HANDLER_TYPE) (std::string);


struct Connection {
	BaseClass* object;
	SIGNAL_TYPE signalMethod;
	HANDLER_TYPE handlerMethod;
};


class BaseClass {
private:
	std::string name;
	BaseClass* parent;

	bool isReady = true;
protected:
	std::vector <BaseClass*> children;
	std::vector <Connection> connections;
	unsigned ID = 0;
public:
	BaseClass(BaseClass* parent, const std::string name = "BaseClassObject");
	~BaseClass();
	void setName(std::string name);
	const std::string getName() const;
	void changeParent(BaseClass* newParent);
	BaseClass* getParent() const;
	void printRoot(const unsigned indent = 0) const;
	BaseClass* findObjectInTree(const std::string& objectName) const;
	BaseClass* findObjectAmongChildren(const std::string& objectName) const;
	void addChild(BaseClass* child);
	void recursiveCleanUp();

	const std::string getFullPath();

	bool areAllParentsReady();
	void setTrueReadiness();
	void setFalseReadiness();
	void setCondition(const int condition);

	virtual void signal(std::string& message) = 0;
	void emitSignal(std::string& message);
	virtual void handler(std::string) = 0;

	//this is not supposed to be working whatsoever
	virtual SIGNAL_TYPE getSignal() = 0;
	virtual HANDLER_TYPE getHandler() = 0;

	unsigned int getID();
	bool getReadiness();
public:
	void setConnection(BaseClass*& recipient, SIGNAL_TYPE donorSignal, HANDLER_TYPE recipientHandler);
	void removeConnection(BaseClass*& target, SIGNAL_TYPE donorSignal, HANDLER_TYPE recipientHandler);
};	
#endif // __BASECLASS_H