#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QListWidget>
#include <QTextEdit>
#include <QGroupBox>

#include <string>
#include <vector>
#include "webpage.h"
#include "searcheng.h"
#include <set>

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(std::string);
	~MainWindow();

private slots:
	void quit();
	void search();
	void displayResults(std::vector<WebPage*>);
	void inSort();
	void outSort();
	void nameSort();
	//void showWebPage(QListWidgetItem*);

private:

	//overall box
	QHBoxLayout* overallLayout;

	//input box
	QVBoxLayout* inputLayout;
	QLabel* searchPrompt;
	QLineEdit* searchTerms;
	QRadioButton* searchAnd;
	QRadioButton* searchOr;
	QRadioButton* searchSingle;
	QGroupBox* searchBy;

	//results
	QVBoxLayout* outputLayout;
	QListWidget* results;
	QGroupBox* sortBy;
	//sort buttons
	QVBoxLayout* toggleResults;
	QLabel* resultsTitle;
	QRadioButton* filename;
	QRadioButton* outgoing;
	QRadioButton* incoming;

	//"search" and "quit" buttons 
	QPushButton* execute;
	QPushButton* quitButton;

	//show the webpage
	QWidget* page;
	QLineEdit* textOfWebPage;
	QListWidget* inLinks;
	QListWidget* outLinks;
	QHBoxLayout* pageLayout;

	std::vector<WebPage*> foundWebPages;
	SearchEng* sengine;
	Parsemd* parse;
};