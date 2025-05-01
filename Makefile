CFLAGS=-O3 -std=c11 -fPIC -g
CXXFLAGS=-O3 -std=c++17 -fPIC -g
LD=g++

all: mergesort_seq mergesort_par

# Sequential version
mergesort_seq: mergesort_seq_nocopy.o
	$(LD) $(LDFLAGS) mergesort_seq_nocopy.o $(ARCHIVES) -o mergesort_seq

mergesort_seq_nocopy.o: mergesort_seq_nocopy.cpp
	$(CXX) $(CXXFLAGS) -c mergesort_seq_nocopy.cpp

# Parallel version
mergesort_par: mergesort_parallel.o
	$(LD) $(LDFLAGS) mergesort_parallel.o $(ARCHIVES) -o mergesort_par

mergesort_parallel.o: mergesort_parallel.cpp
	$(CXX) $(CXXFLAGS) -c mergesort_parallel.cpp

# Benchmark target
bench: mergesort_seq mergesort_par
	./queue.sh

# Clean targets
clean:
	-rm -f *.o mergesort_seq mergesort_par

distclean:
	-rm -f *.sh.*

.PHONY: all clean distclean bench
