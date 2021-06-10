#include <iostream>
#include <cstdint>
#include <ctime>
#include <unordered_map>
#include <string>

class File{
public:
	std::string read(){
		return this->data;
	}
	std::string getFilename(){
		return this->filename;
	}
	time_t getCreationDate(){
		return this->creation;
	}
	time_t getModificationDate(){
		return this->lastmodified;
	}
	void write(std::string d){
		this->data =d;
	}
	void append(std::string d){
		this->data += d;
	}
	void setCreation(time_t time){
		this->creation = time;
	}
	void setModified(time_t time){
			this->lastmodified = time;
	}
	void setFilename(std::string filename){
		this->filename = filename;
	}
	void setPath(std::string p){
		this->path = p;
	}
private:
	std::string data;
	std::string filename;	std::string path;
	time_t creation;
	time_t lastmodified = creation;
};


class MyFS{
public:
	bool createFile(std::string path,std::string filename){
		File* file = new File();
		file->setFilename(filename);
		file->setPath(path);
		file->setCreation(time(NULL));
		file->setModified(time(NULL));

		if(files.find(path+filename) == files.end()){
			this->files.insert(std::make_pair(path+file->getFilename(),file));		
			return true;
		}return false;
	}
	File* getFile(std::string path){
		auto itr = this->files.find(path);
		if(itr == files.end()){
			return NULL;
		}
		return itr->second;
	}
	bool deleteFile(std::string path){
		this->files.erase(path);
		if(getFile(path) == NULL){
			return true;
		}return false;
	}
private:
	uint32_t magic = 0x6D796673;
	std::unordered_map<std::string,File*> files;	// Using unordered_map because of its O(1)
};


int main(){
	MyFS* vfs = new MyFS();
	while(true){
		std::cout << std::endl << "MyFS : ";
		std::string cmd;
		std::cin >> cmd;
		if(cmd == "create"){
			std::string fn;
			std::cout << "Filename : ";
			std::cin >> fn;

			std::string path;
			std::cout << "Path : ";
			std::cin >> path;
			if(vfs->createFile(path,fn)){
				std::cout << fn <<" Created" << std::endl;		
			}else{
				std::cout << fn << " Already Exists" << std::endl;
			}
		}
		else if(cmd == "write"){
			std::string path;
			std::cout << "Path + Filename : ";
			std::cin >> path;
			File* file = vfs->getFile(path);
			if(file != NULL){
			
			std::cout << "Data : ";
			std::string d;
			std::cin >> std::ws >> d;
			file->write(d);
			std::cout << "Written successfly" << std::endl;
			}else{
				std::cout << "Cannot write" << std::endl;
			}
		}
		else if(cmd == "read"){
			std::string path;
			std::cout << "Path + Filename : ";
			std::cin >> path;
			File* file = vfs->getFile(path);
			if(file != NULL){
				std::cout << file->read() << std::endl;
			}else{
				std::cout << "Not Found" << std::endl;
			}
		}
		else if(cmd == "delete"){
			std::string path;
			std::cout << "Path + Filename : ";
			std::cin >> path;

			if(vfs->deleteFile("path")){
				std::cout << path+" deleted successfly"<< std::endl;
			}else{
				std::cout << "cannot delete file" << std::endl;
			}
		}
		else if(cmd == "quit"){
			break;
		}
		else if(cmd == "help"){
			std::cout << "create | write | read | delete | quit | help" << std::endl;
		}
		else{
			std::cout << "Command not found" << std::endl;
		}
	}
	return 0;
}
