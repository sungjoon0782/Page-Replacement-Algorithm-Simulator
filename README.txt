*Name: Sungjoon Kim
*Student ID: 107951338
*Class: CSCI 3453 (Operating System Concept)
*Lab #: 3

*Description: 

main.cpp: It reads 1) frame size / 2) input file name / 3) output file name

	FIFO() function does FIFO page replacement algorithm
	LRU() function does LRU page replacement algorithm
	OPTIMAL() function does Oprimal page replacament algorithm
	
	each function has the page numbers, frame size and the empty vector to store page fault rates as parameters.
	

	
*Sample output:

===========================================================================
    Page Replacement Algorithm Simulation (frame size = 128)
===========================================================================
					Page fault rates
Algorithm    Total page faults	2000	4000	6000	8000	10000
---------------------------------------------------------------------------
FIFO		9653			0.966	0.966	0.966	0.966	0.965	
LRU		9651			0.967	0.966	0.966	0.966	0.965	
Optimal	7773			0.826	0.795	0.785	0.782	0.777	



===========================================================================
    Page Replacement Algorithm Simulation (frame size = 256)
===========================================================================
					Page fault rates
Algorithm    Total page faults	2000	4000	6000	8000	10000
---------------------------------------------------------------------------
FIFO		9334			0.935	0.935	0.934	0.935	0.933	
LRU		9331			0.936	0.935	0.933	0.934	0.933	
Optimal	6934			0.788	0.732	0.710	0.701	0.693	



===========================================================================
    Page Replacement Algorithm Simulation (frame size = 512)
===========================================================================
					Page fault rates
Algorithm    Total page faults	2000	4000	6000	8000	10000
---------------------------------------------------------------------------
FIFO		8752			0.894	0.885	0.877	0.878	0.875	
LRU		8752			0.892	0.883	0.877	0.877	0.875	
Optimal	5909			0.788	0.668	0.621	0.606	0.591	



===========================================================================
    Page Replacement Algorithm Simulation (frame size = 1024)
===========================================================================
					Page fault rates
Algorithm    Total page faults	2000	4000	6000	8000	10000
---------------------------------------------------------------------------
FIFO		7604			0.821	0.788	0.768	0.766	0.760	
LRU		7585			0.819	0.787	0.769	0.765	0.758	
Optimal	4735			0.788	0.636	0.530	0.507	0.473	




Discussion:
	Page fault rates and the number of total page faults for all algorithms decreases as frame size increases.



