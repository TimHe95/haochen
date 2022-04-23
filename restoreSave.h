#include "tainter.h"


const int vertif = 0x1234abcd;		//vertif放在文件的开头和结尾用于简单判断是否正确读取数据 
string filePath = "gepData";	


//将vector保存到二进制文件 
int saveData(vector< pair < pair < Type *, vector<int> >, Value* > > & Data){

	//将vector保存到文件,格式：4字节检验码+4字节数组长度+4字节数据长度+可变长度的数据+4字节尾部检验码
	ofstream ofile(filePath.c_str(), ios::binary);
	if(ofile.is_open()==false){
		cout<<"Open file fail!"<<endl;
		exit(1);
	}
	ofile.write((char*)&vertif, sizeof(int));
	
    // 4字节数组长度
	int length = Data.size();
	ofile.write((char*)&length, sizeof(int)); 

	// Write 可变长度的数据
     
    for(vector<pair<pair<Type* , vector<int>>, Value* >>::iterator it = Data.begin(); it!=Data.end(); it++)    {    

        // Type
        ofile.write((char*)&(*(it->first.first)), sizeof(Type));

        // lenght of `vector<int>`
        int l = it->first.second.size();
        ofile.write((char*)&l, sizeof(int)); 

        // vector<int>
        for(vector<int>::iterator it2 = it->first.second.begin(); it2!=it->first.second.end(); it2++){
            ofile.write((char*)&(*it2), sizeof(int));
        }

        // Value
        ofile.write((char*)&(*(it->second)), sizeof(Value));              
    }

    // 4字节尾部检验码
	ofile.write((char*)&vertif, sizeof(int));
	
	ofile.close();
    llvm::outs() << "SAVED.\n";
	return 0;
} 

//从二进制中读取之前保存的数据并还原vector
vector< pair < pair < Type*, vector<int> >, Value*> > restore(){
	ifstream ifile(filePath.c_str(), ios::binary);
	int tmpVertif, length, totalSize;

    // 4字节检验码
	ifile.read((char*)&tmpVertif, sizeof(int));
	if (tmpVertif!=vertif){
		cout<<"Unknow format at the begin of file..."<<endl;
		exit(1);
	} else {
        cout<<"Restore verify OK. [START]"<<endl;
    }

    // 4字节数组长度
	ifile.read((char*)&length, sizeof(int));

    // 可变长度的数据
	vector< pair < pair < Type*, vector<int> >, Value*> > Data;	

    for(int i=0; i<length; i++){    

        // Type
        Type* t = (Type*) malloc(sizeof(Type));
        ifile.read((char*)&(*t), sizeof(Type));

        // lenght of `vector<int>`
        int l;
        ifile.read((char*)&l, sizeof(int)); 

        // vector<int>
        vector<int> vec(l);
        for(int j=0; j<l; j++){
            ifile.read((char*)&(vec[j]), sizeof(int));
        }

        // Value
        Value* v = (Value*) malloc(sizeof(Value));
        ifile.read((char*)&(*v),   sizeof(Value));

        pair < Type*, vector<int> > pp(t, vec);
        pair < pair < Type*, vector<int> >, Value*> p(pp, v);
        Data.push_back(p);
    }

    // 4字节尾部检验码
	ifile.read((char*)&tmpVertif, sizeof(int));	
    if (tmpVertif!=vertif){
		cout<<"Unknow format at the end of file..."<<endl;
		exit(1);
	} else {
        cout<<"Restore verify OK. [END]"<<endl;
    }

    for(vector< pair < pair < Type*, vector<int> >, Value*> >::iterator it = Data.begin(); it!=Data.end(); it++)    {    
        //it->second->print(llvm::outs());
        //llvm::outs() << " ";
        //it->first.first->print(llvm::outs());
        for(vector<int>::iterator it2 = it->first.second.begin(); it2!=it->first.second.end(); it2++)
            llvm::outs() << ", " << *it2;
        //llvm::outs() << "\n";
    }

	return Data;
} 
