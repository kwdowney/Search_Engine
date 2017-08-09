#include "mainwindow.h"
#include "webpage.h"
#include "searcheng.h"
#include "msort.h"
#include <string>
#include <set>
#include <QString>
#include <sstream>

using namespace std;

//structs to sort by filename, incoming, outgoing links

struct FilenameComp {
    bool operator()(const WebPage* lhs, const WebPage* rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs->filename() < rhs->filename(); 
    }
 };

struct OutgoingComp {
    bool operator()( const WebPage* lhs, const WebPage* rhs) 
    { 
      return lhs->outgoing_links().size() < rhs->outgoing_links().size(); 
    }
};

struct IncomingComp {
    bool operator()(const WebPage* lhs, const WebPage* rhs) 
    { 
      return lhs->incoming_links().size() < rhs->incoming_links().size(); 
    }
};

MainWindow::MainWindow(string indexFile) 
{
	//title
	setWindowTitle("Search engine");

	parse = new Parsemd;
	sengine = new SearchEng;
        sengine->add_parse_from_index_file(indexFile, parse);

	//overall layout
	overallLayout = new QHBoxLayout();

	//search input layout
	inputLayout = new QVBoxLayout();

	//prompt the user for search terms
	searchPrompt = new QLabel("Enter items to search for:");
	inputLayout->addWidget(searchPrompt);

	//store the user input
	searchTerms = new QLineEdit();
	inputLayout->addWidget(searchTerms);

	//search criteria
	searchBy = new QGroupBox();
	overallLayout->addWidget(searchBy);
	searchBy->setLayout(inputLayout);

	searchOr = new QRadioButton("OR (for multiple words)");
	inputLayout->addWidget(searchOr);

	searchSingle = new QRadioButton("Single word");
	inputLayout->addWidget(searchSingle);

	searchBy->setLayout(inputLayout);

	//make sure one of the options is always clicked
	searchSingle->setChecked(true);

	//button to launch the search
	execute = new QPushButton("Search");
	inputLayout->addWidget(execute);

	//button to exit the application
	quitButton = new QPushButton("Quit");
	inputLayout->addWidget(quitButton);

	//scrolling table of results
	results = new QListWidget();
	overallLayout->addWidget(results);

	//add layout with buttons to sort results by filename and # of incoming/outgoing links
	toggleResults = new QVBoxLayout();
	sortBy = new QGroupBox();
	overallLayout->addWidget(sortBy);
	resultsTitle = new QLabel("Sort results by:");
	toggleResults->addWidget(resultsTitle);
	filename = new QRadioButton("Filename");
	toggleResults->addWidget(filename);
	incoming = new QRadioButton("# of incoming links");
	toggleResults->addWidget(incoming);
	outgoing = new QRadioButton("# of outgoing links");
	toggleResults->addWidget(outgoing);
	filename->setChecked(true);

	sortBy->setLayout(toggleResults);

	toggleResults->addStretch();
	inputLayout->addStretch();

	setLayout(overallLayout);

	//connect the search and sort functions to user-events (clicks/enter)
	connect(execute, SIGNAL(clicked()), this, SLOT(search()));	
	//connect(results, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showWebPage(QListWidgetItem*)));
	connect(filename, SIGNAL(clicked()), this, SLOT(nameSort()));
	connect(incoming, SIGNAL(clicked()), this, SLOT(inSort()));
	connect(outgoing, SIGNAL(clicked()), this, SLOT(outSort()));
	connect(searchTerms, SIGNAL(returnPressed()), this, SLOT(search()));
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));
}

