#include "pageparser.h"
#include "myset.h"
#include <fstream>
#include <iostream>

void generalParse( std::string input, MySetString& allinputs, MySetString& allLinks);

Parsemd::Parsemd() {}

void Parsemd::parse(std::string filename, MySetString& allinputs, MySetString& allLinks) {

	std::ifstream inFile;
	inFile.open(filename.c_str());
	std::string curr;

	while(inFile >> curr) {
		generalParse(curr, allinputs, allLinks);
	}

	inFile.close();
}

void Parsemd::generalParse( std::string input, MySetString& allinputs, MySetString& allLinks ) {

	std::string output = "";
	std::string link = "";
	std::string anchorText = "";

	for(unsigned int i = 0; i<input.length(); i++) {

		//if we run into a [, it is anchor text
		if( (input.at(i)==91) ) {
			
			if(output.length()>0) {
				allinputs.insert(output);
			}
			i++;
			
			while(input.at(i)!=93 && i<input.length()-1) {
				anchorText += input.at(i);
				i++;
			}

			anchorText += input.at(i);
		}

		//if we run into a ], we have reached the end of anchor text
		//check to see if there is text directly after the ], if there is
		//we need to parse it and add it toallinputs
		else if(input.at(i)==93) {
			i++;
			if(input.at(i)==40) {
				i++;
				while(input.at(i)!=41) {
					link += input.at(i);
					i++;
				}
			}
			allLinks.insert(link);
		}	

		//if the char is lowercase or a number, use it
		else if(  (input.at(i)>=48 && input.at(i)<= 57) || (input.at(i)>=97 && input.at(i)<=122) ) {
			output += input.at(i);
		}

		//if it is capitalized, make it lowercase
		else if ( (input.at(i)>=65 && input.at(i)<=90) ) {
			output += (input.at(i)+32);
		}

		//whatever is left, shoot it off to allinputs
		else {
			allinputs.insert(output);
			output = "";
		}	
	}
	allinputs.insert(output);
}

Parsemd::~Parsemd() {}
