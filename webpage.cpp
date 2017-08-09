#include "webpage.h"
#include "myset.h"
#include <fstream>

WebPage::WebPage() {}

WebPage::WebPage(std::string filename) { this->finame = filename; }

 /**
  * Sets the filename/URL of this webpage
  */

void WebPage::filename(std::string fname) {
  finame = fname;
}

 /**
   * Returns the filename/URL of this webpage
   */
std::string WebPage::filename() const {
  return this->finame;
}

  /**
   * Updates the set containing all unique words in the text
   *  with the contents of the input parameter words
   */
void WebPage::all_words(const MySetString& words) {
  allWords = allWords.set_union(words);
}

  /**
   * Returns all the unique, tokenized words in this webpage 
   */
MySetString  WebPage::all_words() const {
  return this->allWords;
}

  /**
   * Adds a webpage that links to this page
   */
void WebPage::add_incoming_link(WebPage* wp) {
  inLinks.insert(wp);
}

  /**
   * Returns all webpages that link to this page
   */
MySetWebPage WebPage::incoming_links() const {
  return this->inLinks;
}

  /**
   * Adds a webpage that this page links to
   */
void WebPage::add_outgoing_link(WebPage* wp) {
  outLinks.insert(wp);
}

  /**
   * Returns all webpages this page links to
   */
MySetWebPage WebPage::outgoing_links() const {
  return this->outLinks;
}

  /**
   * Displays the webpage text to the screen 
   */
std::ostream & operator<< (std::ostream & os, const WebPage & page) {

  std::string curr;
  std::ifstream infile;
  infile.open(page.filename().c_str());

  while(infile >> curr) {

    unsigned int i = 0;

    //if still in bounds
    if(i<curr.length()) {

    //as long as i is not the beginning of anchor text
    if(curr.at(i)!=91) {
      os << curr.at(i);
      i++;
    }

    //if we encounter anchor text
    else if(curr.at(i)==91) {
      //while we are not at the end of the anchor text
      while(curr.at(i)!=93) {
        os << curr.at(i);
        i++; 
      }
      //when we do reach the end
      if(curr.at(i)==93) {
        os << curr.at(i);
        i++;
      }
      if(curr.at(i)==40) {
        while(curr.at(i)!=41) {
          i++;
        }
        i++;
      }
    }

    os << " ";

    }
  }
  infile.close();
  return os;
}

WebPage::~WebPage() {}