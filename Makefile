CXXFLAGS += -Ofast -Wall -Wextra -Werror -std=c++11 -lncurses

BUILD_DIR = build

all: $(BUILD_DIR)/gol

run: all
	$(BUILD_DIR)/gol

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/src:
	mkdir -p $(BUILD_DIR)/src

$(BUILD_DIR)/src/%.o: src/%.cpp src/*.h | $(BUILD_DIR)/src
	$(CXX) ${CPPFLAGS} $(CXXFLAGS) -c $< -o $@

standards:
	@find src/ -regex '.*.\(h\|cpp\)' | xargs cpplint --root=src --filter=+build/include_alpha,-readability/streams 2>&1 | grep -v 'Done processing'

$(BUILD_DIR)/gol : $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(wildcard src/*.cpp))
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
