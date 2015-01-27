Simple MSD Radix OpenMP realisation.

Binary help usage: ./sort -h

Switches to insert-sort if number of elements in bucket is too small (more effective). Operates only with indexes of original array, not changing it contents positions.

Another possible solve ways:
	Implementing openMP parallelised 3-way QuickSort (each recurse is an openMP task)
	Implementing HyperQuicksort
