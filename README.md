###############

Project description: Program capable of searching through a provided database of text files that act as our webpages. Can display results by number of links going to a webpage, number of links that are on a webpage, and the filename.

###############

Compile instructions:

user@computer~/path/to/files $ qmake
user@computer~/path/to/files $ make

###############

Usage instructions: user@computer~/path/to/files $ ./social_network [/path/to/index_file.txt]

e.g., user@computer~/path/to/files $ ./social_network data100/index.txt

###############

The search engine upon start up. Search and sort options flank the results window. Users can sort the displayed results by filename, number of incoming links, and number of outgoing links via the radio buttons without having to re-search.

![Alt text](/Images/se1.png?raw=true)

A simple search of a single word, with the results ordered by the number of incoming links.

![Alt text](/Images/se2.png?raw=true)

Searching for "good" or "cruel" throughout the pages, with the results ordered by the number of outgoing links.

![Alt text](/Images/se3.png?raw=true)