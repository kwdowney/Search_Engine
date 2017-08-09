#include "myset.h"
#include "webpage.h"
#include <iostream>

MySetString::MySetString() : std::set<std::string>() {}

MySetString MySetString::set_intersection(const MySetString& other) {
	std::set<std::string>::iterator it1;
	std::set<std::string>::iterator it2;
	MySetString newSet;

	//iterate through the two MySets
	//for each entry, check to see if it matches any of the entries in the other MySet
	for(it1 = this->begin(); it1!=this->end(); ++it1) {
		for(it2 = other.begin(); it2 != other.end(); ++it2) {
			if(*it1 == *it2) {
				newSet.insert(*it1);
			}
		}
	}
	return newSet;
}


//simply add each entry of the two MySets into a single MySet
MySetString MySetString::set_union(const MySetString& other) {
	std::set<std::string>::iterator it1;
	std::set<std::string>::iterator it2;
	MySetString newSet;
	
	for(it1 = this->begin(); it1!=this->end(); ++it1) {
		newSet.insert(*it1);
	}

	for(it2 = other.begin(); it2 != other.end(); ++it2) {
		newSet.insert(*it2);
	}
	return newSet;
}

//do the same for MySetWebPages

MySetWebPage::MySetWebPage() : std::set<WebPage*>() {}

MySetWebPage MySetWebPage::set_intersection(const MySetWebPage& other) {
	std::set<WebPage*>::iterator it1;
	std::set<WebPage*>::iterator it2;
	MySetWebPage newWebPageSet;
	
	for(it1 = this->begin(); it1!=this->end(); ++it1) {
		for(it2 = other.begin(); it2 != other.end(); ++it2) {
			if((*it1) == (*it2)) {
				newWebPageSet.insert(*it1);
			}
		}
	}

	return newWebPageSet;
}

MySetWebPage MySetWebPage::set_union(const MySetWebPage& other) {
	std::set<WebPage*>::iterator it1;
	std::set<WebPage*>::iterator it2;
	MySetWebPage newWebPageSet;
	
	for(it1 = this->begin(); it1!=this->end(); ++it1) {
		newWebPageSet.insert(*it1);
	}

	for(it2 = other.begin(); it2!=other.end(); ++it2) {
		newWebPageSet.insert(*it2);
	}

	return newWebPageSet;
}
