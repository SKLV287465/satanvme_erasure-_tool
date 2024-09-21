# Variables
CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++20
LDFLAGS =
SRC = main.cpp nist_purge/nvme/nvme_sanitize.cpp nist_purge/ata/ata_sanitize.cpp fetch_drives.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = my_program

# Rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
