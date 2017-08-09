#ifndef ELEM_PARSER_H
#define ELEM_PARSER_H

#include <string>
#include "myset.h"

/**
 * Base class for parsers (for some specific
 *  format such as MD or HTML)
 */

class PageParser {
 public:
  virtual ~PageParser() { }

  /** 
   * Parses a file and returns all unique words according
   *  to some parser rules and all hyperlinks based 
   *  on the format the parser is designed to implement
   */
  virtual void parse(std::string filename,
		     MySetString& allWords,
		     MySetString& allLinks) = 0;
};

class Parsemd : public PageParser {

public: 
	Parsemd();
	~Parsemd();
	void parse(std::string filename,
		     MySetString& allWords,
		     MySetString& allLinks);
	void generalParse(std::string input, MySetString& allinputs, MySetString& allLinks);
	void linkParse( std::string input, MySetString& allinputs, MySetString& allLinks);
};

#endif