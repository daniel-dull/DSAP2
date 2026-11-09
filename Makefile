do: 
	cmake -B build
	cmake --build build
run:
	./build/dictionary_app
test:
	./build/hash_tests
	./build/trie_tests
