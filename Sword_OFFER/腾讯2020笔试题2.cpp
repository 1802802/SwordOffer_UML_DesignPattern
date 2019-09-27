//#include <iostream>
//#include <set>
//#include <stack>
//#include <string>
//#include <vector>
//#include <stdio.h>
//using namespace std;
//
//// 自行完成以下代码，可以任意增加函数
//class BaseDataDef {
//private:
//	string m_type;
//	string m_name;
//	string m_value;
//public:
//	string getType() const;
//	string getName() const;
//	string getValue() const;
//
//	virtual ~BaseDataDef() {}
//	// 基础类型变量赋值的代码生成
//	virtual string getInitializeCode() {
//	}
//};
//
//class StructDef : public BaseDataDef {
//private:
//
//public:
//	void addMemeber(BaseDataDef* member) {
//	}
//	virtual string getInitializeCode() {
//	}
//};
//
//BaseDataDef* parseData() {
//}
//
//
//
//int main_tencent222() 
//{
//	int n;
//	cin >> n;
//	string res;
//	for (int i = 0; i < n; ++i) 
//	{
//		BaseDataDef* data = parseData();
//		res += data->getInitializeCode();
//		delete data;
//	}
//	cout << res;
//	return 0;
//}