void MainWindow::search() {

	// Do nothing if user left input blank
	if(searchTerms->text().isEmpty())
	{
		return;
	}

	results->clear();
	foundWebPages.clear();
	
	//fetch the user's input
	string terms = searchTerms->text().toStdString();

	string toSearch = "";
	bool firstWord = true;
	
        MySetWebPage theSet;
    	set<WebPage*>::iterator it2;

     	map<string, MySetWebPage>::iterator it1;
     	map<string, MySetWebPage> theMap;
     	theMap = sengine->initMap();

	//if it's only a single word, simply locate it in our map and 
	//extract the webpages from the set of webpages associated with the 
	//word in the map
    	if(searchSingle->isChecked()) { 
        	for(it1 = theMap.begin(); it1 != theMap.end(); ++it1) {
          		if(terms==it1->first) {
            			theSet = theSet.set_union(it1->second);
          		}
        	}
    	}
   
/*
      else if(searchAnd->isChecked()) {

      unsigned int j =0;
      //if not at a space, continue building the search term
      while(j<terms.length()) {


      	if(terms.at(j)!=' ') {
      		toSearch += terms.at(j);
      	}

      	if(terms.at(j)==' ' || j==terms.length()-1) {
        	if(toSearch.length()>0) {
        		for(it1 = theMap.begin(); it1 != theMap.end(); ++it1) {   	
          			if(it1->first==toSearch) {
            			if(firstWord) {
              				theSet = it1->second;
             	 			firstWord = false;
            			}


            			else {
              				theSet = theSet.set_intersection(it1->second);
            			}
          			}
       			}
        	toSearch = "";      
    		}
      	}

        if(j<terms.length()-1) j++;

        else break;
      }
      }
*/
      	else if(searchOr->isChecked()) {

	unsigned int j =0;
      	//if not at a space, continue building the search term
	      	while(j<terms.length()) {

	      	if(terms.at(j)!=' ') {
	      		toSearch += terms.at(j);
	      	}

			//if we reach a space or the end of the input, we have our word
			//check to make sure it has some length to it
			//use our map matching words to sets of webpages to extract the webpages
			//that contain our word

		      	if(terms.at(j)==' ' || j==terms.length()-1) {
				if(toSearch.length()>0) {
					for(it1 = theMap.begin(); it1 != theMap.end(); ++it1) {	
			  			if(it1->first==toSearch) {
			  				if(firstWord) {
			      					theSet = it1->second;
			      					firstWord = false;
			    				}

			   			else {
			    			theSet = theSet.set_union(it1->second);
			  			}

		      				}
		  			}	

			//reset our dummy string to build the next word from the user's input
		  	toSearch = ""; 
				}
			} 

		//if we are at the end of the user's input, don't loop indefinitely
		if(j<terms.length()-1) j++;	
		else break;	
		}
	}

	//populate our vector that we will use to show the results

       	for(it2 = theSet.begin(); it2 != theSet.end(); ++it2) {
      		foundWebPages.push_back(*it2);
      	}
	
	//call the proper sort functions if a radio button is pressed
      	if(incoming->isChecked()) inSort();
      	if(outgoing->isChecked()) outSort();
     	// nameSort();

	//update the display to reflect the changes in sorting or otherwise
      	displayResults(foundWebPages);

	//make sure we start fresh for our new search
      	theSet.clear();
}

void MainWindow::nameSort() {
	FilenameComp comp;
	if(foundWebPages.size()>0) {
	mergeSort(foundWebPages, comp);
	}
	displayResults(foundWebPages);
}

void MainWindow::inSort() {
	IncomingComp comp;
	mergeSort(foundWebPages, comp);
	displayResults(foundWebPages);
	//for(unsigned int i = 0; i<foundWebPages.size(); i++) {
	//cout << (foundWebPages[i])->incoming_links().size() << endl;
	//}
}

void MainWindow::outSort() {
	OutgoingComp comp;
	if(foundWebPages.size()>0) {
	mergeSort(foundWebPages, comp);
	}
	displayResults(foundWebPages);
}

void MainWindow::displayResults(vector<WebPage*> setwp) {
	results->clear();

	for(unsigned int i = 0; i<setwp.size(); i++) {
		results->addItem(QString::fromStdString((setwp[i])->filename()));
	}
}

/*void MainWindow::showWebPage(QListWidgetItem* clickedWebPage) {
	page = new QWidget();
	textOfWebPage = new QLineEdit();
	//inLinks = new QListWidget();
	//outLinks = new QListWidget();
	pageLayout = new QHBoxLayout();
	pageLayout->addWidget(textOfWebPage);
	//pageLayout->addWidget(inLinks);
	//pageLayout->addWidget(outLinks);
	page->setWindowTitle(clickedWebPage->text());
	WebPage *wp = new WebPage(clickedWebPage->text().toStdString());
	sengine->add_parse_page(clickedWebPage->text().toStdString(), parse);

	stringstream ss;
	QString stringTemp;
	ss << *(wp);
	stringTemp = QString::fromStdString(ss.str());
	textOfWebPage->setText(stringTemp);

	//for(set<WebPage*>::iterator it = wp->outgoing_links().begin(); it!=wp->outgoing_links().end(); ++it) {
	//	outLinks->addItem( QString::fromStdString((*it)->filename()));
	//	cout << (*it)->filename() << endl;
	//}

	page->setLayout(pageLayout);
	page->show();
}*/


void MainWindow::quit() {
	QApplication::exit();
}

MainWindow::~MainWindow() {
	delete sengine;
	delete parse;
}
