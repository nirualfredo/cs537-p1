#
# Sample makefile updated to include the commands to run the Clang Static Analyzer
#
#    scan-build will "make" your program and run CSA at the same time.
#
#    scan-view will do a scan-build (if necessary) and then open a web browser
#      window to review the results.
#
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps
SCAN_BUILD_DIR = scan-build-out

all: main.o parser.o printer.o reader.o
	$(CC) -o $(EXE) main.o parser.o printer.o reader.o
main.o: main.c parser.h printer.h reader.h
	$(CC) $(WARNING_FLAGS) -c main.c
parser.o: parser.c parser.h
	$(CC) $(WARNING_FLAGS) -c parser.c
printer.o: printer.c printer.h
	$(CC) $(WARNING_FLAGS) -c printer.c
reader.o: reader.c reader.h
	$(CC) $(WARNING_FLAGS) -c reader.c
clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
