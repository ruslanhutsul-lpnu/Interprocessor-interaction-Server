#pragma once
#include<string>
public class Process {
private:
	int id;
	char* name;
	char* status;
	char* priority;
	int time;
public:
	Process(int id1, char* name1, char* status1, char* priority1, int time1) {
		id = id1;
		strcpy(name, name1);
		strcpy(status, status1);
		strcpy(priority, priority1);
		time = time1;
	}
	int getId() {
		return id;
	}
	char* getName() {
		return name;
	}
	char* getStatus() {
		return status;
	}
	char* getPriority() {
		return priority;
	}
	int getTime() {
		return time;
	}

};