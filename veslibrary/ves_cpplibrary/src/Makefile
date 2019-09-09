all:
	mkdir build
	cd build; cmake ..; make; make install

.PHONY : test
test:
	mkdir build
	cd build; cmake .. -DENABLE_COVERAGE=ON; make; make install
	mkdir test/build
	cd test/build; cmake .. -DENABLE_COVERAGE=ON; make; ./xtest
	lcov -c -d build/lib/encode/CMakeFiles/xencode.dir -d build/lib/transport/CMakeFiles/xtransport.dir -o coverage.info
	lcov -r coverage.info '/usr/*' '*/transport/gen-cpp/*' -o xvesagent.info
	genhtml xvesagent.info -o coverage
	rm -rf *.info

clean:
	rm *.info -rf
	rm build -rf
	rm coverage -rf
	rm test/build -rf
