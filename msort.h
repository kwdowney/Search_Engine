#include <vector>
#include <iostream>
template <class T, class Comparator>

void mergeSort(std::vector<T> &myvector, Comparator comp) {
	
	if(myvector.size() == 1) return;


	std::vector<T> left;
	std::vector<T> right;

	for(int i = 0; i<myvector.size()/2; i++) {
		left.push_back(myvector[i]);
	}

	for(int j = myvector.size()/2; j<myvector.size(); j++) {
		right.push_back(myvector[j]);
	}

	mergeSort(left, comp);
	mergeSort(right, comp);
	msort(myvector, left, right, comp);
}

template <class T, class Comparator>

void msort(std::vector<T> &result, std::vector<T> leftEnd, std::vector<T> rightEnd, Comparator comp  ) {
	std::vector<T> final;
	int i = 0;
	int j = 0;

	while(leftEnd.size()>i && rightEnd.size()>j) {

		if(comp(leftEnd[i], rightEnd[j])) {
			final.push_back(leftEnd[i]);
			i++;
		}
		else {
			final.push_back(rightEnd[j]);
			j++;
		}
	}

	//if one of the std::vectors has data in it, but the other does not, simply push all the data to the final std::vector
	if(leftEnd.size()==i && rightEnd.size()>j) {
		while(rightEnd.size()>j) {
			final.push_back(rightEnd[j]);
			j++;
		}
	}

	else if(leftEnd.size()>i && rightEnd.size()==j) {
		while(leftEnd.size()>i) {
			final.push_back(leftEnd[i]);
			i++;
		}
	}

	result = final;
}