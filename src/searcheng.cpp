#include "searcheng.h"
#include <fstream>
#include <iostream>

SearchEng::SearchEng() {}

void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser) {

	std::ifstream indexFile;
	std::string file_name;
	indexFile.open(index_file.c_str());
	std::set<WebPage*>::iterator it;
	std::set<WebPage*>::iterator it2;

	//loop through the contents of the index file, grabbing the name of the webpage
	// that is on each line, sending each to our add_parse_page function
	while(!indexFile.eof()) {
		getline(indexFile, file_name);
		//std::cout << file_name << std::endl;
		if(file_name.length()>0) {
			add_parse_page(file_name, parser); 
		}
	}
	//std::cout << allpages.size() << std::endl;
	populateIncomingLink();

}

void SearchEng::add_parse_page(std::string filename, PageParser* parser) {

	MySetString allWords;
	MySetString allLinks;
	MySetString::iterator it1;

	WebPage* wp = new WebPage(filename);

	//std::cout << "before parse " << filename << std::endl;

	parser->parse(filename, allWords, allLinks);

	//std::cout << "after parse" << std::endl;

	//populate the outgoing of our webpage
	for(it1=allLinks.begin(); it1!=allLinks.end(); ++it1) {
		//std::cout << *it1 << std::endl;
		WebPage* toAdd = new WebPage(*it1);
		wp->add_outgoing_link(toAdd);
	}

	//update our master list of webpages with our current page
	allpages.insert(wp);

	//std::cout << allLinks.size() << std::endl;

	//cycle through all the words found on the webpage
	for(it1=allWords.begin(); it1!=allWords.end(); ++it1) {

		//std::cout << *it1 << std::endl;
		//std::cout << map1.size() << std::endl;
	
		//check if the word is already in the map
		//if it is, update the MySetWebPage in the map with the new webpage
		//if it is not, create a new MySetWebPage, add the webpage and then insert that into map
		if(map1.find(*it1)!=map1.end()) {

			//get the set of web pages
			std::map<std::string, MySetWebPage>::iterator it2;

			it2 = map1.find(*it1);

			MySetWebPage setwp = it2->second;

			std::set<WebPage*>::iterator it3;
			for(it3 = setwp.begin(); it3!=setwp.end(); ++it3) {
				if((wp)->filename()==(*it3)->filename()) {
					return;
				}
			}

			//update it with the new web page
			setwp.insert(wp);
			map1[*it1] = setwp;

		} else {

		MySetWebPage setwp;
		setwp.insert(wp);

		map1.insert(make_pair(*it1, setwp));
		//std::cout << *it1 << std::endl;
		}
	}
	//std::cout << map1.size() << std::endl;
/*
	std::map<std::string, MySetWebPage>::iterator iti;

	for(iti = map1.begin(); iti!=map1.end(); ++iti) {
		std::cout << iti->first << " " << iti->second.size() << std::endl;
	}*/
}

std::map<std::string, MySetWebPage> SearchEng::initMap() {
    return this->map1;
}


//start with a webpage
//go through our master list of webpages
//access their outgoing links, if our webpage is found amongst them,
// add the former to the latter's list of incoming links
void SearchEng::populateIncomingLink() {
	std::set<WebPage*>::iterator it;
	std::set<WebPage*>::iterator it2;
	MySetWebPage out;

	for(it = allpages.begin(); it!=allpages.end(); ++it) {

		out = (*it)->outgoing_links();
		//std::cout << (*it)->outgoing_links().size() << std::endl;

		//std::cout << out.size() << std::endl;

		//std::cout << "+++++++++++++" << std::endl;

		for(it2 = out.begin(); it2!=out.end(); ++it2) {
			(*it2)->add_incoming_link(*it);
		}
	}
}
