#include <iostream>
#include <deque>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iterator>

int FIFO (std::vector<int> pageNumbers, int frameSize, std::vector<double>& pageFaultRates);
int LRU (std::vector<int> pageNumbers, int frameSize, std::vector<double>& pageFaultRates);
int OPTIMAL (std::vector<int> pageNumbers, int frameSize, std::vector<double>& pageFaultRates);



int main(int argc, char* argv[]) {
    if (argc != 4) {
		std::cout << "Wrong input!" << std::endl;
        return -1;
    }
    
    int frame_size = atoi(argv[1]);
    int total_page_fault;
	
    std::vector<double> page_fault_rate;
    std::vector<int> page_numbers;

	// Read page numbers
	std::ifstream input(argv[2]);
	if(input.is_open()){
		int number;
		while(input >> number){
			page_numbers.push_back(number);
		}	
	} else {
		std::cout << "Wrong input file name!" << std::endl;
		return -1;
	}
    std::ofstream output(argv[3]);
	
	
	
    output << "===========================================================================\n"
		   << "    Page Replacement Algorithm Simulation (frame size = " << frame_size << ")\n"
		   << "===========================================================================\n"
		   << "\t\t\t\t\tPage fault rates\n"
		   << "Algorithm    Total page faults\t2000\t4000\t6000\t8000\t10000\n"
		   << "---------------------------------------------------------------------------\n";
    
    total_page_fault = FIFO(page_numbers, frame_size, page_fault_rate);
    output << "FIFO\t\t" << total_page_fault << "\t\t\t";
    for (int i = 0; i < page_fault_rate.size(); ++i) {
        output << std::fixed << std::setprecision(3) << page_fault_rate[i] << "\t";
    }
	
	total_page_fault = LRU(page_numbers, frame_size, page_fault_rate);
    output << "\nLRU\t\t" << total_page_fault << "\t\t\t";
    for (int i = 0; i < page_fault_rate.size(); ++i) {
        output <<  std::fixed << std::setprecision(3) << page_fault_rate[i] << "\t";
    }
	
	total_page_fault = OPTIMAL(page_numbers, frame_size, page_fault_rate);
    output << "\nOptimal\t" << total_page_fault << "\t\t\t";
    for (int i = 0; i < page_fault_rate.size(); ++i) {
        output <<  std::fixed << std::setprecision(3) << page_fault_rate[i] << "\t";
    }
	
    return 0;
}



int FIFO (std::vector<int> page_numbers, int frame_size, std::vector<double>& page_fault_rate) {
    std::deque<int> frame;
	
    int page_fault = 0;
    
    page_fault_rate.clear();
	
    int size = page_numbers.size();
	
    for (int i = 0; i < size; ++i) {
		// find() function returns end() if there is no element that we are looking for.
		// If there is the element, then it returns the element.
		
		// Therfore, if there is not the page number in the frame
        if (find(frame.begin(), frame.end(), page_numbers[i]) == frame.end()) {
				
            // If the frame is not full
            if (frame.size() < frame_size) {
				// then, push the page number into frame
                frame.push_front(page_numbers[i]);
            } else {
				// If the frame is full
				// then, pop the oldest page number 
                frame.pop_back();
                // and push the new page number into frame
                frame.push_front(page_numbers[i]);
            }
			// Since the new page number was added into frame
			// increment page fault num
            page_fault++;
        }
        
        if (i > 0 && i % 2000 == 0) {
            page_fault_rate.push_back((page_fault * 1.0) / i);
        }
    }
    
    page_fault_rate.push_back((page_fault * 1.0) / page_numbers.size());
    
    return page_fault;
}


int OPTIMAL (std::vector<int> page_numbers, int frame_size, std::vector<double>& page_fault_rate) {
    std::vector<int> frame;
	// 'temp' vector that stores the index number where the page number occurs next time
    std::vector<int> index(frame_size, -1);
    int page_fault = 0;
    page_fault_rate.clear();
	int size = page_numbers.size();

    for (int i = 0; i < size; ++i) {
		
		// If there is not the page number in the frame
        if (find(frame.begin(), frame.end(), page_numbers[i]) == frame.end()){
			
			// If the frame is not full
			if (frame.size() < frame_size) {
				// then, push the page number into frame
                frame.push_back(page_numbers[i]);
			} else {
				// If the frame is full
				// , then try to find which number should be removed
				// , which means finding the number that will come again the last among the numbers currently in the frame.
				bool remove = false;
				
				for (int j = 0; j < frame_size; ++j) {
					index[j] = -1;
					// Find the index number for each number in the frame, which tells when the number comes again.
					for (int k = i+1; k < page_numbers.size(); ++k) {
						if(frame[j] == page_numbers[k]) {
							// Store the index number into temporary vector
							index[j] = k;
							break;
						}
					
					}
				}				

				int max = index[0];
				int target = 0;
				
				// If there is a number that does not come again, then the system is good to remove that number.
				for (int j = 0; j < frame_size; ++j){
					if (index[j] == -1){
						target = j;
						remove = true;
						break;
					}
				}

				// Compare indices numbers and find the page that has the biggest index number
				if (!remove){
					for (int j = 1; j < frame_size; ++j) {
						if (index[j] > max){
							max = index[j];
							target = j;
						}
					}
				}

				// Finally, remove the target number.
				frame[target] = page_numbers[i];
			}
			++page_fault;
        }
        
        if (i > 0 && i % 2000 == 0) {
            page_fault_rate.push_back((page_fault * 1.0) / i);
        }
    }
    page_fault_rate.push_back((page_fault * 1.0) / page_numbers.size());
    
    return page_fault;
}


int LRU (std::vector<int> page_numbers, int frame_size, std::vector<double>& page_fault_rate) {
	std::deque<int> frame;
	std::deque<int>::iterator it;
	
	page_fault_rate.clear();

	int page_fault = 0;
	int size = page_numbers.size();
	
	for (int i = 0; i < size; ++i) {
		// iterator that stores the location of the number
		it = find(frame.begin(), frame.end(), page_numbers[i]);
		
		// If there is not the page number in the frame
		if (it == frame.end()) {
			// If the frame is not full
			if (frame.size() < frame_size) {
				// then, push the page number into frame
                frame.push_front(page_numbers[i]);
			}
			else{
				// If the frame is full
				// then, pop the oldest page number and push the new number.
				frame.pop_back();	
				frame.push_front(page_numbers[i]);
			}
			++page_fault;
		} else {
			// If the number is currently in the frame
			// , then update the number's order
			frame.erase(it);
			frame.push_front(page_numbers[i]);
		}
		
		if (i > 0 && i % 2000 == 0) {
            		page_fault_rate.push_back((page_fault * 1.0) / i);
        	}
	}
	
	page_fault_rate.push_back((page_fault * 1.0) / page_numbers.size());
    
    return page_fault;
}
